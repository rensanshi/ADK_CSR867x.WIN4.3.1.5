// -----------------------------------------------------------------------------
// Copyright (c) 2010 - 2015 Qualcomm Technologies International, Ltd.
// Generated by DerivationEngine.py
// source v1.1, namespace com.csr.cps.2 on 2018-03-01 05:08:23 by SHA-Audio_Dev
// from cvc_headset_2mic.xml $Revision: #1 $
// last modifed with $Change: 2929828 $ by $Author: ac52 $ on $DateTime: 2018/01/15 12:31:54 $
// -----------------------------------------------------------------------------
#ifndef __CVC_HEADSET_2MIC_CONFIG_H__
#define __CVC_HEADSET_2MIC_CONFIG_H__

#define uses_R_DIGITAL_MIC	0
#define uses_L_DIGITAL_MIC	0
#define uses_RCV_AGC      	1
#define uses_DCBLOCK      	1
#define uses_RCV_PEQ      	1
#define uses_SND_PEQ      	1
#define uses_NSVOLUME     	1
#define uses_SND_AGC      	1
#define uses_SND_NS       	1
#define uses_ADF          	1
#define uses_NC           	1
#define uses_PLC          	1
#define uses_AEQ          	1
#define uses_RCV_NS       	1
#define uses_AEC          	1
#define uses_VCAEC        	1
#define uses_MGDC         	1
#define uses_ASF          	1

#define flag_uses_R_DIGITAL_MIC	0x020000
#define flag_uses_L_DIGITAL_MIC	0x010000
#define flag_uses_RCV_AGC      	0x008000
#define flag_uses_DCBLOCK      	0x004000
#define flag_uses_RCV_PEQ      	0x002000
#define flag_uses_SND_PEQ      	0x001000
#define flag_uses_NSVOLUME     	0x000800
#define flag_uses_SND_AGC      	0x000400
#define flag_uses_SND_NS       	0x000200
#define flag_uses_ADF          	0x000100
#define flag_uses_NC           	0x000080
#define flag_uses_PLC          	0x000040
#define flag_uses_AEQ          	0x000020
#define flag_uses_RCV_NS       	0x000010
#define flag_uses_AEC          	0x000008
#define flag_uses_VCAEC        	0x000004
#define flag_uses_MGDC         	0x000002
#define flag_uses_ASF          	0x000001


// Bit-mask flags to return in SPI status, which tells the Parameter Manager
// (Windows Realtime Tuning GUI) which modules are included in the build.  The
// mask is also written to the kap file so that the build configuration can be
// identified using a text editor.

#define CVC_HEADSET_2MIC_CONFIG_FLAG	uses_R_DIGITAL_MIC*flag_uses_R_DIGITAL_MIC +  uses_L_DIGITAL_MIC*flag_uses_L_DIGITAL_MIC +  uses_RCV_AGC*flag_uses_RCV_AGC +  uses_DCBLOCK*flag_uses_DCBLOCK +  uses_RCV_PEQ*flag_uses_RCV_PEQ +  uses_SND_PEQ*flag_uses_SND_PEQ +  uses_NSVOLUME*flag_uses_NSVOLUME +  uses_SND_AGC*flag_uses_SND_AGC +  uses_SND_NS*flag_uses_SND_NS +  uses_ADF*flag_uses_ADF +  uses_NC*flag_uses_NC +  uses_PLC*flag_uses_PLC +  uses_AEQ*flag_uses_AEQ +  uses_RCV_NS*flag_uses_RCV_NS +  uses_AEC*flag_uses_AEC +  uses_VCAEC*flag_uses_VCAEC +  uses_MGDC*flag_uses_MGDC +  uses_ASF*flag_uses_ASF


#endif // __CVC_HEADSET_2MIC_CONFIG_H__
