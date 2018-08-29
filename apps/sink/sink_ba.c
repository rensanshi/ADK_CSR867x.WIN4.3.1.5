/*******************************************************************************
Copyright (c) 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    sink_ba.c

DESCRIPTION
    Manages Broadcast Audio Application.
    
NOTES

*/

#include "sink_ba.h"
#include "sink_ba_common.h"
#include "sink_ba_broadcaster.h"
#include "sink_ba_receiver.h"
#include "sink_private_data.h"
#include "sink_audio_indication.h"
#include "sink_statemanager.h"
#include "sink_multi_channel_config_def.h"
#include "sink_ble.h"
#include "sink_ba_ble_gap.h"

#ifdef ENABLE_BROADCAST_AUDIO
#include "sink_broadcast_audio_config_def.h"

#include <gatt_manager.h>
#include <message.h>
#include <gain_utils.h>
#include <audio_output.h>
#include <vmtypes.h>
#include <broadcast_context.h>
#include <broadcast_cmd.h>
#include <ttp_latency.h>

#define BOOTMODE_DFU_HCI (0)
#ifdef DEBUG_BA_COMMON
#define DEBUG_BA(x) DEBUG(x)
#else
#define DEBUG_BA(x) 
#endif

/* PSKEY to store broadcast audio mode */
#define SINK_BROADCAST_AUDIO_PSKEY  (CONFIG_BROADCAST_AUDIO_MODE)
/* Offset for BA mode in config data */
#define SINK_BA_MODE_OFFSET 0
/* Offset for switch action in config data */
#define SINK_BA_SWITCH_ACTION_OFFSET (SINK_BA_MODE_OFFSET + 1)
/* Number of Items that could be configurable in BA */
#define SINK_BA_CONFIG_ITEMS 2
/* Reboot system afer the delay */
#define SINK_BA_REBOOT_DELAY 2
/* I2S local audio ouput format */
#define SINK_BA_AUDIO_OUPUT_FORMAT_I2S 0
/* Default BA association time out */
#define SINK_BA_ASSOCIATION_TIME_OUT 30

const char * const ba_modes[3] = {
    "NORMAL",
    "BROADCASTER",
    "RECEIVER",
};

/* Global data for Broadcast Audio Module  */
typedef struct _ba_global_data_t
{
 TaskData baAppTask; /* Broadcast Audio Application handler */
 uint16 modeswitch_inprogress; /* Are we in the process of mode change */
 unsigned ba_mode:2; /* Stores current broadcast Audio Mode*/
}ba_global_data_t;

/*!
    @brief sink_ba_stored_action_t

    This type defines stored switching/poweroff/on actions.
    sink_switch_to_normal : Swithing to normal speaker mode.
    sink_start_as_normal :  start as normal speaker
    sink_switch_to_broadcaster : switching to broadcaster mode
    sink_start_as_broadcaster : start as broadcaster
    sink_switch_to_receiver : switching to receiver mode
    sink_start_as_receiver :  start as receiver
    sink_power_off_broadcaster : power off broadcaster mode
    sink_power_off_receiver : power off reciever mode
*/
typedef enum _sink_ba_stored_action_t
{
    sink_switch_to_normal,
    sink_start_as_normal,
    sink_switch_to_broadcaster,
    sink_start_as_broadcaster,
    sink_switch_to_receiver,
    sink_start_as_receiver,
    sink_power_off_broadcaster,
    sink_power_off_receiver
}sink_ba_stored_action_t;

/* Broadcast audio global data */
static ba_global_data_t gBaData;
#define BA_DATA  gBaData

/* Broadcast Audio Role Defines */
#define IS_MODE_CHANGE_IN_PROGRESS (BA_DATA.modeswitch_inprogress == TRUE)

/* The delay in seconds for playing power on prompt, after which Broadcast audio is powered on */
#define BA_POWER_ON_PROMPT_DELAY (1)

/*-----------------------Static Functions ---------------------------------*/

/***************************************************************************
NAME
    isBAModeRetainable
 
DESCRIPTION
    Utility function used to check whether BA Mode is retainable after cold Reset.
 
PARAMS
    void 
RETURNS
    bool TRUE is BA mode is retainable else FALSE
*/
static bool isBAModeRetainable(void)
{
    ba_config_def_t* ro_config_data = NULL;
    bool result = FALSE;

    if (configManagerGetReadOnlyConfig(BA_CONFIG_BLK_ID, (const void **)&ro_config_data))
    {
        if(ro_config_data->retain_ba_mode)
            result = TRUE;
        configManagerReleaseConfig(BA_CONFIG_BLK_ID);
    }
    return result; 
}

/***************************************************************************
NAME
    broadcastAudioResetData
 
DESCRIPTION
    Utility function used to reset Broadcast Audio related data.
 
PARAMS
    void 
RETURNS
    void
*/
static void broadcastAudioResetData(void)
{
   memset(&BA_DATA,0,sizeof(BA_DATA));
}

