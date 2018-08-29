/****************************************************************************
Copyright (c) 2010 - 2018 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    sink_gaia.h

DESCRIPTION
    Header file for interface with Generic Application Interface Architecture
    library

NOTES

*/
#ifndef _SINK_GAIA_H_
#define _SINK_GAIA_H_


/* Work around gcc bug converting uppercase defines to lower case */
#ifdef enable_gaia
#define ENABLE_GAIA
#endif

#include <stream.h>
#include <gaia.h>
#include <pio_common.h>

#include "sink_private_data.h"


#ifndef GATT_ENABLED
#undef GATT_GAIA_SERVER
#endif

#ifdef GATT_GAIA_SERVER
#include "sink_gatt_db.h"
#endif

#ifdef DEBUG_GAIA
#define GAIA_DEBUG(x) DEBUG(x)
#else
#define GAIA_DEBUG(x)
#endif

#define GAIA_API_MINOR_VERSION (5)

#define GAIA_TONE_BUFFER_SIZE (94)
#define GAIA_TONE_MAX_LENGTH ((GAIA_TONE_BUFFER_SIZE - 4) / 2)

#define GAIA_ILLEGAL_PARTITION (15)
#define GAIA_DFU_REQUEST_TIMEOUT (30)

typedef struct
{
    unsigned fixed:1;
    unsigned size:15;
} gaia_config_entry_size_t;

/*For complete information about the GAIA commands, refer to the document GAIAHeadsetCommandReference*/

#define CHANGE_NUMBER_OF_ACTIVE_BANKS   0xFFFF
#define CHANGE_NUMBER_OF_BANDS          0xF0FF
#define CHANGE_BANK_MASTER_GAIN         0xF0FE
#define CHANGE_BAND_PARAMETER           0xF000
#define USER_EQ_BANK_INDEX              1

/*************************************************************************
NAME
    initGaia

DESCRIPTION
    Initialize GAIA system by allocating memory for GAIA global structure
*/
void initGaia(void);
/*************************************************************************
NAME
    gaiaReportPioChange

DESCRIPTION
    Relay any registered PIO Change events to the Gaia client
    We handle the PIO-like GAIA_EVENT_CHARGER_CONNECTION here too
*/
void gaiaReportPioChange(pio_common_allbits *pio_state);


/*************************************************************************
NAME
    gaiaReportEvent

DESCRIPTION
    Relay any significant application events to the Gaia client
*/
void gaiaReportEvent(uint16 id);


/*************************************************************************
NAME
    gaiaReportUserEvent

DESCRIPTION
    Relay any user-generated events to the Gaia client
*/
void gaiaReportUserEvent(uint16 id);


/*************************************************************************
NAME
    gaiaReportSpeechRecResult

DESCRIPTION
    Relay a speech recognition result to the Gaia client
*/
void gaiaReportSpeechRecResult(uint16 id);


/*************************************************************************
NAME
    handleGaiaMessage

DESCRIPTION
    Handle messages passed up from the Gaia library
*/
void handleGaiaMessage(Task task, MessageId id, Message message);

/*************************************************************************
NAME
    gaiaGetBdAddrNonGaiaDevice

DESCRIPTION
    Determines the BD Address of the device which is not connected to GAIA.
*/
bool gaiaGetBdAddrNonGaiaDevice(bdaddr *bdaddr_non_gaia_device);



/*************************************************************************
NAME
    gaiaDfuRequest

DESCRIPTION
    Request Device Firmware Upgrade from the GAIA host
*/
void gaiaDfuRequest(void);


/*************************************************************************
NAME
    gaiaDisconnect

DESCRIPTION
    Disconnect from GAIA client
*/
void gaiaDisconnect(void);


/*************************************************************************
NAME
    gaia_send_response

DESCRIPTION
    Build and Send a Gaia acknowledgement packet

*/
void gaia_send_response(uint16 vendor_id, uint16 command_id, uint16 status,
                          uint16 payload_length, uint8 *payload);


/*************************************************************************
NAME
    GaiaHandleGetUserEqParamResponse
DESCRIPTION
    Send get user eq param response message to gaia
*/
void GaiaHandleGetUserEqParamResponse(AUDIO_GET_USER_EQ_PARAMETER_CFM_T* get_user_eq_resp_msg);


/*************************************************************************
NAME
    GaiaHandleGetUserEqParamsResponse
DESCRIPTION
    Send get user eq params response message to gaia
*/
void GaiaHandleGetUserEqParamsResponse(AUDIO_GET_USER_EQ_PARAMETERS_CFM_T* get_user_eq_resp_msg);


