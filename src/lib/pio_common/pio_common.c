/****************************************************************************
Copyright (c) 2005 - 2015 Qualcomm Technologies International, Ltd.

FILE NAME
    pio_common.c

DESCRIPTION
    Common PIO opperations used by libraries and applications

NOTES

*/


/****************************************************************************
    Header files
*/
#include <pio.h>
#include <print.h>
#include "pio_common.h"
#include <string.h>
#include <panic.h>

/* Input/Pull are the same */
#define pio_input   pio_pull


/* PIO mask creation macros */

#define PIO_NONE        (0)
#define PIO_MASK(x)     (PIN_IS_VALID(x) ? ((uint32)1 << ((x) & 0x1F)) : PIO_NONE)

pio_common_allbits gInvertMask;

/****************************************************************************
NAME
    pioCommonPreparePin
    
DESCRIPTION
    This function converts from a pin to a PIO pins
*/
static uint32 pioCommonGetMask(uint8 pin, pio_common_dir dir)
{
    uint32 mask = PIO_MASK(pin);

    if (PioSetDir32(mask, (dir ? mask : 0)) != PIO_NONE)
        return PIO_NONE;

    return mask;
}


/****************************************************************************
NAME
    PioCommonSetPin
    
DESCRIPTION
    This function will drive/pull a PIO to the specified level
*/
bool PioCommonSetPin(uint8 pin, pio_common_dir dir, bool level)
{
    uint32 mask = pioCommonGetMask(pin, dir);

    PRINT(("PIO: %s %d (0x%lX) ", (dir ? "Drive" : "Pull"), pin, mask));
    level = PioCommonAllBitsBitIsSet(&gInvertMask, pin) ? !level : level;
    if((mask != PIO_NONE) && (PioSet32(mask, (level ? mask : 0)) == PIO_NONE))
    {
        PRINT(("%s\n", level ? "High" : "Low"));
        return TRUE;
    }
    PRINT(("Failed\n"));
    return FALSE;
}


/****************************************************************************
NAME
    PioCommonGetPin
    
DESCRIPTION
    This function will configure a pin as input and attempt to read it. This
    will return TRUE if the pin is high, FALSE if the pin is low or could
    not be configured.
*/
bool PioCommonGetPin(uint8 pin)
{
    uint32 mask = pioCommonGetMask(pin, pio_input);

    PRINT(("PIO: Get %d (0x%lX) ", pin, mask));
    mask &= PioGet32();
    PRINT(("%s\n", mask ? "High" : "Low"));

    return ((mask != PIO_NONE) ? TRUE : FALSE);
}



/*
    This function configures the requested pin_mask as inputs and attempts to 
    debounce them.

    Successful debounce of pins leads to the #MESSAGE_PIO_CHANGED message
    being sent to the task registered with MessagePioTask().

    If it is not possible to set up debounce on all the requested pins then 
    this function debounces all possible PIOs and returns FALSE.
*/
bool PioCommonDebounce(const pio_common_allbits *pin_mask, uint16 count, uint16 period)
{
    uint32              result;
    pio_common_allbits  allowed_mask;
    bool                debounce_mask_limited = FALSE;

    if (pin_mask)
    {
        allowed_mask = *pin_mask;

        PRINT(("PIO: Debounce %08lx\n",allowed_mask.mask[0]));
        PioSetDir32(allowed_mask.mask[0], pio_input);
        result = PioDebounce32(allowed_mask.mask[0], count, period);

        if(result != PIO_NONE)
        {
            /* Clear the bits that failed */
            allowed_mask.mask[0] &= ~result;
            debounce_mask_limited = TRUE;
        }

        if (!debounce_mask_limited)
        {
            return TRUE;
        }

        PRINT(("PIO: Debounce retry %08lx\n",allowed_mask.mask[0]));
        PioDebounce32(allowed_mask.mask[0], count, period);
    }

    return FALSE;
}

/*
    Specifies pins to be used as pios rather than their normal function.

    returns TRUE if requested changes were successful. FALSE, and a non-zero result, 
            in case of failure
*/ 
bool PioCommonSetMap(pio_common_allbits *result, const pio_common_allbits *mask, 
                     const pio_common_allbits *bits)
{
    if (result && mask && bits)
    {

        result->mask[0] = PioSetMapPins32(mask->mask[0], bits->mask[0]);
        if (result->mask[0] == PIO_NONE)
        {
            return TRUE;
        }
    }
    else
    {
        /* Panic here as the value of result is misleading otherwise */
        Panic();
    }

    return FALSE;
}