/***************************************************************************
NAME
    broadcastAudioStoreConfigItem
 
DESCRIPTION
    Utility function to store Broadcast Audio Config Items
PARAMS
    item Buffer from where the config item need to be stored to PS store 
RETURNS
    uint16 Number of words stored in PS
*/
static uint16  broadcastAudioStoreConfigItem(uint16* item)
{
    return PsStore(SINK_BROADCAST_AUDIO_PSKEY, (const void*)item, SINK_BA_CONFIG_ITEMS);
}

/***************************************************************************
NAME
    broadcastAudioGetDefaultConfig
 
DESCRIPTION
    Utility function to Read Default config items for Broadcast Audio 
PARAMS
    config_item  Buffer to where the config item will be copied
RETURNS
    void
*/
static void broadcastAudioGetDefaultConfig(uint16* config_item)
{
    if(config_item)
    {
        config_item[SINK_BA_MODE_OFFSET] = sink_ba_appmode_normal;
        config_item[SINK_BA_SWITCH_ACTION_OFFSET] = sink_start_as_normal;
    }
}

/***************************************************************************
NAME
    broadcastAudioReadConfigItem
 
DESCRIPTION
    Utility function to Read Broadcast Audio Config Items, if the config items
    are not as per required format then defualt values will be used
PARAMS
    item  Buffer to where config item need to be copied
RETURNS
    void
*/
static void broadcastAudioReadConfigItem(uint16* item)
{
    if(item)
    {
        uint16 read_data_size;

        read_data_size = PsRetrieve(SINK_BROADCAST_AUDIO_PSKEY, (void*)item, SINK_BA_CONFIG_ITEMS);
        /* If the data read is not as per required, then fill in default values */
        if( read_data_size != SINK_BA_CONFIG_ITEMS )
        {
            broadcastAudioGetDefaultConfig(item);
        }
    }
}

/***************************************************************************
NAME
    broadcastAudioIndicatePrompt

DESCRIPTION
    Utility function to handle Broadcast Audio prompt play

PARAMS
    delay  Delay before system reboot is triggered
RETURNS
    void
*/
static void broadcastAudioIndicatePrompt(sinkEvents_t event)
{
    switch(event)
    {
        case EventUsrPowerOn:
        case EventUsrPowerOff:
        case EventSysBaSwitchToSpeaker:
            sinkAudioIndicationPlayEvent(event);
            break;

        default:
            break;
    }
}

/*******************************************************************************
NAME
    broadcastAudioGetRequestedMode().

DESCRIPTION
    Utility function to get the requested mode

 PARAMS
    None

 RETURNS
    sink_ba_app_mode_t current app mode
*/
static sink_ba_app_mode_t broadcastAudioGetRequestedMode(void)
{
    uint16 config_data[SINK_BA_CONFIG_ITEMS];
    sink_ba_app_mode_t req_mode;
    broadcastAudioReadConfigItem(config_data);
    req_mode = config_data[SINK_BA_MODE_OFFSET];

    return req_mode;
}

/*******************************************************************************
NAME
    broadcastAudioGetStoredAction().

DESCRIPTION
    This interface is used to get the stored action

 PARAMS
    None

 RETURNS
    sink_ba_stored_action_t stored action
*/
static sink_ba_stored_action_t broadcastAudioGetStoredAction(void)
{
    uint16 config_data[SINK_BA_CONFIG_ITEMS];
    sink_ba_stored_action_t switch_action;
    broadcastAudioReadConfigItem(config_data);
    switch_action = config_data[SINK_BA_SWITCH_ACTION_OFFSET];

    return switch_action;
}

/*******************************************************************************
NAME
    broadcastAudioStorePowerOffAction().

DESCRIPTION
    Utility function to store the power off action in BA mode

 PARAMS
    None

 RETURNS
    None
*/
static void broadcastAudioStorePowerOffAction(void)
{
    uint16 config_data[SINK_BA_CONFIG_ITEMS];
    broadcastAudioReadConfigItem(config_data);

    if(BA_BROADCASTER_MODE_ACTIVE)
        config_data[SINK_BA_SWITCH_ACTION_OFFSET] = sink_power_off_broadcaster;
    else
        config_data[SINK_BA_SWITCH_ACTION_OFFSET] = sink_power_off_receiver;

    broadcastAudioStoreConfigItem(&config_data[0]);
}

/***************************************************************************
NAME
    broadcastAudioSwitchActionEvent
 
DESCRIPTION
    Utility function to return the switch action system event based on the stored switch action 
PARAMS
    void
RETURNS
    sinkEvents_t system event to return
*/
static sinkEvents_t broadcastAudioSwitchActionEvent(void)
{
    sinkEvents_t switch_event = sink_start_as_normal;

    switch(broadcastAudioGetStoredAction())
    {
        case sink_switch_to_normal:
            switch_event = EventSysBaSwitchToSpeaker;
            break;

        default:
            break;
    }
    return switch_event;
}

/***************************************************************************
NAME
    broadcastAudioHandlePowerOff
 
DESCRIPTION
    Utility function to Handle a power off complete 
PARAMS
    void
RETURNS
    void
*/
static void broadcastAudioHandlePowerOffComplete(void)
{
    /* Check if power off happens due to a mode change, then handle it */
    if(IS_MODE_CHANGE_IN_PROGRESS)
    {
        /* Flush all messages to BA task handler */
        MessageFlushTask(&BA_DATA.baAppTask);
        sinkBroadcastAudioHandlePrompts(broadcastAudioSwitchActionEvent());
    }
    else
    {
        /* User power off in BA mode */
        broadcastAudioStorePowerOffAction();
        DEBUG_BA(("BA: Sending EventUsrPowerOff\n" ));
        sinkBroadcastAudioHandlePrompts(EventUsrPowerOff);
    }
}

