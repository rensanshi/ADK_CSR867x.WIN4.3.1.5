/*************************************************************************
Copyright (c) 2005 - 2017 Qualcomm Technologies International, Ltd.
 Part of ADK_CSR867x.WIN 4.3

FILE : 
    pio_common.h

CONTAINS:
    Common PIO operations used by libraries and applications

**************************************************************************/

#ifndef PIO_COMMON_H_
#define PIO_COMMON_H_

#define PIN_INVALID 0xFF

/*!
    @brief Define the types for the upstream messages sent from the Power
    library to the application.
*/
typedef enum
{
    pio_pull, 
    pio_drive
} pio_common_dir;

typedef enum
{
    pin_pcma_in     = (1 <<  0),
    pin_pcma_out    = (1 <<  1),
    pin_pcma_sync   = (1 <<  2),
    pin_pcma_clk    = (1 <<  3),
    pin_pcmb_in     = (1 <<  4),
    pin_pcmb_out    = (1 <<  5),
    pin_pcmb_sync   = (1 <<  6),
    pin_pcmb_clk    = (1 <<  7),
    pin_spdifa_rx   = (1 <<  8),
    pin_spdifa_tx   = (1 <<  9),
    pin_spdifb_rx   = (1 << 10),
    pin_spdifb_tx   = (1 << 11)
} pio_common_pin_t;

#ifndef NUMBER_OF_PIOS
# ifdef HYDRACORE
#  define NUMBER_OF_PIOS   96
# else
#  define NUMBER_OF_PIOS   32
# endif
#endif
#ifndef PIOS_PER_BANK
# define PIOS_PER_BANK 32
#endif
#ifndef NUMBER_OF_PIO_BANKS
# define NUMBER_OF_PIO_BANKS ((NUMBER_OF_PIOS+PIOS_PER_BANK-1) / (PIOS_PER_BANK))
#endif

#define PIN_IS_VALID(x) ((x) < NUMBER_OF_PIOS)

/*!
 * Structure used to contains mask or values from all PIOs. 
 *
 * A structure is provided for this as some supported devices have more than 
 * 32 PIOs.
 */
typedef struct
{
        /*! Actual mask or value. The accessor functions for this type should
         *  be used to access specific bits. */
    uint32 mask[NUMBER_OF_PIO_BANKS];
        /*! Flags that may be associated with the PIO state. No meaning is applied
         *  to this by the pio_common library. */
    uint32 flags;
} pio_common_allbits;

/****************************************************************************
NAME
    PioCommonSetPin
    
DESCRIPTION
    This function will drive/pull a PIO to the specified level
    
RETURNS
    TRUE if successful, FALSE otherwise
*/
bool PioCommonSetPin(uint8 pin, pio_common_dir dir, bool level);


/****************************************************************************
NAME
    PioCommonGetPin
    
DESCRIPTION
    This function will configure a pin as input and attempt to read it. This
    will return TRUE if the pin is high, FALSE if the pin is low or could
    not be configured.
*/
bool PioCommonGetPin(uint8 pin);


/*!
    This function configures the requested  pin_mask as inputs and attempts to 
    debounce them.

    Successful debounce of pins leads to the #MESSAGE_PIO_CHANGED message
    being sent to the task registered with MessagePioTask().

    If it is not possible to set up debounce on all the requested pins then 
    this function debounces all possible PIOs and returns FALSE.

    @note This overrides any previous calls to PioCommonDebounce or 
    PioDebounce32Bank.

    @param[in] pin_mask Pointer to pio_common_allbits structure with complete mask of PIOs
    @param count Number of successive reads required, see documentation for PioDebounce32Bank
    @param period Time between reads
    
    @returns TRUE If all pins requested debounced
*/
bool PioCommonDebounce(const pio_common_allbits *pin_mask, uint16 count, uint16 period);

/*! 
    Specifies pins to be used as pios rather than their normal function.

    \note The pios that may be successfully used as PIOs may be restricted on
    the device.

    If it is not possible to configure all pins as requested then the function 
    will populate the result with the pins that failed and return FALSE.

    \see PioSetMapPins32
    
    @param mask The mask of PIOs to be updated.
    @param bits The setting for the specific bits
    @param[in,out] result Pointer to a pio_common_allbits structure that will be populated 
            with any failed bits

    @returns TRUE if requested changes were successful. FALSE, and a non-zero result, 
            in case of failure
*/ 
bool PioCommonSetMap(pio_common_allbits *result, const pio_common_allbits *mask, const pio_common_allbits *bits);

