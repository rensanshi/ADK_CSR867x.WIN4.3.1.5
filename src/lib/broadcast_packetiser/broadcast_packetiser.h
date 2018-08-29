/****************************************************************************
Copyright (c) 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    broadcast_packetiser.h

DESCRIPTION
    Interface to the Broadcast Packetiser library.

*/

#ifndef BROADCAST_PACKETISER_H_
#define BROADCAST_PACKETISER_H_

#include <source.h>
#include <sink.h>
#include <erasure_coding.h>
#include <library.h>
#include <rtime.h>
#include <message.h>
#include <packetiser_helper.h>

/****************************************************************************
 * Typedefs and Enumerations
 ****************************************************************************/

/*! Statistics generated by the packetiser receiver */
typedef struct __broadcast_packetiser_stats_receiver
{
    /*! The number of AESCCM authentication errors */
    uint32 authentication_errors;
    /*! The number of broadcast packets successfully received */
    uint32 broadcast_packets_received;
    /*! The number of broadcast packets received whose TTP is a duplicate of the
      previous packet. */
    uint32 broadcast_packet_duplicate_ttp;
    /*! The number of invalid broadcast packets detected (e.g. framing errors) */
    uint32 broadcast_packet_invalid;
    /*! The number of broadcast packets received with an unsupported sample rate */
    uint32 broadcast_packet_unsupported_sample_rate;
    /*! The number of audio frames received */
    uint32 audio_frames_received;
    /*! The number of audio frames discarded because late */
    uint32 audio_frames_late;
    /*! The number of audio frames discarded because no space in sink or sink
      was invalid. */
    uint32 audio_frames_no_space;
} broadcast_packetiser_stats_receiver_t;

/*! Statistics generated by the packetiser broadcaster */
typedef struct __broadcast_packetiser_stats_broadcaster
{
    /*! The number of audio frames transmitted */
    uint32 audio_frames_transmitted;
    /*! The number of audio frames discarded because late */
    uint32 audio_frames_late;
    /*! The number of broadcast packets transmitted */
    uint32 broadcast_packets_transmitted;
} broadcast_packetiser_stats_broadcaster_t;

/*! The broadcast packetiser can operate in the role of broadcaster or
  receiver. */
typedef enum __broadcast_packetiser_role
{
    broadcast_packetiser_role_broadcaster,
    broadcast_packetiser_role_receiver
} broadcast_packetiser_role_t;

/*! AESCCM parameters */
typedef struct __aesccm_config
{
    /*! The 128-bit AESCCM key */
    uint8 key[16];

    /*! The fixed IV is fixed per manufacturer */
    uint16 fixed_iv[3];

    /*! The dynamic IV is regularly changed */
    uint16 dynamic_iv;
} aesccm_config_t;

/*! Structure defining the broadcast packetiser configuration.
  Unless noted otherwise, all members must be set when initialising the library.
  The library provides an API to set members that may be updated at run-time.
  To change other members, the library instance must be destroyed and a new
  instance created with the desired new parameters.
*/
typedef struct __broadcast_packetiser_config
{
    /*! Broadcaster or receiver */
    broadcast_packetiser_role_t role;

    /*! Application task to which messages from this instance will be sent */
    Task client_task;

    union
    {
        /*! Broadcaster role (optional): The source of audio frames with metadata. */
        Source source;
        /*! Receiver role (optional): The sink of audio frames with metadata. */
        Sink sink;
    } port;

    /*! AESCCM configuration */
    aesccm_config_t aesccm;
    
    /* Disable AESCCM */
    bool aesccm_disabled;

    /*! The interval to send statistics messages to the client task */
    rtime_t stats_interval;

    /*! The fixed length of each audio frame.
      Broadcaster role: used to check the frames read from the source are the
      correct length.
      Receiver role: used to read fixed length frames out of the received
      broadcast packet.
     */
    uint16 frame_length;

    /*! The fixed number of samples represented by each audio frame.
     Broadcaster role: not used.
     Receiver role: used to calculate the TTP of each frame in the received
     broadcast packet.
    */
    uint16 frame_samples;

    /*! Broadcaster role: The sample rate to transmit.
      Receiver role: The sample rate to expect to receive.
      A #BROADCAST_PACKETISER_SAMPLE_RATE_CHANGE_IND will be sent to the client
      task when a packet is received not matching the configured value. */
    rtime_sample_rate_t sample_rate;

    /*! Broadcaster role: The audio serial copy management system type to transmit.
      Receiver role: Set to any valid value.
      A #BROADCAST_PACKETISER_SCMST_CHANGE_IND will be sent to the client task
      when the value changes. */
    packetiser_helper_scmst_t scmst;

    /*! Broadcaster role: the system volume to transmit.
      Receiver role: does not need to be configured - it is used internally to
      track changes in volume.
      A #BROADCAST_PACKETISER_VOLUME_CHANGE_IND will be sent to the client task
      when the volume changes. */
    uint32 volume;

    /*! Extends the TTP to 40 bits
        Broadcaster role: used to initialise the TTP extension value.
        Receiver role: not used. */
    uint8 ttp_extension;

    /*! The handle to an instance of the erasure coding library */
    union
    {
        ec_handle_rx_t rx;
        ec_handle_tx_t tx;
    } ec_handle;

} broadcast_packetiser_config_t;