/***************************************************************************
NAME
    BroadcasterMessageHandler
 
DESCRIPTION
    Application Message Handler for Broadcaster Role.
 
PARAMS
    task Application Task
    id Message ID
    Message Message to application Broadcaster task
 
RETURNS
    void
*/
static void BroadcasterMessageHandler(Task task, MessageId id, Message message)
{
    UNUSED(task);
    /* No need to handle any messages if we are not in proper role */
    if(!BA_BROADCASTER_MODE_ACTIVE)
    {
        /* We could have received this for switching to standalone mode */
        if(id == BROADCASTER_INTERNAL_MSG_STOP_BLE_BROADCAST)
            sinkBleStopBroadcastEvent();
        return;
    }
    
   /* handle Broadcast messages */
    if ((id >= BROADCAST_MESSAGE_BASE) && (id < BROADCAST_MESSAGE_TOP))
    {
        sinkBroadcasterHandleBroadcastMessage(&BA_DATA.baAppTask, id, message);
        return;
    }
    
    /* handle SCM messages */
    if ((id >= BROADCAST_CMD_MESSAGE_BASE) && (id < BROADCAST_CMD_MESSAGE_TOP))
    {
        sinkBroadcasterHandleBcmdMessage(&BA_DATA.baAppTask, id, message);
        return;
    }

    switch(id)
    {
        case BROADCASTER_MSG_START_BROADCAST:
            sinkBroadcasterStartBroadcast(broadcast_mode_auto);
        break;

        case BROADCASTER_MSG_POWER_OFF_COMPLETE:
            /* Broadcaster did a Gracefull power off,Handle the power off complete */
            broadcastAudioHandlePowerOffComplete();
        break;
        case BROADCASTER_INTERNAL_MSG_STOP_BROADCASTER:
            sinkBroadcasterStopBroadcast(broadcast_mode_auto);
            break;
        case BROADCASTER_INTERNAL_MSG_DESTROY_BROADCASTER:
            sinkBroadcasterDestroyBroadcaster();
            break;
        default:
            DEBUG_BA(("BA:Error!!! BroadcasterMessageHandler() Unknown Message\n" ));
        break;

    }
}

/***************************************************************************
NAME
    ReceiverMessageHandler
 
DESCRIPTION
    Application Message Handler for Receiver Role.
 
PARAMS
    task Application Task
    id Message ID
    Message Message to application receiver task
 
RETURNS
    void
*/
static void ReceiverMessageHandler(Task task, MessageId id, Message message)
{
    UNUSED(task);

    if(!BA_RECEIVER_MODE_ACTIVE)
    {
        /* We could have received this for switching to standalone mode */
        if(id == RECEIVER_INTERNAL_MSG_STOP_BLE_BROADCAST)
            sinkBleStopBroadcastEvent();
        return;
    }

    if ((id >= BROADCAST_MESSAGE_BASE) && (id < BROADCAST_MESSAGE_TOP))
    {
        sinkReceiverHandleBroadcastMessage(&BA_DATA.baAppTask, id, message);
        return;
    }

    /* handle SCM messages */
    if ((id >= BROADCAST_CMD_MESSAGE_BASE) && (id < BROADCAST_CMD_MESSAGE_TOP))
    {
        sinkReceiverHandleBcmdMessage(&BA_DATA.baAppTask, id, message);
        return;
    }

    switch(id)
    {
    case RECEIVER_MSG_WRITE_VOLUME_PSKEY:
        sinkReceiverWriteVolumePsKey();
        break;

    case RECEIVER_MSG_POWER_OFF_COMPLETE:
        /* Receiver did a Gracefull power off,Handle the power off complete */
        broadcastAudioHandlePowerOffComplete();
        break;

    case RECEIVER_INTERNAL_MSG_STOP_RECEIVER:
        sinkReceiverStopReceiver();
        break;

    case RECEIVER_INTERNAL_MSG_DESTROY_RECEIVER:
        sinkReceiverDestroyReceiver();
        break;

    case RECEIVER_INTERNAL_MSG_START_RECEIVER:
        sinkReceiverInternalStartReceiver(task);
        break;

    case RECEIVER_INTERNAL_MSG_AUDIO_DISCONNECT:
        sinkReceiverInternalDisconnectAudio();
        break;

    default:
        DEBUG_BA(("BA: Receiver unhandled Message : %d) \n",id ));
        break;
    }
}

/***************************************************************************
NAME
    broadcastAudioPowerOff
 
DESCRIPTION
    Utility function to power off broadacast Audio.
 
PARAMS
    None
RETURNS
    bool TRUE if init successful else FALSE;
*/
static bool broadcastAudioPowerOff(void)
{
    broadcastAudioStorePowerOffAction();
    /* No action if in broadcaster mode */
    if(BA_RECEIVER_MODE_ACTIVE)
    {
       DEBUG_BA(("BA: Power Off Receiver\n" ));
       sinkReceiverPowerOff(&BA_DATA.baAppTask);
       return TRUE;
    }
    return FALSE;
}

