/*************************************************************************
Copyright (c) 2005 - 2015 Qualcomm Technologies International, Ltd.
 Part of ADK_CSR867x.WIN 4.3

FILE : 
    power.h

CONTAINS:
    API for the Battery power monitoring and charger management

**************************************************************************/


#ifndef POWER_H_
#define POWER_H_

#include <adc.h>
#include <charger.h>
#include <library.h>

#define POWER_MAX_VTHM_LIMITS   0x07
#define POWER_MAX_VBAT_LIMITS   0x05
#define POWER_MAX_VTHM_REGIONS  (POWER_MAX_VTHM_LIMITS + 1)
#define POWER_MAX_VBAT_REGIONS  (POWER_MAX_VBAT_LIMITS + 1)
#define POWER_VBAT_LIMIT_END    0xFF
#define POWER_VTHM_LIMIT_END    0xFFFF
#define POWER_VSCALE            PowerChargerGetVoltageScale()
#define POWER_PERIOD_SCALE      0x0A
#define MAX_TRICKLE_CURRENT       50
#define MAX_INTERNAL_CURRENT     200
#define MAX_EXTERNAL_CURRENT    1800
#define MAX_SENSE_RESISTOR_MV    100
#define ONE_HUNDRED_PERCENT      100

/*!
    @brief Define the types for the upstream messages sent from the Power
    library to the application.
*/
typedef enum
{
/* 0x7800 */    POWER_INIT_CFM = POWER_MESSAGE_BASE,
/* 0x7801 */    POWER_BATTERY_VOLTAGE_IND, 
/* 0x7802 */    POWER_BATTERY_TEMPERATURE_IND,
/* 0x7803 */    POWER_CHARGER_VOLTAGE_IND,
/* 0x7804 */    POWER_CHARGER_CURRENT_LIMITING_IND,
/* 0x7805 */    POWER_CHARGER_STATE_IND,

/* Library message limit */
/* 0x7806 */    POWER_MESSAGE_TOP
}PowerMessageId ;

/*! 
    @brief Charger state
*/
typedef enum
{
    power_charger_disconnected,
    power_charger_disabled,
    power_charger_trickle,
    power_charger_just_connected,
    power_charger_fast, /* DO NOT reorder this enum without checking where it is used! */
    power_charger_boost_internal,
    power_charger_boost_external,
    power_charger_complete
} power_charger_state;

/*! 
    @brief Boost setting
*/
typedef enum
{
    power_boost_disabled,
    power_boost_internal_enabled,
    power_boost_external_enabled
} power_boost_enable;

/*! 
    @brief ADC monitoring info
*/
typedef struct
{
    vm_adc_source_type source:8;         /* The ADC source */
    unsigned           unused:8;
    unsigned           period_chg:16;    /* Interval (in milli-seconds) between measurements when charging */
    unsigned           period_no_chg:16; /* Interval (in milli-seconds) between measurements when not charging */
} power_adc;

/*! 
    @brief VREF Configuration
*/
typedef struct
{
    power_adc           adc;                /* VREF ADC */
} power_vref_config;

/*! 
    @brief Battery Limit Setting
*/
typedef struct
{
    unsigned notify_period:8;       /* Interval (seconds/POWER_PERIOD_SCALE) between notifications (0 to disable) */
    uint16   limit;                 /* Battery Voltage Threshold / Voltage Scale */
} power_vbat_limit;

/*! 
    @brief Battery Configuration
*/
typedef struct
{
    power_adc           adc;                            /* Battery Voltage ADC */
    power_vbat_limit    limits[POWER_MAX_VBAT_REGIONS]; /* Battery Voltage Thresholds Settings */
} power_vbat_config;

