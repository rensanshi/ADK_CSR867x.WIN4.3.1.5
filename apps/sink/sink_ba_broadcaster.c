/*******************************************************************************
Copyright (c) 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    sink_ba_broadcaster.c

DESCRIPTION
    This is an internal submodule for broadcast audio. This module implements
    Broadcaster functionalities of broadcast audio. It provides interface to other
    sub modules to access(set/get) broadcaster behaviors.
    Major functionalities handled in this module are
    1.Broadcaster Association
    2.Security key/random number generation for association
    3.Handle Broadcaster configuration
    4.Gatt related functionality for Association
    5.Handles all messages form broadcaster/SCM/Gatt/GattManager/Connection Lib
    gatt related interfaces
    6.Broadcaster audio plugin setup with broadcaster plugin module
    7.Broadcaster connection
    
NOTES
    This module interfaces need to be exposed to sink_ba or sink_ba_pluging modules
    only. It is restricted to access these interfaces from any other modules

*/

/* Sink app module interfaces */
#include "sink_ba.h"
#include "sink_ba_broadcaster.h"
#include "sink_private_data.h"
#include "sink_utils.h"
#include "sink_gatt.h"
#include "sink_gatt_server_ba.h"
#include "sink_hfp_data.h"
#include "sink_ble.h"

/* Library interfaces */
#include <ps.h>
#include <vm.h>
#include <util.h>
#include <panic.h>
#include <gatt_server.h>
#include <gatt_gap_server.h>
#include <broadcast.h>
#include <broadcast_stream_service_record.h>
#include <gain_utils.h>
#include <gatt_broadcast_server_uuids.h>
#include <vmtypes.h>
#include <broadcast_context.h>
#include <broadcast_cmd.h>
#include <afh_channel_map.h>

#ifdef ENABLE_BROADCAST_AUDIO

#include "sink_broadcast_audio_config_def.h"

/* Debugging defines */
#ifdef DEBUG_BA_BROADCASTER
#define DEBUG_BROADCASTER(x) DEBUG(x)
#else
#define DEBUG_BROADCASTER(x)
#endif

#ifdef AFH_LOGGING
#define AFH_LOGGING_DEBUG(x)   DEBUG(x)
#else
#define AFH_LOGGING_DEBUG(x)
#endif

/*! Offset to apply to the instant for an AFH update to be applied on broadcaster
 *  and receiver, in BT slots when using sync train method; 1 second. */
#define AFH_UPDATE_INSTANT_OFFSET   (3200)


/*---------------------CSB Defines--------------------------*/
/* Time in slots before we'll receive a supervision timeout
 * for failure to transmit a CSB packet. */
#define CSB_SUPERVISION_TIMEOUT         0x2000
/* Permitted packets to use for CSB. */
#define CSB_PACKET_TYPE                 8

/*---------------------SYNC TRAIN related Defines ----------*/
/* Default sync train timeout of 30s (in BT slots) */
#define SYNC_TRAIN_TIMEOUT              (0xBB80)
/* Don't timeout the sync train, broadcast library will
 * automatically restart it for us, and always keep it running */
#define SYNC_TRAIN_NO_TIMEOUT           0
/* Minimum interval for sync train packets. */
#define SYNC_TRAIN_INTERVAL_MIN         0xA0 
/* Maximum interval for sync train packets. */
#define SYNC_TRAIN_INTERVAL_MAX         0xC0
/* Service data in the sync train, must be 0x00 */
#define SYNC_TRAIN_SERVICE_DATA_WORD    0x00

/*---------------------CELT related Defines ----------------*/

/* Number of times each SCM segment will be retransmitted by the DSP. */
#define DEFAULT_SCM_MSG_RETX_ATTEMPTS       15

/* Number of SCM segment retransmissions to use for AFH Update SCM messages. */
#define AFH_MESSAGE_RETX_NUM                DEFAULT_SCM_MSG_RETX_ATTEMPTS

/*-----------------Data structure used for Broadcaster------*/ 