/*******************************************************************************
NAME
    broadcastAudioSetStoredAction().

DESCRIPTION
    This interface is used to set the stored action

 PARAMS
    sink_ba_stored_action_t store_action to set

 RETURNS
    None
*/
static void broadcastAudioSetStoredAction(sink_ba_stored_action_t store_action)
{
    uint16 config_data[SINK_BA_CONFIG_ITEMS];
    broadcastAudioReadConfigItem(config_data);

    if (config_data[SINK_BA_SWITCH_ACTION_OFFSET] != store_action)
    {
        config_data[SINK_BA_SWITCH_ACTION_OFFSET] = store_action;
        broadcastAudioStoreConfigItem(&config_data[0]);
    }
}

/*******************************************************************************
NAME
    broadcastAudioDetermineSwitchAction().

DESCRIPTION
    This interface is used to determine the switch action based on the requested mode change request

 PARAMS
    sink_ba_app_mode_t requested_mode to switch

 RETURNS
    sink_ba_stored_action_t switch action
*/
static sink_ba_stored_action_t broadcastAudioDetermineSwitchAction(sink_ba_app_mode_t requested_mode)
{
    sink_ba_app_mode_t current_app_mode;
    sink_ba_stored_action_t mode_action = sink_start_as_normal;

    current_app_mode = broadcastAudioGetRequestedMode();

    if(current_app_mode != requested_mode)
    {
            /* Switching from normal/receiver mode to broadcaster */
        if(requested_mode == sink_ba_appmode_broadcaster)
        {
            mode_action = sink_switch_to_broadcaster;
        }
        else if(requested_mode == sink_ba_appmode_receiver)
        {
            /* Switching from normal/broadcaster mode to receiver */
            mode_action = sink_switch_to_receiver;
        }
        else if(requested_mode == sink_ba_appmode_normal)
        {
            /* Switching from broadcaster/receiver to normal mode */
            mode_action = sink_switch_to_normal;
        }
    }
    return mode_action;
}

/***************************************************************************
NAME
    broadcastAudioCheckRetainableMode
 
DESCRIPTION
    Checks whether BA mode is non sticky,if it is then clears off the PS data. 
    So that after cold reset BA Mode will fall back to Normal Mode 
 
PARAMS
    None
RETURNS
    void
*/
static void broadcastAudioCheckRetainableMode(void)
{
    if(!isBAModeRetainable())
    {
        uint16 config_data[SINK_BA_CONFIG_ITEMS];
        memset(&config_data,0,sizeof(config_data));
        broadcastAudioGetDefaultConfig(config_data); 
        broadcastAudioStoreConfigItem(config_data);
    }
}

/*******************************************************************************/
static bool broadcastAudioIsModeValid(sink_ba_app_mode_t mode)
{
    bool valid = FALSE;
    
    switch(mode)
    {
        case sink_ba_appmode_normal:
        case sink_ba_appmode_broadcaster:
        case sink_ba_appmode_receiver:
            valid = TRUE;
            break;
        default:
            break;
    }
    return valid;
}

/*******************************************************************************/
static bool broadcastAudioAllowModeChange(sink_ba_app_mode_t mode)
{
    if( stateManagerGetState() != deviceLimbo )
    {
        /* If we are already in the process of mode switching or the switch request
            role is the existing role, then reject the request
        */
        if((BA_DATA.ba_mode != mode) &&
            (!IS_MODE_CHANGE_IN_PROGRESS))
        {
            /* if Call is in progress */
            if(stateManagerGetState() != deviceActiveCallSCO)
               return TRUE;
        }
    }
    return FALSE;
}

/*******************************************************************************/
static bool isModeSwitchToNormal(void)
{
    bool switch_to_normal = FALSE;
    
   if(IS_MODE_CHANGE_IN_PROGRESS && 
      (broadcastAudioGetRequestedMode() == sink_ba_appmode_normal))
        switch_to_normal = TRUE;

    return switch_to_normal;
}

/*******************************************************************************/
static void broadcastAudioStart(void)
{
    /* Init Broadcaster/Receiver */
    sinkBroadcastAudioInit();
    sinkBroadcastAudioPowerOn();
}

