/*************************************************************************
Copyright (c) 2017 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE
    rwcp_server.c

DESCRIPTION
   This file defines routines for using RWCP server
*/

#include "rwcp_server.h"
#include <panic.h>
#include <stdio.h>
#include <string.h>
#include "rwcp_server.h"

/* Service data type */
typedef struct
{
    rwcp_protocol_state protocol_state;          /* RWCP Server states */
    bool gap_mute;          /* temporarily mute GAP replies during congestion */
    uint8 last_sequence_number;          /* last acknowledged sequence number */
    uint8 pending_sequence_number;          /* pending sequence number which has to be acknowledged*/
    uint8 rwcp_upgrade_packet_len;          /* cumulative upgrade packet length while acknowledging*/
    uint8 rwcp_upgrade_buffer_size;          /* upgrade buffer size calculated for maximum throughput*/
    uint8 rwcp_upgrade_header_size;          /*cumulative header size of GAIA and Upgrade headers */
    bool accept_segments;          /* flow control flag */
    Task client_task;          /*Client task*/
} SERVER_DATA_T;

/*
 * RWCP protocol definitions
 */
typedef enum
{
    RWCP_CLIENT_CMD_DATA         = 0x00,
    RWCP_CLIENT_CMD_SYN          = 0x40,
    RWCP_CLIENT_CMD_RST          = 0x80,
    RWCP_CLIENT_CMD_RESERVED     = 0xc0
} rwcp_client_commands_t;

typedef enum
{
    RWCP_SERVER_CMD_DATA_ACK     = 0x00,
    RWCP_SERVER_CMD_SYN_ACK      = 0x40,
    RWCP_SERVER_CMD_RST          = 0x80,
    RWCP_SERVER_CMD_GAP          = 0xc0
} rwcp_server_commands_t;

#define RWCP_COMMAND_MASK                               0xc0
#define RWCP_SEQUENCE_MASK                              0x3f
#define RWCP_HEADER_OFFSET                              0
#define RWCP_HEADER_SIZE                                1
#define RWCP_PAYLOAD_OFFSET                             1
#define RWCP_SEQUENCE_NUMBER_MAX                        64
#define RWCP_RECEIVE_WINDOW_MAX                         32
#define RWCP_SEQUENCE_NUMBER_INVALID                0xFF

#if defined(DEBUG_RWCP_SERVER)
#define RWCP_SERVER_DEBUG(x)     printf x
#else
#define RWCP_SERVER_DEBUG(x)
#endif  /* DEBUG_RWCP_SERVER */

/* Service data */
static SERVER_DATA_T g_server_data;

/*----------------------------------------------------------------------------*
 *  NAME
 *      rwcpSendNotification
 *
 *  DESCRIPTION
 *      This function sends a RWCP Notification
 *
 *      NOTE: This function ignores notification errors since the protocol
 *      is designed to work with unreliable messages.
 *
 *  RETURNS
 *      None.
 *
 *---------------------------------------------------------------------------*/
static void rwcpSendNotification( uint8 sequence,
                                    rwcp_server_commands_t command)
{
    uint8* rwcp_header = PanicUnlessMalloc(RWCP_HEADER_SIZE);

    MESSAGE_MAKE(data_ack, RWCP_DATA_T);

    /* create the RWCP header */
    *rwcp_header = 0;
    *rwcp_header |= sequence & RWCP_SEQUENCE_MASK;
    *rwcp_header |= command & RWCP_COMMAND_MASK;

    data_ack->payload = rwcp_header;
    data_ack->size_payload = RWCP_HEADER_SIZE;

    MessageSend(g_server_data.client_task, RWCP_UPGRADE_DATA_ACK, data_ack);
}

/*----------------------------------------------------------------------------*
 *  NAME
 *      rwcpDataAck
 *
 *  DESCRIPTION
 *      Send a DATA ACK segment
 *
 *  RETURNS
 *      None.
 *
 *---------------------------------------------------------------------------*/