/* Broadcaster data, this single structure handles all
   data related to broadcaster, it also contains broadcast lib
   scm lib and gatt related data for broadcaster
*/
typedef struct _brodcasterdata_t{
    uint16      volume;

    /* Reference to an instance of the broadcast library, configured  as a broadcaster */
    BROADCAST* broadcaster;

    /* Parameters for configuring a broadcast stream */
    broadcaster_csb_params csb_params;
    /* Parameters for configuring a sync train, advertising the broadcast stream */
    broadcaster_sync_params sync_params;

    /* Connection ID of link to GATT peer. */
    uint16      cid;

    /* Pointer to the memory allocated for sending AFH Update
     * SCM messages. */
    uint8*      afh_update_scm_message;

    /* Lock during handling of adverts/connecting/disconnecting BLE link */
    unsigned        connecting:1;

    /* Flag to indicate AFH update SCM send is in progress */
    unsigned      afh_update_scm_in_progress:1;

    /*! Flag indicating we have requested a local change in the
     * AFH channel map, and not yet been notified it has been
     * applied. */
    unsigned afh_local_map_change_in_progress:1;
    
    /* Flag to record whether Broadcaster is started */
    unsigned broadcaster_started:1;

    /*! Spare bit fields */
    unsigned __SPARE__:12;

    /* Broadcaster task. */
    Task task;

}brodcasterdata_t;


/* Reference to broadcaster data for use in this module */
static brodcasterdata_t *gBroadcaster = NULL;
#define BROADCASTER   gBroadcaster

/*-------------------------Static Function Definitions------------------------*/

/*----------------Broadcaster connection Handling Helper functions-------------*/

/*----------------Broadcaster Association Config Utilities ----------------*/

/***************************************************************************
NAME
    broadcasterLoadStoredLtAddress
 
DESCRIPTION
    Utility function to retrieve the Broadcaster LT Address from PS store

PARAMS
    void

RETURNS
    bool TRUE if retrieved LT Address is Valid else FALSE 
*/
static uint8 broadcasterLoadStoredLtAddress(void)
{
    ba_config_def_t* rw_config_data = NULL;
    uint8 lt_addr;

    if(configManagerGetReadOnlyConfig(BA_CONFIG_BLK_ID, (const void **)&rw_config_data))
    {
       lt_addr = (uint8)(rw_config_data->broadcaster_lt_addr);
       configManagerReleaseConfig(BA_CONFIG_BLK_ID);

       return lt_addr;
    }
    return LT_ADDR_DEFAULT;
}

/***************************************************************************
NAME
    broadcasterConfigStoreKey
 
DESCRIPTION
    Store the security key.
 
PARAMS
    key  Security Key
RETURNS
    void
*/
static void broadcasterConfigStoreKey(uint16* key)
{
    broadcaster_writeable_keys_config_def_t* rw_config_data = NULL;
    
    DEBUG_BROADCASTER(("Broadcaster: broadcasterConfigStoreKey(): Security Key\n"));

    if (configManagerGetWriteableConfig(BROADCASTER_WRITEABLE_KEYS_CONFIG_BLK_ID, (void **)&rw_config_data, 0))
    {
        memmove(&rw_config_data->broadcaster_keys.sec, key, sizeof(rw_config_data->broadcaster_keys.sec));
        configManagerUpdateWriteableConfig(BROADCASTER_WRITEABLE_KEYS_CONFIG_BLK_ID);
    }
}

/***************************************************************************
NAME
    broadcasterRandomBitsGenerator
 
DESCRIPTION
    Utility function to generate random number
 
PARAMS
    num_bits number of bit random number to be generated (16bit random number, 128bit random number etc)
    dest pointer to where number needs to be stored
    
RETURNS
    None
*/
static void broadcasterRandomBitsGenerator(uint16 num_bits, uint16* dest)
{
    uint16 iterations = num_bits / 16;
    uint16 i;

    for (i=0; i<iterations; i++)
    {
        *dest = UtilRandom();
        dest++;
    }
}

/***************************************************************************
NAME
    broadcasterSecKeyGenerator
 
DESCRIPTION
    Utility function to generate random number for security key
 
PARAMS
    broadcast_encr_config_t encryption configuration structure
    
RETURNS
    None
*/
static void broadcasterSecKeyGenerator(broadcast_encr_config_t* encr_config)
{
    broadcasterRandomBitsGenerator(128, &encr_config->seckey[1]);

    /* only using private/AES keys at the moment, just set that type */
   encr_config->seckey[0] = (BSSR_SECURITY_ENCRYPT_TYPE_AESCCM |
            BSSR_SECURITY_KEY_TYPE_PRIVATE);

    /* store the key in PS */
    broadcasterConfigStoreKey(encr_config->seckey);
}