/*******************************************************************************/
static void broadcastAudioSwitchMode(sink_ba_app_mode_t requested_mode)
{
    switch(requested_mode)
    {
        case sink_ba_appmode_normal:
            {
                if(BA_RECEIVER_MODE_ACTIVE)
                {
                    /* De-Init Receiver */
                   sinkReceiverDeInit();
                }
                else if(BA_BROADCASTER_MODE_ACTIVE)
                {
                    /*De-Init Broadcaster*/
                    sinkBroadcasterDeInit();
                }
                audioUpdateAudioRouting();
            }
            break;
        case sink_ba_appmode_broadcaster:
            {
                if(BA_RECEIVER_MODE_ACTIVE)
                {
                    sinkReceiverDeleteBroadcasterInfo();
                    /* De-Init Receiver */
                    sinkReceiverDeInit();
                }
                else
                {
                    /* Set New mode as Broadcaster */
                    sinkBroadcastAudioSetMode(requested_mode);
                    broadcastAudioStart();
                }

                sinkA2dpRestrictSupportedCodecs(sinkBroadcastAudioGetOptionalCodecsMask());
                sinkA2dpRenegotiateCodecsForAllSources();

                audioUpdateAudioRouting();
            }
            break;
        case sink_ba_appmode_receiver:
            {
                if(BA_BROADCASTER_MODE_ACTIVE)
                    sinkBroadcasterDeInit();
                else
                {
                    /* Set New mode as Receiver */
                    sinkBroadcastAudioSetMode(requested_mode);
                    /* Init Receiver */
                    broadcastAudioStart();
                }
            }
            break;
        default:
            break;
    }
}

/*--------------------Interfaces to BA Module----------------------*/

/*******************************************************************************/
void sinkBroadcastAudioHandlePrompts(MessageId event)
{
    switch(event)
    {
        case EventSysBaSwitchToSpeaker:
            /* Initiate a Gracefull power off of the system and play switch prompt */
            broadcastAudioIndicatePrompt(event);
            break;

        case EventUsrPowerOff:
            broadcastAudioIndicatePrompt(EventUsrPowerOff);
            MessageSend(sinkGetMainTask(), EventUsrPowerOff, 0);
            break;

        default:
            break;
    }
}

/*******************************************************************************/
void sinkBaUpdatePowerOnAction(void)
{
    sink_ba_stored_action_t power_on_store_action = sink_start_as_normal;

    switch(broadcastAudioGetStoredAction())
    {
        case sink_switch_to_broadcaster:
        case sink_start_as_broadcaster:
        case sink_power_off_broadcaster:
            power_on_store_action = sink_start_as_broadcaster;
            break;

        case sink_switch_to_receiver:
        case sink_start_as_receiver:
        case sink_power_off_receiver:
            power_on_store_action = sink_start_as_receiver;
            break;

        case sink_switch_to_normal:
        case sink_start_as_normal:
            power_on_store_action = sink_start_as_normal;
            break;

        default:
            break;
    }
    broadcastAudioSetStoredAction(power_on_store_action);
}

/*******************************************************************************/
bool isPowerOnInBroadcastMode(void)
{
    bool handle_power_on = FALSE;
    sink_ba_stored_action_t power_off_action = broadcastAudioGetStoredAction();

    if(sinkBroadcastAudioIsActive())
    {
        /* Check if the power off was in BA mode, only then handle power on in BA mode */
        if((power_off_action == sink_power_off_broadcaster) || (power_off_action == sink_power_off_receiver) ||
           /* There could have been reset so if power-on after reset just play the prompt */
           (power_off_action == sink_start_as_broadcaster) || (power_off_action == sink_start_as_receiver))
            handle_power_on = TRUE;
    }
    return handle_power_on;
}

/*******************************************************************************/
void sinkBroadcastAudioHandleUserPowerOn(void)
{
    if(isPowerOnInBroadcastMode())
    {
        sinkBaUpdatePowerOnAction();
        /* Handle user power on in BA mode, let the power on Prompt complete (approx ~1 Sec)
            after which BA power on shall be triggered.
        */
        sinkBroadcastAudioPowerOn();
    }
    else
    {
        sinkBaUpdatePowerOnAction();
        /* Power On broadcast audio */
        sinkBroadcastAudioPowerOn();
    }
}

/*******************************************************************************/
bool isPowerOffInBroadcastMode(void)
{
    bool handle_power_off = FALSE;
    sink_ba_stored_action_t stored_action = broadcastAudioGetStoredAction();

    if (sinkBroadcastAudioIsActive())
    {
        /* Check if this was a power off while in BA mode */
        if((stored_action == sink_start_as_broadcaster) || (stored_action == sink_start_as_receiver))
            handle_power_off = TRUE;
    }
    return handle_power_off;
}
/*******************************************************************************/
void sinkBroadcastAudioPowerOff(void)
{
    if (sinkBroadcastAudioIsActive())
    {
        /* If broadcast audio is in the process of mode change no need to handle
         power off request, power off of broadcst audio must be already handled
         */
        if(!IS_MODE_CHANGE_IN_PROGRESS)
            broadcastAudioPowerOff();
    }
}

/*******************************************************************************/
void sinkBroadcastAudioVolumeUp(void)
{
} 

/*******************************************************************************/
void sinkBroadcastAudioVolumeDown(void)
{
}

/*******************************************************************************/
void sinkBroadcastAudioStartAssociation(void)
{
    if(BA_RECEIVER_MODE_ACTIVE)
    {
       DEBUG_BA(("BA: Start Association for receiver\n" ));
       sinkReceiverStartAssociation();
    }
    /* Call the BLE module to take care of the event */
    sinkBleAssociationEvent();
}

/*******************************************************************************/
Task sinkBroadcastAudioGetAppTask(void)
{
    return (&BA_DATA.baAppTask);
}

