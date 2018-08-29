/*******************************************************************************
Copyright (c) 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    sink_ba_broadcaster.h

DESCRIPTION
    Interface File to manage broadcaster of Broadcast Audio. This is an internal
    module interface file. All the interfaces to this internal mdodule are
    restricted to use only from broadcast aduio module or broadcast audio plugin
    module
    
NOTES

*/

#ifndef _SINK_BA_BROADCASTER_H_
#define _SINK_BA_BROADCASTER_H_


#include "sink_ba_common.h"
#include <gatt_server.h>
#include <gatt_gap_server.h>
#include <gatt_manager.h>
#include <broadcast_context.h>

/* 8 16-bit words = 128 bits */
#define MAX_RANDOM_BITS 8  

/* Message Base for broadcaster application . */
#define BROADCASTER_MESSAGE_BASE    0x0000

#define BROADCASTER_DSP_SCALING_FACTOR (10)

/* Message definitions for internal use within the application. */
typedef enum _broadcaster_message_t
{
    BROADCASTER_MSG_WRITE_VOLUME_PSKEY  =  BROADCASTER_MESSAGE_BASE,
    BROADCASTER_MSG_POWER_OFF_COMPLETE,
    BROADCASTER_MSG_START_BROADCAST,
    BROADCASTER_INTERNAL_MSG_STOP_BLE_BROADCAST,
    BROADCASTER_INTERNAL_MSG_STOP_BROADCASTER,
    BROADCASTER_INTERNAL_MSG_DESTROY_BROADCASTER,
    BROADCASTER_MSG_TOP
}broadcaster_message_t;


/***************************************************************************
NAME
    sinkBroadcasterInit
 
DESCRIPTION
    This function could use to initialise broadcast audio broadcaster.
    It will initialise broadcaster data structures and internally initialise
    broadcaster lib with role as broadcast_role_broadcaster
 
PARAMS
    Task Task which required to register with Broadcast Lib.
 
RETURNS
    bool TRUE: Init sucess, FALSE: failure.
*/
#ifdef ENABLE_BROADCAST_AUDIO
bool sinkBroadcasterInit(Task task);
#else
#define sinkBroadcasterInit(task) (FALSE)
#endif

/***************************************************************************
NAME
    sinkBroadcasterStartBroadcast
 
DESCRIPTION
    Start Broadcast Audio
 
PARAMS
    mode Broadcast mode as defined in broadcast_mode
 
RETURNS
    Void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterStartBroadcast(broadcast_mode mode);
#else
#define sinkBroadcasterStartBroadcast(mode) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterStopBroadcast
 
DESCRIPTION
    Stop Broadcast Audio
 
PARAMS
    mode Broadcast mode as defined in broadcast_mode
 
RETURNS
    Void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterStopBroadcast(broadcast_mode mode);
#else
#define sinkBroadcasterStopBroadcast(mode) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterHandleRandomBitsReq
 
DESCRIPTION
    Random Bit request handler
 
PARAMS
    message Random Bit request Message
 
RETURNS
    Void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterHandleRandomBitsReq(Message message);
#else
#define sinkBroadcasterHandleRandomBitsReq(message) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterGetVolume
 
DESCRIPTION
    Interface to Get Broadcaster Volume settings
 
PARAMS
    Void 
RETURNS
    uint16: Volume level
*/
#ifdef ENABLE_BROADCAST_AUDIO
uint16 sinkBroadcasterGetVolume( void );
#else
#define sinkBroadcasterGetVolume() 0
#endif

/***************************************************************************
NAME
    sinkBroadcasterSetMasterRole
 
DESCRIPTION
    Interface to set device id
 
PARAMS
    device_id Device ID
RETURNS
    void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterSetMasterRole( uint16 device_id);
#else
#define sinkBroadcasterSetMasterRole(device_id) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterClearScmPowerOffhandle
 
DESCRIPTION
    Interface to Clear SCM power off handle
 
PARAMS
    void
RETURNS
    void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterClearScmPowerOffhandle(void);
#else
#define sinkBroadcasterClearScmPowerOffhandle() ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterHandleBroadcastMessage
 
DESCRIPTION
    Handler for Broadcaster Lib Messages
 
PARAMS
    Task Task which registered with Broadcast Lib.
    id Message ID
    message Messages Structure
 
RETURNS
    Void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterHandleBroadcastMessage(Task task, MessageId id, Message message);
#else
#define sinkBroadcasterHandleBroadcastMessage(task, id, msg) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterHandleBcmdMessage
 
DESCRIPTION
    Handler for Broadcast Cmd Lib Messages
 
PARAMS
    Task Task which registerd with Broadcast Cmd Lib.
    id Message ID
    message Messages Strcuture
 
RETURNS
    Void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterHandleBcmdMessage(Task task, MessageId id, Message message);
#else
#define sinkBroadcasterHandleBcmdMessage(task, id, msg) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterHandlePowerOn
 
DESCRIPTION
    Interface to handle Broadcaster specific activites after Power On
 
PARAMS
    Task broadcaster_task
RETURNS
    void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterHandlePowerOn(Task broadcaster_task);
#else
#define sinkBroadcasterHandlePowerOn(broadcaster_task) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterHandleReceiverConnectCfm
 
DESCRIPTION
    Interface to allow broadcaster association for the connected receiver
 
PARAMS
    cfm Gatt Managers connection response of receiver
RETURNS
    void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterHandleReceiverConnectCfm(GATT_MANAGER_REMOTE_SERVER_CONNECT_CFM_T* cfm);
#else
#define sinkBroadcasterHandleReceiverConnectCfm(cfm) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterHandleReceiverDisconnectInd
 
DESCRIPTION
    Interface to indicate receiver disconnected the LE link
 
PARAMS
    ind Gatt Managers disconnect indication of receiver
RETURNS
    void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterHandleReceiverDisconnectInd(GATT_MANAGER_DISCONNECT_IND_T* ind);
#else
#define sinkBroadcasterHandleReceiverDisconnectInd(ind) ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterIsReceiverCid
 
DESCRIPTION
    Utility function to check if the provided CID is that of receiver link
 
PARAMS
    cid GATT connection ID of the receiver
RETURNS
    TRUE if receiver's CID else FALSE
*/
#ifdef ENABLE_BROADCAST_AUDIO
bool sinkBroadcasterIsReceiverCid(uint16 cid);
#else
#define sinkBroadcasterIsReceiverCid(cid) FALSE
#endif

/***************************************************************************
NAME
    sinkBroadcasterDeInit
 
DESCRIPTION
    This function is used to de-initialise broadcast audio broadcaster.
    It will de-initialise broadcaster data structures and internally de-initialise
    broadcaster lib
 
PARAMS
    void
 
RETURNS
    void
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterDeInit(void);
#else
#define sinkBroadcasterDeInit() ((void)(0))
#endif

/***************************************************************************
NAME
    sinkBroadcasterDestroyBroadcaster

DESCRIPTION
    Destroy the broadcast broadcaster instance and related resources.

    Note: In the kymera audio framework this must only be called after the scm
          instance has been disabled and the broadcast packetiser has been
          destroyed. Otherwise there will be a race between disabling scm and
          destroying scm.
*/
#ifdef ENABLE_BROADCAST_AUDIO
void sinkBroadcasterDestroyBroadcaster(void);
#else
#define sinkBroadcasterDestroyBroadcaster() ((void)0)
#endif

#endif /* _SINK_BA_BROADCASTER_H_ */

