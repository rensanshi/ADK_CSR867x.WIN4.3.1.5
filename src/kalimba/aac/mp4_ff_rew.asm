// *****************************************************************************
// Copyright (c) 2017 Qualcomm Technologies International, Ltd.
// Part of ADK_CSR867x.WIN 4.3
//
// *****************************************************************************

#include "aac_library.h"

#include "stack.h"

// *****************************************************************************
// MODULE:
//    $aacdec.mp4_ff_rew
//
// DESCRIPTION:
//
//
// INPUTS:
//    - None
//
// OUTPUTS:
//    - None
//
// TRASHED REGISTERS:
//    - assume everything including $aacdec.tmp
//
// *****************************************************************************
.MODULE $M.aacdec.mp4_ff_rew;
   .CODESEGMENT AACDEC_MP4_FF_REW_PM;
   .DATASEGMENT DM;

   $aacdec.mp4_ff_rew:

   .CONST MP4_FF_REW_STSS_UNDERFLOW 1;

   .VAR mp4_ff_rew_state;
   // push rLink onto stack
   push rLink;


   // underflow? resume STSS/STSZ parsing
/*   Null = M[mp4_ff_rew_state];
   if Z jump not_stss_undeflow;
      call $aacdec.mp4_find_random_seek_frame;
      jump check_stss_underflow;

   not_stss_undeflow: */

   r8 = 0;
   // if (stsz parsing not finished)
   r4 = M[$aacdec.sample_count];
   r5 = M[&$aacdec.sample_count + 1];
   Null = r4 OR r5;
   if Z jump not_stsz_underflow;
      call $aacdec.mp4_calculate_frame_offset;
      jump check_stsz_underflow;

   not_stsz_underflow:
   M[mp4_ff_rew_state] = Null;
   M[&$aacdec.ff_rew_skip_amount + 1] = Null;
   M[$aacdec.ff_rew_skip_amount] = Null;

   // Calculate number of frames to skip
   r1 = M[$aacdec.fast_fwd_samples_ls];
   r2 = M[$aacdec.fast_fwd_samples_ms];
   // check if it is rewind
   Null = r2;
   if POS jump not_rewind;
      r1 = Null - r1;
      r2 = Null - r2 - Borrow;

   not_rewind:
   // rMAC = {r2,r1)
   rMAC = r1 LSHIFT 0 (LO);
   r3 = 0x800000;
   rMAC = rMAC + r2 * r3 (UU);

   r0 = 2;
   r3 = $aacdec.MAX_AUDIO_FRAME_SIZE_IN_WORDS;
   Null = M[$aacdec.sbr_present];
   if NZ r3 = r0 * r3 (int);

   Div = rMAC/r3;

   r0 = DivResult; // Number of frames
   Null = M[$aacdec.fast_fwd_samples_ms];
   if NEG r0 = -r0;

   // Calculate target frame number
   r0 = r0 + M[$aacdec.mp4_frame_count];
   if NEG r0 = 0; // if requested rewind value is > elapsed value, r0 will be negative
   M[$aacdec.mp4_frame_count] = r0;

   // Check if STSS is present