/*******************************************************************************/
void sinkBroadcastAudioHandleInitCfm(void)
{
    if(IS_MODE_CHANGE_IN_PROGRESS)
    {
        DEBUG_BA(("BA: sinkBroadcastAudioHandleInitCfm(): Mode = %d \n", sinkBroadcastAudioGetMode()));
        /* This initialization is due to mode switch */
        BA_DATA.modeswitch_inprogress  = FALSE;
    }
    else
    {
        /* Initialization in BA mode upon boot up */
    }
}

/*******************************************************************************/
void sinkBroadcastAudioHandleDeInitCfm(sink_ba_app_mode_t mode)
{
    if(IS_MODE_CHANGE_IN_PROGRESS)
    {
        sink_ba_app_mode_t next_mode = broadcastAudioGetRequestedMode();
        /* Set New mode */
        sinkBroadcastAudioSetMode(next_mode);

        /* This initialization was due to mode switch */
        if(mode != next_mode)
        {
            if(next_mode == sink_ba_appmode_normal)
            {
                /* Switching from BA to normal mode */
                BA_DATA.modeswitch_inprogress = FALSE;
                /*Indicate on LED that we came out of BA Mode */
                MessageSend(sinkGetMainTask(), EventSysBAModeIndicationEnd, NULL );
            }
            else
            {
                /* Initialize Broadcaster/reciever */
                broadcastAudioStart();
            }
        }
    }
    else
    {
        /* Initialization in BA mode upon boot up */
    }
}

/*******************************************************************************/
void sinkBroadcastAudioInit(void)
{
    DEBUG_BA(("BA: sinkBroadcastAudioInit(): Mode = %s \n", ba_modes[sinkBroadcastAudioGetMode()]));
    /* Check if we are in proper BA role before initialising the lib */
    switch(sinkBroadcastAudioGetMode())
    {
        case sink_ba_appmode_broadcaster:
            {
                /* Initialise Broadcaster task handler */
                BA_DATA.baAppTask.handler = BroadcasterMessageHandler;
                /* Initialize the Broadcaster */
                (void)sinkBroadcasterInit(&BA_DATA.baAppTask);
            }
            break;
        case sink_ba_appmode_receiver:
            {
                /* Initialise Broadcaster task handler */
                BA_DATA.baAppTask.handler = ReceiverMessageHandler;
                /* Init receiver */
                sinkReceiverInit(&BA_DATA.baAppTask);
            }
            break;

        default:
            return;
    }

    broadcastAudioCheckRetainableMode();
    /*Indicate on LED that we are in BA Mode */
    MessageSend(sinkGetMainTask(), EventSysBAModeIndicationStart, NULL ) ;

}

/*******************************************************************************/
bool sinkBroadcastAudioIsActive(void)
{
    return (BA_DATA.ba_mode != sink_ba_appmode_normal);
}

/*******************************************************************************/
void sinkBroadcastAudioConfigure(void)
{
    uint16 config_data[SINK_BA_CONFIG_ITEMS];

    DEBUG_BA(("BA: sinkBroadcastAudioConfigure()\n"));
    /* Reset BA global data */
    broadcastAudioResetData();
    /* Read the mode configuration */
    broadcastAudioReadConfigItem(config_data);
    /* Store the Mode for future use */
    BA_DATA.ba_mode = config_data[SINK_BA_MODE_OFFSET];

    /* Validate mode */
    PanicFalse(broadcastAudioIsModeValid(BA_DATA.ba_mode));
    
    /*If BA mode is non sticky,then clear off the PS data. After cold reset
    BA Mode will fall back to Normal Mode */
    if(!isBAModeRetainable())
    {
        memset(&config_data,0,sizeof(config_data));
        broadcastAudioGetDefaultConfig(config_data); 
        broadcastAudioStoreConfigItem(config_data);
    }
    
    DEBUG_BA(("BA: Broadcast Audio Configured with Mode [%s] \n",ba_modes[BA_DATA.ba_mode]));
}

/*******************************************************************************/
void sinkBroadcastAudioSetMasterRole( uint16 device_id)
{
    if(BA_BROADCASTER_MODE_ACTIVE)
        sinkBroadcasterSetMasterRole(device_id);
}

/*******************************************************************************/
sink_ba_app_mode_t sinkBroadcastAudioGetMode(void)
{
    DEBUG_BA(("BA: sinkBroadcastAudioGetMode(), Mode [%s] \n",ba_modes[BA_DATA.ba_mode]));
    return BA_DATA.ba_mode;
}

/*******************************************************************************/
void sinkBroadcastAudioSetMode(sink_ba_app_mode_t mode)
{
    DEBUG_BA(("BA: sinkBaSetBroadcastMode(), Mode %s \n",ba_modes[mode]));
    BA_DATA.ba_mode = mode;
}