/*! Opaque reference to an instance of the Broadcast Packetiser library. */
struct __broadcast_packetiser;
typedef struct __broadcast_packetiser broadcast_packetiser_t;

/****************************************************************************
 * Message Interface
 ****************************************************************************/

/*! Messages sent by the broadcast_packetiser library to the client_task
  registered with #BroadcastPacketiserInit().
*/
typedef enum
{
    BROADCAST_PACKETISER_INIT_CFM = BROADCAST_PACKETISER_MESSAGE_BASE,
    BROADCAST_PACKETISER_STATS_BROADCASTER_IND,
    BROADCAST_PACKETISER_STATS_RECEIVER_IND,
    BROADCAST_PACKETISER_VOLUME_CHANGE_IND,
    BROADCAST_PACKETISER_SCMST_CHANGE_IND,
    BROADCAST_PACKETISER_SAMPLE_RATE_CHANGE_IND,
    BROADCAST_PACKETISER_START_OF_STREAM_IND,
    BROADCAST_PACKETISER_MESSAGE_TOP
} broadcast_packetiser_message_id_t;

/*! Confirmation sent to the client task on completion of initialisation. */
typedef struct
{
    /*! Pointer to the instance of the broadcast packetiser library */
    broadcast_packetiser_t *broadcast_packetiser;
    /*! The library task */
    Task lib_task;
    /*! Initialisation success or failure */
    bool initialisation_success;
    /*! The configuration */
    broadcast_packetiser_config_t config;
} BROADCAST_PACKETISER_INIT_CFM_T;

/*! Indication sent periodically to the client task with statistics on the
  broadcast role packetisation.
*/
typedef struct
{
    /*! Pointer to the instance of the broadcast packetiser library */
    broadcast_packetiser_t *broadcast_packetiser;
    /*! The statistics */
    broadcast_packetiser_stats_broadcaster_t stats;
} BROADCAST_PACKETISER_STATS_BROADCASTER_IND_T;

/*! Indication sent periodically to the client task with statistics on the
  receiver role packetisation.
*/
typedef struct
{
    /*! Pointer to the instance of the broadcast packetiser library */
    broadcast_packetiser_t *broadcast_packetiser;
    /*! The statistics */
    broadcast_packetiser_stats_receiver_t stats;
} BROADCAST_PACKETISER_STATS_RECEIVER_IND_T;

/*! Indication sent to the client task when a volume change is detected by the
  packetiser in the receiver role. Not applicable in the broadcaster role.
  The client does not need to respond to this indication.
*/
typedef struct
{
    /*! Pointer to the instance of the broadcast packetiser library */
    broadcast_packetiser_t *broadcast_packetiser;
    /*! The new volume */
    uint32 volume;
} BROADCAST_PACKETISER_VOLUME_CHANGE_IND_T;

/*! Indication sent to the client task when a scmst change is detected by the
  packetiser in the receiver role. Not applicable in the broadcaster role.
  The client does not need to respond to this indication.
*/
typedef struct
{
    /*! Pointer to the instance of the broadcast packetiser library */
    broadcast_packetiser_t *broadcast_packetiser;
    /*! The new scmst type */
    packetiser_helper_scmst_t scmst;
} BROADCAST_PACKETISER_SCMST_CHANGE_IND_T;

/*! Indication sent to the client task when a sample rate change is detected by
  the packetiser in the receiver role. Not applicable in the broadcaster role.
  The client task must respond by calling
  #BroadcastPacketiserSampleRateChangeResponse.
*/
typedef struct
{
    /*! Pointer to the instance of the broadcast packetiser library */
    broadcast_packetiser_t *broadcast_packetiser;
    /*! The new sample rate */
    rtime_sample_rate_t sample_rate;
} BROADCAST_PACKETISER_SAMPLE_RATE_CHANGE_IND_T;

/*! Indication sent to the client task in the broadcaster role, when the source
  signals a new start of stream. Not applicable in the receiver role.
  The client task must respond by changing the library configuration to match
  the new stream and then by calling
  #BroadcastPacketiserStartOfStreamResponse.
*/
typedef struct
{
    /*! Pointer to the instance of the broadcast packetiser library */
    broadcast_packetiser_t *broadcast_packetiser;
} BROADCAST_PACKETISER_START_OF_STREAM_IND_T;

/****************************************************************************
 * Functions
 ****************************************************************************/

/*!
  @brief Create an instance and initialise the broadcast packetiser.
  @param config The library configuration.
*/
void BroadcastPacketiserInit(broadcast_packetiser_config_t *config);

/*!
  @brief Destroy the broadcast packetiser instance.
  @param bp The #broadcast_packetiser_t instance to destroy.
*/
void BroadcastPacketiserDestroy(broadcast_packetiser_t *bp);

