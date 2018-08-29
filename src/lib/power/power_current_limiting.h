/****************************************************************************
Copyright (c) 2005 - 2017 Qualcomm Technologies International, Ltd.

FILE NAME
    power_current_limiting.h

DESCRIPTION
    This file contains the curent limiting operation of the battery charging
    functionality..

    Performs imperical maximum current discovery and prevents VCHG dropping
    below it's critical voltage (~4.6V).

NOTES

**************************************************************************/


#ifndef POWER_CURRENT_LIMITING_H_
#define POWER_CURRENT_LIMITING_H_


/****************************************************************************
NAME
    powerCurrentLimitingInit
    
DESCRIPTION
    Initialise the current limiting operation.
    
RETURNS
    void
*/
void powerCurrentLimitingInit(void);

#endif /* POWER_CURRENT_LIMITING_H_ */
