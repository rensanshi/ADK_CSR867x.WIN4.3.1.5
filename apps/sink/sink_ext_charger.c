/*
Copyright (c) 2017 Qualcomm Technologies International, Ltd.
*/

/*!
@file
@ingroup sink_app
@brief
    Module responsible for interfacing with SMB1352 battery charger
************************************************************************/

#include <i2c.h>
#include "sink_configmanager.h"
#include "sink_debug.h"

#ifdef ENABLE_EXT_CHARGER

#include "sink_ext_charger.h"
#include "sink_ext_charger_config_def.h"

#ifdef DEBUG_EXT_CHG
#define EXT_CHG_DEBUG(x) DEBUG(x)
#else
#define EXT_CHG_DEBUG(x) 
#endif

#define EXT_CHG_REG_CMD_I2C (0x30)
#define EXT_CHG_CMD_ENABLE_VOLATILE_WRITES (0x40)

static uint8 ext_chg_i2c_address;

/****************************************************************************
NAME
    reg_read

DESCRIPTION
    Read from a register on the external charger

RETURNS
    TRUE iff the read was successful
*/
static bool reg_read(uint8 reg, uint8 *data)
{
    uint16 ack = I2cTransfer(ext_chg_i2c_address, &reg, 1, data, 1);
    
    /* Expect addr + reg + addr + data (4 bytes) acknowledged */
    if (ack == 4)
    {
        return TRUE;
    }
    
    EXT_CHG_DEBUG(("ext_chg: reg read failed; addr=0x%02X len=%u\n", ext_chg_i2c_address, ack));
    return FALSE;    
}


/****************************************************************************
NAME
    reg_write

DESCRIPTION
    Write to a register on the external charger

RETURNS
    TRUE iff the write was successful
*/
static bool reg_write(uint8 reg, uint8 data)
{
    uint8 packet[2];
    uint16 ack;
    
    packet[0] = reg;
    packet[1] = data;
    ack = I2cTransfer(ext_chg_i2c_address, packet, 2, NULL, 0);
    
    /*  Expect addr + reg + data (3 bytes) acknowledged */
    if (ack == 3)
    {
        return TRUE;
    }
    
    EXT_CHG_DEBUG(("ext_chg: reg write failed; addr=0x%02X len=%u\n", ext_chg_i2c_address, ack));
    return FALSE;    
}


/****************************************************************************
NAME
    reg_write_enable

DESCRIPTION
    Enable / disable writes to the external charger configuration registers,
    panic on failure

RETURNS
    void
*/
static void reg_write_enable(bool enable)
{
    PanicFalse(reg_write(EXT_CHG_REG_CMD_I2C, enable ? EXT_CHG_CMD_ENABLE_VOLATILE_WRITES : 0));
}


/****************************************************************************
NAME
    sinkExtChargerInit

DESCRIPTION
    Initialise the external charger by writing the stored configuration,
    panic on failure

RETURNS
    void
*/
void sinkExtChargerInit(void)
{
    ext_charger_config_def_t *config;
    uint16 size;
    
    size = configManagerGetReadOnlyConfig(EXT_CHARGER_CONFIG_BLK_ID, (const void **) &config);
    EXT_CHG_DEBUG(("ext_chg: size=%u\n", size));
    if (size)
    {
        uint16 reg;
        
        ext_chg_i2c_address = config->ext_charger_i2c;
        
        reg_write_enable(TRUE);
        for (reg = 0; reg < EXT_CHG_NUM_REGS; ++reg)
        {
            PanicFalse(reg_write(reg, config->ext_charger_data[reg]));
        }
    }
    
    configManagerReleaseConfig(EXT_CHARGER_CONFIG_BLK_ID);
    reg_write_enable(FALSE);
    
    EXT_CHG_DEBUG(("float %u mV\n", sinkExtChargerReadFloatVoltage()));
}


/****************************************************************************
NAME
    sinkExtChargerReadFloatVoltage

DESCRIPTION
    Read the float voltage from the external charger

RETURNS
    Float voltage in millivolts
*/
uint16 sinkExtChargerReadFloatVoltage(void)
{
    uint8 data;
    
    PanicFalse(reg_read(EXT_CHG_REG_STS_FLOAT_VOLTAGE, &data));

    return EXT_CHG_FLOAT_BASE_MILLIVOLTS + EXT_CHG_FLOAT_STEP_MILLIVOLTS * (data & EXT_CHG_MASK_STS_FLOAT_VOLTAGE);
}

#endif /* def ENABLE_EXT_CHARGER */