/***************************************************************************
NAME
    broadcasterVariantIVGenerator
 
DESCRIPTION
    Utility function to generate random number for vairant IV
 
PARAMS
    None
    
RETURNS
    None
*/
static void broadcasterVariantIVGenerator(void)
{
    broadcast_encr_config_t* encr_config = BroadcastContextGetEncryptionConfig();
    /* Generate the variant_iv */ 
    broadcasterRandomBitsGenerator(16, &encr_config->variant_iv);
    /* Update broadcast context library with encryption information, to be used by the plugin */
    BroadcastContextSetEncryptionConfig(encr_config);
    /* got new IV, so reset prev_ttp_ext */
    BroadcastContextSetTtpExtension(0);
}

/***************************************************************************
NAME
    broadcasterConfigLoadKey
 
DESCRIPTION
    Load the security key.
 
PARAMS
    key_dest  Where the security key is stored
    
RETURNS
    bool TRUE success else FALSE 
*/
static bool broadcasterConfigLoadKey(uint16* key_dest)
{
    broadcaster_writeable_keys_config_def_t* rw_config_data = NULL;
    bool ret_val = FALSE;
    
    if (configManagerGetReadOnlyConfig(BROADCASTER_WRITEABLE_KEYS_CONFIG_BLK_ID, (const void **)&rw_config_data))
    {
        /* if we loaded something, but the first words is 0x0000, return FALSE
        this is just initialised data not a real key */
        if (rw_config_data->broadcaster_keys.sec[0] != 0x0000)
        {
            /* get data from PS and copy section we need to destination */
            memmove(key_dest, &rw_config_data->broadcaster_keys.sec, sizeof(rw_config_data->broadcaster_keys.sec));
            ret_val = TRUE;
        }
        configManagerReleaseConfig(BROADCASTER_WRITEABLE_KEYS_CONFIG_BLK_ID);
    }
    return ret_val;
}

/***************************************************************************
NAME
    broadcasterIscontinuousSyncTrainSet
 
DESCRIPTION
    Check whether continuous sync train is Enabled for Broadcaster.
 
PARAMS
    void
    
RETURNS
    bool TRUE if Sync Train is Enabled else FALSE 
*/
static bool broadcasterIscontinuousSyncTrainSet(void)
{
    ba_config_def_t* ro_config_data = NULL;
    bool result = FALSE;

    if (configManagerGetReadOnlyConfig(BA_CONFIG_BLK_ID, (const void **)&ro_config_data))
    {
        if(ro_config_data->continuous_sync_train)
            result = TRUE;
        configManagerReleaseConfig(BA_CONFIG_BLK_ID);
    }
    return result; 
}

/***************************************************************************
NAME
    broadcasterConfigLoadFixedIv
 
DESCRIPTION
    Load the fixed IV.
 
PARAMS
    fixed_iv_dest  Where the fixed IV need to be copied
    
RETURNS
    bool TRUE success else FALSE 
*/
static bool broadcasterConfigLoadFixedIv(uint16* fixed_iv_dest)
{
    broadcaster_writeable_keys_config_def_t* rw_config_data = NULL;
    bool ret_val = FALSE;

    if (configManagerGetReadOnlyConfig(BROADCASTER_WRITEABLE_KEYS_CONFIG_BLK_ID, (const void **)&rw_config_data))
    {
        /* if we loaded something, but the first words is 0x0000, return FALSE
        this is just initialised data not a real fixed IV */
        if (rw_config_data->broadcaster_keys.fiv[0] != 0x0000)
        {
            /* get data from PS and copy section we need to destination */
            memmove(fixed_iv_dest, &rw_config_data->broadcaster_keys.fiv, sizeof(rw_config_data->broadcaster_keys.fiv));
            ret_val = TRUE;
        }
        configManagerReleaseConfig(BROADCASTER_WRITEABLE_KEYS_CONFIG_BLK_ID);
    }
    return ret_val;
}

