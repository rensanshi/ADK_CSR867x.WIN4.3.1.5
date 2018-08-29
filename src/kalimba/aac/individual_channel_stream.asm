// *****************************************************************************
// Copyright (c) 2017 Qualcomm Technologies International, Ltd.
// Part of ADK_CSR867x.WIN 4.3
//
// *****************************************************************************

#include "aac_library.h"

#include "stack.h"
#include "profiler.h"

// *****************************************************************************
// MODULE:
//    $aacdec.individual_channel_stream
//
// DESCRIPTION:
//    Get the individual channel stream data
//
// INPUTS:
//    - none
//
// OUTPUTS:
//    - none
//
// TRASHED REGISTERS:
//    - assume everything including $aacdec.tmp
//
// *****************************************************************************
.MODULE $M.aacdec.individual_channel_stream;
   .CODESEGMENT AACDEC_INDIVIDUAL_CHANNEL_STREAM_PM;
   .DATASEGMENT DM;

   $aacdec.individual_channel_stream:

   // push rLink onto stack
   push rLink;

   // global_gain = getbits(8);
   r4 = M[$aacdec.current_ics_ptr];
   call $aacdec.get1byte;
   M[r4 + $aacdec.ics.GLOBAL_GAIN_FIELD] = r1;

   // if (common_window == 0)
   // {
   //    ics_info();
   // }
   Null = M[$aacdec.common_window];
   if Z call $aacdec.ics_info;
   Null = M[$aacdec.possible_frame_corruption];
   if NZ jump $aacdec.possible_corruption;


   // -- read section data --
   call $aacdec.section_data;
   Null = M[$aacdec.possible_frame_corruption];
   if NZ jump $aacdec.possible_corruption;


   // -- read scalefactor data --
   PROFILER_START(&$aacdec.profile_read_scalefactors)
   call $aacdec.scalefactor_data;
   Null = M[$aacdec.possible_frame_corruption];
   if NZ jump $aacdec.possible_corruption;
   PROFILER_STOP(&$aacdec.profile_read_scalefactors)


   // pulse_data_present = getbits(1);
   call $aacdec.get1bit;
   M[r4 + $aacdec.ics.PULSE_DATA_PTR_FIELD] = r1;

   // if (pulse_data_present == 1)
   //    read pulse_data
   if NZ call $aacdec.pulse_data;
   Null = M[$aacdec.possible_frame_corruption];
   if NZ jump $aacdec.possible_corruption;


   // tns_data_present = getbits(1);
   call $aacdec.get1bit;
   // if (tns_data_present == 1)
   //    read tns data;
   call $aacdec.tns_data;
   Null = M[$aacdec.possible_frame_corruption];
   if NZ jump $aacdec.possible_corruption;

   // dummy = getbits(1); // gain_control_data
   call $aacdec.get1bit;

   // if (gain_control_data_present == 1)
   //    return error;  // gain control data not in LC profile
   if NZ jump $aacdec.possible_corruption;

   // -- read spectral data --
   PROFILER_START(&$aacdec.profile_read_spectral_data)
   call $aacdec.spectral_data;
   Null = M[$aacdec.possible_frame_corruption];
   if NZ jump $aacdec.possible_corruption;
   PROFILER_STOP(&$aacdec.profile_read_spectral_data)


   // if (pulse_data_present == 1)
   // {
   //    if (window_sequence != EIGHT_SHORT_SEQUENCE)
   //       pulse_decode();
   //    else
   //       error 'Pulse data not allowed for short sequences'
   // }
   r3 = M[r4 + $aacdec.ics.PULSE_DATA_PTR_FIELD];
   if Z jump no_pulse_decode;
      r0 = M[r4 + $aacdec.ics.WINDOW_SEQUENCE_FIELD];
      Null = r0 - $aacdec.EIGHT_SHORT_SEQUENCE;
      if Z jump $aacdec.possible_corruption;
      // read pulse data
      call $aacdec.pulse_decode;
      Null = M[$aacdec.possible_frame_corruption];
      if NZ jump $aacdec.possible_corruption;
   no_pulse_decode:


   // pop rLink from stack
   jump $pop_rLink_and_rts;

.ENDMODULE;
