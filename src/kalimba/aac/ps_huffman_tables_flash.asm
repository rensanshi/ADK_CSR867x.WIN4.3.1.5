// *****************************************************************************
// Copyright (c) 2017 Qualcomm Technologies International, Ltd.
// Part of ADK_CSR867x.WIN 4.3
//
// *****************************************************************************

#include "aac_library.h"

#ifdef AACDEC_PARAMETRIC_STEREO_ADDITIONS

// *****************************************************************************
// MODULE:
//    $aacdec.ps_huffman_tables
//
// DESCRIPTION:
//    - huffman tables that will go into flash
//
// INPUTS:
//    - none
//
// OUTPUTS:
//    - none
//
// TRASHED REGISTERS:
//    none
//
// *****************************************************************************


.BLOCK/DMCONST_WINDOWED16 aacdec_packed_ps_huffman_tables;

.VAR t_huffman_iid_def[] =
                           0xE101,  0xE002,  0xE203,  0xDF04,  0xE305,  0xDE06,  0xE407,  0xDD08,  0xE509,  0xDC0A,  0xE60B,  0xDB0C,
                           0xE70D,  0xE80E,  0xDA0F,  0x1011,  0xE9D9,  0x1213,  0x1415,  0x1617,  0xEAD3,  0xD4D5,  0x1819,  0x1A1B,
                           0xD6D7,  0xD8EB,  0xECED,  0xEEEF;



.VAR f_huffman_iid_def[] =
                           0xE101,  0x0203,  0xE2E0,  0x0405,  0xE3DF,  0x0607,  0xE4DE,  0x0809,  0xDDE5,  0xE60A,  0xDC0B,  0xE70C,
                           0xDB0D,  0xDA0E,  0xE80F,  0x1011,  0xE9D9,  0x1213,  0xEAEB,  0x1415,  0xD8EC,  0x1617,  0xD718,  0x191A,
                           0xD6D3,  0xD4D5,  0xED1B,  0xEEEF;



.VAR t_huffman_iid_fine[] =
                           0x01E1,  0xE202,  0x03E0,  0x0405,  0x0607,  0xDFE3,  0x08DE,  0xE409,  0xDDE5,  0x0A0B,  0xE60C,  0x0D0E,
                           0xDBE7,  0x0F10,  0x11DC,  0x12DA,  0xE813,  0x1415,  0xEA16,  0x1718,  0xD9E9,  0x191A,  0xEC1B,  0x1C1D,
                           0xD7EB,  0x1E1F,  0x20D8,  0x21D4,  0xEE22,  0x2324,  0x25D5,  0xED26,  0x27D6,  0x2829,  0x2A2B,  0x2C2D,
                           0x2ED2,  0xF02F,  0xD3EF,  0x3031,  0xEBCD,  0xF3F4,  0xCECF,  0x3233,  0x3435,  0x3637,  0x38D0,  0xF239,
                           0x3AD1,  0xF13B,  0xC7FB,  0xC5C6,  0xFEFF,  0xFCFD,  0xC3C4,  0xC8FA,  0xC9F9,  0xCAF8,  0xCBF7,  0xF5F6;



.VAR f_huffman_iid_fine[] =
                           0x01E1,  0x0203,  0x04E0,  0xE205,  0xDFE3,  0x0607,  0xDEE4,  0x0809,  0xDDE5,  0x0A0B,  0xDCE6,  0x0C0D,
                           0xDBE7,  0x0E0F,  0xE810,  0x1112,  0x13D9,  0xE914,  0x15DA,  0xEB16,  0x17D8,  0xEA18,  0xD6EC,  0x191A,
                           0x1BD7,  0x1CD5,  0xED1D,  0x1E1F,  0x20D3,  0xEF21,  0x22D4,  0xEE23,  0x2425,  0x26D2,  0xF027,  0x2829,
                           0x2A2B,  0xD0F2,  0x2C2D,  0x2E2F,  0x3031,  0xD1F1,  0xCCF6,  0xCEF4,  0xCFF3,  0x3233,  0x3435,  0x3637,
                           0x3839,  0x3A3B,  0xC7C8,  0xC5C6,  0xCBF7,  0xC9CA,  0xFAFB,  0xF8F9,  0xFEFF,  0xFCFD,  0xC3C4,  0xCDF5;



.VAR t_huffman_icc[] =
                           0xE101,  0xE202,  0xE003,  0xE304,  0xDF05,  0xE406,  0xDE07,  0xE508,  0xDD09,  0xE60A,  0xDC0B,  0xE70C,
                           0xDB0D,  0xDAE8;



.VAR f_huffman_icc[] =
                           0xE101,  0xE202,  0xE003,  0xE304,  0xDF05,  0xE406,  0xDE07,  0xE508,  0xE609,  0xDD0A,  0xE70B,  0xDC0C,
                           0xE80D,  0xDBDA;



.VAR t_huffman_ipd[] =
                           0x01E1,  0x0203,  0x0405,  0xE2E8,  0xE606,  0xE3E7,  0xE5E4;



.VAR f_huffman_ipd[] =
                           0x01E1,  0x0203,  0xE204,  0x0506,  0xE5E6,  0xE4E7,  0xE3E8;



.VAR t_huffman_opd[] =
                           0x01E1,  0x0203,  0x0405,  0xE2E8,  0xE6E3,  0xE706,  0xE5E4;



.VAR f_huffman_opd[] =
                           0x01E1,  0x0203,  0xE8E2,  0x0405,  0xE4E7,  0xE306,  0xE6E5;
.ENDBLOCK;

#endif