/*!
    Initialise a pio_common_allbits structure to zero.

    @param[in,out] mask Pointer to pio_common_allbits structure 
*/
void PioCommonAllBitsInit(pio_common_allbits *mask);


/*!
    Add a bit representing the requested pio to to a pin_mask.

    @param[in,out] mask Pointer to pio_common_allbits structure to be modified
    @param[in] pio number of pio to be included in the mask
*/
void PioCommonAllBitsSetBit(pio_common_allbits *mask,unsigned pio);

/*!
    Check if a specified PIO is enabled in the supplied mask.

    @param mask pointer to a pio_common_allbits structure to be checked
    @param pio The PIO number to be checked.

    @returns TRUE if the bit is set, FALSE if not set or the mask pointer is NULL.
*/
bool PioCommonAllBitsBitIsSet(const pio_common_allbits *mask,unsigned pio);

/*!
    Check if any PIOs are enabled in the supplied mask.

    @param mask pointer to a pio_common_allbits structure to be checked

    @returns TRUE if no bits are set. Flags are not checked.
*/
bool PioCommonAllBitsIsEmpty(const pio_common_allbits *mask);

/*!
    Set the flags element of the pio_common_allbits structure to the supplied flags

    @param mask pointer to a pio_common_allbits structure to be updated
    @param flags the flags to be set
*/
void PioCommonAllBitsSetFlags(pio_common_allbits *mask,uint32 flags);


/*!
    This function combines two pio masks.

    The masks and flags, if any, are combined by logical OR.

    Either of the mask1 or mask2 parameters can be the same as result.

    @param[in,out] mask Pointer to pio_common_allbits structure to be modified
    @param[in] mask1 Pointer to pio_common_allbits structure to combined 
    @param[in] mask2 Pointer to pio_common_allbits structure to combined

    @returns TRUE if any bits or flags in the result are set false otherwise

*/
bool PioCommonAllbitsOR(      pio_common_allbits *result,
                        const pio_common_allbits *mask1,
                        const pio_common_allbits *mask2);

/*!
    This function checks for changes between two PIO masks

    The masks are checked for differences, in either direction, with a bit being set
    in the result if the bits are different.

    Either of the mask or old_mask parameter can be the same as result

    @param[in,out] result Pointer to pio_common_allbits structure for the result
    @param[in] mask Pointer to pio_common_allbits structure of current value.
    @param[in] old_mask Pointer to pio_common_allbits structure of previous value

    @return TRUE if any bits change changed, false otherwise
*/
bool PioCommonAllbitsXOR(      pio_common_allbits *result,
                         const pio_common_allbits *mask,
                         const pio_common_allbits *old_mask);

/*!
    This function ANDS two pio masks.

    The masks and flags, if any, are combined by logical AND.

    Either of the mask1 or mask2 parameters can be the same as result.

    @param[in,out] result Pointer to pio_common_allbits structure for the result
    @param[in] mask1 Pointer to pio_common_allbits structure to combine 
    @param[in] mask2 Pointer to pio_common_allbits structure to combine 

    @returns TRUE if any bits or flags in the result are set false otherwise
*/
bool PioCommonAllbitsAND(      pio_common_allbits *result,
                         const pio_common_allbits *mask1,
                         const pio_common_allbits *mask2);


/*!
    Read all PIOs into the supplied pio_common_allbits structure.

    @param[in,out] pioState Pointer to the structure to hold the read pio state

    @return the passed pioState pointer. The structure will have been updated.
*/
pio_common_allbits *PioCommonAllBitsRead(pio_common_allbits *pioState);


/*!
    Invert PIOs based on invert mask.

    Any bit specified in the pioInvertMask will be inverted in the supplied 
    pioState structure. Bits not affected by the pioInvertMask will be 
    unchanged. 

    @param[in,out] pioState Pointer to the structure to update

    @return the passed pioState pointer. The structure will have been updated.
*/
pio_common_allbits *PioCommonAllBitsInvert(pio_common_allbits *pioState);

/*!
    Stores the supplied invert mask.

    @param[in] pioInvertMask Pointer to the invert mask to be stored
*/
void PioCommonStoreInvertMask(const pio_common_allbits *pioInvertMask);

/*!
    Enables special functions of device pins.

    @param[in] pins Bitmap of pins to be enabled
*/
bool PioCommonEnableFunctionPins(pio_common_pin_t pins);

#endif /*PIO_COMMON_H_*/
