// *****************************************************************************
// Copyright (c) 2017 Qualcomm Technologies International, Ltd.
// Part of ADK_CSR867x.WIN 4.3
//
// *****************************************************************************

#include "aac_library.h"

#ifdef AACDEC_SBR_ADDITIONS

#include "stack.h"
#include "profiler.h"

// *****************************************************************************
// MODULE:
//    $aacdec.sbr_noise
//
// DESCRIPTION:
//    Get noise floor information
//
// INPUTS:
//    - r5 current channel (0/1)
//
// OUTPUTS:
//    - none
//
// TRASHED REGISTERS:
//    - r0-r4, r6-r8, r10, I1-I5, I7, M0-M2
//    - an element of $aacdec.tmp
//
// *****************************************************************************
.MODULE $M.aacdec.sbr_noise;
   .CODESEGMENT AACDEC_SBR_NOISE_PM;
   .DATASEGMENT DM;

   $aacdec.sbr_noise:

   // push rLink onto stack
   push rLink;


   Null = M[$aacdec.sbr_info + $aacdec.SBR_bs_coupling];
   if Z jump not_coupling_mode;
      // if(ch==0)
      Null = r5;
      if Z jump ch_0_coupling_mode;
         I3 = &$aacdec.t_huffman_noise_bal_3_0dB;
         I4 = &$aacdec.f_huffman_env_bal_3_0dB;
         r7 = $aacdec.SBR_T_HUFFMAN_NOISE_BAL_3_0_DB_SIZE;  // same as SBR_HUFFMAN_ENV_BAL_3_0_DB_SIZE
         jump huffman_tables_selected;
      ch_0_coupling_mode:
   not_coupling_mode:
      I3 = &$aacdec.t_huffman_noise_3_0dB;
      I4 = &$aacdec.f_huffman_env_3_0dB;
      r7 = $aacdec.SBR_T_HUFFMAN_NOISE_3_0_DB_SIZE;  // same as SBR_HUFFMAN_ENV_3_0_DB_SIZE
   huffman_tables_selected:


   r6 = M[($aacdec.tmp_mem_pool + $aacdec.SBR_bs_num_noise) + r5];

   // allocate temporary memory for SBR_Q_envelope
   r0 = r6 * 5 (int);
   call $aacdec.tmp_mem_pool_allocate;
   if NEG jump $aacdec.possible_corruption;
   M[($aacdec.tmp_mem_pool + $aacdec.SBR_Q_envelope_base_ptr) + r5] = r1;
   r8 = r1;
   I5 = r1;

   M[$aacdec.tmp + $aacdec.SBR_HUFFMAN_TABLE_SIZE] = r7;

   #ifdef AACDEC_SBR_HUFFMAN_IN_FLASH
      r0 = I3;
      r2 = M[$flash.windowed_data16.address];
      call $aacdec.sbr_allocate_and_unpack_from_flash;
      I3 = r1;

      r0 = I4;
      r2 = M[$flash.windowed_data16.address];
      call $aacdec.sbr_allocate_and_unpack_from_flash;
      I4 = r1;
   #endif

   r0 = M[$aacdec.sbr_info + $aacdec.SBR_Nq];
   M2 = r0;
   // noise = 0
   r7 = 0;

   // for noise=0:SBR_bs_num_noise[ch]-1,
   outer_loop:
      // if(SBR_bs_df_noise[ch][noise] == 0)
      r0 = r5 LSHIFT 1;
      r0 = r0 + r7;
      Null = M[($aacdec.tmp_mem_pool + $aacdec.SBR_bs_df_noise) + r0];
      if NZ jump delta_time_coding;
         // SBR_Q_envelope[ch][band=0][noise] = getbits(5)
         call $aacdec.get5bits;
         M[I5,1] = r1;

         I2 = I4;
         // for band=1:SBR_Nq-1,
         r10 = M2 - 1;

         do huff_decode_envelope_d_freq_coding;
            call $aacdec.sbr_huff_dec;
            M[I5, 1] = r1;
         huff_decode_envelope_d_freq_coding:

         jump eval_loop_index;
      delta_time_coding:
         // for band=0:SBR_Nq-1,
         r10 = M2;

         I2 = I3;

         do huff_decode_noise_d_time_coding;
            call $aacdec.sbr_huff_dec;
            M[I5, 1] = r1;
         huff_decode_noise_d_time_coding:

   eval_loop_index:
   r7 = r7 + 1;
   r0 = r7 * 5 (int);
   I5 = r8 + r0;
   Null = r6 - r7;
   if GT jump outer_loop;

   #ifdef AACDEC_SBR_HUFFMAN_IN_FLASH
      r0 = M[$aacdec.tmp + $aacdec.SBR_HUFFMAN_TABLE_SIZE];
      r0 = r0 LSHIFT 1;
      call $aacdec.frame_mem_pool_free;
   #endif

  PROFILER_START(&$aacdec.profile_sbr_extract_noise_floor_data)
      call $aacdec.sbr_extract_noise_floor_data;
  PROFILER_STOP(&$aacdec.profile_sbr_extract_noise_floor_data)


   // pop rLink from stack
   jump $pop_rLink_and_rts;


.ENDMODULE;

#endif