/*!
  @brief Response from the client task to the
         #BROADCAST_PACKETISER_SAMPLE_RATE_CHANGE_IND.
  @param bp The #broadcast_packetiser_t instance.
  @param response TRUE if the client successfully changed the sample rate.
                  FALSE if the client could not change the sample rate.
  Only applicable in the receiver role. If the response if FALSE, the
  packetiser receiver will continue to read broadcast packets (including
  the SCM portion) but will discard the audio frames as the sample rate is
  unsupported. When the sample rate changes again (potentially to a new rate
  that is supported) a new indication will be sent.
*/
void BroadcastPacketiserSampleRateChangeResponse(broadcast_packetiser_t *bp,
                                                 bool response);

/*!
  @brief Response from the client task to the
         #BROADCAST_PACKETISER_START_OF_STREAM_IND.
  @param bp The #broadcast_packetiser_t instance.
  Only applicable in the broadcaster role. It it obligatory for the client
  to respond. There is no option for the client to respond with a rejection
  of the start of stream, as the client must have changed to the source
  to trigger the new start of stream.
*/
void BroadcastPacketiserStartOfStreamResponse(broadcast_packetiser_t *bp);

/*!
  @brief Set the 16 bit dynamic initialisation vector used by AESCCM.
  @param bp The #broadcast_packetiser_t instance.
  @param iv The 16 bit dynamic initialisation vector.
  The dynamic IV may be changed at any time.
*/
void BroadcastPacketiserSetAesccmDynamicIv(broadcast_packetiser_t *bp,
                                           uint16 iv);

/*!
  @brief Set the broadcast system volume.
  @param bp The #broadcast_packetiser_t instance.
  @param volume The volume in BA steps 0..31.
  The volume may be changed at any time.
*/
void BroadcastPacketiserSetVolume(broadcast_packetiser_t *bp, uint16 volume);

/*!
  @brief Set the interval the library will send statistics messages to the
  client task.
  @param bp The #broadcast_packetiser_t instance.
  @param interval The interval in microseconds.
  The interval may be changed at any time.
*/
void BroadcastPacketiserSetStatsInterval(broadcast_packetiser_t *bp,
                                         rtime_t interval);

/*!
  @brief Set the sample rate.
  @param bp The #broadcast_packetiser_t instance.
  @param sample_rate The sample rate.
  In the receiver role, the sample rate must not be changed using this
  function. Instead the #BroadcastPacketiserSampleRateChangeResponse function
  should be used to accept support for new sample rates indicated by a
  #BROADCAST_PACKETISER_SAMPLE_RATE_CHANGE_IND.
  In the broadcaster role, this function shall be called after receiving a
  #BROADCAST_PACKETISER_START_OF_STREAM_IND if the start of stream was caused by
  a change in the source's configured sample rate.
  In the broadcaster role, this function may also be called if the source is
  not set.
*/
void BroadcastPacketiserSetSampleRate(broadcast_packetiser_t *bp,
                                      rtime_sample_rate_t sample_rate);

/*!
  @brief Set the packetiser's Source in the broadcaster role.
  @param bp The #broadcast_packetiser_t instance.
  @param new The new Source. Set to NULL to remove the current Source.
  @return The existing source or NULL if the packetiser has no Source.
  This function should not be called in the receiver role.
*/
Source BroadcastPacketiserSetSource(broadcast_packetiser_t *bp, Source source);

/*!
  @brief Set the packetiser's Sink in the receiver role.
  @param bp The #broadcast_packetiser_t instance.
  @param new The new Sink. Set to NULL to remove the current Sink.
  @return The existing sink or NULL if the packetiser has no Sink.
  This function should not be called in the broadcaster role.
*/
Sink BroadcastPacketiserSetSink(broadcast_packetiser_t *bp, Sink sink);

/*!
  @brief Get the current TTP extension value.
  @param bp The #broadcast_packetiser_t instance.
  @return uint8 Current TTP extension value.
  This function can be used to retrieve the current TTP extension prior to
  destroying a broadcast packetiser instance, so that it can be provided
  in configuration when creating a new packetiser to continue from the same
  TTP extension.
  Only valid in the broadcaster role, this function should not be called
  in the receiver role.
*/
uint8 BroadcastPacketiserGetTtpExtension(broadcast_packetiser_t *bp);

/*!
  @brief Set new frame length and frame samples codec parameters.
  @param bp The #broadcast_packetiser_t instance.
  @param frame_length The fixed length of each audio frame.
  @param frame_samples The fixed number of samples represented by each audio frame.
  This function should be called to update a broadcast packetiser instance
  with new codec parameters.
  It may only be called in response to receiving either a
  #BROADCAST_PACKETISER_STREAM_ID_CHANGE_IND message or a 
  #BROADCAST_PACKETISER_SAMPLE_RATE_CHANGE_IND message.
  In both case it must be called prior to the client responding to that message 
  with #BroadcastPacketiserStreamIDChangeResponse() or 
  #BroadcastPacketiserSampleRateChangeResponse() respectively.
  In the broadcaster role, this function may only be called if the source is
  not set.
*/
void BroadcastPacketiserSetCodecParameters(broadcast_packetiser_t *bp,
                                           uint16 frame_length,
                                           uint16 frame_samples);

#endif
