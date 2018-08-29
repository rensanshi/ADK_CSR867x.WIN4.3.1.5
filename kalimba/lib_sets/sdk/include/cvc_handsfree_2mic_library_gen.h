// -----------------------------------------------------------------------------
// Copyright (c) 2010 - 2015 Qualcomm Technologies International, Ltd.
// Generated by DerivationEngine.py
// source v1.1, namespace com.csr.cps.2 on 2018-03-01 05:08:37 by SHA-Audio_Dev
// from cvc_handsfree_2mic.xml $Revision: #1 $
// last modifed with $Change: 2929828 $ by $Author: ac52 $ on $DateTime: 2018/01/15 12:31:54 $
// -----------------------------------------------------------------------------
#ifndef __CVC_HANDSFREE_2MIC_LIBRARY_GEN_H__
#define __CVC_HANDSFREE_2MIC_LIBRARY_GEN_H__

// Algorithm IDs
.CONST $CVC_HANDSFREE_2MIC_SYSID     	0xA104;

// Piecewise Enables
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_PREP       		0x000800;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.PLCENA            		0x000400;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_NDVC       		0x000200;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.AEQENA            		0x000100;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BEXENA            		0x000080;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_SNDAGC     		0x000040;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_RCVAGC     		0x000020;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.CNGENA            		0x000010;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.RERENA            		0x000008;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.AECENA            		0x000004;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.SNDOMSENA         		0x000002;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.RCVOMSENA         		0x000001;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_ADFRNR     		0x001000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_ADFPS      		0x002000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_RPT_POSTP  		0x004000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.WIDE_MIC_ENA      		0x008000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_MGDC       		0x010000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_MGDCPERSIST		0x020000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_AGCPERSIST 		0x040000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.HDBYP             		0x080000;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_ADF        		0x000001;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_BF         		0x000002;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_AED        		0x000004;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_AEDNR      		0x000008;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_NC         		0x000010;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.BYPASS_NC_DIV     		0x000020;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.FLAG_TMP_MODE     		0x000040;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.DRIVER_LEFT_FLAG  		0x000080;
.CONST $M.CVC_HANDSFREE_2MIC.CONFIG.TEST_FLAG         		0x000100;

// SPI Status Block
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.CUR_MODE_OFFSET      		0;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.CALL_STATE_OFFSET    		1;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.SYS_CONTROL_OFFSET   		2;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.CUR_DAC_OFFSET       		3;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PRIM_PSKEY_OFFSET    		4;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.SEC_STAT_OFFSET      		5;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PEAK_DAC_OFFSET      		6;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PEAK_ADC_LEFT_OFFSET 		7;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PEAK_ADC_RIGHT_OFFSET		8;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PEAK_SCO_IN_OFFSET   		9;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PEAK_SCO_OUT_OFFSET  		10;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PEAK_MIPS_OFFSET     		11;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.NDVC_NOISE_EST_OFFSET		12;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.NDVC_DAC_ADJ_OFFSET  		13;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PEAK_AUX_OFFSET      		14;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.COMPILED_CONFIG      		15;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.VOLUME               		16;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.CONNSTAT             		17;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.PLC_PACKET_LOSS      		18;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.AEQ_GAIN_LOW         		19;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.AEQ_GAIN_HIGH        		20;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.AEQ_STATE            		21;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.AEQ_POWER_TEST       		22;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.AEQ_TONE_POWER       		23;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.NLP_TIER_HC_ACTIVE   		24;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.AEC_COUPLING_OFFSET  		25;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.VAD_RCV_DET_OFFSET   		26;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.SND_AGC_SPEECH_LVL   		27;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.SND_AGC_GAIN         		28;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.RCV_AGC_SPEECH_LVL   		29;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.RCV_AGC_GAIN         		30;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.INTERFACE_TYPE       		31;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.INPUT_RATE           		32;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.OUTPUT_RATE          		33;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.CODEC_RATE           		34;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.DSP_VOL_FLAG         		35;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.DSP_VOL              		36;
.CONST $M.CVC_HANDSFREE_2MIC.STATUS.BLOCK_SIZE                		37;