#if 0 //Disable for now
   r0 = M[$aacdec.stss_offset + 1];
   r1 = M[$aacdec.stss_offset];
   Null = r0 OR r1;
   if Z jump stss_parse_done;
      Null = r1 + 1;
      if Z jump random_seek_allowed;
         // Random seek not allowed
         // Just gobble
         M[$aacdec.fast_fwd_samples_ls] = Null;
         M[$aacdec.fast_fwd_samples_ms] = Null;
         jump $pop_rLink_and_rts;

      random_seek_allowed:
      // Calculate seek value(to STSS)
      r3 = r0 - M[&$aacdec.mp4_file_offset + 1];
      r4 = r1 - M[$aacdec.mp4_file_offset] - Borrow;

      // update the file offset
      M[&$aacdec.mp4_file_offset + 1] = r0;
      M[$aacdec.mp4_file_offset] = r1;

      // Seek to location of STSZ
      r6 = M[$aacdec.skip_function];
      call $aacdec.skip_through_file;

      // Check if reasonable amount of data available
      r0 = M[$aacdec.num_bytes_available];
      Null = r0 - 16; // Atom Size:4, Name:4, Flags:4, Sample Count:4
      if POS jump stss_data_available;
         r0 = 1;
         M[$aacdec.frame_underflow] = r0;
         M[mp4_ff_rew_state] = r0;
         // return back to mp4_sequence
         jump $pop_rLink_and_rts;

      stss_data_available:
      // Find the nearest random seek frame number
      call $aacdec.mp4_find_random_seek_frame;

      check_stss_underflow:
      r0 = M[$aacdec.frame_underflow];
      if Z jump stss_parse_done;
         M[mp4_ff_rew_state] = r0;
         jump $pop_rLink_and_rts;

#endif
   stss_parse_done:
   M[mp4_ff_rew_state] = Null;
   // Calculate seek value(to STSZ)
   r0 = M[&$aacdec.stsz_offset + 1];
   r1 = M[$aacdec.stsz_offset];

   Null = r0 OR r1;
   if NZ jump stsz_available;
      r0 = $aacdec.MP4_FF_REW_SEEK_NOT_POSSIBLE;
      M[$aacdec.mp4_ff_rew_status] = r0;
      M[$aacdec.fast_fwd_samples_ls] = Null;
      M[$aacdec.fast_fwd_samples_ms] = Null;
      jump $pop_rLink_and_rts;


   stsz_available:
   r3 = r0 - M[&$aacdec.mp4_file_offset + 1];
   r4 = r1 - M[$aacdec.mp4_file_offset] - Borrow;

   // update the file offset
   M[&$aacdec.mp4_file_offset + 1] = r0;
   M[$aacdec.mp4_file_offset] = r1;

   // Seek to location of STSZ
   r6 = M[$aacdec.skip_function];
   call $aacdec.skip_through_file;

   // Calculate offset of target frame
   r6 = M[$aacdec.mp4_frame_count];
   call $aacdec.mp4_calculate_frame_offset;

   check_stsz_underflow:
   Null = M[$aacdec.frame_underflow];
   if NZ jump $pop_rLink_and_rts;

   seek_frame:
   // Calculate seek value
   r3 = M[$aacdec.mdat_offset + 1];
   r4 = M[$aacdec.mdat_offset];

   r0 = r3 + M[&$aacdec.ff_rew_skip_amount + 1];
   r1 = r4 + M[$aacdec.ff_rew_skip_amount];

   r3 = r0 - M[&$aacdec.mp4_file_offset + 1];
   r4 = r1 - M[$aacdec.mp4_file_offset] - Borrow;

   M[&$aacdec.mp4_file_offset + 1] = r0;
   M[$aacdec.mp4_file_offset] = r1;
   // Seek to target frame
   r6 = M[$aacdec.skip_function];
   call $aacdec.skip_through_file;

   r0 = $aacdec.MP4_FF_REW_DONE;
   M[$aacdec.mp4_ff_rew_status] = r0;
   jump $pop_rLink_and_rts;

.ENDMODULE;

// *****************************************************************************
// MODULE:
//    $aacdec.mp4_calculate_frame_offset
//
// DESCRIPTION:
//
//
// INPUTS:
//    - None
//
// OUTPUTS:
//    - None
//
// TRASHED REGISTERS:
//    - assume everything including $aacdec.tmp
//
// *****************************************************************************