/*************************************************************************
NAME
    gaia_send_response_16

DESCRIPTION
    Build and Send a Gaia acknowledgement packet from a uint16[] payload

*/
void gaia_send_response_16(uint16 command_id, uint16 status,
                          uint16 payload_length, uint16 *payload);

/****************************************************************************
NAME
	gaia_get_transport

DESCRIPTION
    Get the GAIA transport

PARAMS
    void

RETURNS
	GAIA_TRANSPORT *
*/
GAIA_TRANSPORT* gaia_get_transport(void);

/****************************************************************************
NAME
	gaia_set_transport

DESCRIPTION
    Set the GAIA transport

PARAMS
    GAIA_TRANSPORT* transport

RETURNS
	void
*/
void gaia_set_transport(GAIA_TRANSPORT* transport);

/****************************************************************************
NAME
    gaia_get_pio_change_mask

DESCRIPTION
    Get the GAIA pio change mask which is a 32 bit value, mapped against the
    translation table.

RETURNS
    The 32 bit mask.
*/
uint32 gaia_get_pio_change_mask32(void);

/****************************************************************************
NAME
    gaia_get_pio_change_mask

DESCRIPTION
    Get the GAIA pio change mask, populating the supplied pio_common_allbits
    structure.

RETURNS
    TRUE if the mask is non-empty
*/
bool gaia_get_pio_change_mask(pio_common_allbits *mask);

/****************************************************************************
NAME
    gaia_set_pio_change_mask

DESCRIPTION
    Set the GAIA pio change mask

PARAMS
    mask A 32 bit value representing "gaia PIOS" that are mapped using a
    configuration table

*/
void gaia_set_pio_change_mask(uint32 mask);

/****************************************************************************
NAME
    gaia_clear_pio_change_mask

DESCRIPTION
    Clear the GAIA pio change mask so it represents "no bits"

*/
void gaia_clear_pio_change_mask(void);

/****************************************************************************
NAME
	gaia_get_pio_old_state

DESCRIPTION
    Get the old state of PIO bits, populating the supplied pio_common_allbits
    structure.

PARAMS
    state   Pointer to pio_common_allbits structure to take the old state of the PIOs

RETURNS
    TRUE if the mask is non-empty
*/
bool gaia_get_pio_old_state(pio_common_allbits *state);

/****************************************************************************
NAME
    gaia_set_pio_old_state

DESCRIPTION
    Set the GAIA pio old state

PARAMS
    state  Pointer to the pio_common_allbits svariable holding the state to
    set PIOs to.

RETURNS
    void
*/
void gaia_set_pio_old_state(pio_common_allbits *state);

/****************************************************************************
NAME
	gaia_get_alert_tone

DESCRIPTION
    Get the GAIA alert tone

PARAMS
    void

RETURNS
	uint32
*/
ringtone_note* gaia_get_alert_tone(void);

/****************************************************************************
NAME
	gaia_set_alert_tone

DESCRIPTION
    Set the GAIA alert tone

PARAMS
    ringtone_note* tone

RETURNS
	void
*/
void gaia_set_alert_tone(ringtone_note* tone);

/****************************************************************************
NAME
	gaia_get_notify_ui_event

DESCRIPTION
    Get the GAIA notify ui event

PARAMS
    void

RETURNS
	uint8
*/
uint8 gaia_get_notify_ui_event(void);

/****************************************************************************
NAME
	gaia_set_notify_ui_event

DESCRIPTION
    Set the GAIA notify ui event

PARAMS
    event GAIA notification event

RETURNS
	void
*/
void gaia_set_notify_ui_event(uint8 event);

/****************************************************************************
NAME
	gaia_get_notify_charger_connection

DESCRIPTION
    Get the GAIA notify charger connection

PARAMS
    void

RETURNS
	uint8
*/
uint8 gaia_get_notify_charger_connection(void);

/****************************************************************************
NAME
	gaia_set_notify_charger_connection

DESCRIPTION
    Set the GAIA notify charger connection

PARAMS
    connection GAIA charger connection

RETURNS
	void
*/
void gaia_set_notify_charger_connection(uint8 connection);

/****************************************************************************
NAME
	gaia_get_notify_battery_charged

DESCRIPTION
    Get the GAIA notify battery charged

PARAMS
    void

RETURNS
	uint8
*/
uint8 gaia_get_notify_battery_charged(void);