/*!
    @brief Thermistor Configuration. VTHM is read from an external 
    AIO. Limits can be calculated from your thermistor's data sheet, 
    where T is the resistance of the thermistor for given temperature 
    and R is a fixed resistor:
    
    VSRC -------
                |
                R                VSRC(mV) x T
                |---- VTHM(mV) = ------------
                T                   T + R
                |
                _
                -
    
    Where VSRC is the same source as the ADC we can configure limits 
    in terms of raw ADC counts in place of the calculated voltage 
    for improved accuracy:
    
                       VSRC(ADC Counts) x T
    VTHM(ADC Counts) = --------------------
                              T + R
    
    VSRC(ADC Counts) = VADC(ADC Counts) = Max ADC Counts.
    
    NOTES:
    - Thermistor may be driven from a constant source or via a PIO
    - ADC readings are 10 bits: Max ADC Counts = 1023.
    - ADC readings will saturate above ADC source voltage, on BC5/BC6 
    this is 1.5v, on BC7 1.35v. No limit should be set above this level.
*/
typedef struct
{
    power_adc           adc;                           /* Thermistor ADC */
    unsigned            delay:4;                       /* Delay(ms) between setting PIO and reading ADC */
    unsigned            unused:1;                      /* Unused */
    unsigned            raw_limits:1;                  /* Set limits in ADC counts rather than voltage */
    unsigned            drive_ics:1;                   /* Drive thermistor from internal current source */
    unsigned            drive_pio:1;                   /* Drive thermistor from a PIO */
    unsigned            pio:8;                         /* PIO to use */
    uint16              limits[POWER_MAX_VTHM_LIMITS]; /* Voltage Thresholds (mV/ADC Counts) */
} power_vthm_config;

/*! 
    @brief Charger Configuration
*/
typedef struct
{
    power_adc           adc;                        /* VCHG ADC */
    
    unsigned            current_limit_period_chg:16;     /* Vchg current limit read period in ms. */
    unsigned            non_current_limit_period_chg:16; /* Vchg non current limit read period in ms. */
    	
    uint16              limit;                      /* VCHG Threshold / Voltage Scale */

    unsigned            ext_fast:1;                 /* Use external resistor for pre-charge. */
    unsigned            unused1:2;                  /* Unused */
    unsigned            ext_resistor_tolerance:3;   /* Tolerance of external series resistor */
    unsigned            ext_resistor_value:10;      /* Resistor value for external series resistor */

    unsigned            trickle_charge_ratio:7;     /* Trickle charge current as a percentage of fast charge current. */
    unsigned            precharge_ratio:7;          /* Pre-charge current as a percentage of fast charge current. */
    unsigned            debounce_time:2;            /* State change debounce timer */

    unsigned            default_vfloat:4;           /* Default terminal voltage */
    unsigned            iterm_ctrl:2;               /* Termination current control */
    unsigned            standby_fast_hysteresis:2;  /* Standby/fast voltage hysteresis */
    unsigned            pre_fast_threshold:2;       /* Pre/fast voltage threshold */
    unsigned            quiescent_current:2;        /* Maximum quiescent device charge current */
    unsigned            unused2:4;                  /* Unused */

    unsigned            current_limit_threshold:13;     /* Vchg current limit threshold in mV */
    unsigned            unused3:3;                      /* Unused */
    unsigned            current_limit_recovery_threshold:13;  /* Vchg current recovery threshold in mV */
    unsigned            unused4:3;                      /* Unused */

    unsigned            positive_current_step:6;    /* Current increment step size in mA */
    unsigned            unused5:2;                  /* Unused */
    unsigned            negative_current_step:6;    /* Current decrement step size in mA */
    unsigned            unused6:2;                  /* Unused */


} power_vchg_config;

typedef struct
{
    power_adc           adc;                        /* Charger Progress Monitor ADC */
} power_chg_prg_mon_config;

/*!
    @brief  PMU temperature based charging control configuration
*/
typedef struct
{
    uint16              min_charge_i;           /*!< Minimum charger current */
    uint16              max_charge_i;           /*!< Maximum charger current */
    uint16              monitor_period_active;  /*!< Period (ms) to monitor PMU temperature when charger is active */
    uint16              monitor_period_idle;    /*!< Period (ms) to monitor PMU temperature when charger is idle */
    uint16              monitor_period_nopwr;   /*!< Period (ms) to monitor PMU temperature when there is no charger power */
    unsigned            no_incr_i_temp:8;       /*!< Temeprature (degC) where current will not be increased */
    unsigned            charger_i_step:8;       /*!< Charger current step-size */
    unsigned            unused:8;               /*!< Not used (set to 0) */
    unsigned            decr_i_temp:8;          /*!< Temeprature (degC) where current will be decreased */
} power_pmu_temp_mon_config;

/*! 
    @brief Battery Level 
*/
typedef enum
{
    POWER_BATT_CRITICAL,           /* when voltage (mV) < level0 * PowerChargerGetVoltageScale() */
    POWER_BATT_LOW,                /* when voltage (mV) < level1 * PowerChargerGetVoltageScale() */
    POWER_BATT_LEVEL0,             /* when voltage (mV) < level2 * PowerChargerGetVoltageScale() */
    POWER_BATT_LEVEL1,             /* when voltage (mV) < level3 * PowerChargerGetVoltageScale() */
    POWER_BATT_LEVEL2,             /* when voltage (mV) < level4 * PowerChargerGetVoltageScale() */
    POWER_BATT_LEVEL3              /* when voltage (mV) < level5 * PowerChargerGetVoltageScale() */
}power_battery_level;

