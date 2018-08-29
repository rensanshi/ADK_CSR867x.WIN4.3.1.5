// *****************************************************************************
// Copyright (c) 2017 Qualcomm Technologies International, Ltd.
// Part of ADK_CSR867x.WIN 4.3
//
// *****************************************************************************

#include "aac_library.h"

#ifdef AACDEC_SBR_ADDITIONS

// *****************************************************************************
// MODULE:
//    $aacdec.sbr_huffman_tables_packed
//
// DESCRIPTION:
//    - Packed up huffman tables that will go into flash
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

.VAR/DMCONST_WINDOWED16 t_huffman_env_1_5dB[] =
      0x0201,    0xbfc0,    0x0403,    0xbec1,    0x0605,    0xbdc2,    0x0807,    0xbcc3,
      0x0a09,    0xbbc4,    0x0c0b,    0xbac5,    0x0e0d,    0xb9c6,    0x100f,    0xb8c7,
      0x1211,    0xc8b7,    0x1513,    0x14b6,    0xb5c9,    0x1a16,    0x1817,    0xb4ca,
      0x19b3,    0xb2cb,    0x221b,    0x1d1c,    0xb1cc,    0x1f1e,    0xcdb0,    0x2120,
      0xaead,    0xceaf,    0x3923,    0x2824,    0x2625,    0xaca8,    0x27d0,    0xaba6,
      0x2e29,    0x2b2a,    0xa9cf,    0x2d2c,    0xaaa7,    0x8584,    0x322f,    0x3130,
      0x8786,    0x8988,    0x3633,    0x3534,    0x8b8a,    0x8d8c,    0x3837,    0x8f8e,
      0x9190,    0x593a,    0x4a3b,    0x433c,    0x403d,    0x3f3e,    0x9392,    0x9594,
      0x4241,    0x9796,    0x9998,    0x4744,    0x4645,    0x9b9a,    0x9d9c,    0x4948,
      0x9f9e,    0xa1a0,    0x524b,    0x4f4c,    0x4e4d,    0xa3a2,    0xa5a4,    0x5150,
      0xd2d1,    0xd4d3,    0x5653,    0x5554,    0xd6d5,    0xd8d7,    0x5857,    0xdad9,
      0xdcdb,    0x695a,    0x625b,    0x5f5c,    0x5e5d,    0xdedd,    0xe0df,    0x6160,
      0xe2e1,    0xe4e3,    0x6663,    0x6564,    0xe6e5,    0xe8e7,    0x6867,    0xeae9,
      0xeceb,    0x716a,    0x6e6b,    0x6d6c,    0xeeed,    0xf0ef,    0x706f,    0xf2f1,
      0xf4f3,    0x7572,    0x7473,    0xf6f5,    0xf8f7,    0x7776,    0xfaf9,    0xfcfb;

.VAR/DMCONST_WINDOWED16 f_huffman_env_1_5dB[] =
      0x0201,    0xbfc0,    0x0403,    0xbec1,    0x0605,    0xc2bd,    0x0807,    0xc3bc,
      0x0a09,    0xc4bb,    0x0d0b,    0x0cba,    0xb9c5,    0x100e,    0x0fc6,    0xc7b8,
      0x1311,    0x12b7,    0xb6c8,    0x1714,    0x1615,    0xb5c9,    0xcbca,    0x1b18,
      0x1a19,    0xccb4,    0xcdb3,    0x1f1c,    0x1e1d,    0xb2ce,    0xcfb1,    0x2420,
      0x2221,    0xd1d0,    0x23b0,    0xaeaf,    0x2f25,    0x2926,    0x2827,    0xd2ad,
      0xacd3,    0x2c2a,    0x2bab,    0xd5d4,    0x2e2d,    0xa9a8,    0xa6aa,    0x4230,
      0x3831,    0x3532,    0x3433,    0xd6a4,    0xd9d7,    0x3736,    0xa797,    0xdbda,
      0x3c39,    0x3b3a,    0xa5a2,    0xdcd8,    0x3f3d,    0x3eec,    0x928d,    0x4140,
      0x9594,    0x9f9b,    0x5943,    0x4b44,    0x4845,    0x4746,    0xa3a1,    0xe5de,
      0x4a49,    0xefea,    0x84f0,    0x524c,    0x4f4d,    0x4e85,    0x8786,    0x5150,
      0x8988,    0x8b8a,    0x5653,    0x5554,    0x8e8c,    0x908f,    0x5857,    0x9391,
      0x9896,    0x695a,    0x625b,    0x5f5c,    0x5e5d,    0x9a99,    0x9d9c,    0x6160,
      0xa09e,    0xdfdd,    0x6663,    0x6564,    0xe1e0,    0xe3e2,    0x6867,    0xe6e4,
      0xe8e7,    0x716a,    0x6e6b,    0x6d6c,    0xebe9,    0xeeed,    0x706f,    0xf2f1,
      0xf4f3,    0x7572,    0x7473,    0xf6f5,    0xf8f7,    0x7776,    0xfaf9,    0xfcfb;

