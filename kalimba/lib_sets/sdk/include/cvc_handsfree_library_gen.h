// -----------------------------------------------------------------------------
// Copyright (c) 2010 - 2015 Qualcomm Technologies International, Ltd.
// Generated by DerivationEngine.py
// source v1.1, namespace com.csr.cps.2 on 2018-03-01 05:08:29 by SHA-Audio_Dev
// from cvc_handsfree.xml $Revision: #1 $
// last modifed with $Change: 2929828 $ by $Author: ac52 $ on $DateTime: 2018/01/15 12:31:54 $
// -----------------------------------------------------------------------------
#ifndef __CVC_HANDSFREE_LIBRARY_GEN_H__
#define __CVC_HANDSFREE_LIBRARY_GEN_H__

// Algorithm IDs
.CONST $CVC_HANDSFREE_SYSID     	0xA012;

// Piecewise Enables
.CONST $M.CVC_HANDSFREE.CONFIG.CNGENA           		0x008000;
.CONST $M.CVC_HANDSFREE.CONFIG.RERENA           		0x004000;
.CONST $M.CVC_HANDSFREE.CONFIG.PLCENA           		0x002000;
.CONST $M.CVC_HANDSFREE.CONFIG.SNDAGCBYP        		0x001000;
.CONST $M.CVC_HANDSFREE.CONFIG.BEXENA           		0x000800;
.CONST $M.CVC_HANDSFREE.CONFIG.AEQBYP           		0x000400;
.CONST $M.CVC_HANDSFREE.CONFIG.NDVCBYP          		0x000200;
.CONST $M.CVC_HANDSFREE.CONFIG.RCVAGCBYP        		0x000100;
.CONST $M.CVC_HANDSFREE.CONFIG.SND2OMSBYP       		0x000080;
.CONST $M.CVC_HANDSFREE.CONFIG.RCVOMSBYP        		0x000040;
.CONST $M.CVC_HANDSFREE.CONFIG.RERCBAENA        		0x000020;
.CONST $M.CVC_HANDSFREE.CONFIG.BYPASS_FBC       		0x000010;
.CONST $M.CVC_HANDSFREE.CONFIG.WNRBYP           		0x000008;
.CONST $M.CVC_HANDSFREE.CONFIG.AECENA           		0x000004;
.CONST $M.CVC_HANDSFREE.CONFIG.BYPASS_AGCPERSIST		0x040000;

