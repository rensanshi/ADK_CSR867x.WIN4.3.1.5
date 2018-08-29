/****************************************************************************
Copyright (c) 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    ahi_test.c

DESCRIPTION
    Application module that handles AHI related operations. For example:

    Intercepting events and echoing them back to the Host when running
    automated tests.

*/

#include <a2dp.h>
#include <avrcp.h>
#include <connection.h>
#include <hfp.h>
#include <message.h>

#include "ahi.h"
#include "ahi_test.h"


#ifdef ENABLE_AHI_TEST_WRAPPER

#define MESSAGE_SIZE(msg_id) (sizeof(msg_id##_T))

/* All the message sizes will be < 256 so we can pack two per uint16. */
#define PACK16(hi_byte,lo_byte) ((((hi_byte) & 0xFF) << 8) | ((lo_byte) & 0xFF))

#define UINT16_HI(value) (((value) >> 8) & 0xFF)
#define UINT16_LO(value) ((value) & 0xFF)
#define UNPACK16(idx,array) (((idx) & 0x1) ? UINT16_LO((array)[(idx)/2]) : UINT16_HI((array)[(idx)/2]))


static void sendMessageToAhi(uint16 index, const uint16* table, uint16 id, const uint8 *data)
{
    uint16 size = UNPACK16(index, table);

    AhiTestReportEvent(id, (size ? data : 0), size);
}