/*!
    @brief Power Library Configuration
*/
typedef struct
{
    power_vref_config       vref;       /* VREF Config */
    power_vbat_config       vbat;       /* Battery config */
    power_vthm_config       vthm;       /* Thermistor config */
    power_vchg_config       vchg;       /* Charger config */
    power_chg_prg_mon_config   chg_prg_mon;   /* Charger progress monitor config */
} power_config;

/*!
    @brief Contains voltage and level
*/
typedef struct
{
    uint16 voltage;
    uint8  level;
} voltage_reading;

/*!
    @brief This message is returned when the battery and charger monitoring 
    subsystem has been initialised.
*/
typedef struct
{
    bool            success;
    voltage_reading vthm;
    voltage_reading vbat;
    voltage_reading vchg;
    power_charger_state state;
} POWER_INIT_CFM_T;

/*!
    @brief This message is sent to App to indicate the battery voltage level and its value.
*/
typedef struct
{
    voltage_reading vbat;
} POWER_BATTERY_VOLTAGE_IND_T;

/*!
    @brief This message is sent to App to indicate the temperature level and its value.
*/
typedef struct
{
    voltage_reading vthm;
} POWER_BATTERY_TEMPERATURE_IND_T;

/*!
    @brief This message is sent to App to indicate the charger voltage level and its value.
*/
typedef struct
{
    voltage_reading vchg;
} POWER_CHARGER_VOLTAGE_IND_T;

/*!
    @brief This message is sent to App to indicate the charger voltage level for dynamic current limiting.
*/
typedef struct
{
    uint16 voltage;
} POWER_CHARGER_CURRENT_LIMITING_IND_T;

/*!
    @brief This message is sent to App to indicate the charging state.
*/
typedef struct
{
    power_charger_state   state;
} POWER_CHARGER_STATE_IND_T;

/****************************************************************************
NAME    
    PowerInit
    
DESCRIPTION
    This function will initialise the battery and battery charging sub-system
    The sub-system manages the reading and calulation of the battery voltage 
    and temperature
    
    The application will receive a POWER_INIT_CFM message from the 
    library indicating the initialisation status.
    
RETURNS
    void
*/
void PowerInit(Task clientTask, const power_config *power_data, const power_pmu_temp_mon_config *pmu_mon_config);


/****************************************************************************
NAME
    PowerBatteryGetVoltage
    
DESCRIPTION
    Call this function to get the current battery voltage (in mV) and the 
    level
 
RETURNS
    bool
*/
bool PowerBatteryGetVoltage(voltage_reading* vbat);


/****************************************************************************
NAME
    PowerBatteryGetTemperature
    
DESCRIPTION
    Call this function to get the current thermistor voltage (in mV) and the
    level
    
RETURNS
    bool
*/
bool PowerBatteryGetTemperature(voltage_reading *vthm);


/****************************************************************************
NAME
    PowerChargerGetVoltage
    
DESCRIPTION
    Call this function to get the current charger voltage (in mV)
    
RETURNS
    bool
*/
bool PowerChargerGetVoltage(voltage_reading* vchg);


/****************************************************************************
NAME
    PowerChargerGetState
    
DESCRIPTION
    The value pointed to by state will be set to the updated charger state 
    unless state is NULL.
    
RETURNS
    void
*/
void PowerChargerGetState(power_charger_state* state);


/****************************************************************************
NAME
    PowerChargerMonitor
    
DESCRIPTION
    Enable/disable the charger monitoring. Monitoring is enabled by default 
    but is disabled when charger detach is detected. It is up to the 
    application to re-enable charger monitoring when the charger is attached
    
RETURNS
    void
*/
void PowerChargerMonitor(void);


/****************************************************************************
NAME
    PowerChargerEnable
    
DESCRIPTION
    Enable/disable the charger.
    
RETURNS
    void
*/
void PowerChargerEnable(bool enable);


/****************************************************************************
NAME
    PowerChargerSetCurrent
    
DESCRIPTION
    Set charger current level (actual current for each level (0-15) can be
    found in the data sheet for your chip). For newer chips such as Dale or
    Gordon the value in mA should be given (this value will be rounded to 
    the nearest possible current setting).
    
RETURNS
    void
*/
void PowerChargerSetCurrent(uint16 current);