/***************************************************************************
NAME
    broadcasterReadEncryptionConfig
 
DESCRIPTION
    Reads the encryption configuration
 
PARAMS
    Void
RETURNS
    broadcast_encr_config_t  Encryption config
*/
static broadcast_encr_config_t* broadcasterReadEncryptionConfig(void)
{
    broadcast_encr_config_t* encr_config = NULL;

    /* get memory for encryption configuration */
    encr_config = PanicUnlessMalloc(sizeof(broadcast_encr_config_t));
    memset( encr_config, 0, sizeof(broadcast_encr_config_t) );

    /* Load security key (if already associated), else generate one */
    if (!broadcasterConfigLoadKey(encr_config->seckey))
    {
        /* No security key, not already associated hence generate one */
        broadcasterSecKeyGenerator(encr_config);
    }

    /* Load Fixed IV */
    if (!broadcasterConfigLoadFixedIv(encr_config->fixed_iv))
    {
        /* must have a FixedIV in PS */
        Panic();
    }
    BroadcastContextSetEncryptionConfig(encr_config);
    return encr_config;
}

/*--------------------------Broadcaster GATT Utility Function------------------*/

/***************************************************************************
NAME
    broadcasterBlBroadcastStoppedHandling
 
DESCRIPTION
    Standard Action for Broadcaster Stop
 
PARAMS
    void 
RETURNS
    void
*/
static void broadcasterBlBroadcastStoppedHandling(void)
{
    /* no longer streaming, so stop advertising the IV */
    sinkBroadcastAudioStopIVAdvertsAndScan();

    /* stop receiving AFH map updates from firmware, as we can't send them
       over SCM */
    CsbEnableNewAfhMapEvent(FALSE);

    /* sink is no longer valid */
    BroadcastContextSetSink(NULL);
}

/********************** External Interface Definitions*************************/

/*--------------------------Interfaces to BA Module---------------------------*/
bool sinkBroadcasterInit(Task task)
{
    if(!BROADCASTER)
    {
        broadcast_encr_config_t* encr_config = NULL;

        /* Init memory for broadcaster */
        BROADCASTER = (brodcasterdata_t*)PanicUnlessMalloc(sizeof(brodcasterdata_t));
        memset(BROADCASTER,0,sizeof(brodcasterdata_t));

        /* Store the broadcaster task */
        BROADCASTER->task = task;

        /* Set default volume */
        BROADCASTER->volume = sinkHfpDataGetDefaultVolume();

        /* Update the broadcaster server database with the stream ID */
        sinkGattBAServerUpdateStreamID(CELT_STREAM_ID);
        BroadcastContextSetStreamId(CELT_STREAM_ID);

        /* load our security config */
        encr_config = broadcasterReadEncryptionConfig();

        /* update the security key in our GATT Broadcast Service server */
        sinkGattBAServerUpdateSecKey(encr_config->seckey,
                                            sizeof(encr_config->seckey)/sizeof(uint16));

        /* Generate the new Variant IV */
        broadcasterVariantIVGenerator();

        sinkBroadcastAcquireVolumeTable();

        /* Init Broadcast Lib with broadcaster Role */
        BroadcastInit(task, broadcast_role_broadcaster);

        /* Enough of encrytion config*/
        free(encr_config);
        return TRUE;
    }
    return FALSE;
}

/*******************************************************************************/
void sinkBroadcasterStartBroadcast(broadcast_mode mode)
{
    if(!BROADCASTER->broadcaster_started)
    {
        DEBUG_BROADCASTER(("APP:BROADCASTER_MSG_START_BROADCAST calling BroadcastStartBroadcast()\n"));
        BROADCASTER->broadcaster_started = TRUE;
        BroadcastStartBroadcast(BROADCASTER->broadcaster, mode);
    }
}

/*******************************************************************************/
void sinkBroadcasterStopBroadcast(broadcast_mode mode)
{
    DEBUG_BROADCASTER(("BA: sinkBroadcasterStopBroadcast()\n"));
    BROADCASTER->broadcaster_started = FALSE;
    BroadcastStopBroadcast(BROADCASTER->broadcaster, mode);
}

/*--------------------Interfaces to BA Audio Plugin Module----------------------*/

/*******************************************************************************/
uint16 sinkBroadcasterGetVolume( void )
{
    return BROADCASTER->volume;
}