static const uint16 connection_table[] = {
/* 0x5000 */    PACK16(MESSAGE_SIZE(CL_INIT_CFM),
/* 0x5001 */           MESSAGE_SIZE(CL_DM_ROLE_CFM)),
/* 0x5002 */    PACK16(MESSAGE_SIZE(CL_DM_ROLE_IND),
/* 0x5003 */           MESSAGE_SIZE(CL_DM_LINK_SUPERVISION_TIMEOUT_IND)),
/* 0x5004 */    PACK16(MESSAGE_SIZE(CL_DM_SNIFF_SUB_RATING_IND),

/* 0x5005 */           MESSAGE_SIZE(CL_DM_INQUIRE_RESULT)),
/* 0x5006 */    PACK16(MESSAGE_SIZE(CL_DM_REMOTE_NAME_COMPLETE),
/* 0x5007 */           MESSAGE_SIZE(CL_DM_LOCAL_NAME_COMPLETE)),
/* 0x5008 */    PACK16(MESSAGE_SIZE(CL_DM_READ_INQUIRY_TX_CFM),
/* 0x5009 */           MESSAGE_SIZE(CL_DM_READ_TX_POWER_CFM)),
/* 0x500A */    PACK16(MESSAGE_SIZE(CL_DM_CLASS_OF_DEVICE_CFM),

/* 0x500B */           MESSAGE_SIZE(CL_DM_SYNC_REGISTER_CFM)),
/* 0x500C */    PACK16(MESSAGE_SIZE(CL_DM_SYNC_UNREGISTER_CFM),
/* 0x500D */           MESSAGE_SIZE(CL_DM_SYNC_CONNECT_CFM)),
/* 0x500E */    PACK16(MESSAGE_SIZE(CL_DM_SYNC_CONNECT_IND),
/* 0x500F */           MESSAGE_SIZE(CL_DM_SYNC_DISCONNECT_IND)),
/* 0x5010 */    PACK16(MESSAGE_SIZE(CL_DM_SYNC_RENEGOTIATE_IND),
    
/* 0x5011 */           MESSAGE_SIZE(CL_DM_LOCAL_BD_ADDR_CFM)),
/* 0x5012 */    PACK16(MESSAGE_SIZE(CL_DM_LINK_QUALITY_CFM),
/* 0x5013 */           MESSAGE_SIZE(CL_DM_RSSI_CFM)),
/* 0x5014 */    PACK16(MESSAGE_SIZE(CL_DM_RSSI_BDADDR_CFM),
/* 0x5015 */           MESSAGE_SIZE(CL_DM_REMOTE_FEATURES_CFM)),
/* 0x5016 */    PACK16(MESSAGE_SIZE(CL_DM_LOCAL_VERSION_CFM),
/* 0x5017 */           MESSAGE_SIZE(CL_DM_REMOTE_VERSION_CFM)),
/* 0x5018 */    PACK16(MESSAGE_SIZE(CL_DM_CLOCK_OFFSET_CFM),
/* 0x5019 */           MESSAGE_SIZE(CL_DM_READ_BT_VERSION_CFM)),
/* 0x501A */    PACK16(MESSAGE_SIZE(CL_DM_ACL_OPENED_IND),
/* 0x501B */           MESSAGE_SIZE(CL_DM_ACL_CLOSED_IND)),
/* 0x501C */    PACK16(MESSAGE_SIZE(CL_DM_APT_IND),
/* 0x501D */           MESSAGE_SIZE(CL_DM_READ_APT_CFM)),
/* 0x501E */    PACK16(MESSAGE_SIZE(CL_DM_WRITE_APT_CFM),

/* 0x501F */           0 /*MESSAGE_SIZE(CL_SM_INIT_CFM)*/),
/* 0x5020 */    PACK16(MESSAGE_SIZE(CL_SM_REGISTER_OUTGOING_SERVICE_CFM),
/* 0x5021 */           MESSAGE_SIZE(CL_SM_READ_LOCAL_OOB_DATA_CFM)),
/* 0x5022 */    PACK16(MESSAGE_SIZE(CL_SM_AUTHENTICATE_CFM),
/* 0x5023 */           MESSAGE_SIZE(CL_SM_SECURITY_LEVEL_CFM)),
/* 0x5024 */    PACK16(MESSAGE_SIZE(CL_SM_SEC_MODE_CONFIG_CFM),
/* 0x5025 */           MESSAGE_SIZE(CL_SM_PIN_CODE_IND)),
/* 0x5026 */    PACK16(MESSAGE_SIZE(CL_SM_IO_CAPABILITY_REQ_IND),
/* 0x5027 */           MESSAGE_SIZE(CL_SM_REMOTE_IO_CAPABILITY_IND)),
/* 0x5028 */    PACK16(MESSAGE_SIZE(CL_SM_USER_CONFIRMATION_REQ_IND),
/* 0x5029 */           MESSAGE_SIZE(CL_SM_USER_PASSKEY_REQ_IND)),
/* 0x502A */    PACK16(MESSAGE_SIZE(CL_SM_USER_PASSKEY_NOTIFICATION_IND),
/* 0x502B */           MESSAGE_SIZE(CL_SM_KEYPRESS_NOTIFICATION_IND)),
/* 0x502C */    PACK16(MESSAGE_SIZE(CL_SM_AUTHORISE_IND),
/* 0x502D */           MESSAGE_SIZE(CL_SM_ENCRYPT_CFM)),
/* 0x502E */    PACK16(MESSAGE_SIZE(CL_SM_ENCRYPTION_KEY_REFRESH_IND),
/* 0x502F */           MESSAGE_SIZE(CL_SM_ENCRYPTION_CHANGE_IND)),

/* 0x5030 */    PACK16(MESSAGE_SIZE(CL_SDP_REGISTER_CFM),
/* 0x5031 */           MESSAGE_SIZE(CL_SDP_UNREGISTER_CFM)),
/* 0x5032 */    PACK16(MESSAGE_SIZE(CL_SDP_OPEN_SEARCH_CFM),
/* 0x5033 */           MESSAGE_SIZE(CL_SDP_CLOSE_SEARCH_CFM)),
/* 0x5034 */    PACK16(MESSAGE_SIZE(CL_SDP_SERVICE_SEARCH_CFM),
/* 0x5035 */           MESSAGE_SIZE(CL_SDP_SERVICE_SEARCH_REF_CFM)),
/* 0x5036 */    PACK16(MESSAGE_SIZE(CL_SDP_ATTRIBUTE_SEARCH_CFM),
/* 0x5037 */           MESSAGE_SIZE(CL_SDP_ATTRIBUTE_SEARCH_REF_CFM)),
/* 0x5038 */    PACK16(MESSAGE_SIZE(CL_SDP_SERVICE_SEARCH_ATTRIBUTE_CFM),
/* 0x5039 */           MESSAGE_SIZE(CL_SDP_SERVICE_SEARCH_ATTRIBUTE_REF_CFM)),

/* 0x503A */    PACK16(MESSAGE_SIZE(CL_L2CAP_REGISTER_CFM),
/* 0x503B */           MESSAGE_SIZE(CL_L2CAP_UNREGISTER_CFM)),
/* 0x503C */    PACK16(MESSAGE_SIZE(CL_L2CAP_CONNECT_CFM),
/* 0x503D */           MESSAGE_SIZE(CL_L2CAP_CONNECT_IND)),
/* 0x503E */    PACK16(MESSAGE_SIZE(CL_L2CAP_MAP_CONNECTIONLESS_CFM),
/* 0x503F */           MESSAGE_SIZE(CL_L2CAP_MAP_CONNECTIONLESS_IND)),
/* 0x5040 */    PACK16(MESSAGE_SIZE(CL_L2CAP_UNMAP_CONNECTIONLESS_IND),
/* 0x5041 */           MESSAGE_SIZE(CL_L2CAP_DISCONNECT_IND)),
/* 0x5042 */    PACK16(MESSAGE_SIZE(CL_L2CAP_DISCONNECT_CFM),
/* 0x5043 */           MESSAGE_SIZE(CL_L2CAP_TIMEOUT_IND)),

/* 0x5044 */    PACK16(MESSAGE_SIZE(CL_RFCOMM_REGISTER_CFM),
/* 0x5045 */           MESSAGE_SIZE(CL_RFCOMM_UNREGISTER_CFM)),
/* 0x5046 */    PACK16(MESSAGE_SIZE(CL_RFCOMM_CLIENT_CONNECT_CFM),
/* 0x5047 */           MESSAGE_SIZE(CL_RFCOMM_SERVER_CONNECT_CFM)),
/* 0x5048 */    PACK16(MESSAGE_SIZE(CL_RFCOMM_CONNECT_IND),
/* 0x5049 */           MESSAGE_SIZE(CL_RFCOMM_DISCONNECT_IND)),
/* 0x504A */    PACK16(MESSAGE_SIZE(CL_RFCOMM_DISCONNECT_CFM),
/* 0x504B */           MESSAGE_SIZE(CL_RFCOMM_PORTNEG_IND)),
/* 0x504C */    PACK16(MESSAGE_SIZE(CL_RFCOMM_PORTNEG_CFM),
/* 0x504D */           MESSAGE_SIZE(CL_RFCOMM_CONTROL_IND)),
/* 0x504E */    PACK16(MESSAGE_SIZE(CL_RFCOMM_CONTROL_CFM),
/* 0x504F */           MESSAGE_SIZE(CL_RFCOMM_LINE_STATUS_IND)),
/* 0x5050 */    PACK16(MESSAGE_SIZE(CL_RFCOMM_LINE_STATUS_CFM),

/* 0x5051 */           0 /*MESSAGE_SIZE(CL_DM_LINK_POLICY_IND)*/),
/* 0x5052 */    PACK16(MESSAGE_SIZE(CL_DM_DUT_CFM),
/* 0x5053 */           MESSAGE_SIZE(CL_DM_MODE_CHANGE_EVENT)),
/* 0x5054 */    PACK16(MESSAGE_SIZE(CL_DM_WRITE_INQUIRY_ACCESS_CODE_CFM),
/* 0x5055 */           MESSAGE_SIZE(CL_DM_WRITE_INQUIRY_MODE_CFM)),
/* 0x5056 */    PACK16(MESSAGE_SIZE(CL_DM_READ_INQUIRY_MODE_CFM),
/* 0x5057 */           MESSAGE_SIZE(CL_DM_READ_EIR_DATA_CFM)),

/* 0x5058 */    PACK16(MESSAGE_SIZE(CL_SM_GET_ATTRIBUTE_CFM),
/* 0x5059 */           MESSAGE_SIZE(CL_SM_GET_INDEXED_ATTRIBUTE_CFM)),
/* 0x505A */    PACK16(MESSAGE_SIZE(CL_SM_ADD_AUTH_DEVICE_CFM),
/* 0x505B */           MESSAGE_SIZE(CL_SM_GET_AUTH_DEVICE_CFM)),
/* 0x505C */    PACK16(MESSAGE_SIZE(CL_SM_SET_TRUST_LEVEL_CFM),

/* 0x505D */           MESSAGE_SIZE(CL_DM_REMOTE_EXTENDED_FEATURES_CFM)),

/* 0x505E */    PACK16(MESSAGE_SIZE(CL_DM_BLE_ADVERTISING_REPORT_IND),
/* 0x505F */           MESSAGE_SIZE(CL_DM_BLE_SET_ADVERTISING_DATA_CFM)),
/* 0x5060 */    PACK16(MESSAGE_SIZE(CL_DM_BLE_SET_ADVERTISING_PARAMS_CFM),
/* 0x5061 */           MESSAGE_SIZE(CL_DM_BLE_SECURITY_CFM)),
/* 0x5062 */    PACK16(MESSAGE_SIZE(CL_DM_BLE_SET_CONNECTION_PARAMETERS_CFM),
/* 0x5063 */           MESSAGE_SIZE(CL_DM_BLE_CONNECTION_PARAMETERS_UPDATE_CFM)),
/* 0x5064 */    PACK16(MESSAGE_SIZE(CL_DM_BLE_SET_SCAN_PARAMETERS_CFM),
/* 0x5065 */           MESSAGE_SIZE(CL_DM_BLE_SET_SCAN_RESPONSE_DATA_CFM)),
/* 0x5066 */    PACK16(MESSAGE_SIZE(CL_DM_BLE_READ_WHITE_LIST_SIZE_CFM),
/* 0x5067 */           MESSAGE_SIZE(CL_DM_BLE_CLEAR_WHITE_LIST_CFM)),
/* 0x5068 */    PACK16(MESSAGE_SIZE(CL_DM_BLE_ADD_DEVICE_TO_WHITE_LIST_CFM),
/* 0x5069 */           MESSAGE_SIZE(CL_DM_BLE_REMOVE_DEVICE_FROM_WHITE_LIST_CFM)),
/* 0x506A */    PACK16(MESSAGE_SIZE(CL_DM_BLE_CONFIGURE_LOCAL_ADDRESS_CFM),
/* 0x506B */           MESSAGE_SIZE(CL_DM_BLE_ACCEPT_CONNECTION_PAR_UPDATE_IND)),
/* 0x506C */    PACK16(MESSAGE_SIZE(CL_SM_BLE_SIMPLE_PAIRING_COMPLETE_IND),
/* 0x506D */           MESSAGE_SIZE(CL_DM_BLE_ADVERTISING_PARAM_UPDATE_IND)), 
/* 0x506E */    PACK16(MESSAGE_SIZE(CL_SM_BLE_LINK_SECURITY_IND),
/* Unused */           0)
};

