/***************************************************************************
Copyright (c) 2004 - 2015 Qualcomm Technologies International, Ltd.
Part of ADK_CSR867x.WIN 4.3

FILE NAME
    sink_debug.h
    
DESCRIPTION
    
*/

#ifndef _SINK_DEBUG_H_
#define _SINK_DEBUG_H_


#ifndef RELEASE_BUILD /*allows the release build to ensure all of the below are removed*/
    
    /*The individual configs*/
    
 
#ifndef DO_NOT_DOCUMENT

#endif 
 /*end of DO_NOT_DOCUMENT*/

    /*The global debug enable*/ 
    #define DEBUG_PRINT_ENABLEDx

#define DEBUG_VM_HATSx

#ifdef DEBUG_VM_HATS
/*************************************************************************
NAME
	printVmLogsInTestSystem

DESCRIPTION
	This function prints logs of VM code in conjunction with HATS logs if
	it is enabled.

RETURNS
	void
*/
void printVmLogsInTestSystem (const char *format, ...);

#define PRINT_BUFF_SIZE      50
#define DEBUG(x)   {printVmLogsInTestSystem x;}

#endif /*DEBUG_VM_HATS*/

    #ifdef DEBUG_PRINT_ENABLED
	
        #ifndef DEBUG_VM_HATS
            #define DEBUG(x) {printf x;}
        #endif

        /*The individual Debug enables*/

        #define DEBUG_A2DPx
        #define DEBUG_ACCESSORYx
        #define DEBUG_AHIx

        /* Debug Always-on-Voice (AoV) module */
        #define DEBUG_AOVx

        #define DEBUG_AT_COMMANDSx
        #define DEBUG_AUDIO_PROMPTSx
        #define DEBUG_AUDIOx
        /* Debug Authentication*/
        #define DEBUG_AUTHx
        #define DEBUG_AUTO_POWER_OFFx
        #define DEBUG_AVRCPx
        #define DEBUG_BA_BROADCASTERx
        /* Broadcast Audio plugin debug */
        #define DEBUG_BA_PLUGINx
        #define DEBUG_BA_RECEIVERx
        /* Battery Reporting debug */ 
        #define DEBUG_BAT_REPx
        /* Broadcat audio debug */
        #define DEBUG_BA_COMMONx
        /* BLE GAP message debug */
        #define DEBUG_BLE_GAPx
        #define DEBUG_BLE_SCx
        /* BLE transport / messages debug */
        #define DEBUG_BLEx
        /*Debug button manager */
        #define DEBUG_BUT_MANx
        /* Debug Low Level Button Parsing*/
        #define DEBUG_BUTTONSx
        /* Debug Call Manager*/
        #define DEBUG_CALL_MANx
        /* Debug Config Manager */
        #define DEBUG_CONFIGx
        #define DEBUG_CSR2CSRx
        /* Debug sink_devicemanager.c */
        #define DEBUG_DEVx
        /* Dimming LEDs*/
        #define DEBUG_DIMx
        #define DEBUG_DISPLAYx
        /* Device Id */
        #define DEBUG_DIx
        #define DEBUG_DORMANTx
        #define DEBUG_DUTx
        /* Debug external charger interface */
        #define DEBUG_EXT_CHGx
        #define DEBUG_FILTER_ENABLEx
        #define DEBUG_FMx
        #define DEBUG_GAIAx
        #define DEBUG_GATT_ANCS_CLIENTx
        #define DEBUG_GATT_BATTERY_CLIENTx
        #define DEBUG_GATT_BATTERY_SERVERx
        #define DEBUG_GATT_CLIENTx
        #define DEBUG_GATT_DIS_CLIENTx
        #define DEBUG_GATT_HID_CLIENTx
        #define DEBUG_GATT_HID_QUALIFICATIONx
        /* Debug HID Remote Control */
        #define DEBUG_GATT_HID_RCx
        #define DEBUG_GATT_HRS_CLIENTx
        #define DEBUG_GATT_IAS_CLIENTx
        /* Debug Link Loss server */
        #define DEBUG_GATT_LLS_SERVERx
        #define DEBUG_GATT_MANAGERx
        #define DEBUG_GATT_SERVICE_CLIENTx
        #define DEBUG_GATT_SPC_CLIENTx
        #define DEBUG_GATTx
        #define DEBUG_HIDx
        #define DEBUG_INITx
        #define DEBUG_INPUT_MANAGERx
        /* RSSI pairing */
        #define DEBUG_INQx
        /* IR Remote Control debug */
        #define DEBUG_IR_RCx
        /* Debug Lower Level LED drive */
        #define DEBUG_LEDSx
        #define DEBUG_LINKLOSSx
        /* Debug LED manager */
        #define DEBUG_LMx
        /* Debug sink_link_policy.c */
        #define DEBUG_LPx
        /* Debug main system messages*/
        #define DEBUG_MAINx
        #define DEBUG_MALLOCx 
        #define DEBUG_MAPCx
        /* Debug Multipoint Manager*/
        #define DEBUG_MULTI_MANx
        #define DEBUG_NFCx
        #define DEBUG_PBAPx
        #define DEBUG_PEER_SMx
        #define DEBUG_PEERx
        /* Debug Lower Level PIO drive*/
        #define DEBUG_PIOx
        /* Debug Power Manager*/
        #define DEBUG_POWERx
        /* Debug BR EDR Secure connection. */
        #define DEBUG_SCx
        #define DEBUG_SLCx
        #define DEBUG_SPEECH_RECx
        /* State manager*/
        #define DEBUG_STATESx
        /* Debug Subwoofer  */
        #define DEBUG_SWATx
        #define DEBUG_TONESx
        #define DEBUG_USBx

        /* Debug Voice Assistant (VA) module */
        #define DEBUG_VAx

        #define DEBUG_VOLUMEx
        #define DEBUG_WIREDx

    #else
        #ifndef DEBUG_VM_HATS
            #define DEBUG(x) 
        #endif
    #endif /*DEBUG_PRINT_ENABLED*/

        /* If you want to carry out cVc license key checking in Production test
           Then this needs to be enabled */
    #define CVC_PRODTESTx

	/* Audio Prompt/Tone Sink Event Queue debug */
	#define DEBUG_AUDIO_PROMPTS_TONES_QUEUEx

	/*Audio Indication module to play prompt and tones*/
	#define DEBUG_AUDIO_INDICATIONx


#else /*RELEASE_BUILD*/    

 /*used by the build script to include the debug but none of the 
          individual debug components*/
		#ifndef DEBUG_VM_HATS
			#ifdef DEBUG_BUILD 
				#define DEBUG(x) {printf x;}
			#else
				#define DEBUG(x) 
			#endif /*DEBUG_BUILD*/
		#endif /*DEBUG_VM_HATS*/    
#endif /*RELEASE_BUILD*/

#ifdef DEBUG_PEER
	#define PEER_DEBUG(x) DEBUG(x)
#else
	#define PEER_DEBUG(x) 
#endif /*DEBUG_PEER*/



#define INSTALL_PANIC_CHECK
#define NO_BOOST_CHARGE_TRAPS
#undef SINK_USB
#define HAVE_VBAT_SEL
#define HAVE_FULL_USB_CHARGER_DETECTION

#endif /*_SINK_DEBUG_H_*/

