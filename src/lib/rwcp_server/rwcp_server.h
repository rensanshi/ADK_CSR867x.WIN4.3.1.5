/****************************************************************************
Copyright (c) 2017 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

*/
 
/*!
    @file rwcp_server.h
    @brief Header file for the RWCP server library

    This library implements the RWCP server protocol.
*/

#ifndef __RWCP_server_H__
#define __RWCP_server_H__

#include <library.h>
#include <csrtypes.h>
#include <stdlib.h>
#include <message.h>

#define RWCP_UPGRADE_MAX_DATA_SIZE (0x0A)

/*! @brief Enumeration of RWCP server states
 */
typedef enum
{
    RWCP_LISTEN,                    /* RWCP state LISTEN    */
    RWCP_SYN_RCVD,                  /* RWCP state SYN_RCVD  */
    RWCP_ESTABLISHED                /* RWCP state ESTABLISHED  */
} rwcp_protocol_state;   

/*! @brief RWCP messages
 */
typedef enum
{
    RWCP_UPGRADE_DATA = RWCP_MSG_BASE,
    RWCP_UPGRADE_DATA_ACK,

    RWCP_MESSAGE_TOP
} rwcp_transport_message;

/*! @brief Message containing RWCP data
 */ 
typedef struct
{
    uint8 *payload;
    uint16 size_payload;
}RWCP_DATA_T;

/*! 
    @brief Handles the UPGRADE_TRANSPORT_DATA_IND received from upgrade lib. 

    @param none
*/
void RwcpHandleUpgradeTransportDataInd(void);
/*! 
    @brief Current RWCP server state is retrieved
    
    @param none
*/
rwcp_protocol_state RwcpGetProtocolState(void);

/*! 
    @brief Stop/start the RWCP protocol message handler. 
    Used to pause the RWCP. When paused, it will ignore all messages.
    
    @param accept TRUE to accept and process RWCP message, FALSE to ignore them
*/
void RwcpServerFlowControl(bool accept);

  /*! 
    @brief Handle a RWCP server message
    
    @param data The payload of the RWCP message
    @param size The size of the payload
    @param is_partition_data_state TRUE if upgrade library is in UPGRADE_PARTITION_DATA_STATE_DATA
    @param rwcp_upgrade_buffer_size upgrade buffer size calculated for upgrade libray when RWCP is enabled
*/
void RwcpServerHandleMessage(uint8 *data, uint16 size, bool request_full_partition_size);

 /*! 
    @brief Stores the client task in RWCP context
    
    @param transportTask The client task to be saved
*/
void RwcpSetClientTask(Task transportTask);

 /*! 
    @brief Initialise the RWCP server
    
    @param buffer_size buffer size calculated for RWCP maximum throughput
    @param header_size cumulative size of the GAIA and Upgrade headers
*/
void RwcpServerInit(uint8 buffer_size, uint8 header_size);

#endif /* __RWCP_SERVER_H__ */