/*******************************************************************************/
void sinkBroadcasterSetMasterRole( uint16 device_id)
{
    /* Make sure we are master of link */
    ConnectionSetRole(sinkGetMainTask(), A2dpSignallingGetSink(device_id), hci_role_master);
}

/******************************************************************************
 * Broadcast LIB Message Handlers
 ******************************************************************************/

static void broadcasterHandleBlInitCfm(Task task,BROADCAST_INIT_CFM_T* cfm)
{
    if (cfm->status == broadcast_success)
    {
        BROADCASTER->csb_params.lpo_allowed = TRUE;
        BROADCASTER->csb_params.packet_type = CSB_PACKET_TYPE;
        BROADCASTER->csb_params.interval_min = CSB_INTERVAL_SLOTS;
        BROADCASTER->csb_params.interval_max = CSB_INTERVAL_SLOTS;
        BROADCASTER->csb_params.supervision_timeout = CSB_SUPERVISION_TIMEOUT;
        BROADCASTER->sync_params.interval_min = SYNC_TRAIN_INTERVAL_MIN;
        BROADCASTER->sync_params.interval_max = SYNC_TRAIN_INTERVAL_MAX;

        if(broadcasterIscontinuousSyncTrainSet())
            BROADCASTER->sync_params.sync_train_timeout = SYNC_TRAIN_NO_TIMEOUT;
       else
            BROADCASTER->sync_params.sync_train_timeout = SYNC_TRAIN_TIMEOUT;

        BROADCASTER->sync_params.service_data = SYNC_TRAIN_SERVICE_DATA_WORD;
       DEBUG_BROADCASTER(("BA: Broadcast Lib Init\n"));
        BROADCASTER->broadcaster = cfm->broadcast;
            
        BroadcastConfigureBroadcaster(BROADCASTER->broadcaster, 
                                      broadcasterLoadStoredLtAddress(), 
                                      &BROADCASTER->csb_params, &BROADCASTER->sync_params);
        BroadcastCmdScmInit(task, broadcast_cmd_role_broadcaster);
    }


}

/******************************************************************************/
static void broadcasterHandleBlConfigureCfm(Task task,BROADCAST_CONFIGURE_CFM_T* cfm)
{
    UNUSED(task);

    if (cfm->status == broadcast_success)
    {
        DEBUG_BROADCASTER(("BA: Broadcast Configure Success\n"));
    }
}

/******************************************************************************/
static void broadcasterHandleBlStartBroadcastCfm(Task task,BROADCAST_START_BROADCAST_CFM_T* cfm)
{
    UNUSED(task);
    DEBUG_BROADCASTER(("BA: BROADCAST_START_BROADCAST_CFM_T: Status %x, mode %x\n", cfm->status , cfm->mode));

    if (cfm->status == broadcast_success)
    {
        if (cfm->mode == broadcast_mode_broadcast_only)
        {
            BroadcastContextSetSink(cfm->sink);
#ifndef DISABLE_AFH
            /* start receiving AFH map updates from firmware */
            CsbEnableNewAfhMapEvent(TRUE);
#endif

            /* Trigger advertising non-conn IV adverts */
            sinkBleStartBroadcastEvent();
            /* connect CSB to the DSP */
            /* connect plugin using audio routing */
            BroadcastStartBroadcast(cfm->broadcast, broadcast_mode_synctrain_only);
        }
        else if (cfm->mode == broadcast_mode_synctrain_only)
        {
            /* Send system event for LED */
        }
        else
        {
            DEBUG_BROADCASTER(("BA: BRD_START_CFM: Auto started\n"));
            BroadcastContextSetSink(cfm->sink);
            /* Send system event for LED */

#ifndef DISABLE_AFH
            /* start receiving AFH map updates from firmware */
            CsbEnableNewAfhMapEvent(TRUE);
#endif
             /* Trigger advertising non-conn IV adverts */
            sinkBleStartBroadcastEvent();
            /* connect CSB to the DSP */
            /* connect plugin using audio routing */
            audioUpdateAudioRouting();
        }
    }
}

