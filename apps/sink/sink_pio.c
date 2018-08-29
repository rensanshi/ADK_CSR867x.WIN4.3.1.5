/*
Copyright (c) 2004 - 2016 Qualcomm Technologies International, Ltd.
*/

/*!
@file
@ingroup sink_app
*/

#include "sink_pio.h"

#include "sink_configmanager.h"
#include "sink_leds.h"

#include <pio.h>
#include <psu.h>
/* Include config store and definition headers */
#include "config_definition.h"
#include "sink_pio_config_def.h"
#include <config_store.h>

#ifdef DEBUG_PIO
#define PIO_DEBUG(x)  DEBUG (x)
#else
#define PIO_DEBUG(x) 
#endif

#define PIO_CONFIG_ERROR  16

#define PIO_WRITE_SESSION_DATA_DELAY (D_SEC(5))

#ifdef __GNUC__
    /* PioSetMapPins32 should not try to map PIO_29, PIO_30, PIO_31 */
#define PIO_MAP_VALID_BITS(pio_map) do { \
                pio_map.mask[0] &= 0x1FFFFFFF;\
            } while(0)
#else
#define PIO_MAP_VALID_BITS(pio_map) ((void)0)
#endif

/* Pack higher and lower uint16s to form Uint32 bitmask */
#define PACK_32(pio_low, pio_high) (((uint32)pio_high << 16) | ((uint32) (pio_low) & 0x0000FFFFUL))

static bool user_pio_state;
                
static void pioConfigGetInvertMask(void);
static void pioReadSessionData(void);

/****************************************************************************
NAME	
	PioSetMapPins

DESCRIPTION
    Map PIO pins as per configurations
    
RETURNS
	TRUE: Success, FALSE: Failure
*/
static bool pioSetMapPins(const pio_common_allbits *pio_map)
{
    pio_common_allbits allowed_map = *pio_map;
    pio_common_allbits result;

    PIO_MAP_VALID_BITS(allowed_map);

    /* Map in any required pins */
    PIO_DEBUG(("PIO: Map PIO\n"));

    if (!PioCommonSetMap(&result, &allowed_map, &allowed_map))
    {
        PIO_DEBUG(("  -- bad pins detected\n"));
        return FALSE;
    }
    return TRUE;
}

/****************************************************************************
NAME	
	PioInit

DESCRIPTION
    Function to Initialize PIO module
    
RETURNS
	TRUE: Success, FALSE: Failure
*/
bool PioInit(void)
{
    pio_common_allbits pio_map;

    pioConfigGetInvertMask();
    pioReadSessionData();
    
    return pioSetMapPins(PioGetPioMap(&pio_map));
}

/****************************************************************************
NAME	
	PioSetPio

DESCRIPTION
    Fn to change a PIO
    Set drive pio_drive to drive PIO, pio_pull to pull PIO
    Set dir TRUE to set high, FALSE to set low
    
RETURNS
	void
*/
void PioSetPio(uint8 pio, pio_common_dir drive, bool dir) 
{
    PIO_DEBUG(("PIO: %s pin %d %s\n", (drive ? "Drive" : "Pull"), pio, (dir ? "high" : "low")));
    PioCommonSetPin(pio, drive, dir);
}


/****************************************************************************
NAME	
	PioGetPio

DESCRIPTION
    Fn to read a PIO
    
RETURNS
	TRUE if set, FALSE if not
*/
bool PioGetPio(uint8 pio)
{
    bool result =  PioCommonGetPin(pio);    
    PIO_DEBUG(("PIO: Read pin %d [state = %s]\n", pio,result ? "high" : "low"));
    return result;
}


/****************************************************************************
NAME	
	PioDrivePio

DESCRIPTION
    Drive a PIO to the passed state if configured.
    
RETURNS
	void
    
*/
void PioDrivePio(uint8 pio, bool state)
{
    if (pio != NO_PIO)
    {
        PioSetPio(pio, pio_drive, state);
    }
}


