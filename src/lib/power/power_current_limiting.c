/****************************************************************************
Copyright (c) 2005 - 2017    Qualcomm Technologies International, Ltd.

FILE NAME
    power_current_limiting.c

DESCRIPTION
    This file contains the curent limiting operation of the battery charging
    functionality..

    Performs imperical maximum current discovery and prevents VCHG dropping
    below it's critical voltage (~4.6V).

NOTES

**************************************************************************/


/****************************************************************************
    Header files
*/

#include "power.h"
#include "power_private.h"
#include "power_utils.h"
#include "power_current_limiting.h"
#include "power_charger.h"
#include "power_monitor.h"

/****************************************************************************
NAME
    powerCurrentLimitingGetVchgAdcPeriod

DESCRIPTION
    Get the correct Vchg Adc reading period depending on the feature
    configuration and the charger state.

RETURNS
    Vchg Adc reading period
*/
static Delay powerCurrentLimitingGetVchgAdcPeriod(void);

/****************************************************************************
NAME
    limit_current

DESCRIPTION
    Perform the current limiting operation.

RETURNS
    void
*/
static void limit_current(int16 current_step)
{
    uint16 new_current;
    
    new_current = (uint16)((int16)power->charger_i_actual_fast+current_step);
    
    if(new_current < INITIAL_FAST_DYNAMIC_CURRENT_IN_MA)
    {
        new_current = INITIAL_FAST_DYNAMIC_CURRENT_IN_MA;
    }
    
    if(new_current > power->charger_i_safe_fast)
    {
        new_current = power->charger_i_safe_fast;
    }
    
    if(new_current != power->charger_i_actual_fast)
    {
        powerChargerConfigHelper(CHARGER_CONFIG_FAST_CURRENT,
                                     (power->charger_i_actual_fast = new_current));
        powerUtilChargerEnable(TRUE);
    }
}

void PowerCurrentLimitingStart(void)
{
    if (power->enable_current_limiting)
    {
        power->config.vchg.adc.period_chg = power->config.vchg.current_limit_period_chg;

        power->current_limiting_active = FALSE;

        powerChargerSetChargerCurrents(INITIAL_FAST_DYNAMIC_CURRENT_IN_MA);

        if(!powerMonitorReadAdcNow(&power->task, POWER_INTERNAL_VCHG_REQ, &power->config.vchg.adc, power_init_vchg))
            powerMonitorReadAdc(&power->task, POWER_INTERNAL_VCHG_REQ, 0);

        PRINT(("POWER: Starting current limiting. Period = %u, Starting current = %u\n",
               power->config.vchg.adc.period_chg, INITIAL_FAST_DYNAMIC_CURRENT_IN_MA));
    }
}

void PowerCurrentLimitingStop(void)
{
    power->config.vchg.adc.period_chg = power->config.vchg.non_current_limit_period_chg;

    power->current_limiting_active = FALSE;
}

/****************************************************************************
NAME
    powerCurrentLimitingInit

DESCRIPTION
    Initialise the current limiting operation.

RETURNS
    void
*/
void powerCurrentLimitingInit(void)
{

    power->config.vchg.adc.period_chg = powerCurrentLimitingGetVchgAdcPeriod();

    power->current_limiting_active = FALSE;

    PRINT(("POWER: Current Limiting enabled = %u\n", power->enable_current_limiting));
    PRINT(("POWER: Current Limiting VCHG Monitor Period (Charging) = %ums\n", power->config.vchg.adc.period_chg));
    PRINT(("POWER: Current Limiting VCHG Threshold = %umv\n", power->config.vchg.current_limit_threshold));
    PRINT(("POWER: Current Limiting VCHG Recovery Threshold = %umv\n", power->config.vchg.current_limit_recovery_threshold));
    PRINT(("POWER: Current Limiting +ve Step = %u degC\n", power->config.vchg.positive_current_step));
    PRINT(("POWER: Current Limiting -ve Step = %u degC\n", power->config.vchg.negative_current_step));
    PRINT(("POWER: Current Limiting charger_i_actual_fast = %umA\n", power->charger_i_actual_fast));
    PRINT(("POWER: Current Limiting charger_i_safe_fast = %umA\n", power->charger_i_safe_fast));
}

static Delay powerCurrentLimitingGetVchgAdcPeriod(void)
{
    return (power->enable_current_limiting && (FAST_CHARGE == ChargerStatus())) ?
           power->config.vchg.current_limit_period_chg : power->config.vchg.non_current_limit_period_chg;
}

/****************************************************************************
NAME
    PowerCurrentLimitingHandleMonitorReq

DESCRIPTION
    Handle current limiting power monitoring requests.

RETURNS
    void
*/
void PowerCurrentLimitingHandleMonitorReq(uint16 vchgReading)
{
    if(power->charger_i_safe_fast != 0)
    {
        if(power->current_limiting_active)
        {
            if(vchgReading > power->config.vchg.current_limit_recovery_threshold)
            {
                limit_current(power->config.vchg.positive_current_step);
                power->current_limiting_active = FALSE;
            }
            else
            {
                limit_current(-(power->config.vchg.negative_current_step));
            }
        }
        else
        {
            if(vchgReading < power->config.vchg.current_limit_threshold)
            {
                limit_current(-(power->config.vchg.negative_current_step));
                power->current_limiting_active = TRUE;
            }
            else
            {
                limit_current(power->config.vchg.positive_current_step);
            }
        }
    }
}


/****************************************************************************
NAME
    PowerCurrentLimitingHandleHeadroomError

DESCRIPTION
    Handle current limiting 'Headroom Error' handler.

RETURNS
    void
*/
void PowerCurrentLimitingHandleHeadroomError(void)
{
    limit_current(-(power->config.vchg.negative_current_step));
}