/******************************************************************************/
static void broadcasterHandleBlStopBroadcastCfm(Task task, BROADCAST_STOP_BROADCAST_CFM_T* cfm)
{
    UNUSED(task);

    if (cfm->status == broadcast_success)
    {
        if (cfm->mode == broadcast_mode_auto)
        {
            DEBUG_BROADCASTER(("Broadcaster: BRD_STOP_CFM: Broadcast Auto Stopped\n"));
            /* standard actions on broadcast stopping */
            broadcasterBlBroadcastStoppedHandling();
        }
    }
}

/******************************************************************************/
static void broadcasterHandleBlStopBroadcastInd(Task task, BROADCAST_STOP_BROADCAST_IND_T* ind)
{
    /* broadcast timed out, it's no longer running try and restart it */
    DEBUG_BROADCASTER(("Broadcaster: BRD_STOP_IND: Broadcast Timed Out, restarting...\n"));

    /* respond to the timeout */
    BroadcastBroadcasterTimeoutResponse(ind->broadcast);

    /* standard actions on broadcast stopping */
    broadcasterBlBroadcastStoppedHandling();

    /* request broadcast restart */
    MessageSend(task, BROADCASTER_MSG_START_BROADCAST, NULL);
}

/******************************************************************************/
/*! @brief Count the number of set bits in the AFH channel map. 
    AFH channel map is 10 bytes packed into 5 uint16s.
 */
static int broadcastercountNumberAfhChannelsInMap(AfhMap afh_map)
{
    int map_index;
    int afh_channel_count = 0;

    for (map_index = 0; map_index < (int)(sizeof(AfhMap)/sizeof(uint16)); map_index++)
    {
        uint16 v=afh_map[map_index], c;
        for (c=0;v;c++)
            v &= v-1;
        afh_channel_count += c;
    }
    return afh_channel_count;
}

/******************************************************************************/
static void broadcasterHandleBlAfhUpdateInd(Task task, BROADCAST_AFH_UPDATE_IND_T* ind)
{
    uint16 map_index = 0;
    uint32 apply_instant = ind->clock + AFH_UPDATE_INSTANT_OFFSET;
    uint16 afh_channel_count = broadcastercountNumberAfhChannelsInMap(ind->channel_map);

    UNUSED(task);

    AFH_LOGGING_DEBUG(("Broadcaster: New AFH Map: VMTime:%08lx Clock:%08lx New Clock:%08lx ChannelCount:%d ", 
                                    VmGetClock(), ind->clock, apply_instant, afh_channel_count));

    /* only send AFH update if we don't already have one in-flight to receivers */
    if ((!BROADCASTER->afh_local_map_change_in_progress)
        && (afh_channel_count >= 20))
    {
        for (map_index = 0; map_index < sizeof(ind->channel_map)/sizeof(uint16); map_index++)
        {
                /* build AfhMap structure for local AFH update trap */
               AFH_LOGGING_DEBUG(("%02x ", (ind->channel_map[map_index] & 0xFF)));
        }
        AFH_LOGGING_DEBUG(("\n"));

        AFH_LOGGING_DEBUG(("Broadcaster:AFH: Sending this AFH update\n"));

        BROADCASTER->afh_local_map_change_in_progress = CsbTransmitterSetAfhMap(BroadcastGetLtAddr(BROADCASTER->broadcaster),
                                                                                &ind->channel_map, apply_instant);
        if(!BROADCASTER->afh_local_map_change_in_progress)
        {
            DEBUG_BROADCASTER(("Broadcaster:AFH: Failure to set local AFH map! Channel Count %d\n",
                                                    afh_channel_count));
        }
        else
        {
            if(sinkAudioIsAudioRouted())
            {
                afhChannelMapChangeIsPending();
            }
        }
    }
}

/******************************************************************************/
static void broadcasterHandleBlAfhChannelMapChangeInd(Task task, BROADCAST_AFH_CHANNEL_MAP_CHANGED_IND_T *ind)
{
    UNUSED(task);
    UNUSED(ind);

    DEBUG_BROADCASTER(("APP:BL: AFH Channel map changed\n"));
    BROADCASTER->afh_local_map_change_in_progress = FALSE;
}

/******************************************************************************
 * BCMD LIB Message Handlers
 ******************************************************************************/