/*******************************************************************************/
bool sinkBroadcastAudioChangeMode(sink_ba_app_mode_t mode)
{
    bool result = FALSE;
    uint16 config_data[SINK_BA_CONFIG_ITEMS];

    if( broadcastAudioAllowModeChange(mode) )
    {
        /* Mark we are in the process of mode switch */
        BA_DATA.modeswitch_inprogress = TRUE;

        /* If association is in progress then cancel before we leave BA mode */
        if(gapBaGetAssociationInProgress())
            sinkBleCancelAssociationEvent();

        /* First disconnect routed Audio/Voice source if any */
        audioDisconnectRoutedAudio();
        audioDisconnectRoutedVoice();
                
        /* Store the requested mode to PS store */
        config_data[SINK_BA_MODE_OFFSET] = mode;
        /* Store the switch action to PS store */
        config_data[SINK_BA_SWITCH_ACTION_OFFSET] = broadcastAudioDetermineSwitchAction(mode);

        if(broadcastAudioStoreConfigItem(&config_data[0]))
        {
            broadcastAudioSwitchMode(mode);
        }
        result = TRUE;
    }
    return result;
}

/*******************************************************************************/
Task sinkBroadcastAudioGetHandler(void)
{
    return &BA_DATA.baAppTask;
}

/*******************************************************************************/
void sinkBroadcastAudioPowerOn(void)
{
    DEBUG_BA(("BA: Broadcast Audio Power On \n"));
    if(BA_BROADCASTER_MODE_ACTIVE)
    {
        sinkBroadcasterHandlePowerOn(&BA_DATA.baAppTask);
    }
    else if(BA_RECEIVER_MODE_ACTIVE)
    {
        sinkReceiverHandlePowerOn(&BA_DATA.baAppTask);
    }
}

/*******************************************************************************/
uint8 sinkBroadcastAudioGetOptionalCodecsMask(void)
{
    uint8 mask = 1 << AAC_CODEC_BIT;

    return mask;
}

/*******************************************************************************/
uint16 sinkBroadcastAudioGetAssociationTimeOut(void)
{
    ba_config_def_t* ro_config_data = NULL;
    /* Let's have default timer value of 30 seconds */
    uint16 assoc_timeout = SINK_BA_ASSOCIATION_TIME_OUT;

    if (configManagerGetReadOnlyConfig(BA_CONFIG_BLK_ID, (const void **)&ro_config_data))
    {
        assoc_timeout = ro_config_data->assoc_timeout_s;
        configManagerReleaseConfig(BA_CONFIG_BLK_ID);
    }
    return assoc_timeout;
}

/*******************************************************************************/
bool sinkBroadcatAudioAllowEvent(sinkEvents_t event)
{
    bool allow_event = TRUE;

    /* check if any switch is taking place */
    switch(broadcastAudioGetStoredAction())
    {
        /* fall thru cases, when Audio prompt is busy */
        case sink_switch_to_receiver:
        case sink_switch_to_broadcaster:
        case sink_switch_to_normal:
            /* Just allow User Power-On and off events */
            if((event != EventUsrPowerOn) && (event != EventUsrPowerOff))
                allow_event = FALSE;
            break;
            
        default:
            break;
    }

    return allow_event;
}

/***************************************************************************
NAME
    setupReceiverAudio
 
DESCRIPTION
    Utility function to Connect DSP to DACs
 
PARAMS
    rate Sampling Frequency
 
RETURNS
    void
*/
static void audioGetVolumeInfoFromSource(audio_sources source, volume_info *volume)
{
    switch(source)
    {  
        case audio_source_ANALOG:
        case audio_source_I2S:
            SinkWiredGetAnalogVolume(volume);
            break;

        case audio_source_USB:
            sinkUsbGetUsbVolume(volume);
            break;
        case audio_source_a2dp_1:
            *volume = *sinkA2dpGetA2dpVolumeInfoAtIndex(a2dp_primary);
            break;
        case audio_source_a2dp_2:
            *volume = *sinkA2dpGetA2dpVolumeInfoAtIndex(a2dp_secondary);
            break;
        case audio_source_none:
        default:
            memset(volume, 0, sizeof(*volume));
            break;
    }
}

/***************************************************************************
NAME
    getSystemGainFromMaster
 
DESCRIPTION
    Utility function to get system gain from Master (digital) gain
 
PARAMS
    volume Volume in DB
 
RETURNS
    uint16 Gain
*/
static uint16 getSystemGainFromMaster(int16 master)
{
    int16 system = 0;
    int16 ba_offset = 0;
    /* Convert dB master volume to DAC based system volume */
    int16 normal_mode_system_step = (CODEC_STEPS + (master / DB_TO_DAC));

    if(normal_mode_system_step > 0)
    {
        /* BA offset is always 2 times as it ranges from 0-31 */
        ba_offset = (CODEC_STEPS - normal_mode_system_step) * 2;
        system = BA_MAX_STEPS - ba_offset;
    }

    DEBUG_BA(("BA System Volume level %d\n", system));
   
    return (uint16)system;
}

/*******************************************************************************/
int16 sinkBroadcastAudioGetVolume(audio_sources audio_source)
{
    volume_info volume;
    int16 master_volume_in_db;

    audioGetVolumeInfoFromSource(audio_source, &volume);
    
    /* Set current volume */
    master_volume_in_db = sinkVolumeGetVolInDb(volume.main_volume, audio_output_group_main);
    return (getSystemGainFromMaster(master_volume_in_db));
}

/*******************************************************************************/
bool useBroadcastPlugin( void )
{
    bool broadcast_plugin = FALSE;
    if((sinkBroadcastAudioGetMode() == sink_ba_appmode_broadcaster) && sinkBroadcastAudioIsActive())
    {
        broadcast_plugin = TRUE;
    }
    return broadcast_plugin;
}