void ahiTestEchoConnectionMessage(MessageId id, Message message)
{
    sendMessageToAhi((id - CL_MESSAGE_BASE), connection_table, id, message);
}


static const uint16 hfp_table[] = {
/* 0x5A00 */    PACK16(MESSAGE_SIZE(HFP_INIT_CFM),
/* Service Level Connection messages */
/* 0x5A01 */           MESSAGE_SIZE(HFP_SLC_CONNECT_CFM)),
/* 0x5A02 */    PACK16(MESSAGE_SIZE(HFP_SLC_CONNECT_IND),
/* 0x5A03 */           MESSAGE_SIZE(HFP_SLC_LINK_LOSS_IND)),
/* 0x5A04 */    PACK16(MESSAGE_SIZE(HFP_SLC_DISCONNECT_IND),
/* Audio messages */
/* 0x5A05 */           MESSAGE_SIZE(HFP_AUDIO_CONNECT_CFM)),
/* 0x5A06 */    PACK16(MESSAGE_SIZE(HFP_AUDIO_CONNECT_IND),
/* 0x5A07 */           MESSAGE_SIZE(HFP_AUDIO_DISCONNECT_IND)),
/* Indicators */
/* 0x5A08 */    PACK16(MESSAGE_SIZE(HFP_SERVICE_IND),
/* 0x5A09 */           MESSAGE_SIZE(HFP_SIGNAL_IND)),
/* 0x5A0A */    PACK16(MESSAGE_SIZE(HFP_ROAM_IND),
/* 0x5A0B */           MESSAGE_SIZE(HFP_BATTCHG_IND)),
/* 0x5A0C */    PACK16(MESSAGE_SIZE(HFP_RING_IND),
/* 0x5A0D */           MESSAGE_SIZE(HFP_CALLER_ID_IND)),
/* Call control */
/* 0x5A0E */    PACK16(MESSAGE_SIZE(HFP_CALL_STATE_IND),
/* 0x5A0F */           MESSAGE_SIZE(HFP_CALL_WAITING_IND)),
/* Dialling */
/* 0x5A10 */    PACK16(MESSAGE_SIZE(HFP_DIAL_LAST_NUMBER_CFM),
/* 0x5A11 */           MESSAGE_SIZE(HFP_DIAL_NUMBER_CFM)),
/* 0x5A12 */    PACK16(MESSAGE_SIZE(HFP_DIAL_MEMORY_CFM),
/* 0x5A13 */           MESSAGE_SIZE(HFP_VOICE_RECOGNITION_ENABLE_CFM)),
/* 0x5A14 */    PACK16(MESSAGE_SIZE(HFP_VOICE_RECOGNITION_IND),
/* Volume controls */
/* 0x5A15 */           MESSAGE_SIZE(HFP_VOLUME_SYNC_SPEAKER_GAIN_IND)),
/* 0x5A16 */    PACK16(MESSAGE_SIZE(HFP_VOLUME_SYNC_MICROPHONE_GAIN_IND),
/* Other */
/* 0x5A17 */           MESSAGE_SIZE(HFP_VOICE_TAG_NUMBER_IND)),
/* 0x5A18 */    PACK16(MESSAGE_SIZE(HFP_UNRECOGNISED_AT_CMD_IND),
/* 0x5A19 */           MESSAGE_SIZE(HFP_EXTRA_INDICATOR_INDEX_IND)),
/* 0x5A1A */    PACK16(MESSAGE_SIZE(HFP_EXTRA_INDICATOR_UPDATE_IND),
/* 0x5A1B */           MESSAGE_SIZE(HFP_SUBSCRIBER_NUMBER_IND)),
/* 0x5A1C */    PACK16(MESSAGE_SIZE(HFP_CURRENT_CALLS_IND),
/* 0x5A1D */           MESSAGE_SIZE(HFP_NETWORK_OPERATOR_IND)),
/* CSR Extended Features */
/* 0x5A1E */    PACK16(MESSAGE_SIZE(HFP_CSR_FEATURES_TEXT_IND),
/* 0x5A1F */           MESSAGE_SIZE(HFP_CSR_FEATURES_NEW_SMS_IND)),
/* 0x5A20 */    PACK16(MESSAGE_SIZE(HFP_CSR_FEATURES_GET_SMS_CFM),
/* 0x5A21 */           MESSAGE_SIZE(HFP_CSR_FEATURES_BATTERY_LEVEL_REQUEST_IND)),
/* Optional confirmation messages */
/* 0x5A22 */    PACK16(MESSAGE_SIZE(HFP_CALLER_ID_ENABLE_CFM),
/* 0x5A23 */           MESSAGE_SIZE(HFP_CALL_ANSWER_CFM)),
/* 0x5A24 */    PACK16(MESSAGE_SIZE(HFP_CALL_TERMINATE_CFM),
/* 0x5A25 */           MESSAGE_SIZE(HFP_CALL_WAITING_ENABLE_CFM)),
/* 0x5A26 */    PACK16(MESSAGE_SIZE(HFP_CALL_HOLD_ACTION_CFM),
/* 0x5A27 */           MESSAGE_SIZE(HFP_RESPONSE_HOLD_ACTION_CFM)),
/* 0x5A28 */    PACK16(MESSAGE_SIZE(HFP_HS_BUTTON_PRESS_CFM),
/* 0x5A29 */           MESSAGE_SIZE(HFP_DTMF_CFM)),
/* 0x5A2A */    PACK16(MESSAGE_SIZE(HFP_SUBSCRIBER_NUMBERS_CFM),
/* 0x5A2B */           MESSAGE_SIZE(HFP_CURRENT_CALLS_CFM)),
/* 0x5A2C */    PACK16(MESSAGE_SIZE(HFP_NETWORK_OPERATOR_CFM),
/* 0x5A2D */           MESSAGE_SIZE(HFP_VOICE_TAG_NUMBER_CFM)),
/* 0x5A2E */    PACK16(MESSAGE_SIZE(HFP_AT_CMD_CFM),

/* Library message limit */
/* HF Indicators Feature */
/* 0x5A2F */           MESSAGE_SIZE(HFP_HF_INDICATORS_REPORT_IND)),
/* 0x5A30 */    PACK16(MESSAGE_SIZE(HFP_HF_INDICATORS_IND), 0)
};

