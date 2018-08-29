/****************************************************************************
Copyright (c) 2017 Qualcomm Technologies International, Ltd.

FILE NAME
    sink_aov.h

DESCRIPTION
    Sink module to support Always-on-Voice (AoV) functionality.

*/
/*!
@file   sink_aov.h
@brief  Sink module to support Always-on-Voice (AoV) functionality.
*/

#ifndef SINK_AOV_H_
#define SINK_AOV_H_

#include <csrtypes.h>

/*!
    @brief Request to activate or deactivate AoV functionality.

    Note: If AoV functionality is disabled in the application config all
          requests to this function will be ignored.

    @param activate TRUE to turn on the AoV audio graph and audio subsystem
                    low-power mode, FALSE to turn it off.
*/
#ifdef ENABLE_AOV
void sinkAovActivate(bool activate);
#else
#define sinkAovActivate(activate) ((void)0)
#endif

/*!
    @brief Cycle through AoV phrases.

    Note: If AoV functionality is disabled in the application config all
          requests to this function will be ignored.

*/
#ifdef ENABLE_AOV
void sinkAovCyclePhrase(void);
#else
#define sinkAovCyclePhrase() ((void)0);
#endif

/*!
    @brief Initialise the AoV Module.

    Note: If AoV functionality is disabled in the application config all
          requests to this function will be ignored.

*/
#ifdef ENABLE_AOV
void sinkAovInit(void);
#else
#define sinkAovInit() ((void)0);
#endif

#endif /* SINK_AOV_H_ */
