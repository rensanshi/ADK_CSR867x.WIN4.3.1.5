/*
Copyright (c) 2017 Qualcomm Technologies International, Ltd.
*/

/*!
@file
@ingroup sink_app
@brief
    Module responsible for interfacing with SMB1352 battery charger
************************************************************************/

#ifndef SINK_EXT_CHARGER_H
#define SINK_EXT_CHARGER_H

#define EXT_CHG_NUM_REGS (21)
#define EXT_CHG_REG_STS_FLOAT_VOLTAGE (0x38)
#define EXT_CHG_MASK_STS_FLOAT_VOLTAGE (0x3F)

#define EXT_CHG_FLOAT_BASE_MILLIVOLTS (3500)
#define EXT_CHG_FLOAT_STEP_MILLIVOLTS (20)

#ifdef ENABLE_EXT_CHARGER

void sinkExtChargerInit(void);
uint16 sinkExtChargerReadFloatVoltage(void);

#else /* not def ENABLE_EXT_CHARGER */

#define sinkExtChargerInit() ((void) 0)
#define sinkExtChargerReadFloatVoltage() ((uint16) 0)

#endif /* def ENABLE_EXT_CHARGER */
#endif /* def SINK_EXT_CHARGER_H */