.MODULE $M.aacdec.mp4_calculate_frame_offset;
   .CODESEGMENT AACDEC_MP4_FF_REW_PM;
   .DATASEGMENT DM;

   $aacdec.mp4_calculate_frame_offset:

   // push rLink onto stack
   push rLink;

   // Record bit count
   r0 = M[$aacdec.read_bit_count];
   M[$aacdec.tmp] = r0;


   // Previous call returned underflow? Resume parsing
   r8 = 0;
   // if (stsz/stz2 parsing not finished)
   r4 = M[$aacdec.sample_count];
   r5 = M[&$aacdec.sample_count + 1];
   Null = r4 OR r5;
   if Z jump not_underflow;
      r0 = M[&$aacdec.ff_rew_skip_amount + 1];
      r1 = M[$aacdec.ff_rew_skip_amount];
      Null = r0 OR r1;
      if NZ jump stsz_variable_sample_size;
      jump check_input;

   not_underflow:
   M[&$aacdec.sample_count + 1] = r6;
   M[&$aacdec.sample_count] = Null;

   check_input:
   // Check if reasonable amount of data available
   r0 = M[$aacdec.num_bytes_available];
   Null = r0 - 20; // Atom Size:4, Name:4, Flags:4, Sample size: 4, Sample Count:4
   if POS jump data_available;
      r0 = 1;
      M[$aacdec.frame_underflow] = r0;
      // return back to mp4_sequence
      jump $pop_rLink_and_rts;
   data_available:

   // Read atom header
   r0 = M[$aacdec.num_bytes_available];
   r0 = r0 - $aacdec.MP4_ATOM_NAME_AND_SIZE_BYTES;
   M[$aacdec.num_bytes_available] = r0;

   //    - r4 = most significant byte of sub_atom_size
   //    - r5 = least significant 3 bytes of sub_atom_size
   //    - r6 = least significant 2 bytes of sub_atom_name
   //    - r7 = most significant 2 bytes of sub_atom_name
   call $aacdec.mp4_read_atom_header;

   // Check whether it is STSZ
   Null = r7 - $aacdec.MP4_STSZ_TAG_MS_WORD;
   if NZ jump $error;
   Null = r6 - $aacdec.MP4_STSZ_TAG_LS_WORD;
   if NZ jump $error;
      // -- Return Error if not STSZ

   // Parse STSZ
    // discard 4 bytes
   call $aacdec.get2bytes;
   call $aacdec.get2bytes;

   // Read sample size
   call $aacdec.get1byte;
   r6 = r1;
   call $aacdec.get2bytes;
   r1 = r1 LSHIFT 8;
   r7 = r1;
   call $aacdec.get1byte;
   r7 = r7 + r1;
   // now sample size = {r6,r7}

   // read sample count
   call $aacdec.get1byte;
   r4 = r1;
   call $aacdec.get2bytes;
   r1 = r1 LSHIFT 8;
   r5 = r1;
   call $aacdec.get1byte;
   r5 = r5 + r1;
   // now sample count = {r4,r5}

   Null = r5 - M[&$aacdec.sample_count + 1];
   if POS jump enough_samples;
      Null = r4;
      if POS jump enough_samples;
         // Boundary condition
         // error -not enough samples. This means request FF value is high
         // Use all avaialbe samples. This will just result in EOF as FF response
         r0 = M[$aacdec.mdat_size  + 2];
         r1 = M[$aacdec.mdat_size + 1];
         M[&$aacdec.ff_rew_skip_amount + 1] = r0;
         M[$aacdec.ff_rew_skip_amount] = r1;
         M[&$aacdec.sample_count + 1] = Null;
         M[&$aacdec.sample_count] = Null;
         jump update_offset_and_exit;

   enough_samples:
   r5 = M[&$aacdec.sample_count + 1];
   r4 = M[$aacdec.sample_count];

   r8 = 12; //bytes read till here
   // if sample size is zero, read size of each sample and add
   Null = r7 OR r6;
   if Z jump stsz_variable_sample_size;

      // fixed sample size
      // sample size = {r6,r7}; - ie. r0 is MSW and r1 is LSW
      // sample count = {r4,r5};

      rMAC = r7 * r5 (UU); // Compute LSW

      r1 = rMAC LSHIFT 23;
      M[&$aacdec.ff_rew_skip_amount + 1] = r1;

      rMAC0 = rMAC1; // shift right 24-bits
      rMAC12 = rMAC2 (ZP);
      rMAC = rMAC + r6 * r5 (UU); // compute inner products
      rMAC = rMAC + r4 * r7 (UU);

      r1 = rMAC LSHIFT 23;
      M[$aacdec.ff_rew_skip_amount] = r1;

      // The product can be 64 bit theoritically.
      // For all practical purposes 48 bits should be sufficient
      // Ignore the MS 16 bits (would be zero)
      /* rMAC0 = rMAC1;
         rMAC12 = rMAC2 (ZP);
         rMAC = rMAC + r6 * r4 (UU);

         r1 = rMAC LSHIFT 23;
         r1 = r1 AND 0xFFFF;
         M[$aacdec.ff_rew_skip_amount] = r1; */

      jump update_offset_and_exit;

   stsz_variable_sample_size:

      r0 = M[$aacdec.num_bytes_available];
      //Subtract num bytes used.r8 = 0 if resumed, else 12
      r0 = r0 - r8;
      // Get num samples avaiable. 4 bytes per sample
      r0 = r0 LSHIFT -2;

      // if r4 > 0, r10 = r0, else r10 = min(r5,r0)
      r10 = r5;
      Null = r4;
      //check if r4 > 0
      if NZ r10 = r0;
      Null = r0 - r10;
      if NEG r10 = r0; //underflow

      M[&$aacdec.sample_count + 1] = r5 - r10;
      M[$aacdec.sample_count] = r4 - Borrow;

      r7 = M[&$aacdec.ff_rew_skip_amount + 1];
      r6 = M[$aacdec.ff_rew_skip_amount];

      do stsz_mdat_loop;
         // Read and add sample size
         call $aacdec.get1byte;
         r6 = r6 + r1;
         call $aacdec.get2bytes;
         r1 = r1 LSHIFT 8;
         r8 = r1;
         call $aacdec.get1byte;
         r8 = r8 + r1;
         r7 = r7 + r8;
         r6 = r6 + Carry;
      stsz_mdat_loop:

      // store the size
      M[&$aacdec.ff_rew_skip_amount + 1] = r7;
      M[$aacdec.ff_rew_skip_amount] = r6;

      // Check if all done
      r4 = M[$aacdec.sample_count];
      r5 = M[&$aacdec.sample_count + 1];
      Null = r4 OR r5;
      if Z jump update_offset_and_exit;
         r0 = 1;
         M[$aacdec.frame_underflow] = r0;

   update_offset_and_exit:
      // Calculate number of bytes read in mp4a atom
      r0 = M[$aacdec.read_bit_count];
      r0 = r0 - M[$aacdec.tmp];
      r1 = r0 ASHIFT -3;

      r0 = M[$aacdec.num_bytes_available];
      r0 = r0 - r1;
      M[$aacdec.num_bytes_available] = r0;

      r0 = r1 + M[&$aacdec.mp4_file_offset + 1];
      r1 = M[$aacdec.mp4_file_offset] + Carry;
      M[&$aacdec.mp4_file_offset + 1] = r0;
      M[$aacdec.mp4_file_offset] = r1;

   jump $pop_rLink_and_rts;