/****************************************************************************
NAME	
	PioSetPowerPin

DESCRIPTION
    controls the internal regulators to latch / remove the power on state
    
RETURNS
	void
*/
void PioSetPowerPin ( bool enable ) 
{
    /* power on or off the smps */
#ifdef BC5_MULTIMEDIA
    PsuConfigure(PSU_SMPS0, PSU_ENABLE, enable);
#elif !defined(HYDRACORE) || TRAPSET_PSU
    /* when shutting down ensure all psus are off for BC7 chips */
    if(!enable)
        PsuConfigure(PSU_ALL, PSU_ENABLE, enable);
#else
    UNUSED(enable);   /* Only used for debug */
#endif
    PIO_DEBUG(("PIO : PowerOnSMPS %X\n", enable)) ;      
}


/****************************************************************************
NAME
    pioConfigGetInvertMask

DESCRIPTION
      Interface to get PIO invert Mask

RETURNS
    Uint32 value if there is a mask else 0
*/
static void pioConfigGetInvertMask(void)
{
    pio_common_allbits mask;
    pio_readonly_config_def_t *read_config_data = NULL;

    PioCommonAllBitsInit(&mask);

    if (configManagerGetReadOnlyConfig(PIO_READONLY_CONFIG_BLK_ID, (const void **)&read_config_data))
    {
        mask.mask[0] = PACK_32(read_config_data->pio_invert_0_15, read_config_data->pio_invert_16_31);
#if NUMBER_OF_PIO_BANKS > 1
        mask.mask[1] = PACK_32(read_config_data->pio_invert_32_47, read_config_data->pio_invert_48_63);
# if NUMBER_OF_PIO_BANKS > 2
        mask.mask[2] = PACK_32(read_config_data->pio_invert_64_79, read_config_data->pio_invert_80_95);
#  if NUMBER_OF_PIO_BANKS > 3
#   error "Need to update code for more pio banks"
#  endif
# endif
#endif
        configManagerReleaseConfig(PIO_READONLY_CONFIG_BLK_ID);
    }

    PioCommonStoreInvertMask(&mask);
}


/****************************************************************************
NAME
    PioGetPioMap

DESCRIPTION
    Interface to get the PIO map

RETURNS
    Uint32 value if there is a pio map else 0
*/
pio_common_allbits *PioGetPioMap(pio_common_allbits *map)
{
   pio_readonly_config_def_t *read_config_data = NULL;

   PioCommonAllBitsInit(map);

   if (   map
       && configManagerGetReadOnlyConfig(PIO_READONLY_CONFIG_BLK_ID, (const void **)&read_config_data))
   {
        map->mask[0] = PACK_32(read_config_data->pio_mapping_0_15, read_config_data->pio_mapping_16_31);
#if NUMBER_OF_PIO_BANKS > 1
        map->mask[1] = PACK_32(read_config_data->pio_mapping_32_47, read_config_data->pio_mapping_48_63);
# if NUMBER_OF_PIO_BANKS > 2
        map->mask[2] = PACK_32(read_config_data->pio_mapping_64_79, read_config_data->pio_mapping_80_95);
#  if NUMBER_OF_PIO_BANKS > 3
#   error "Need to update code for more pio banks"
#  endif
# endif
#endif
        configManagerReleaseConfig(PIO_READONLY_CONFIG_BLK_ID);
   }
   return map;
}

/****************************************************************************
NAME
        PioGetPioMask

DESCRIPTION
    Interface to get the PIO mask based on the bank number

PARAMETERS
	bank_number which specify the pio pack range

RETURNS
    uint32 value based on the bank number
*/
uint32 PioGetPioMask(uint8 bank_number)
{
   pio_readonly_config_def_t *read_config_data = NULL;
   uint32 ret_val = 0;

   if (configManagerGetReadOnlyConfig(PIO_READONLY_CONFIG_BLK_ID, (const void **)&read_config_data))
   {
        if (bank_number == 0)
                ret_val =   PACK_32(read_config_data->pio_mapping_0_15, read_config_data->pio_mapping_16_31);

#if NUMBER_OF_PIO_BANKS > 1
        else if (bank_number == 1)
                ret_val =   PACK_32(read_config_data->pio_mapping_32_47, read_config_data->pio_mapping_48_63);
#endif
            
#if NUMBER_OF_PIO_BANKS > 2
        else if (bank_number == 2)
                ret_val =    PACK_32(read_config_data->pio_mapping_64_79, read_config_data->pio_mapping_80_95);
#endif
        configManagerReleaseConfig(PIO_READONLY_CONFIG_BLK_ID);
   }
   return ret_val;
}