void ahiTestEchoHfpMessage(MessageId id, Message message)
{
    sendMessageToAhi((id - HFP_MESSAGE_BASE), hfp_table, id, message);
}


static const uint16 avrcp_table[] = {
    PACK16(MESSAGE_SIZE(AVRCP_INIT_CFM),        /* 0x5E00 */     
            
    /* Connection/ disconnection management */
           MESSAGE_SIZE(AVRCP_CONNECT_CFM)),                          /* 0x5E01 */
    PACK16(MESSAGE_SIZE(AVRCP_CONNECT_IND),                          /* 0x5E02 */
           MESSAGE_SIZE(AVRCP_DISCONNECT_IND)),                       /* 0x5E03 */
    
    /* AV/C Specific */
    PACK16(MESSAGE_SIZE(AVRCP_PASSTHROUGH_CFM),                      /* 0x5E04 */
           MESSAGE_SIZE(AVRCP_PASSTHROUGH_IND)),                      /* 0x5E05 */
    PACK16(MESSAGE_SIZE(AVRCP_UNITINFO_CFM),                         /* 0x5E06 */
           MESSAGE_SIZE(AVRCP_UNITINFO_IND)),                         /* 0x5E07 */
    PACK16(MESSAGE_SIZE(AVRCP_SUBUNITINFO_IND),                      /* 0x5E08 */ 
           MESSAGE_SIZE(AVRCP_SUBUNITINFO_CFM)),                      /* 0x5E09 */ 
    PACK16(MESSAGE_SIZE(AVRCP_VENDORDEPENDENT_CFM),                  /* 0x5E0A */
           MESSAGE_SIZE(AVRCP_VENDORDEPENDENT_IND)),                  /* 0x5E0B */

    /* AVRCP Metadata transfer extension */
    PACK16(MESSAGE_SIZE(AVRCP_GET_CAPS_CFM),                         /* 0x5E0C */
           MESSAGE_SIZE(AVRCP_GET_CAPS_IND)),                         /* 0x5E0D */
    PACK16(MESSAGE_SIZE(AVRCP_LIST_APP_ATTRIBUTE_CFM),               /* 0x5E0E */
           MESSAGE_SIZE(AVRCP_LIST_APP_ATTRIBUTE_IND)),               /* 0x5E0F */
    PACK16(MESSAGE_SIZE(AVRCP_LIST_APP_VALUE_IND),                   /* 0x5E10 */
           MESSAGE_SIZE(AVRCP_LIST_APP_VALUE_CFM)),                   /* 0x5E11 */
    PACK16(MESSAGE_SIZE(AVRCP_GET_APP_VALUE_CFM),                    /* 0x5E12 */
           MESSAGE_SIZE(AVRCP_GET_APP_VALUE_IND)),                    /* 0x5E13 */
    PACK16(MESSAGE_SIZE(AVRCP_SET_APP_VALUE_CFM),                    /* 0x5E14 */
           MESSAGE_SIZE(AVRCP_SET_APP_VALUE_IND)),                    /* 0x5E15 */
    PACK16(MESSAGE_SIZE(AVRCP_GET_APP_ATTRIBUTE_TEXT_CFM),           /* 0x5E16 */
           MESSAGE_SIZE(AVRCP_GET_APP_ATTRIBUTE_TEXT_IND)),           /* 0x5E17 */
    PACK16(MESSAGE_SIZE(AVRCP_GET_APP_VALUE_TEXT_CFM),               /* 0x5E18 */
           MESSAGE_SIZE(AVRCP_GET_APP_VALUE_TEXT_IND)),               /* 0x5E19 */
    PACK16(MESSAGE_SIZE(AVRCP_GET_ELEMENT_ATTRIBUTES_CFM),           /* 0x5E1A */
           MESSAGE_SIZE(AVRCP_GET_ELEMENT_ATTRIBUTES_IND)),           /* 0x5E1B */
    PACK16(MESSAGE_SIZE(AVRCP_GET_PLAY_STATUS_CFM),                  /* 0x5E1C */
           MESSAGE_SIZE(AVRCP_GET_PLAY_STATUS_IND)),                  /* 0x5E1D */
    PACK16(MESSAGE_SIZE(AVRCP_REGISTER_NOTIFICATION_CFM),            /* 0x5E1E */
           MESSAGE_SIZE(AVRCP_REGISTER_NOTIFICATION_IND)),            /* 0x5E1F */
    PACK16(MESSAGE_SIZE(AVRCP_EVENT_PLAYBACK_STATUS_CHANGED_IND),    /* 0x5E20 */
           MESSAGE_SIZE(AVRCP_EVENT_TRACK_CHANGED_IND)),              /* 0x5E21 */
    PACK16(MESSAGE_SIZE(AVRCP_EVENT_TRACK_REACHED_END_IND),          /* 0x5E22 */
           MESSAGE_SIZE(AVRCP_EVENT_TRACK_REACHED_START_IND)),        /* 0x5E23 */
    PACK16(MESSAGE_SIZE(AVRCP_EVENT_PLAYBACK_POS_CHANGED_IND),       /* 0x5E24 */
           MESSAGE_SIZE(AVRCP_EVENT_BATT_STATUS_CHANGED_IND)),        /* 0x5E25 */
    PACK16(MESSAGE_SIZE(AVRCP_EVENT_SYSTEM_STATUS_CHANGED_IND),      /* 0x5E26 */
           MESSAGE_SIZE(AVRCP_EVENT_PLAYER_APP_SETTING_CHANGED_IND)), /* 0x5E27 */
    PACK16(MESSAGE_SIZE(AVRCP_REQUEST_CONTINUING_RESPONSE_CFM),      /* 0x5E28 */
           MESSAGE_SIZE(AVRCP_ABORT_CONTINUING_RESPONSE_CFM)),        /* 0x5E29 */
    PACK16(MESSAGE_SIZE(AVRCP_NEXT_GROUP_CFM),                       /* 0x5E2A */
           MESSAGE_SIZE(AVRCP_NEXT_GROUP_IND)),                       /* 0x5E2B */
    PACK16(MESSAGE_SIZE(AVRCP_PREVIOUS_GROUP_CFM),                   /* 0x5E2C */
           MESSAGE_SIZE(AVRCP_PREVIOUS_GROUP_IND)),                   /* 0x5E2D */
    PACK16(MESSAGE_SIZE(AVRCP_INFORM_BATTERY_STATUS_CFM),            /* 0x5E2E */
           MESSAGE_SIZE(AVRCP_INFORM_BATTERY_STATUS_IND)),            /* 0x5E2F */
    PACK16(MESSAGE_SIZE(AVRCP_INFORM_CHARACTER_SET_CFM),             /* 0x5E30 */
           MESSAGE_SIZE(AVRCP_INFORM_CHARACTER_SET_IND)),             /* 0x5E31 */
    PACK16(MESSAGE_SIZE(AVRCP_GET_SUPPORTED_FEATURES_CFM),           /* 0x5E32 */
           MESSAGE_SIZE(AVRCP_GET_EXTENSIONS_CFM)),                   /* 0x5E33 */
    PACK16(MESSAGE_SIZE(AVRCP_SET_ABSOLUTE_VOLUME_IND),              /* 0x5E34 */
           MESSAGE_SIZE(AVRCP_SET_ABSOLUTE_VOLUME_CFM)),              /* 0x5E35 */
    PACK16(MESSAGE_SIZE(AVRCP_EVENT_VOLUME_CHANGED_IND),             /* 0x5E36 */

    /* AVRCP Browsing related Messages */
           MESSAGE_SIZE(AVRCP_SET_ADDRESSED_PLAYER_IND)),             /* 0x5E37 */
    PACK16(MESSAGE_SIZE(AVRCP_SET_ADDRESSED_PLAYER_CFM),             /* 0x5E38 */
           MESSAGE_SIZE(AVRCP_PLAY_ITEM_IND)),                         /*0x5E39 */
    PACK16(MESSAGE_SIZE(AVRCP_PLAY_ITEM_CFM),                        /* 0x5E3A */
           MESSAGE_SIZE(AVRCP_ADD_TO_NOW_PLAYING_IND)),               /* 0x5E3B */
    PACK16(MESSAGE_SIZE(AVRCP_ADD_TO_NOW_PLAYING_CFM),               /* 0x5E3C */
           MESSAGE_SIZE(AVRCP_EVENT_ADDRESSED_PLAYER_CHANGED_IND)),   /* 0x5E3D */
    PACK16(MESSAGE_SIZE(AVRCP_EVENT_AVAILABLE_PLAYERS_CHANGED_IND),  /* 0x5E3E */
           MESSAGE_SIZE(AVRCP_EVENT_UIDS_CHANGED_IND)),               /* 0x5E3F */
    PACK16(MESSAGE_SIZE(AVRCP_EVENT_NOW_PLAYING_CONTENT_CHANGED_IND),/* 0x5E40 */
           MESSAGE_SIZE(AVRCP_BROWSE_CONNECT_IND)),                   /* 0x5E41 */
    PACK16(MESSAGE_SIZE(AVRCP_BROWSE_CONNECT_CFM),                   /* 0x5E42 */
           MESSAGE_SIZE(AVRCP_BROWSE_DISCONNECT_IND)),                /* 0x5E43 */
    PACK16(MESSAGE_SIZE(AVRCP_BROWSE_SET_PLAYER_IND),                /* 0x5E44 */
           MESSAGE_SIZE(AVRCP_BROWSE_SET_PLAYER_CFM)),                /* 0x5E45 */
    PACK16(MESSAGE_SIZE(AVRCP_BROWSE_CHANGE_PATH_IND),               /* 0x5E46 */
           MESSAGE_SIZE(AVRCP_BROWSE_CHANGE_PATH_CFM)),               /* 0x5E47 */
    PACK16(MESSAGE_SIZE(AVRCP_BROWSE_GET_FOLDER_ITEMS_IND),          /* 0x5E48 */
           MESSAGE_SIZE(AVRCP_BROWSE_GET_FOLDER_ITEMS_CFM)),          /* 0x5E49 */
    PACK16(MESSAGE_SIZE(AVRCP_BROWSE_GET_ITEM_ATTRIBUTES_IND),       /* 0x5E4A */
           MESSAGE_SIZE(AVRCP_BROWSE_GET_ITEM_ATTRIBUTES_CFM)),       /* 0x5E4B */
    PACK16(MESSAGE_SIZE(AVRCP_BROWSE_SEARCH_IND),                    /* 0x5E4C */
           MESSAGE_SIZE(AVRCP_BROWSE_SEARCH_CFM)),                    /* 0x5E4D */
    PACK16(0 /*MESSAGE_SIZE(AVRCP_BROWSE_TIMEOUT_IND)*/,                   /* 0x5E4E */
           MESSAGE_SIZE(AVRCP_BROWSE_GET_NUMBER_OF_ITEMS_CFM)), /* 0x5E4F */
    PACK16(MESSAGE_SIZE(AVRCP_BROWSE_GET_NUMBER_OF_ITEMS_IND), /* 0x5E50 */
           0)
};