/*****************************************************************************/
uint16 SinkBroadcasAudioGetA2dpLatency( void )
{
    /* returns the a2dp delay for broadcast audio */
    return (BA_A2DP_LATENCY_MS * 10);
}

/*******************************************************************************/
void sinkBroadcastAudioStopIVAdvertsAndScan(void)
{
    /* Defer stoping of IV adverts/scanning until de-init of broadcast library is complete */
    if(isModeSwitchToNormal())
    {
        MessageId id = BROADCASTER_INTERNAL_MSG_STOP_BLE_BROADCAST;
        if(BA_RECEIVER_MODE_ACTIVE)
            id = RECEIVER_INTERNAL_MSG_STOP_BLE_BROADCAST;
        MessageSendConditionally(&BA_DATA.baAppTask, id, NULL, &BA_DATA.modeswitch_inprogress);
    }        
    else
    {
        /* so stop advertising/scanning the IV */
        sinkBleStopBroadcastEvent();
    }
}

void SinkBroadcastAudioHandlePluginUpStreamMessage(Task task, MessageId id, Message message)
{
    if(BA_RECEIVER_MODE_ACTIVE)
    {
        sinkReceiverUpStreamMsgHandler(task, id, message);
    }
    /* Broadcaster too will handle up stream messages in future */
}

static bool isSeidSupported(uint16 seid)
{
    /* SBC is always supported */
    if(seid == SBC_SEID)
    {
        return TRUE;
    }

    if(sinkBroadcastAudioGetOptionalCodecsMask() & sinkA2dpGetCodecBitMaskFromSeid(seid))
    {
        return TRUE;
    }

    return FALSE;
}

bool sinkBroadcastIsA2dpCodecSupported(uint16 a2dp_source_index)
{
    if(sink_ba_appmode_broadcaster == sinkBroadcastAudioGetMode())
    {
        if(!isSeidSupported(getA2dpLinkDataSeId(a2dp_source_index)))
        {
            return FALSE;
        }
    }
    return TRUE;
}

bool sinkBroadcastIsReadyForRouting(void)
{
    /* In the brodcaster mode presence of sink indicates that
       broadcaster is ready for streaming.
     */
    if(sink_ba_appmode_broadcaster == sinkBroadcastAudioGetMode())
    {
        if(BroadcastContextGetSink() == NULL)
        {
            return FALSE;
        }
    }
    return TRUE;
}

void baAudioPostRoutingAudioConfiguration(void)
{
    DEBUG_BA(("BA: baAudioPostRoutingAudioConfiguration\n"));

    if(!sinkAudioIsAudioRouted() && !sinkAudioIsVoiceRouted())
    {
        DEBUG_BA(("nothing is routed\n"));

        if (BA_BROADCASTER_MODE_ACTIVE)
        {
            /* If we are powering off, stop broadcasting */
            if (sink_power_off_broadcaster == broadcastAudioGetStoredAction())
            {
                DEBUG_BA(("Sending stop broadcaster\n"));
                MessageSendConditionally(&BA_DATA.baAppTask,
                                         BROADCASTER_INTERNAL_MSG_STOP_BROADCASTER,
                                         NULL, BroadcastContextGetBroadcastBusy());
            }
        }
        else if (BA_RECEIVER_MODE_ACTIVE)
        {
            /* If we are powering off, stop receiving */
            if (sink_power_off_receiver == broadcastAudioGetStoredAction())
            {
                DEBUG_BA(("Sending stop receiver\n"));
                MessageSendConditionally(&BA_DATA.baAppTask,
                                         RECEIVER_INTERNAL_MSG_STOP_RECEIVER,
                                         NULL, BroadcastContextGetBroadcastBusy());
            }
            else if (!sinkReceiverIsRoutable()
                && (deviceLimbo != stateManagerGetState()))
            {
                /* Unless the sink has powered off,
                   re-start the broadcast receiver. */
                DEBUG_BA(("start receiver\n"));
                sinkReceiverStartReceiver();
            }
        }
    }
    else if(sinkAudioIsAudioRouted())
    {
        DEBUG_BA(("some audio is routed\n"));
    }
    else if(sinkAudioIsVoiceRouted())
    {
        DEBUG_BA(("voice is routed\n"));
    }
}

void sinkBroadcastAcquireVolumeTable(void)
{
    ba_volume_readonly_config_def_t *ro_config = NULL;

    if(configManagerGetReadOnlyConfig(BA_VOLUME_READONLY_CONFIG_BLK_ID, (const void **)&ro_config))
    {
        BroadcastContextSetVolumeTable((int16 *)ro_config->ba_volume_array);
    }
}

void sinkBroadcastReleaseVolumeTable(void)
{
    BroadcastContextSetVolumeTable(NULL);
    configManagerReleaseConfig(BA_VOLUME_READONLY_CONFIG_BLK_ID);
}

bool sinkBroadcastAudioIsModeChangeInProgress(void)
{
    return IS_MODE_CHANGE_IN_PROGRESS;
}

#endif /* ENABLE_BROADCAST_AUDIO */