.VAR/DMCONST_WINDOWED16 t_huffman_env_bal_1_5dB[] =
      0x01c0,    0x02c1,    0x03bf,    0x04c2,    0x05be,    0x06c3,    0x07bd,    0x08c4,
      0x09bc,    0x0b0a,    0xc5bb,    0x0d0c,    0xc6ba,    0x1c0e,    0x150f,    0x1210,
      0x11c7,    0xc8b9,    0x1413,    0xa9a8,    0xabaa,    0x1916,    0x1817,    0xadac,
      0xafae,    0x1b1a,    0xb1b0,    0xb3b2,    0x241d,    0x211e,    0x201f,    0xb5b4,
      0xb7b6,    0x2322,    0xc9b8,    0xcbca,    0x2925,    0x2726,    0xcdcc,    0x28ce,
      0xd0cf,    0x2d2a,    0x2c2b,    0xd2d1,    0xd4d3,    0x2f2e,    0xd6d5,    0xd8d7;

.VAR/DMCONST_WINDOWED16 f_huffman_env_bal_1_5dB[] =
      0x01c0,    0x02bf,    0x03c1,    0x04be,    0x05c2,    0x06c3,    0x07bd,    0x08bc,
      0x09c4,    0x0b0a,    0xc5bb,    0x0cba,    0x0dc6,    0x110e,    0x0fb9,    0x10c7,
      0xb7c8,    0x2012,    0x1913,    0x1614,    0x15b8,    0xa9a8,    0x1817,    0xabaa,
      0xadac,    0x1d1a,    0x1c1b,    0xafae,    0xb1b0,    0x1f1e,    0xb3b2,    0xb5b4,
      0x2821,    0x2522,    0x2423,    0xc9b6,    0xcbca,    0x2726,    0xcdcc,    0xcfce,
      0x2c29,    0x2b2a,    0xd1d0,    0xd3d2,    0x2e2d,    0xd5d4,    0x2fd6,    0xd8d7;

.VAR/DMCONST_WINDOWED16 t_huffman_env_3_0dB[] =
      0x01c0,    0x02bf,    0x03c1,    0x04be,    0x05c2,    0x06bd,    0x07c3,    0x08bc,
      0x09c4,    0x0b0a,    0xc5bb,    0x0e0c,    0x0dba,    0xc6b9,    0x120f,    0x1110,
      0xc7b8,    0xb6b7,    0x1613,    0x14c8,    0x15c9,    0xb3ca,    0x1f17,    0x1918,
      0xb4b5,    0x1b1a,    0xcbb2,    0x1d1c,    0xa1cc,    0x1ea2,    0xa4a3,    0x2f20,
      0x2821,    0x2522,    0x2423,    0xa6a5,    0xa8a7,    0x2726,    0xaaa9,    0xacab,
      0x2c29,    0x2b2a,    0xaead,    0xb0af,    0x2e2d,    0xcdb1,    0xcfce,    0x3730,
      0x3431,    0x3332,    0xd1d0,    0xd3d2,    0x3635,    0xd5d4,    0xd7d6,    0x3b38,
      0x3a39,    0xd9d8,    0xdbda,    0x3d3c,    0xdddc,    0xdfde;