/******************************************************************************/
static void broadcasterHandleBcmdInitConfirm(Task task, BROADCAST_CMD_INIT_CFM_T *cfm)
{
    UNUSED(task);

    DEBUG_BROADCASTER(("Broadcaster:broadcasterHandleBcmdInitConfirm(), Status %d\n",cfm->status));
    
    /* Check if SCM Library initialised successfully */
    if (cfm->status == broadcast_cmd_success)
    {
        BROADCASTER->afh_update_scm_in_progress = FALSE;
        sinkBroadcastAudioHandleInitCfm();
    }
    else
    {
        DEBUG_BROADCASTER(("Broadcaster:broadcasterHandleScmInitConfirm() Failed\n"));
    }
}

/******************************************************************************/
static void broadcasterHandleAfhUpdateMessageCfm(void)
{
    /* if this was an AFH Update message cfm, clear the flag to prevent further messages
     * and free the memory for the message just completed. */
    if (BROADCASTER->afh_update_scm_in_progress)
    {
        free(BROADCASTER->afh_update_scm_message);
        BROADCASTER->afh_update_scm_in_progress = FALSE;
    }
}

/*******************************************************************************/
static void broadcasterHandleShutdownCfm(void)
{
    /* we have some memory waiting to be freed on completion of an
     * AFH SCM transmission, free it if we were still waiting for it */
    if ((BROADCASTER->afh_update_scm_in_progress) && (BROADCASTER->afh_update_scm_message))
    {
        free(BROADCASTER->afh_update_scm_message);
        BROADCASTER->afh_update_scm_in_progress = FALSE;
    }
}

/******************************************************************************
 * Broadcaster message Handlers
 ******************************************************************************/
/******************************************************************************/
void sinkBroadcasterHandleReceiverConnectCfm(GATT_MANAGER_REMOTE_SERVER_CONNECT_CFM_T* cfm)
{
    if (cfm->status == gatt_status_success)
    {
        DEBUG_BROADCASTER(("Broadcaster: Gatt Remote server Connect Success->Start Assoc\n"));
        BROADCASTER->cid = cfm->cid;
        /* found and connected to a csb_receiver, allow it to read the broadcaster's association data */
        sinkGattBAServerEnableAssociation(TRUE);
    }
    else
    {
        DEBUG_BROADCASTER(("Broadcaster: Gatt Remote server Connect Failed (0x%x)->Retry\n", cfm->status));
        /* TODO SS78: Should we try again to connect to receiver? */
        /*broadcasterGattConnectToReceiver(task,&cfm->taddr);*/
    }
}

/******************************************************************************/
void sinkBroadcasterHandleReceiverDisconnectInd(GATT_MANAGER_DISCONNECT_IND_T* ind)
{
    UNUSED(ind);

    DEBUG_BROADCASTER(("Broadcaster: Gatt Manger DisconnectInd\n"));
    BROADCASTER->cid = INVALID_CID;
    sinkGattBAServerEnableAssociation(FALSE);    
    /* Send system message to stop associating led pattern LedAssociating(FALSE);*/
}

/******************************************************************************/
bool sinkBroadcasterIsReceiverCid(uint16 cid)
{
    if(BROADCASTER)
        return (cid == BROADCASTER->cid) ? TRUE : FALSE;
    return FALSE;
}

/******************************************************************************/
static void broadcasterHandleBlDeInitCfm(Task task, BROADCAST_DESTROY_CFM_T* cfm)
{
    UNUSED(task);

    if (cfm->status == broadcast_success)
    {
        /* De-initialize the Broadcaster Global instance */
        free(BROADCASTER);
        BROADCASTER = NULL;
        BroadcastContextSetEncryptionConfig(NULL);
        sinkBroadcastAudioHandleDeInitCfm(sink_ba_appmode_broadcaster);
    }
}