// System Mode
.CONST $M.CVC_HANDSFREE_2MIC.SYSMODE.STANDBY      		0;
.CONST $M.CVC_HANDSFREE_2MIC.SYSMODE.HFK          		1;
.CONST $M.CVC_HANDSFREE_2MIC.SYSMODE.SSR          		2;
.CONST $M.CVC_HANDSFREE_2MIC.SYSMODE.PSTHRGH_LEFT 		3;
.CONST $M.CVC_HANDSFREE_2MIC.SYSMODE.PSTHRGH_RIGHT		4;
.CONST $M.CVC_HANDSFREE_2MIC.SYSMODE.LPBACK       		5;
.CONST $M.CVC_HANDSFREE_2MIC.SYSMODE.MAX_MODES    		7;

// Call State
.CONST $M.CVC_HANDSFREE_2MIC.CALLST.UNKNOWN   		0;
.CONST $M.CVC_HANDSFREE_2MIC.CALLST.CONNECTED 		1;
.CONST $M.CVC_HANDSFREE_2MIC.CALLST.CONNECTING		2;
.CONST $M.CVC_HANDSFREE_2MIC.CALLST.MUTE      		3;

// System Control
.CONST $M.CVC_HANDSFREE_2MIC.CONTROL.DAC_OVERRIDE      		0x8000;
.CONST $M.CVC_HANDSFREE_2MIC.CONTROL.CALLSTATE_OVERRIDE		0x4000;
.CONST $M.CVC_HANDSFREE_2MIC.CONTROL.MODE_OVERRIDE     		0x2000;

// AEQ State

// System Control

// NLP State

// Interface
.CONST $M.CVC_HANDSFREE_2MIC.INTERFACE.ANALOG		0;
.CONST $M.CVC_HANDSFREE_2MIC.INTERFACE.I2S   		1;