// SPI Status Block
.CONST $M.CVC_HANDSFREE.STATUS.CUR_MODE_OFFSET      		0;
.CONST $M.CVC_HANDSFREE.STATUS.CALL_STATE_OFFSET    		1;
.CONST $M.CVC_HANDSFREE.STATUS.SYS_CONTROL_OFFSET   		2;
.CONST $M.CVC_HANDSFREE.STATUS.CUR_DAC_OFFSET       		3;
.CONST $M.CVC_HANDSFREE.STATUS.PRIM_PSKEY_OFFSET    		4;
.CONST $M.CVC_HANDSFREE.STATUS.SEC_STAT_OFFSET      		5;
.CONST $M.CVC_HANDSFREE.STATUS.PEAK_DAC_OFFSET      		6;
.CONST $M.CVC_HANDSFREE.STATUS.PEAK_ADC_OFFSET      		7;
.CONST $M.CVC_HANDSFREE.STATUS.PEAK_SCO_IN_OFFSET   		8;
.CONST $M.CVC_HANDSFREE.STATUS.PEAK_SCO_OUT_OFFSET  		9;
.CONST $M.CVC_HANDSFREE.STATUS.PEAK_MIPS_OFFSET     		10;
.CONST $M.CVC_HANDSFREE.STATUS.NDVC_NOISE_EST_OFFSET		11;
.CONST $M.CVC_HANDSFREE.STATUS.NDVC_DAC_ADJ_OFFSET  		12;
.CONST $M.CVC_HANDSFREE.STATUS.PEAK_AUX_OFFSET      		13;
.CONST $M.CVC_HANDSFREE.STATUS.COMPILED_CONFIG      		14;
.CONST $M.CVC_HANDSFREE.STATUS.VOLUME               		15;
.CONST $M.CVC_HANDSFREE.STATUS.CONNSTAT             		16;
.CONST $M.CVC_HANDSFREE.STATUS.PLC_PACKET_LOSS      		17;
.CONST $M.CVC_HANDSFREE.STATUS.AEQ_GAIN_LOW         		18;
.CONST $M.CVC_HANDSFREE.STATUS.AEQ_GAIN_HIGH        		19;
.CONST $M.CVC_HANDSFREE.STATUS.AEQ_STATE            		20;
.CONST $M.CVC_HANDSFREE.STATUS.AEQ_POWER_TEST       		21;
.CONST $M.CVC_HANDSFREE.STATUS.AEQ_TONE_POWER       		22;
.CONST $M.CVC_HANDSFREE.STATUS.NLP_TIER_HC_ACTIVE   		23;
.CONST $M.CVC_HANDSFREE.STATUS.AEC_COUPLING_OFFSET  		24;
.CONST $M.CVC_HANDSFREE.STATUS.FBC_POWER_DROP       		25;
.CONST $M.CVC_HANDSFREE.STATUS.VAD_RCV_DET_OFFSET   		26;
.CONST $M.CVC_HANDSFREE.STATUS.SND_AGC_SPEECH_LVL   		27;
.CONST $M.CVC_HANDSFREE.STATUS.SND_AGC_GAIN         		28;
.CONST $M.CVC_HANDSFREE.STATUS.RCV_AGC_SPEECH_LVL   		29;
.CONST $M.CVC_HANDSFREE.STATUS.RCV_AGC_GAIN         		30;
.CONST $M.CVC_HANDSFREE.STATUS.WNR_PWR_LVL          		31;
.CONST $M.CVC_HANDSFREE.STATUS.WIND_FLAG            		32;
.CONST $M.CVC_HANDSFREE.STATUS.INTERFACE_TYPE       		33;
.CONST $M.CVC_HANDSFREE.STATUS.INPUT_RATE           		34;
.CONST $M.CVC_HANDSFREE.STATUS.OUTPUT_RATE          		35;
.CONST $M.CVC_HANDSFREE.STATUS.CODEC_RATE           		36;
.CONST $M.CVC_HANDSFREE.STATUS.DSP_VOL_FLAG         		37;
.CONST $M.CVC_HANDSFREE.STATUS.DSP_VOL              		38;
.CONST $M.CVC_HANDSFREE.STATUS.BLOCK_SIZE                		39;

// System Mode
.CONST $M.CVC_HANDSFREE.SYSMODE.STANDBY		0;
.CONST $M.CVC_HANDSFREE.SYSMODE.HFK    		1;
.CONST $M.CVC_HANDSFREE.SYSMODE.SSR    		2;
.CONST $M.CVC_HANDSFREE.SYSMODE.PSTHRGH		3;
.CONST $M.CVC_HANDSFREE.SYSMODE.LPBACK 		4;
.CONST $M.CVC_HANDSFREE.SYSMODE.MAX_MODES		6;

// Call State
.CONST $M.CVC_HANDSFREE.CALLST.UNKNOWN   		0;
.CONST $M.CVC_HANDSFREE.CALLST.CONNECTED 		1;
.CONST $M.CVC_HANDSFREE.CALLST.CONNECTING		2;
.CONST $M.CVC_HANDSFREE.CALLST.MUTE      		3;

// System Control
.CONST $M.CVC_HANDSFREE.CONTROL.DAC_OVERRIDE      		0x8000;
.CONST $M.CVC_HANDSFREE.CONTROL.CALLSTATE_OVERRIDE		0x4000;
.CONST $M.CVC_HANDSFREE.CONTROL.MODE_OVERRIDE     		0x2000;

// AEQ State

// System Control

// NLP State

// W_Flag

// Interface
.CONST $M.CVC_HANDSFREE.INTERFACE.ANALOG		0;
.CONST $M.CVC_HANDSFREE.INTERFACE.I2S   		1;