void sinkBroadcasterHandleBroadcastMessage(Task task, MessageId id, Message message)
{
    switch (id)
    {
        case BROADCAST_INIT_CFM:
            broadcasterHandleBlInitCfm(task,(BROADCAST_INIT_CFM_T*)message);
            break;

        case BROADCAST_DESTROY_CFM:
            broadcasterHandleBlDeInitCfm(task, (BROADCAST_DESTROY_CFM_T*)message);
            break;

        case BROADCAST_CONFIGURE_CFM:
            broadcasterHandleBlConfigureCfm(task,(BROADCAST_CONFIGURE_CFM_T*)message);
            break;

        case BROADCAST_START_BROADCAST_CFM:
            broadcasterHandleBlStartBroadcastCfm(task,(BROADCAST_START_BROADCAST_CFM_T*)message);
            break;

        case BROADCAST_STATUS_IND:
            DEBUG_BROADCASTER(("Broadcaster: BROADCAST_STATUS_IND: %x\n", ((BROADCAST_STATUS_IND_T*)message)->status ));
            break;

        case BROADCAST_STOP_BROADCAST_CFM:
            broadcasterHandleBlStopBroadcastCfm(task,(BROADCAST_STOP_BROADCAST_CFM_T*)message);
            break;
        
        case BROADCAST_STOP_BROADCAST_IND:
            broadcasterHandleBlStopBroadcastInd(task,(BROADCAST_STOP_BROADCAST_IND_T*)message);
            break;

        case BROADCAST_AFH_UPDATE_IND:
            broadcasterHandleBlAfhUpdateInd(task,(BROADCAST_AFH_UPDATE_IND_T*)message);
            break;

        case BROADCAST_AFH_CHANNEL_MAP_CHANGED_IND:
            broadcasterHandleBlAfhChannelMapChangeInd(task,(BROADCAST_AFH_CHANNEL_MAP_CHANGED_IND_T*)message);
            break;

        default:
            DEBUG_BROADCASTER(("Broadcaster: Unhandled Broadcast message 0x%x\n", id));
            break;
    }
}

/******************************************************************************/
void sinkBroadcasterHandleBcmdMessage(Task task, MessageId id, Message message)
{
    switch (id)
    {
        case BROADCAST_CMD_INIT_CFM:
            DEBUG_BROADCASTER(("BA: BCMD: INIT CFM\n"));
            broadcasterHandleBcmdInitConfirm(task,(BROADCAST_CMD_INIT_CFM_T *)message);
            break;

        case BROADCAST_CMD_AFH_UPDATE_CFM:
            DEBUG_BROADCASTER(("BA: BCMD: AFH Update CFM\n"));
            broadcasterHandleAfhUpdateMessageCfm();
            break;

        case BROADCAST_CMD_SHUTDOWN_CFM:
            DEBUG_BROADCASTER(("BA: BCMD: SHUTDOWN CFM\n"));
            broadcasterHandleShutdownCfm();
            break;

        case BROADCAST_CMD_ENABLE_CFM:
            DEBUG_BROADCASTER(("BA: BCMD: ENABLE_CFM\n"));
            break;

        case BROADCAST_CMD_DISABLE_CFM:
            DEBUG_BROADCASTER(("BA:BCMD: DISABLE_CFM\n"));
            break;

        default:
            DEBUG_BROADCASTER(("BA:Unhandled SCM message 0x%x\n", id));
            break;
    }
}

/*****************************************************************************/
void sinkBroadcasterHandlePowerOn(Task broadcaster_task)
{
    DEBUG_BROADCASTER(("Broadcaster: Power On \n"));
    /* Attempt to start the broadcast */
    MessageSend(broadcaster_task, BROADCASTER_MSG_START_BROADCAST, NULL);
}

/*****************************************************************************/
void sinkBroadcasterDeInit(void)
{
    DEBUG_BROADCASTER(("Broadcaster: sinkBroadcasterDeInit\n"));

    if(BROADCASTER)
    {
        /* Use a conditional message so that the plugin can disable scm,
           destroy the packetiser etc. before we destroy scm and the
           broadcast receiver. */
        MessageSendConditionally(BROADCASTER->task,
                                 BROADCASTER_INTERNAL_MSG_DESTROY_BROADCASTER,
                                 0, BroadcastContextGetBroadcastBusy());
    }
}

void sinkBroadcasterDestroyBroadcaster(void)
{
    DEBUG_BROADCASTER(("Broadcaster: sinkBroadcasterDestroyBroadcaster\n"));

    /* Stop the Broadcast */
    sinkBroadcasterStopBroadcast(broadcast_mode_auto);

    /* Free the SCMB memory which was allocated as part of init */
    BroadcastCmdScmDestroy();

    /* De-initialize Broadcast library */
    BroadcastDestroy(BROADCASTER->broadcaster);

    sinkBroadcastReleaseVolumeTable();
}

#endif /* ENABLE_BROADCAST_AUDIO*/