/****************************************************************************
NAME
	gaia_set_notify_battery_charged

DESCRIPTION
    Set the GAIA notify battery charged

PARAMS
    charged Battery charged state

RETURNS
	void
*/
void gaia_set_notify_battery_charged(uint8 charged);

/****************************************************************************
NAME
	gaia_get_notify_speech_rec

DESCRIPTION
    Get the GAIA notify speech recognization

PARAMS
    void

RETURNS
	uint8
*/
uint8 gaia_get_notify_speech_rec(void);

/****************************************************************************
NAME
	gaia_set_notify_speech_rec

DESCRIPTION
    Set the GAIA notify speech recognization

PARAMS
    rec Speech recognition notification

RETURNS
	void
*/
void gaia_set_notify_speech_rec(uint8 rec);

/****************************************************************************
NAME
	gaia_get_dfu_boot_status

DESCRIPTION
    Get the GAIA dfu boot status

PARAMS
    void

RETURNS
	uint8
*/
uint8 gaia_get_dfu_boot_status(void);

/****************************************************************************
NAME
	gaia_set_dfu_boot_status

DESCRIPTION
    Set the GAIA dfu boot status

PARAMS
    status DFU boot status to set

RETURNS
	void
*/
void gaia_set_dfu_boot_status(uint8 status);

/****************************************************************************
NAME
    gaia_get_activate_peq_done

DESCRIPTION
    Get the GAIA activate_peq_done flag

PARAMS
    void

RETURNS
    bool
*/
bool gaia_get_activate_peq_done(void);

/****************************************************************************
NAME
    gaia_set_activate_peq_done

DESCRIPTION
    Set the GAIA activate_peq_done flag

PARAMS
    status activate_peq_done status to set

RETURNS
    void
*/
void gaia_set_activate_peq_done(bool status);

/****************************************************************************
NAME
	gaia_get_enable_session

DESCRIPTION
    Get the GAIA enable session

PARAMS
    void

RETURNS
	bool
*/
bool gaia_get_enable_session(void);

/****************************************************************************
NAME
	gaia_get_remain_connected

DESCRIPTION
    Get the GAIA remain connected

PARAMS
    void

RETURNS
	bool
*/
bool gaia_get_remain_connected(void);

/****************************************************************************
NAME
	gaia_set_remain_connected

DESCRIPTION
    Set the GAIA remain connected

PARAMS
    connected Flag for remain connected

RETURNS
	void
*/
void gaia_set_remain_connected(bool connected);

/****************************************************************************
NAME
	gaia_get_dfu_partition

DESCRIPTION
    Get the GAIA dfu partition

PARAMS
    void

RETURNS
	uint16
*/
uint16 gaia_get_dfu_partition(void);

/****************************************************************************
NAME
	gaia_get_SC_PEQ_Settings_Timeout

DESCRIPTION
    Get the GAIA Store PEQ settings time out

PARAMS
    void

RETURNS
	uint16
*/
uint16 gaia_get_SC_PEQ_Settings_Timeout(void);

#if defined GATT_GAIA_SERVER && defined ENABLE_GAIA
#define gaiaGattEnabled() (TRUE)
#else
#define gaiaGattEnabled() (FALSE)
#endif


#if defined GATT_GAIA_SERVER && defined ENABLE_GAIA
#define gaiaGattServerInitialise(void) GaiaStartGattServer(HANDLE_GAIA_SERVICE, HANDLE_GAIA_SERVICE_END)
#else
#define gaiaGattServerInitialise(void)
#endif


#if defined GATT_GAIA_SERVER && defined ENABLE_GAIA
#define gaiaGattConnect(cid) GaiaConnectGatt(cid)
#else
#define gaiaGattConnect(cid)
#endif

#if defined GATT_GAIA_SERVER && defined ENABLE_GAIA
#define gaiaGattDisconnect(cid) GaiaDisconnectGatt(cid)
#else
#define gaiaGattDisconnect(cid)
#endif

#ifdef ENABLE_VOICE_ASSISTANT
void gaiaVoiceAssistantStart(void);
void gaiaVoiceAssistantEnd(void);
void gaiaVoiceAssistantCancel(void);
#else
#define gaiaVoiceAssistantStart() ((void) 0)
#define gaiaVoiceAssistantEnd() ((void) 0)
#define gaiaVoiceAssistantCancel() ((void) 0)
#endif

#endif /*_SINK_GAIA_H_*/