/*
    This function initialises a pin_mask to zero.
*/
void PioCommonAllBitsInit(pio_common_allbits *mask)
{
    if (mask)
    {
        memset(mask,0,sizeof(*mask));
    }
}

/*
    This function adds a bit representing the requested pio to to a pin_mask.
*/
void PioCommonAllBitsSetBit(pio_common_allbits *mask,unsigned pio)
{
    if (mask)
    {
        mask->mask[0] |= PIO_MASK(pio);
    }
}

/*
    Check if a specified PIO is enabled in the supplied mask.

    returns TRUE if the bit is set, FALSE if not set or the mask pointer is NULL.
*/
bool PioCommonAllBitsBitIsSet(const pio_common_allbits *mask,unsigned pio)
{
    if (mask)
    {
        uint32 bitmask = PIO_MASK(pio);

        if (mask->mask[0] & bitmask)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*
    Check if any PIOs are enabled in the supplied mask.

    @returns TRUE if no bits are set. Flags are not checked.
*/
bool PioCommonAllBitsIsEmpty(const pio_common_allbits *mask)
{
    return mask && (mask->mask[0] == 0);
}


/*
    Set the flags element of the pio_common_allbits structure to the supplied flags
*/
void PioCommonAllBitsSetFlags(pio_common_allbits *mask,uint32 flags)
{
    if (mask)
    {
        mask->flags = flags;
    }
}


/*
    This function combines two pio masks.

    The masks and flags, if any, are combined by logical OR.
*/
bool PioCommonAllbitsOR(pio_common_allbits *result,const pio_common_allbits *mask1,const pio_common_allbits *mask2)
{
    if (result && mask1 && mask2)
    {
        result->mask[0] = mask1->mask[0] | mask2->mask[0];
        result->flags = mask1->flags | mask2->flags;
        return (result->mask[0] | result->flags) != 0;
    }
    return FALSE;

}

/*
    This function combines two pio masks.

    The masks and flags, if any, are combined by logical XOR.
*/
bool PioCommonAllbitsXOR(pio_common_allbits *result,const pio_common_allbits *mask1,const pio_common_allbits *mask2)
{
    if (result && mask1 && mask2)
    {
        result->mask[0] = mask1->mask[0] ^ mask2->mask[0];
        result->flags = mask1->flags ^ mask2->flags;
        return (result->mask[0] | result->flags) != 0;
    }
    return FALSE;

}

/*
    This function combines two pio masks.

    The masks and flags, if any, are combined by logical AND.
*/
bool PioCommonAllbitsAND(pio_common_allbits *result,const pio_common_allbits *mask1,const pio_common_allbits *mask2)
{
    if (result && mask1 && mask2)
    {
        result->mask[0] = mask1->mask[0] & mask2->mask[0];
        result->flags = mask1->flags | mask2->flags;
        return (result->mask[0] | result->flags) != 0;
    }
    return FALSE;
}

/* 
    Read all PIOs into the supplied pio_common_allbits structure.

    return the passed pioState pointer. The structure will have been updated.
*/
pio_common_allbits *PioCommonAllBitsRead(pio_common_allbits *pioState)
{
    if (!pioState)
    {
        Panic();
    }

    PioCommonAllBitsInit(pioState);
    pioState->mask[0] = PioGet32();

    return pioState;
}


/* 
    Invert PIOs based on invert mask.

    return the passed pioState pointer. The structure will have been updated.
*/
pio_common_allbits *PioCommonAllBitsInvert(pio_common_allbits *pioState)
{
    if (!pioState)
    {
        Panic();
    }

    pioState->mask[0] = pioState->mask[0] ^ gInvertMask.mask[0];

    return pioState;
}

/*
    Stores the supplied invert mask.

    @param[in] pioInvertMask Pointer to the invert mask to be stored
*/
void PioCommonStoreInvertMask(const pio_common_allbits *pioInvertMask)
{
    gInvertMask.mask[0] = pioInvertMask->mask[0];
}

