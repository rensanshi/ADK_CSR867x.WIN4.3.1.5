// *****************************************************************************
// Copyright (c) 2017 Qualcomm Technologies International, Ltd.
// Part of ADK_CSR867x.WIN 4.3
//
// *****************************************************************************

#include "aac_library.h"

#ifdef AACDEC_SBR_ADDITIONS

#include "stack.h"

// *****************************************************************************
// MODULE:
//    $aacdec.sbr_huff_dec
//
// DESCRIPTION:
//    Read huffman pair of values
//
// INPUTS:
//    - I0,L0 = buffer to read words from
//    - I2 = pointer to the hufftable to use
//
// OUTPUTS:
//    - I0,L0 = updated
//    - r1 huffman data
//
// TRASHED REGISTERS:
//    - r0, r2-r4, M0, M1, I1
//
// *****************************************************************************
.MODULE $M.aacdec.sbr_huff_dec;
   .CODESEGMENT AACDEC_SBR_HUFF_DEC_PM;
   .DATASEGMENT DM;

   $aacdec.sbr_huff_dec:

   // push rLink onto stack
   push rLink;

   call $aacdec.huffman_start;

   // save base pointer to huffman table
   I1 = I2;
   r4 = -8;

   huff_loop:


      // mask out current bit from bitstream
      Null = r2 AND r3,
       r1 = M[I1,M0];       // read huffman node data

      // if bit=1 then take high 8 bits of huffman node
      if NZ r1 = r1 LSHIFT r4;

      // form next bitmask
      r3 = r3 LSHIFT -1;
      if NZ jump no_new_word_needed;
         // read next word from bitstream
         r2 = M[I0,1];
         // set bitmask to 0x8000
         r3 = Null OR BITPOS_START_MASK;
      no_new_word_needed:

      // AND off the lower 8-bits of huffman node
      r1 = r1 AND 0xFF;

      // if bit 7 set then huffman code has ended
      r0 = r1 - 0x80;
      if POS jump code_ended;

      // move huffman pointer onto the next node in the binary tree
      I1 = I2 + r1;

   jump huff_loop;

   code_ended:


   // fill out upper 16 bits with sign bit (1)
   r1 = r1 + (0xFFFF00 + 64);

   call $aacdec.huffman_finish;


   // pop rLink from stack
   jump $pop_rLink_and_rts;



.ENDMODULE;

#endif