void ahiTestEchoAvrcpMessage(MessageId id, Message message)
{
    sendMessageToAhi((id - AVRCP_MESSAGE_BASE), avrcp_table, id, message);
}

static const uint16 a2dp_table[] = {
    PACK16(MESSAGE_SIZE(A2DP_INIT_CFM),  /* 00 */

    /* New API */    
         MESSAGE_SIZE(A2DP_SIGNALLING_CONNECT_IND)),            /* 01 */
    PACK16(MESSAGE_SIZE(A2DP_SIGNALLING_CONNECT_CFM),            /* 02 */
         MESSAGE_SIZE(A2DP_SIGNALLING_DISCONNECT_IND)),         /* 03 */
    PACK16(MESSAGE_SIZE(A2DP_SIGNALLING_LINKLOSS_IND),           /* 04 */
    
         MESSAGE_SIZE(A2DP_MEDIA_OPEN_IND)),                    /* 05 */
    PACK16(MESSAGE_SIZE(A2DP_MEDIA_OPEN_CFM),                    /* 06 */
         MESSAGE_SIZE(A2DP_MEDIA_CLOSE_IND)),                   /* 07 */
    PACK16(0, /*MESSAGE_SIZE(A2DP_MEDIA_CLOSE_CFM),*/            /* 08 */
         MESSAGE_SIZE(A2DP_MEDIA_START_IND)),                   /* 09 */
    PACK16(MESSAGE_SIZE(A2DP_MEDIA_START_CFM),                   /* 0A */
         MESSAGE_SIZE(A2DP_MEDIA_SUSPEND_IND)),                 /* 0B */
    PACK16(MESSAGE_SIZE(A2DP_MEDIA_SUSPEND_CFM),                 /* 0C */
         MESSAGE_SIZE(A2DP_MEDIA_RECONFIGURE_IND)),             /* 0D */
    PACK16(MESSAGE_SIZE(A2DP_MEDIA_RECONFIGURE_CFM),             /* 0E */
         MESSAGE_SIZE(A2DP_MEDIA_AV_SYNC_DELAY_IND)),           /* 0F */
    PACK16(MESSAGE_SIZE(A2DP_MEDIA_AV_SYNC_DELAY_CFM),           /* 10 */
         MESSAGE_SIZE(A2DP_MEDIA_AV_SYNC_DELAY_UPDATED_IND)),   /* 11 */
    /* End of new API */
    
    PACK16(MESSAGE_SIZE(A2DP_CODEC_CONFIGURE_IND),               /* 12 */
         MESSAGE_SIZE(A2DP_ENCRYPTION_CHANGE_IND)),             /* 13 */
    PACK16(MESSAGE_SIZE(A2DP_LINKLOSS_RECONNECT_CANCEL_IND),      /* 14 */
         0)
};   

void ahiTestEchoA2dpMessage(MessageId id, Message message)
{
    sendMessageToAhi((id - A2DP_MESSAGE_BASE), a2dp_table, id, message);
}


#endif /* ENABLE_AHI_TEST_WRAPPER */