/****************************************************************************
NAME
    PioGetUserPio

DESCRIPTION
    Gets the PIO configured for user event control

RETURNS
    PIO number
*/
static uint8 PioGetUserPio(void)
{
   pio_readonly_config_def_t *read_config_data = NULL;
   uint8 pio = PIN_INVALID;

   if (configManagerGetReadOnlyConfig(PIO_READONLY_CONFIG_BLK_ID, (const void **)&read_config_data))
   {
       pio = read_config_data->user_pio;
       configManagerReleaseConfig(PIO_READONLY_CONFIG_BLK_ID);
   }
   
   return pio;
}

/****************************************************************************
NAME
    PioDriveUserPio

DESCRIPTION
    Sets the state of the user-configurable PIO

RETURNS
    void
*/
void PioDriveUserPio(bool state)
{
    PioDrivePio(PioGetUserPio(), state);
}

/****************************************************************************
NAME
    PioGetUserPioState

DESCRIPTION
    Gets the stored state of the PIO configured for user event control

RETURNS
    TRUE if PIO is active, FALSE otherwise
*/
bool PioGetUserPioState(void)
{
    return user_pio_state;
}

/****************************************************************************
NAME
    PioSetUserPioState

DESCRIPTION
    Sets the stored state of the PIO configured for user event control

RETURNS
    void
*/
void PioSetUserPioState(bool state)
{
    user_pio_state = state;
    PioDriveUserPio(user_pio_state);
    sinkCancelAndSendLater(EventSysPioWriteSessionData, PIO_WRITE_SESSION_DATA_DELAY);
}

/****************************************************************************
NAME
    PioHandleEvent

DESCRIPTION
    Handles a user event which changes the state of the configured PIO

RETURNS
    void
*/
void PioHandleUserEvent(sinkEvents_t event)
{
    bool new_state = user_pio_state;
    
    switch (event)
    {
    case EventUsrPioClear:
        new_state = FALSE;
        break;
        
    case EventUsrPioSet:
        new_state = TRUE;
        break;
        
    case EventUsrPioToggle:
        new_state = !user_pio_state;
        break;
        
    default:
        PIO_DEBUG(("PIO: unhandled 0x%04X\n", event));
        return;
    }
    
    if (new_state != user_pio_state)
    {
        PioSetUserPioState(new_state);
    }
}

/****************************************************************************
NAME
    pioReadSessionData

DESCRIPTION
    Reads module session data from configuration storage

RETURNS
    void
*/
static void pioReadSessionData(void)
{
    pio_writeable_config_def_t *rw_config_data;
    
    if (configManagerGetReadOnlyConfig(PIO_WRITEABLE_CONFIG_BLK_ID, (const void**)&rw_config_data))
    {
        user_pio_state = rw_config_data->user_pio_state;
        configManagerReleaseConfig(PIO_WRITEABLE_CONFIG_BLK_ID);
    }
}
/****************************************************************************
NAME
    PioWriteSessionData

DESCRIPTION
    Writes module session data to configuration storage

RETURNS
    void
*/
void PioWriteSessionData(void)
{
    pio_writeable_config_def_t *rw_config_data;
    
    if (configManagerGetWriteableConfig(PIO_WRITEABLE_CONFIG_BLK_ID, (void**)&rw_config_data, 0))
    {
        rw_config_data->user_pio_state = user_pio_state;
        configManagerUpdateWriteableConfig(PIO_WRITEABLE_CONFIG_BLK_ID);
    }
}
