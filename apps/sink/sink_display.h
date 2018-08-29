/****************************************************************************
Copyright (c) 2010 - 2017 Qualcomm Technologies International, Ltd.

FILE NAME
    sink_display.h

DESCRIPTION

*/
#ifndef _SINK_DISPLAY_H_
#define _SINK_DISPLAY_H_

#include "sink_states.h"

#ifdef ENABLE_DISPLAY_MIDAS
#ifndef ENABLE_DISPLAY
#define ENABLE_DISPLAY
#endif
#endif

#ifdef ENABLE_DISPLAY

/* Pre-define some text strings */
#define DISPLAYSTR_HELLO        "Power On"    
#define DISPLAYSTR_GOODBYE      "Goodbye"    

#define DISPLAYSTR_CLEAR      ""    
#define DISPLAYSTR_PAIRING      "Pairing mode"
#define DISPLAYSTR_CONNECTED    "Connected"
#define DISPLAYSTR_OUTGOINGCALL "Outgoing Call"
#define DISPLAYSTR_INCOMINGCALL "Incoming Call"
#define DISPLAYSTR_ACTIVECALL   "Call in progress"
#define DISPLAYSTR_TWCWAITING   "Call Waiting"
#define DISPLAYSTR_TWCONHOLD    "Call On Hold"
#define DISPLAYSTR_TWCMULTI     "Multicall"
#define DISPLAYSTR_INCOMINGONHOLD "Incoming Call On Hold"
#define DISPLAYSTR_ACTIVECALLNOSCO "Call (No audio)"
#define DISPLAYSTR_A2DPSTREAMING   "Play"
#define DISPLAYSTR_LOWBATTERY      "Low Battery"
#define DISPLAYSTR_TESTMODE      "Test Mode"
#define DISPLAYSTR_FM_STORAGE_FULL      "FM storage full"


typedef enum SinkTextType
{
    SINK_TEXT_TYPE_NONE = 0,
    SINK_TEXT_TYPE_AUDIO_SOURCE,
    SINK_TEXT_TYPE_DEVICE_STATE,
    SINK_TEXT_TYPE_CHARGER_STATE,
    SINK_TEXT_TYPE_PLAY_STATE,
    SINK_TEXT_TYPE_MEDIA_INFO,
    SINK_TEXT_TYPE_CALLER_INFO,
    SINK_TEXT_TYPE_GATT_INFO,
    SINK_TEXT_TYPE_RADIO_FREQ,
    SINK_TEXT_TYPE_RADIO_INFO,
    SINK_TEXT_NUM_TYPES
}SINK_TEXT_TYPE_T;


/****************************************************************************
NAME 
    displayInit

DESCRIPTION
    Initialise the display

RETURNS
    void
*/
void displayInit(void);


/****************************************************************************
NAME
    displayShowText

DESCRIPTION
    Display text on display

RETURNS
    void
*/
void displayShowText(const char* text,
                             uint8 txtlen,
                             bool  scroll,
                             uint16 scroll_update,
                             uint16 scroll_pause,
                             bool  flash,
                             uint16 display_time,
                             uint8 type);


/****************************************************************************
NAME 
    displaySetState
    
DESCRIPTION
    Turn display off (state FALSE) or on (state TRUE)
    
RETURNS
    void
*/ 
void displaySetState(bool state);


/****************************************************************************
NAME
    displayShowSimpleText

DESCRIPTION
    Simplified interface to display text

RETURNS
    void
*/
void displayShowSimpleText(const char* text, uint8 type);


/****************************************************************************
NAME
    displayRemoveText

DESCRIPTION
    Remove text of a particular type

RETURNS
    void
*/
void displayRemoveText(uint8 type);


/****************************************************************************
NAME 
    displayUpdateIcon
    
DESCRIPTION
    Updates the state of an icon on the display
    
RETURNS
    void
*/ 

void displayUpdateIcon( uint8 icon, bool state );


/****************************************************************************
NAME 
    displayUpdateVolume
    
DESCRIPTION
    Updates the state of the volume on the display
    
RETURNS
    void
*/ 
void displayUpdateVolume( int16 vol );


/****************************************************************************
NAME 
    displayUpdateBatteryLevel
    
DESCRIPTION
    Updates the state of the battery level on the display
    
RETURNS
    void
*/ 
void displayUpdateBatteryLevel( bool charging );


/****************************************************************************
NAME 
    displayUpdateAppState
    
DESCRIPTION
    Updates the the display with the application state
    
RETURNS
    void
*/ 
void displayUpdateAppState (sinkState newState);

/****************************************************************************
NAME
    displayUpdateAudioSourceText

DESCRIPTION
    Updates the display with the current routed source name.

RETURNS
    void
*/
void displayUpdateAudioSourceText(audio_sources source);


/****************************************************************************
NAME
    displayShowLinkKeyEnable

DESCRIPTION
    Enables/disables the feature to allow the display to show the link keys of the connected devices 
    (test purposes for capturing air traces).

RETURNS
    void
*/
void displayShowLinkKeyEnable(void);


/****************************************************************************
NAME
    displayShowLinkKeyDisable

DESCRIPTION
    Disables the feature to allow the display to show the link keys of the connected devices 
    (test purposes for capturing air traces).

RETURNS
    void
*/
void displayShowLinkKeyDisable(void);


#else

/* dummy display functions if display is disabled */
#define handleDisplayMessage(task, id, message) ((void)(0))
#define displayInit() ((void)(0))
#define displaySetState(state) ((void)(0))
#define displayShowText(text, txtlen, scroll, scroll_update, scroll_pause, flash, display_time, type) ((void)(0))
#define displayShowSimpleText(text, type) ((void)(0))
#define displayRemoveText(type) ((void)(0))
#define displayUpdateIcon(icon, state) ((void)(0))
#define displayUpdateVolume(vol) ((void)(0))
#define displayUpdateBatteryLevel(charging) ((void)(0))
#define displayUpdateAppState(newState) ((void)(0))
#define displayUpdateAudioSourceText(x) ((void)(0))
#define displayShowLinkKeyEnable() ((void)(0))
#define displayShowLinkKeyDisable() ((void)(0))

#endif /* ifdef ENABLE_DISPLAY */

#endif /* _SINK_DISPLAY_H_ */
