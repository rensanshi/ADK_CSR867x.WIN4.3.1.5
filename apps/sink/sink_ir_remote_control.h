/****************************************************************************
Copyright (c) 2013 - 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    sink_ir_remote_control.h

DESCRIPTION
    Header file for interface with Infrared Remote Controllers
*/

#ifndef _SINK_IR_REMOTE_CONTROL_H_
#define _SINK_IR_REMOTE_CONTROL_H_

/* firmware includes */
#include <infrared.h>

/* Application includes */
#ifdef ENABLE_IR_REMOTE
#include "sink_input_manager.h"
#endif
/*!
   A infra-red 'button has been pressed or releases. The message content
   is a MessageInfraRedEvent.
   This message is sent to the task registered with MessageInfraRedTask()
*/
#define MESSAGE_INFRARED_EVENT (SYSTEM_MESSAGE_BASE_ + 58)

/*
    Defines the Timer IDs to differentiate which timer has fired
*/
typedef enum
{
    IR_RC_TIMER_SHORT=0,   /* The SHORT timer has fired whilst the button is still pressed */
    IR_RC_TIMER_LONG,      /* The LONG timer has fired whilst the button is still pressed */
    IR_RC_TIMER_VLONG,     /* The VLONG timer has fired whilst the button is still pressed */
    IR_RC_TIMER_VVLONG     /* The VVLONG timer has fired whilst the button is still pressed */
} irRcTimerID_t;


/*
    Defines the IR RC button events
    These IDs are the actual message ID's as identified by the MessageLoop() scheduler
*/
typedef enum
{
    IR_RC_BUTTON_TIMER_MSG=100, /* Sent when a button duration (SHORT, LONG, VLONG, VVLONG) timer fires (Given ID 100 so it does not conflict with IR message IDs from firmware - this message is only used by the IR handler) */
    IR_RC_BUTTON_REPEAT_MSG     /* Sent when a button REPEAT timer fires */
} irRcMessageID_t;


/* 
    Defines the data structure for BUTTON EVENT messages
*/
typedef struct
{
    uint16              addr;   /* Address to identify the RC the button press was generated by */
    uint16              mask;   /* Identifies which button is currently pressed down */
    irRcTimerID_t       timer;  /* Identifies the button timer that has fired (Only used for IR_RC_BUTTON_TIMER_MSG) */
} IR_RC_BUTTON_EVENT_MSG_T;


/****************************************************************************
NAME    
    irCanLearnNewCode
    
DESCRIPTION
    Function to indicate whether or not the IR controller can learn a new
    code. If the maximum number of codes have already been learnt, will
    not allow a new code to be learnt.
*/
bool irCanLearnNewCode(void);


/****************************************************************************
NAME
    irStartLearningMode

DESCRIPTION
    Function to start the IR Learning mode (if state allows).
*/
bool irStartLearningMode(void);


/****************************************************************************
NAME
    handleIrLearningModeReminder

DESCRIPTION
    Function to handle the learning mode reminder event
*/
void handleIrLearningModeReminder(void);


/****************************************************************************
NAME
    irStopLearningMode

DESCRIPTION
    Function to stop the IR Learning mode
*/
void irStopLearningMode(void);


/****************************************************************************
NAME
    irClearLearntCodes

DESCRIPTION
    Function to clear the IR codes that have been learnt through the learning
    mode
*/
void irClearLearntCodes(void);


/****************************************************************************
NAME 
      irRemoteControlInit

DESCRIPTION
    Initialise the IR RC module 
 
RETURNS
      void
*/ 
void irRemoteControlInit(void);


/****************************************************************************
NAME 
    irRemoteControlIsLearningMode

DESCRIPTION
    Indicate whether or not "learning mode" is in progess
 
RETURNS
      bool TRUE if learning mode is in progress, else FALSE
*/ 
bool irRemoteControlIsLearningMode(void);


/****************************************************************************
NAME 
      irRemoteControlGetLearningModeTimeout

DESCRIPTION
    Get the learning mode timeout
 
RETURNS
      uint16
*/ 
uint16 irRemoteControlGetLearningModeTimeout(void);

/****************************************************************************
NAME 
      irRemoteControlGetLearningModeReminder

DESCRIPTION
    Get the learning mode reminder
 
RETURNS
      uint16
*/ 
uint16 irRemoteControlGetLearningModeReminder(void);


/****************************************************************************
NAME 
      irRemoteControlGetMaxLearningCodes

DESCRIPTION
    Get the max learning codes
 
RETURNS
      uint16
*/ 
uint16 irRemoteControlGetMaxLearningCodes(void);


/****************************************************************************
NAME 
      irRemoteControlGetInputIdToLearn

DESCRIPTION
    When in learning mode, this is the input ID to learn
 
RETURNS
      uint16
*/ 
uint16 irRemoteControlGetInputIdToLearn(void);


/****************************************************************************
NAME 
      irRemoteControlSetInputIdToLearn

DESCRIPTION
    When in learning mode, set this as the input ID to learn
 
RETURNS
      void
*/ 
void irRemoteControlSetInputIdToLearn(uint16 inputId);



/* Macro used by the IR "Input Monitor" to generate messages to send itself */
#define MAKE_IR_RC_MESSAGE(TYPE) TYPE##_T *message = PanicUnlessNew(TYPE##_T);


#endif /* _SINK_IR_REMOTE_CONTROL_H_ */