static void rwcpDataAck( uint8 sequence )
{
    RWCP_SERVER_DEBUG(( "A%d\n", sequence ));
    rwcpSendNotification( sequence, RWCP_SERVER_CMD_DATA_ACK);
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      rwcpRstAck
 *
 *  DESCRIPTION
 *      Send a RST ACK segment
 *
 *  RETURNS
 *      None.
 *
 *---------------------------------------------------------------------------*/
static void rwcpRstAck( uint8 sequence )
{
    RWCP_SERVER_DEBUG(("RA%d\n", sequence ));
    rwcpSendNotification( sequence, RWCP_SERVER_CMD_RST);
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      rwcpRst
 *
 *  DESCRIPTION
 *      Send a RST segment
 *
 *  RETURNS
 *      None.
 *
 *---------------------------------------------------------------------------*/
static void rwcpRst( uint8 sequence )
{
    RWCP_SERVER_DEBUG(( "R%d\n", sequence ));
    rwcpSendNotification( sequence, RWCP_SERVER_CMD_RST);
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      rwcpSynAck
 *
 *  DESCRIPTION
 *      Send a SYN ACK segment
 *
 *  RETURNS
 *      None.
 *
 *---------------------------------------------------------------------------*/
static void rwcpSynAck( uint8 sequence )
{
    RWCP_SERVER_DEBUG(( "SA%d\n", sequence ));
    rwcpSendNotification( sequence, RWCP_SERVER_CMD_SYN_ACK);
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      rwcpGap
 *
 *  DESCRIPTION
 *      Send a GAP segment
 *
 *  RETURNS
 *      None.
 *
 *---------------------------------------------------------------------------*/
static void rwcpGap( uint8 sequence )
{
    RWCP_SERVER_DEBUG(( "G%d\n", sequence ));
    rwcpSendNotification( sequence, RWCP_SERVER_CMD_GAP);
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      isNextSequence
 *
 *  DESCRIPTION
 *      Check if the number is the next expected number
 *
 *  RETURNS
 *      The next sequence number.
 *
 *---------------------------------------------------------------------------*/
static uint8 nextExpectedSequenceNumber(uint8 current_sequence_number)
{
    UNUSED (current_sequence_number);
    return (g_server_data.last_sequence_number + 1) % RWCP_SEQUENCE_NUMBER_MAX;
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      isNextSequence
 *
 *  DESCRIPTION
 *      Check if the number is the next expected number
 *
 *  RETURNS
 *      TRUE if the sequence number matches the the next expected one
 *
 *---------------------------------------------------------------------------*/
static bool isNextSequence(uint8 sequence)
{
    return ( sequence == nextExpectedSequenceNumber(g_server_data.last_sequence_number));
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      isOutOfSequence
 *
 *  DESCRIPTION
 *      Check if the number is an out-of-sequence number, but not a duplicate
 *
 *  RETURNS
 *      TRUE if the sequence number is out of sequence
 *
 *---------------------------------------------------------------------------*/
static bool isOutOfSequence(uint8 sequence)
{
    uint16 norm;

    /* normalise the number to deal with wrap around */
    norm = ( sequence -
            g_server_data.last_sequence_number +
            RWCP_SEQUENCE_NUMBER_MAX) %
            RWCP_SEQUENCE_NUMBER_MAX;

    return ( norm > 0 && norm < RWCP_RECEIVE_WINDOW_MAX );
}


/*----------------------------------------------------------------------------*
 *  NAME
 *      handleDataSegment
 *
 *  DESCRIPTION
 *      Handles an RWCP DATA segment.
 *
 *  RETURNS
 *      None.
 *
 *---------------------------------------------------------------------------*/
static void handleDataSegment(uint8 sequence_number, uint8 *data, uint16 size, bool request_full_partition_size)
{
    /*
     * payload received, check the sequence number
     * Send an ACK if, the sequence number is as expected.
     * Send a GAP if, the sequence number is unexpected.
     * ACK duplicates.
     */
    uint8 header_size = g_server_data.rwcp_upgrade_header_size + RWCP_HEADER_SIZE;

    if(size > (header_size + RWCP_UPGRADE_MAX_DATA_SIZE) )
    {
        RWCP_SERVER_DEBUG(("Invalid Size!\n"));
        return;
    }

    if ( g_server_data.accept_segments )
    {
        if ( isNextSequence(sequence_number) )
        {
            MESSAGE_MAKE(rwcp_data, RWCP_DATA_T);

            g_server_data.gap_mute = FALSE;

            if(request_full_partition_size)
            {
                g_server_data.rwcp_upgrade_packet_len += (size - header_size);
                if(g_server_data.rwcp_upgrade_packet_len < g_server_data.rwcp_upgrade_buffer_size)
                {
                    rwcpDataAck( sequence_number);
                }
                else
                {
                    RwcpServerFlowControl(FALSE);
                    g_server_data.pending_sequence_number = sequence_number;
                    g_server_data.rwcp_upgrade_packet_len = 0;
                }
            }
            else
            {
                 g_server_data.rwcp_upgrade_packet_len = 0;
                 rwcpDataAck( sequence_number);
            }
            g_server_data.last_sequence_number = sequence_number;

            rwcp_data->size_payload = size - RWCP_HEADER_SIZE;
            rwcp_data->payload = (uint8 *)PanicUnlessMalloc(rwcp_data->size_payload);
            memcpy(rwcp_data->payload, &data[RWCP_PAYLOAD_OFFSET], rwcp_data->size_payload);
            MessageSend(g_server_data.client_task, RWCP_UPGRADE_DATA, rwcp_data);
        }
        else if ( isOutOfSequence(sequence_number) )
        {
            if ( !g_server_data.gap_mute )
            {
                g_server_data.gap_mute = TRUE;
                rwcpGap( g_server_data.last_sequence_number);
                RWCP_SERVER_DEBUG(( "rx:%d ex:%d\n",
                            sequence_number,
                            nextExpectedSequenceNumber(g_server_data.last_sequence_number) ));
            }
            else
            {
                RWCP_SERVER_DEBUG(( "g:%d\n", sequence_number ));
            }
        }
        else    /* must be a duplicate, ACK in case the previous ACK was lost */
        {
            RWCP_SERVER_DEBUG(( "dup\n" ));
            rwcpDataAck( sequence_number);
        }
    }
    else
    {
            RWCP_SERVER_DEBUG(( "segment discarded\n" ));   /* silently discard when the server can't accept any more segments */
    }
}

void RwcpHandleUpgradeTransportDataInd (void)
{
    if(g_server_data.pending_sequence_number != RWCP_SEQUENCE_NUMBER_INVALID)
    {
        RwcpServerFlowControl(TRUE);
        rwcpDataAck(g_server_data.pending_sequence_number);
        g_server_data.pending_sequence_number = RWCP_SEQUENCE_NUMBER_INVALID;
    }
}

rwcp_protocol_state RwcpGetProtocolState(void)
{
    return g_server_data.protocol_state;
}

void RwcpServerHandleMessage(uint8 *data, uint16 size, bool request_full_partition_size)
{
    uint8 rwcp_header;
    uint8 sequence_number;
    uint8 command;

    if(data == NULL)
    {
        RWCP_SERVER_DEBUG(( "RwcpServerHandleMessage data NULL\n" ));
        return;
    }

    rwcp_header = data[RWCP_HEADER_OFFSET];

    /* decode the header */
    sequence_number = rwcp_header & RWCP_SEQUENCE_MASK;
    command = rwcp_header & RWCP_COMMAND_MASK;

    RWCP_SERVER_DEBUG(( "RwcpServerHandleMessage\n" ));
    /* handle messages according to state */
    switch ( g_server_data.protocol_state )
    {
        /*
         * Waiting for a SYN segment, send RST on all others
         * This segment contains the starting sequence number (which may be non zero).
         */
        case RWCP_LISTEN:

            switch (command)
            {
                /* SYN received, start the protocol */
                case RWCP_CLIENT_CMD_SYN:
                    RWCP_SERVER_DEBUG(( "SYN received, LISTEN => SYN_RCVD\n" ));
                    rwcpSynAck(sequence_number);
                    g_server_data.last_sequence_number = sequence_number;
                    g_server_data.protocol_state = RWCP_SYN_RCVD;
                    break;

                /* handle the ReSeT command */
                case RWCP_CLIENT_CMD_RST:
                    rwcpRstAck(sequence_number);
                    break;

                /* unexpected command */
                case RWCP_CLIENT_CMD_DATA:
                case RWCP_CLIENT_CMD_RESERVED:
                default:
                    RWCP_SERVER_DEBUG(( "Unexpected, hdr = %x, LISTEN => LISTEN\n", rwcp_header ));
                    rwcpRst(sequence_number);
                    break;
            }
            break;

        /*
         * SYN was received, waiting for the first DATA segment
         */
        case RWCP_SYN_RCVD:

            switch(command)
            {
                /* duplicate SYN received, keep going */
                case RWCP_CLIENT_CMD_SYN:
                    RWCP_SERVER_DEBUG(( "SYN received, SYN_RCVD => SYN_RCVD\n" ));
                    rwcpSynAck(sequence_number);
                    g_server_data.last_sequence_number = sequence_number;
                    break;

                /* handle the ReSeT command */
                case RWCP_CLIENT_CMD_RST:
                    RWCP_SERVER_DEBUG(( "RST received, SYN_RCVD => LISTEN\n" ));
                    rwcpRstAck( sequence_number);
                    g_server_data.protocol_state = RWCP_LISTEN;
                    break;

                /* first DATA segment arrived, handle it, and change state */
                case RWCP_CLIENT_CMD_DATA:
                    RWCP_SERVER_DEBUG(( "DATA received, SYN_RCVD => ESTABLISHED\n" ));
                    g_server_data.gap_mute = FALSE;
                    handleDataSegment( sequence_number, data, size, request_full_partition_size);
                    g_server_data.protocol_state = RWCP_ESTABLISHED;
                    break;

                /* unexpected command */
                case RWCP_CLIENT_CMD_RESERVED:
                default:
                    RWCP_SERVER_DEBUG(( "Unexpected, hdr = %x, SYN_RCVD => LISTEN\n", rwcp_header ));
                    rwcpRst( sequence_number);
                    g_server_data.protocol_state = RWCP_LISTEN;
                    break;
            }
            break;

        /*
         * Server expects DATA segments
         */
        case RWCP_ESTABLISHED:
            switch(command)
            {
                /* handle the ReSeT command */
                case RWCP_CLIENT_CMD_RST:
                    RWCP_SERVER_DEBUG(( "RST received, ESTABLISHED => LISTEN\n" ));
                    rwcpRstAck( sequence_number);
                    g_server_data.protocol_state = RWCP_LISTEN;
                    break;

                /* DATA segment arrived, handle it*/
                case RWCP_CLIENT_CMD_DATA:
                    handleDataSegment( sequence_number, data, size, request_full_partition_size);
                    break;

                /* unexpected command */
                case RWCP_CLIENT_CMD_SYN:
                case RWCP_CLIENT_CMD_RESERVED:
                default:
                    RWCP_SERVER_DEBUG(( "Unexpected, hdr = %x, ESTABLISHED => LISTEN\n", rwcp_header ));
                    rwcpRst( sequence_number);
                    g_server_data.protocol_state = RWCP_LISTEN;
                    break;
            }
            break;

        default:
            RWCP_SERVER_DEBUG(( "Unexpected State\n" ));
            break;

    }
}

void RwcpServerFlowControl(bool accept)
{
    g_server_data.accept_segments = accept;
}

void RwcpSetClientTask(Task client_task)
{
    g_server_data.client_task = client_task;
}

void RwcpServerInit(uint8 buffer_size, uint8 header_size)
{
    RWCP_SERVER_DEBUG(( "RwcpServerInit\n" ));
    /* init server state variables */
    g_server_data.protocol_state = RWCP_LISTEN;
    g_server_data.accept_segments = TRUE;
    g_server_data.client_task = NULL;
    g_server_data.last_sequence_number = 0;
    g_server_data.rwcp_upgrade_packet_len = 0;
    g_server_data.rwcp_upgrade_buffer_size = buffer_size;
    g_server_data.rwcp_upgrade_header_size = header_size;
    g_server_data.pending_sequence_number = RWCP_SEQUENCE_NUMBER_INVALID;
}