/****************************************************************************
NAME    
    PowerChargerSetBoost
    
DESCRIPTION
    Configure boost settings. By default this is disabled, but can be 
    configured to draw boost current from internal/external transistor. 
    Boost charge will be enabled on entering fast charge unless the boost 
    cycle has already completed. The boost cycle is reset on charger attach.
    
RETURNS
    void
*/
void PowerChargerSetBoost(power_boost_enable boost);


/****************************************************************************
NAME
    PowerChargerSetVterm
    
DESCRIPTION
    Reduce the termination voltage to (vterm * PowerChargerGetVoltageScale()). This will
    fail if requested termination voltage is higher than the configured 
    termination voltage.
    
RETURNS
    bool
*/
bool PowerChargerSetVterm(uint8 vterm);

/****************************************************************************
NAME
    PowerChargerGetVterm

DESCRIPTION
    Return the currently set termination voltage.

RETURNS
    uint8
*/
uint8 PowerChargerGetVterm(void);

/****************************************************************************
NAME
    PowerChargerGetVtermMillivolts

DESCRIPTION
    Return the currently set termination voltage in millivolts.

RETURNS
    uint16
*/
uint16 PowerChargerGetVtermMillivolts(uint8 vterm);

/****************************************************************************
NAME
    PowerChargerGetVoltageScale

DESCRIPTION
    Gets the voltage scalar for the charger version.

RETURNS
    uint16
*/
uint16 PowerChargerGetVoltageScale(void);

/****************************************************************************
NAME
    PowerChargerSuppressLed0

DESCRIPTION
    Suppress LED0 whilst charging.

RETURNS
    void
*/
void PowerChargerSuppressLed0(bool suppress);

/****************************************************************************
NAME
    PowerChargerConfigure

DESCRIPTION
    Initialise power charger
*/
void PowerChargerConfigure(void);

/****************************************************************************
NAME
    PowerChargerEnabled

DESCRIPTION
    Check if charger is enabled

RETURNS
    TRUE if enabled, FALSE otherwise
*/
bool PowerChargerEnabled(void);

/****************************************************************************
NAME
    PowerChargerExternalModeResistance

DESCRIPTION
    The external mode resistance is derived from the value and tolerance of
    the fitted external resistor and the tolerance of the charging circuit
    itself, which is 1%.

RETURNS
    TRUE if enabled, FALSE otherwise
*/
uint16 PowerChargerExternalModeResistance(uint16 resistor_value, uint8 resistor_tolerance);

/****************************************************************************
NAME
    PowerMonitorStartChargerProgressMonitor

DESCRIPTION
    Start monitoring Charger Progress Monitor.

RETURNS
    void
*/
void PowerMonitorStartChargerProgressMonitor(void);

/****************************************************************************
NAME
    PowerMonitorStopChargerProgressMonitor

DESCRIPTION
    Stop monitoring Charger Progress Monitor.

RETURNS
    void
*/
void PowerMonitorStopChargerProgressMonitor(void);


/****************************************************************************
NAME
    PowerCurrentLimitingHandleMonitorReq

DESCRIPTION
    Handle current limiting power monitoring requests.

RETURNS
    void
*/
void PowerCurrentLimitingHandleMonitorReq(uint16 vchgReading);

/****************************************************************************
NAME
    PowerCurrentLimitingStart

DESCRIPTION
    Start limiting the current.

RETURNS
    void
*/
void PowerCurrentLimitingStart(void);

/****************************************************************************
NAME
    PowerCurrentLimitingStop

DESCRIPTION
    Stop limiting the current.

RETURNS
    void
*/
void PowerCurrentLimitingStop(void);

/****************************************************************************
NAME
    PowerCurrentLimitingHandleHeadroomError

DESCRIPTION
    Handle current limiting 'Headroom Error' handler.

RETURNS
    void
*/
void PowerCurrentLimitingHandleHeadroomError(void);

/****************************************************************************
NAME
    PowerBatteryIsOverVoltage

DESCRIPTION
    This function is called by applications to check whether the battery
    is in Over Voltage.

RETURNS
    bool
*/
bool PowerBatteryIsOverVoltage(void);

/****************************************************************************
NAME
    PowerBatteryIsRecoveredFromOverVoltage

DESCRIPTION
    This function is called by applications to check whether the battery
    has recovered from Over Voltage.

RETURNS
    bool
*/
bool PowerBatteryIsRecoveredFromOverVoltage(voltage_reading vbat);

#endif     /* POWER_H_ */