// Parameter Block
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_HFK_CONFIG               		0;
// Send OMS
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_OMS_HFK_AGGR         		1;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SSR_OMS_AGGR             		2;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_OMS_HARMONICITY          		3;
// AEC
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_CNG_Q                    		4;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_CNG_SHAPE                		5;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DTC_AGGR                 		6;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_ENABLE_AEC_REUSE         		7;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEC_REF_LPWR_HB          		8;
// RER
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RER_AGGRESSIVENESS       		9;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RER_WGT_SY               		10;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RER_OFFSET_SY            		11;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RER_POWER                		12;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RER_VAR_THRESH           		13;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RERDT_OFF_THRESHOLD      		14;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RERDT_AGGRESSIVENESS     		15;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RERDT_POWER              		16;
// Power Margin
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MAX_LPWRX_MARGIN         		17;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_ADC_GAIN_LEFT            		18;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_ADC_GAIN_RIGHT           		19;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_ADCGAIN_SSR              		20;
// NDVC
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_HYSTERESIS          		21;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_ATK_TC              		22;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_DEC_TC              		23;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_NUMVOLSTEPS         		24;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_MAXNOISELVL         		25;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_MINNOISELVL         		26;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_LB                  		27;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_NDVC_HB                  		28;
// Send PEQ
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_CONFIG           		29;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_GAIN_EXP         		30;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_GAIN_MANT        		31;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B2        		32;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B1        		33;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B0        		34;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_A2        		35;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE1_A1        		36;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B2        		37;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B1        		38;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B0        		39;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_A2        		40;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE2_A1        		41;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B2        		42;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B1        		43;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B0        		44;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_A2        		45;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE3_A1        		46;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B2        		47;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B1        		48;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B0        		49;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_A2        		50;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE4_A1        		51;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B2        		52;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B1        		53;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B0        		54;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_A2        		55;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_STAGE5_A1        		56;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE1           		57;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE2           		58;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE3           		59;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE4           		60;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_PEQ_SCALE5           		61;
// Receive PEQ
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_CONFIG           		62;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_GAIN_EXP         		63;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_GAIN_MANT        		64;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_B2        		65;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_B1        		66;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_B0        		67;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_A2        		68;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_A1        		69;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_B2        		70;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_B1        		71;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_B0        		72;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_A2        		73;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_A1        		74;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_B2        		75;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_B1        		76;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_B0        		77;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_A2        		78;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_A1        		79;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_B2        		80;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_B1        		81;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_B0        		82;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_A2        		83;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_A1        		84;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_B2        		85;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_B1        		86;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_B0        		87;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_A2        		88;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_A1        		89;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_SCALE1           		90;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_SCALE2           		91;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_SCALE3           		92;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_SCALE4           		93;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_PEQ_SCALE5           		94;
// Inverse DAC Table
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE       		95;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE1      		96;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE2      		97;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE3      		98;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE4      		99;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE5      		100;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE6      		101;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE7      		102;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE8      		103;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE9      		104;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE10     		105;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE11     		106;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE12     		107;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE13     		108;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE14     		109;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE15     		110;
// sidetone and clipper
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_CLIP_POINT               		111;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BOOST                    		112;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BOOST_CLIP_POINT         		113;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SNDGAIN_MANTISSA         		114;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SNDGAIN_EXPONENT         		115;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCVGAIN_MANTISSA         		116;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCVGAIN_EXPONENT         		117;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PT_SNDGAIN_MANTISSA      		118;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PT_SNDGAIN_EXPONENT      		119;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PT_RCVGAIN_MANTISSA      		120;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PT_RCVGAIN_EXPONENT      		121;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_REF_DELAY                		122;
// Dual Mic
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PREP_DT_MIC              		123;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SQRT_PREP_SUBFACTOR      		124;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DMSS_REPL_ADJUST         		125;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DMSS_REPL_POWER          		126;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PREP_DT_FM2M             		127;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MGDC_ALFAD               		128;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MGDC_FRONTMICBIAS        		129;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MGDC_MAXCOMP             		130;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MGDC_ADAPT_THRESH        		131;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MGDC_TH0                 		132;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MGDC_TH1                 		133;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_TH_ADF_DLPZ              		134;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_MGDC_TH_L2FBPX           		135;
// Beamformer
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_TMP_CONFIG               		136;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BF_0_DOA                 		137;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BF_1_DOA                 		138;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BF_BEAM_MODE             		139;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BF_STEP_SIZE             		140;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PREP_DT_MIC_IN_MM        		141;
// AED
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AED_ALPHAA               		142;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AED_ALPHAN               		143;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AED_NOISE_TH             		144;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AED_NR_MAX_COUNT         		145;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AED_S_ACTIVE_COUNT       		146;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AED_S_ACTIVE_COUNT_DIV_6 		147;
// Two Channel NC
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_TWOCH_NC_GAMMAP          		148;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_TWOCH_NC_RPTP            		149;
// Send VAD
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_ATTACK_TC        		150;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_DECAY_TC         		151;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_ENVELOPE_TC      		152;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_INIT_FRAME_THRESH		153;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_RATIO            		154;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_MIN_SIGNAL       		155;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_MIN_MAX_ENVELOPE 		156;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_DELTA_THRESHOLD  		157;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_VAD_COUNT_THRESHOLD  		158;
// Send AGC
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_G_INITIAL        		159;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_TARGET           		160;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_ATTACK_TC        		161;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_DECAY_TC         		162;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_A_90_PK          		163;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_D_90_PK          		164;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_G_MAX            		165;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_START_COMP       		166;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_COMP             		167;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_INP_THRESH       		168;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_SP_ATTACK        		169;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_AD_THRESH1       		170;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_AD_THRESH2       		171;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_G_MIN            		172;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_ECHO_HOLD_TIME   		173;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SND_AGC_NOISE_HOLD_TIME  		174;
// Receive VAD
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_ATTACK_TC        		175;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_DECAY_TC         		176;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_ENVELOPE_TC      		177;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_INIT_FRAME_THRESH		178;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_RATIO            		179;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_MIN_SIGNAL       		180;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_MIN_MAX_ENVELOPE 		181;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_DELTA_THRESHOLD  		182;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_VAD_COUNT_THRESHOLD  		183;
// Receive AGC
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_G_INITIAL        		184;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_TARGET           		185;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_ATTACK_TC        		186;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_DECAY_TC         		187;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_A_90_PK          		188;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_D_90_PK          		189;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_G_MAX            		190;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_START_COMP       		191;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_COMP             		192;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_INP_THRESH       		193;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_SP_ATTACK        		194;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_AD_THRESH1       		195;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_AD_THRESH2       		196;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_AGC_G_MIN            		197;
// Adaptive EQ
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_ATK_TC               		198;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_ATK_1MTC             		199;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_DEC_TC               		200;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_DEC_1MTC             		201;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LO_GOAL_LOW          		202;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LO_GOAL_MID          		203;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LO_GOAL_HIGH         		204;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_HI_GOAL_LOW          		205;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_HI_GOAL_MID          		206;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_HI_GOAL_HIGH         		207;
// Bandwidth Expansion
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_HI2_GOAL_LOW         		208;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_HI2_GOAL_MID         		209;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_HI2_GOAL_HIGH        		210;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_TOTAL_ATT_LOW        		211;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_TOTAL_ATT_MID        		212;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_TOTAL_ATT_HIGH       		213;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_NOISE_LVL_FLAGS      		214;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_LOW_STEP             		215;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_BEX_HIGH_STEP            		216;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_POWER_TH             		217;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_MIN_GAIN             		218;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_MAX_GAIN             		219;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_VOL_STEP_UP_TH1      		220;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_VOL_STEP_UP_TH2      		221;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LOW_STEP             		222;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LOW_STEP_INV         		223;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_HIGH_STEP            		224;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_HIGH_STEP_INV        		225;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LOW_BAND_INDEX       		226;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LOW_BANDWIDTH        		227;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LOG2_LOW_BANDWIDTH   		228;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_MID_BANDWIDTH        		229;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LOG2_MID_BANDWIDTH   		230;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_HIGH_BANDWIDTH       		231;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_LOG2_HIGH_BANDWIDTH  		232;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_MID1_BAND_INDEX      		233;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_MID2_BAND_INDEX      		234;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AEQ_HIGH_BAND_INDEX      		235;
// Packet Loss
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_PLC_STAT_INTERVAL        		236;
// Receive OMS
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_RCV_OMS_HFK_AGGR         		237;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_OMS_HI_RES_MODE          		238;
// Noise Level w/ State Machine
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_VSM_HB_TIER1             		239;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_VSM_LB_TIER1             		240;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_VSM_MAX_ATT_TIER1        		241;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_HB_TIER1           		242;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_LB_TIER1           		243;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_MB_TIER1           		244;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_NBINS_TIER1        		245;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_ATT_TIER1          		246;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_ATT_THRESH_TIER1   		247;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_ECHO_THRESH_TIER1  		248;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_TIER2_THRESH             		249;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_VSM_HB_TIER2             		250;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_VSM_LB_TIER2             		251;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_VSM_MAX_ATT_TIER2        		252;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_HB_TIER2           		253;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_LB_TIER2           		254;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_MB_TIER2           		255;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_NBINS_TIER2        		256;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_ATT_TIER2          		257;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_ATT_THRESH_TIER2   		258;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_FDNLP_ECHO_THRESH_TIER2  		259;
// Howling
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_HD_THRESH_GAIN           		260;
// Aux Gain
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AUX_GAIN                 		261;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_SCO_STREAM_MIX           		262;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_AUX_STREAM_MIX           		263;
// User params
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_0               		264;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_1               		265;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_2               		266;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_3               		267;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_4               		268;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_5               		269;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_6               		270;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_7               		271;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_8               		272;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.OFFSET_DSP_USER_9               		273;
.CONST $M.CVC_HANDSFREE_2MIC.PARAMETERS.STRUCT_SIZE                    		274;


#endif // __CVC_HANDSFREE_2MIC_LIBRARY_GEN_H__