.ENDMODULE;

#if 0 //Disable for now. This may be applicable only in mp4 video files

// *****************************************************************************
// MODULE:
//    $aacdec.mp4_find_random_seek_frame
//
// DESCRIPTION:
//
//
// INPUTS:
//    - None
//
// OUTPUTS:
//    - None
//
// TRASHED REGISTERS:
//    - assume everything including $aacdec.tmp
//
// *****************************************************************************
.MODULE $M.aacdec.mp4_find_random_seek_frame;
   .CODESEGMENT AACDEC_MP4_FF_REW_PM;
   .DATASEGMENT DM;

   $aacdec.mp4_find_random_seek_frame:
   r0 = M[$aacdec.read_bit_count];
   M[$aacdec.tmp] = r0;


   // Previous call returned underflow? Resume parsing
   r8 = 0;
   // if (stss parsing not finished)
   r4 = M[$aacdec.sample_count];
   r5 = M[&$aacdec.sample_count + 1];
   Null = r0 OR r1;
   if NZ jump resume_stss_parsing;

   // Read atom header
   r0 = M[$aacdec.num_bytes_available];
   r0 = r0 - $aacdec.MP4_ATOM_NAME_AND_SIZE_BYTES;
   M[$aacdec.num_bytes_available] = r0;

   //    - r4 = most significant byte of sub_atom_size
   //    - r5 = least significant 3 bytes of sub_atom_size
   //    - r6 = least significant 2 bytes of sub_atom_name
   //    - r7 = most significant 2 bytes of sub_atom_name
   call $aacdec.mp4_read_atom_header;


   // Check whether it is STSS
   Null = r7 - $aacdec.MP4_STSS_TAG_MS_WORD;
   if NZ jump $error;
   Null = r6 - $aacdec.MP4_STSS_TAG_LS_WORD;
   if NZ jump $error;
      // -- Return Error if not STSZ

   // discard 4 bytes
   call $aacdec.get2bytes;
   call $aacdec.get2bytes;

   // Read entry count
   call $aacdec.get1byte;
   r4 = r1;
   call $aacdec.get2bytes;
   r1 = r1 LSHIFT 8;
   r5 = r1;
   call $aacdec.get1byte;

   resume_stss_parsing:
   r0 = M[$aacdec.num_bytes_available];
   //Subtract num bytes used.r8 = 0 if resumed, else 12
   r0 = r0 - r8;
   // Get num samples avaiable. 4 bytes per sample
   r0 = r0 LSHIFT -2;

   // if r4 > 0, r10 = r0, else r10 = min(r5,r0)
   r10 = r5;
   Null = r4;
   //check if r4 > 0
   if NZ r10 = r0;
   Null = r0 - r10;
   if NEG r10 = r0; //underflow

   M[&$aacdec.sample_count + 1] = r5 - r10;
   M[$aacdec.sample_count] = r4 - Borrow;

   r8 = 0;
   r7 = M[$aacdec.mp4_frame_count];
   do find_random_seek_frame_loop;
      r6 = r8;//prev entry in the table
      // Read frame number . Ignore 8 bits
      call $aacdec.get1byte;
      call $aacdec.get2bytes;
      r1 = r1 LSHIFT 8;
      r8 = r1;
      call $aacdec.get1byte;
      r8 = r8 + r1;
      // compare this with frame count
      Null = r8 - r7;
      if POS jump found_random_seek_frame; // found the closest random seek frame
   find_random_seek_frame_loop:

   //check if all done
   r4 = M[$aacdec.sample_count];
   r5 = M[&$aacdec.sample_count + 1];
   Null = r4 OR r5;
   if NZ jump stss_underflow;

   found_random_seek_frame:
      M[$aacdec.sample_count] = Null;
      M[&$aacdec.sample_count + 1] = Null;
      Null = r8 - r7;
      if Z jump update_offset_and_exit;
      r7 = r6;
      jump update_offset_and_exit;

   stss_underflow:
      r0 = 1;
      M[$aacdec.frame_underflow] = r0;

   update_offset_and_exit:
      // Calculate number of bytes read in mp4a atom
      r0 = M[$aacdec.read_bit_count];
      r0 = r0 - M[$aacdec.tmp];
      r1 = r0 ASHIFT -3;

      r0 = M[$aacdec.num_bytes_available];
      r0 = r0 - r1;
      M[$aacdec.num_bytes_available] = r0;

      r0 = r1 + M[&$aacdec.mp4_file_offset + 1];
      r1 = M[$aacdec.mp4_file_offset] + Carry;
      M[&$aacdec.mp4_file_offset + 1] = r0;
      M[$aacdec.mp4_file_offset] = r1;

      M[$aacdec.mp4_frame_count] = r7;


   jump $pop_rLink_and_rts;
.ENDMODULE;
#endif