// Parameter Block
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_HFK_CONFIG               		0;
// Send OMS
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_HFK_OMS_AGGR             		1;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SSR_OMS_AGGR             		2;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_OMS_HARMONICITY          		3;
// Wind Noise
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_WNR_AGGR                 		4;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_WNR_POWER_THRES          		5;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_WNR_HOLD                 		6;
// AEC parameters :: The DSP/UFE software assumes that the following thirteen AEC parameters are contiguous: Do not re-order them
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_CNG_Q                    		7;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_CNG_SHAPE                		8;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DTC_AGGR                 		9;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_MAX_LPWRX_MARGIN         		10;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_ENABLE_AEC_REUSE         		11;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEC_REF_LPWR_HB          		12;
// RER
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RER_VAR_THRESH           		13;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RER_AGGRESSIVENESS       		14;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RER_WGT_SY               		15;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RER_OFFSET_SY            		16;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RER_POWER                		17;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RERDT_OFF_THRESHOLD      		18;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RERDT_AGGRESSIVENESS     		19;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RERDT_POWER              		20;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FBC_TH_RER               		21;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RER_ADAPT                		22;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FBC_HPF_ON               		23;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FBC_FILTER_LENGTH        		24;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEC_FILTER_LENGTH        		25;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_ADCGAIN                  		26;
// NDVC
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_HYSTERESIS          		27;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_ATK_TC              		28;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_DEC_TC              		29;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_NUMVOLSTEPS         		30;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_MAXNOISELVL         		31;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_MINNOISELVL         		32;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_LB                  		33;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_NDVC_HB                  		34;
// Send PEQ
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_CONFIG           		35;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_GAIN_EXP         		36;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_GAIN_MANT        		37;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B2        		38;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B1        		39;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE1_B0        		40;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE1_A2        		41;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE1_A1        		42;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B2        		43;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B1        		44;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE2_B0        		45;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE2_A2        		46;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE2_A1        		47;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B2        		48;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B1        		49;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE3_B0        		50;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE3_A2        		51;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE3_A1        		52;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B2        		53;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B1        		54;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE4_B0        		55;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE4_A2        		56;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE4_A1        		57;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B2        		58;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B1        		59;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE5_B0        		60;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE5_A2        		61;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_STAGE5_A1        		62;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_SCALE1           		63;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_SCALE2           		64;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_SCALE3           		65;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_SCALE4           		66;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_PEQ_SCALE5           		67;
// Receive PEQ
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_CONFIG           		68;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_GAIN_EXP         		69;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_GAIN_MANT        		70;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_B2        		71;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_B1        		72;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_B0        		73;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_A2        		74;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE1_A1        		75;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_B2        		76;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_B1        		77;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_B0        		78;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_A2        		79;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE2_A1        		80;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_B2        		81;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_B1        		82;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_B0        		83;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_A2        		84;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE3_A1        		85;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_B2        		86;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_B1        		87;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_B0        		88;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_A2        		89;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE4_A1        		90;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_B2        		91;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_B1        		92;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_B0        		93;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_A2        		94;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_STAGE5_A1        		95;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_SCALE1           		96;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_SCALE2           		97;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_SCALE3           		98;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_SCALE4           		99;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_PEQ_SCALE5           		100;
// Inverse DAC Table
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE       		101;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE1      		102;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE2      		103;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE3      		104;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE4      		105;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE5      		106;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE6      		107;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE7      		108;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE8      		109;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE9      		110;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE10     		111;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE11     		112;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE12     		113;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE13     		114;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE14     		115;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_INV_DAC_GAIN_TABLE15     		116;
// sidetone and clipper
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SIDETONE_GAIN            		117;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_CLIP_POINT               		118;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SIDETONE_LIMIT           		119;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BOOST                    		120;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BOOST_CLIP_POINT         		121;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_G_ALFA                   		122;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SNDGAIN_MANTISSA         		123;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SNDGAIN_EXPONENT         		124;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCVGAIN_MANTISSA         		125;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCVGAIN_EXPONENT         		126;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_PT_SNDGAIN_MANTISSA      		127;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_PT_SNDGAIN_EXPONENT      		128;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_PT_RCVGAIN_MANTISSA      		129;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_PT_RCVGAIN_EXPONENT      		130;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_REF_DELAY                		131;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_ADCGAIN_SSR              		132;
// Send VAD
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_ATTACK_TC        		133;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_DECAY_TC         		134;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_ENVELOPE_TC      		135;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_INIT_FRAME_THRESH		136;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_RATIO            		137;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_MIN_SIGNAL       		138;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_MIN_MAX_ENVELOPE 		139;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_DELTA_THRESHOLD  		140;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_VAD_COUNT_THRESHOLD  		141;
// Send AGC
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_G_INITIAL        		142;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_TARGET           		143;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_ATTACK_TC        		144;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_DECAY_TC         		145;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_A_90_PK          		146;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_D_90_PK          		147;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_G_MAX            		148;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_START_COMP       		149;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_COMP             		150;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_INP_THRESH       		151;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_SP_ATTACK        		152;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_AD_THRESH1       		153;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_AD_THRESH2       		154;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_G_MIN            		155;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SND_AGC_ECHO_HOLD_TIME   		156;
// Receive VAD
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_ATTACK_TC        		157;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_DECAY_TC         		158;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_ENVELOPE_TC      		159;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_INIT_FRAME_THRESH		160;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_RATIO            		161;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_MIN_SIGNAL       		162;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_MIN_MAX_ENVELOPE 		163;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_DELTA_THRESHOLD  		164;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_VAD_COUNT_THRESHOLD  		165;
// Receive AGC
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_G_INITIAL        		166;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_TARGET           		167;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_ATTACK_TC        		168;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_DECAY_TC         		169;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_A_90_PK          		170;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_D_90_PK          		171;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_G_MAX            		172;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_START_COMP       		173;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_COMP             		174;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_INP_THRESH       		175;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_SP_ATTACK        		176;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_AD_THRESH1       		177;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_AD_THRESH2       		178;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_AGC_G_MIN            		179;
// Adaptive EQ
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_ATK_TC               		180;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_ATK_1MTC             		181;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_DEC_TC               		182;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_DEC_1MTC             		183;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LO_GOAL_LOW          		184;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LO_GOAL_MID          		185;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LO_GOAL_HIGH         		186;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_HI_GOAL_LOW          		187;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_HI_GOAL_MID          		188;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_HI_GOAL_HIGH         		189;
// Bandwidth Expansion
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_HI2_GOAL_LOW         		190;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_HI2_GOAL_MID         		191;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_HI2_GOAL_HIGH        		192;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_TOTAL_ATT_LOW        		193;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_TOTAL_ATT_MID        		194;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_TOTAL_ATT_HIGH       		195;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_NOISE_LVL_FLAGS      		196;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_LOW_STEP             		197;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_BEX_HIGH_STEP            		198;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_POWER_TH             		199;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_MIN_GAIN             		200;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_MAX_GAIN             		201;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_VOL_STEP_UP_TH1      		202;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_VOL_STEP_UP_TH2      		203;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LOW_STEP             		204;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LOW_STEP_INV         		205;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_HIGH_STEP            		206;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_HIGH_STEP_INV        		207;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LOW_BAND_INDEX       		208;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LOW_BANDWIDTH        		209;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LOG2_LOW_BANDWIDTH   		210;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_MID_BANDWIDTH        		211;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LOG2_MID_BANDWIDTH   		212;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_HIGH_BANDWIDTH       		213;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_LOG2_HIGH_BANDWIDTH  		214;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_MID1_BAND_INDEX      		215;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_MID2_BAND_INDEX      		216;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AEQ_HIGH_BAND_INDEX      		217;
// Packet Loss
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_PLC_STAT_INTERVAL        		218;
// Receive OMS
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_RCV_OMS_HFK_AGGR         		219;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_OMS_HI_RES_MODE          		220;
// Howling
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_HD_THRESH_GAIN           		221;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_TIER2_THRESH             		222;
// Noise Level w/ State Machine
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_VSM_HB_TIER1             		223;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_VSM_LB_TIER1             		224;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_VSM_MAX_ATT_TIER1        		225;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_HB_TIER1           		226;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_LB_TIER1           		227;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_MB_TIER1           		228;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_NBINS_TIER1        		229;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_ATT_TIER1          		230;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_ATT_THRESH_TIER1   		231;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_ECHO_THRESH_TIER1  		232;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_VSM_HB_TIER2             		233;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_VSM_LB_TIER2             		234;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_VSM_MAX_ATT_TIER2        		235;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_HB_TIER2           		236;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_LB_TIER2           		237;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_MB_TIER2           		238;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_NBINS_TIER2        		239;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_ATT_TIER2          		240;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_ATT_THRESH_TIER2   		241;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_FDNLP_ECHO_THRESH_TIER2  		242;
// Power Margin
// Aux Gain
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AUX_GAIN                 		243;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_SCO_STREAM_MIX           		244;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_AUX_STREAM_MIX           		245;
// User params
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_0               		246;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_1               		247;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_2               		248;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_3               		249;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_4               		250;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_5               		251;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_6               		252;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_7               		253;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_8               		254;
.CONST $M.CVC_HANDSFREE.PARAMETERS.OFFSET_DSP_USER_9               		255;
.CONST $M.CVC_HANDSFREE.PARAMETERS.STRUCT_SIZE                    		256;


#endif // __CVC_HANDSFREE_LIBRARY_GEN_H__
