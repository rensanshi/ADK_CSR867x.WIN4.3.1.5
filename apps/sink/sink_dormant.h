/*
Copyright (c) 2016 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3
*/
/** 
\file 
\ingroup sink_app
\brief Support for Dormant Mode. 

*/

#ifndef _SINK_DORMANT_H_
#define _SINK_DORMANT_H_


#ifdef ENABLE_DORMANT_SUPPORT
bool sinkDormantWakeUpFromNfc(void);
#else
#define sinkDormantWakeUpFromNfc() FALSE
#endif

#ifdef ENABLE_DORMANT_SUPPORT
void sinkDormantEnable(bool deadline_required);
#else
#define sinkDormantEnable(deadline_required) ((void)(0))
#endif

/****************************************************************************
NAME
    sinkDormantIsSupported

DESCRIPTION
    API to check whether the dormant mode is enabled or not
    
****************************************************************************/
#ifdef ENABLE_DORMANT_SUPPORT
#define sinkDormantIsSupported() TRUE
#else
#define sinkDormantIsSupported() FALSE
#endif

#endif /* _SINK_DORMANT_H_ */