.VAR/DMCONST_WINDOWED16 f_huffman_env_3_0dB[] =
      0x01c0,    0x02bf,    0x03c1,    0x04be,    0x05c2,    0x06bd,    0x0807,    0xbcc3,
      0x0a09,    0xbbc4,    0x0c0b,    0xbac5,    0x0e0d,    0xb9c6,    0x100f,    0xb8c7,
      0x1311,    0x12c8,    0xb7c9,    0x1814,    0x1615,    0xcab6,    0x17cb,    0xb4b5,
      0x1e19,    0x1b1a,    0xcdcc,    0x1d1c,    0xb1b3,    0xcfce,    0x271f,    0x2320,
      0x2221,    0xd2b2,    0xa8ae,    0x2524,    0xd0ad,    0x26d1,    0xabaa,    0x2f28,
      0x2c29,    0x2b2a,    0xd4b0,    0xd6d5,    0x2e2d,    0xa9d9,    0xd8ac,    0x3730,
      0x3431,    0x3332,    0xa2a1,    0xa4a3,    0x3635,    0xa6a5,    0xafa7,    0x3b38,
      0x3a39,    0xd7d3,    0xdbda,    0x3d3c,    0xdddc,    0xdfde;

.VAR/DMCONST_WINDOWED16 t_huffman_env_bal_3_0dB[] =
      0x01c0,    0x02c1,    0x03bf,    0x04be,    0x05c2,    0x06c3,    0x07bd,    0x08bc,
      0x09c4,    0x100a,    0x0d0b,    0x0cbb,    0xb5b4,    0x0f0e,    0xb7b6,    0xb9b8,
      0x1411,    0x1312,    0xc5ba,    0xc7c6,    0x1615,    0xc9c8,    0x17ca,    0xcccb;

.VAR/DMCONST_WINDOWED16 f_huffman_env_bal_3_0dB[] =
      0x01c0,    0x02bf,    0x03c1,    0x04be,    0x05c2,    0x06c3,    0x07bd,    0x08bc,
      0x09c4,    0x0d0a,    0x0bbb,    0x0cc5,    0xb4c6,    0x110e,    0x100f,    0xb6b5,
      0xb8b7,    0x1512,    0x1413,    0xbab9,    0xc8c7,    0x1716,    0xcac9,    0xcccb;

.VAR/DMCONST_WINDOWED16 t_huffman_noise_3_0dB[] =
      0x01c0,    0x02c1,    0x03bf,    0x04be,    0x05c2,    0x06bd,    0x0807,    0xbcc3,
      0x1e09,    0x0f0a,    0x0bc4,    0x0cbb,    0x0e0d,    0xcbc5,    0xa2a1,    0x1710,
      0x1411,    0x1312,    0xa4a3,    0xa6a5,    0x1615,    0xa8a7,    0xaaa9,    0x1b18,
      0x1a19,    0xacab,    0xaead,    0x1d1c,    0xb0af,    0xb2b1,    0x2e1f,    0x2720,
      0x2421,    0x2322,    0xb4b3,    0xb6b5,    0x2625,    0xb8b7,    0xbab9,    0x2b28,
      0x2a29,    0xc7c6,    0xc9c8,    0x2d2c,    0xccca,    0xcecd,    0x362f,    0x3330,
      0x3231,    0xd0cf,    0xd2d1,    0x3534,    0xd4d3,    0xd6d5,    0x3a37,    0x3938,
      0xd8d7,    0xdad9,    0x3c3b,    0xdcdb,    0x3ddd,    0xdfde;

.VAR/DMCONST_WINDOWED16 t_huffman_noise_bal_3_0dB[] =
      0x01c0,    0x02bf,    0x03c1,    0x0904,    0x05be,    0x06c2,    0x0807,    0xb5b4,
      0xb7b6,    0x110a,    0x0e0b,    0x0d0c,    0xb9b8,    0xbbba,    0x100f,    0xbdbc,
      0xc4c3,    0x1512,    0x1413,    0xc6c5,    0xc8c7,    0x1716,    0xcac9,    0xcccb;

#endif




