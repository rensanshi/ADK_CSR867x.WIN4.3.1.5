// *****************************************************************************
// Copyright (c) 2017 Qualcomm Technologies International, Ltd.
// Part of ADK_CSR867x.WIN 4.3
//
// *****************************************************************************

#ifndef SBR_CONSTS_HEADER_INCLUDED
#define SBR_CONSTS_HEADER_INCLUDED

   // SBR fields
   .CONST $aacdec.SBR_num_crc_bits                               0;
   .CONST $aacdec.SBR_header_count                               1;
   .CONST $aacdec.SBR_bs_amp_res                                 2;
   .CONST $aacdec.SBR_bs_start_freq                              3;
   .CONST $aacdec.SBR_bs_start_freq_prev                         4;
   .CONST $aacdec.SBR_bs_stop_freq                               5;
   .CONST $aacdec.SBR_bs_stop_freq_prev                          6;
   .CONST $aacdec.SBR_bs_freq_scale                              7;
   .CONST $aacdec.SBR_bs_freq_scale_prev                         8;
   .CONST $aacdec.SBR_bs_alter_scale                             9;
   .CONST $aacdec.SBR_bs_alter_scale_prev                        10;
   .CONST $aacdec.SBR_bs_xover_band                              11;
   .CONST $aacdec.SBR_bs_xover_band_prev                         12;
   .CONST $aacdec.SBR_bs_noise_bands                             13;
   .CONST $aacdec.SBR_bs_noise_bands_prev                        14;
   .CONST $aacdec.SBR_bs_limiter_bands                           15;
   .CONST $aacdec.SBR_bs_limiter_gains                           16;
   .CONST $aacdec.SBR_bs_interpol_freq                           17;
   .CONST $aacdec.SBR_bs_smoothing_mode                          18;
   .CONST $aacdec.SBR_reset                                      19;
   .CONST $aacdec.SBR_k0                                         20;
   .CONST $aacdec.SBR_k2                                         21;
   .CONST $aacdec.SBR_kx                                         22;
   .CONST $aacdec.SBR_Nmaster                                    23;
   .CONST $aacdec.SBR_Nhigh                                      24;
   .CONST $aacdec.SBR_Nlow                                       25;
   .CONST $aacdec.SBR_num_env_bands                              26;
   .CONST $aacdec.SBR_F_table_high                               28;
   .CONST $aacdec.SBR_F_table_low                                92;
   .CONST $aacdec.SBR_Nq                                         156;
   .CONST $aacdec.SBR_F_table_noise                              157;
   .CONST $aacdec.SBR_table_map_k_to_g                           221;
   .CONST $aacdec.SBR_Fmaster                                    285;
   .CONST $aacdec.SBR_M                                          349;
   .CONST $aacdec.SBR_HF_reconstruction                          350;
   .CONST $aacdec.SBR_bs_freq_res                                351;
   .CONST $aacdec.SBR_bs_add_harmonic                            363;
   .CONST $aacdec.SBR_amp_res                                    491;
   .CONST $aacdec.SBR_bs_coupling                                493;
   .CONST $aacdec.SBR_freq_res_prev                              494;
   .CONST $aacdec.SBR_E_prev                                     496;
   .CONST $aacdec.SBR_Q_prev                                     594;
   .CONST $aacdec.SBR_prevEnvIsShort                             604;
   .CONST $aacdec.SBR_bs_add_harmonic_prev                       606;
   .CONST $aacdec.SBR_bs_add_harmonic_flag_prev                  704;
   .CONST $aacdec.SBR_index_noise_prev                           706;
   .CONST $aacdec.SBR_psi_is_prev                                708;
   .CONST $aacdec.SBR_GQ_index                                   710;
   .CONST $aacdec.SBR_kx_prev                                    712;
   .CONST $aacdec.SBR_M_prev                                     713;
   .CONST $aacdec.SBR_bwArray                                    714;
   .CONST $aacdec.SBR_bs_invf_mode_prev                          724;
   .CONST $aacdec.SBR_E_current_exponent_base_ptr                734;
   .CONST $aacdec.SBR_G_LIM_BOOST_BLOCK_EXPONENT_ARRAY_FIELD     736;
   .CONST $aacdec.SBR_Q_M_LIM_BOOST_BLOCK_EXPONENT_ARRAY_FIELD   741;
   .CONST $aacdec.SBR_S_M_BOOST_BLOCK_EXPONENT_ARRAY_FIELD       746;
   .CONST $aacdec.SBR_G_TEMP_BLOCK_EXPONENT_ARRAY_FIELD          751;
   .CONST $aacdec.SBR_Q_TEMP_BLOCK_EXPONENT_ARRAY_FIELD          761;
   .CONST $aacdec.SBR_G_FILT_BLOCK_EXPONENT_FIELD                771;
   .CONST $aacdec.SBR_Q_FILT_BLOCK_EXPONENT_FIELD                772;
   .CONST $aacdec.SBR_G_TEMP_LIM_ENV_ADDR_ARRAY_FIELD            773;
   .CONST $aacdec.SBR_Q_TEMP_LIM_ENV_ADDR_ARRAY_FIELD            783;
   .CONST $aacdec.SBR_G_TEMP_PERSISTENT_ENVELOPES_ARRAY_FIELD    793;
   .CONST $aacdec.SBR_Q_TEMP_PERSISTENT_ENVELOPES_ARRAY_FIELD    989;

   .CONST $aacdec.SBR_SIZE                                       1185;

   // Some temporary variables to be stored at the end of tmp_mem_pool
   .CONST $aacdec.SBR_bit_count                      ($aacdec.TMP_MEM_POOL_LENGTH -1)-0;       // 1
   .CONST $aacdec.SBR_bs_header_extra_1              ($aacdec.TMP_MEM_POOL_LENGTH-1)-2;       // 1
   .CONST $aacdec.SBR_bs_header_extra_2              ($aacdec.TMP_MEM_POOL_LENGTH-1)-3;       // 1
   .CONST $aacdec.SBR_k1                             ($aacdec.TMP_MEM_POOL_LENGTH-1)-2;       // 1
   .CONST $aacdec.SBR_cnt                            ($aacdec.TMP_MEM_POOL_LENGTH-1)-1;       // 1
   .CONST $aacdec.SBR_abs_bord_lead                  ($aacdec.TMP_MEM_POOL_LENGTH-1)-41;      // 2
   .CONST $aacdec.SBR_abs_bord_trail                 ($aacdec.TMP_MEM_POOL_LENGTH-1)-39;      // 2
   .CONST $aacdec.SBR_bs_num_rel_0                   ($aacdec.TMP_MEM_POOL_LENGTH-1)-37;      // 2
   .CONST $aacdec.SBR_bs_num_rel_1                   ($aacdec.TMP_MEM_POOL_LENGTH-1)-35;      // 2
   .CONST $aacdec.SBR_bs_rel_bord                    ($aacdec.TMP_MEM_POOL_LENGTH-1)-33;      // 10
   .CONST $aacdec.SBR_bs_rel_bord_0                  ($aacdec.TMP_MEM_POOL_LENGTH-1)-23;      // 10
   .CONST $aacdec.SBR_bs_rel_bord_1                  ($aacdec.TMP_MEM_POOL_LENGTH-1)-13;      // 10
   .CONST $aacdec.SBR_bs_num_noise                   ($aacdec.TMP_MEM_POOL_LENGTH-1)-3;       // 2
   .CONST $aacdec.SBR_bs_df_env                      ($aacdec.TMP_MEM_POOL_LENGTH-1)-15;      // 10
   .CONST $aacdec.SBR_bs_df_noise                    ($aacdec.TMP_MEM_POOL_LENGTH-1)-19;      // 4
   .CONST $aacdec.SBR_E_envelope_base_ptr            ($aacdec.TMP_MEM_POOL_LENGTH-1)-5;       // 2
   .CONST $aacdec.SBR_Q_envelope_base_ptr            ($aacdec.TMP_MEM_POOL_LENGTH-1)-21;      // 2
   .CONST $aacdec.SBR_l_A                            ($aacdec.TMP_MEM_POOL_LENGTH-1)-1;       // 2
   .CONST $aacdec.SBR_E_current_base_ptr             ($aacdec.TMP_MEM_POOL_LENGTH-1)-11;      // 2
   .CONST $aacdec.SBR_S_mapped                       ($aacdec.TMP_MEM_POOL_LENGTH-1)-2;       // 1
   .CONST $aacdec.SBR_N_L                            ($aacdec.TMP_MEM_POOL_LENGTH-1)-16;      // 4
   .CONST $aacdec.SBR_F_table_lim_base_ptr           ($aacdec.TMP_MEM_POOL_LENGTH-1)-17;      // 1
   .CONST $aacdec.SBR_Q_M_mantissa                   ($aacdec.TMP_MEM_POOL_LENGTH-1)-3;       // 1
   .CONST $aacdec.SBR_Q_M_exponent                   ($aacdec.TMP_MEM_POOL_LENGTH-1)-4;       // 1
   .CONST $aacdec.SBR_G_max_mantissa                 ($aacdec.TMP_MEM_POOL_LENGTH-1)-5;       // 1
   .CONST $aacdec.SBR_G_max_exponent                 ($aacdec.TMP_MEM_POOL_LENGTH-1)-6;       // 1
   .CONST $aacdec.SBR_G_lim_boost_mantissa_ptr       ($aacdec.TMP_MEM_POOL_LENGTH-1)-18;      // 1
   .CONST $aacdec.SBR_G_lim_boost_exponent_ptr       ($aacdec.TMP_MEM_POOL_LENGTH-1)-7;       // 1
   .CONST $aacdec.SBR_Q_M_lim_boost_mantissa_ptr     ($aacdec.TMP_MEM_POOL_LENGTH-1)-19;      // 1
   .CONST $aacdec.SBR_Q_M_lim_boost_exponent_ptr     ($aacdec.TMP_MEM_POOL_LENGTH-1)-8;       // 1
   .CONST $aacdec.SBR_S_M_boost_mantissa_ptr         ($aacdec.TMP_MEM_POOL_LENGTH-1)-20;      // 1
   .CONST $aacdec.SBR_S_M_boost_exponent_ptr         ($aacdec.TMP_MEM_POOL_LENGTH-1)-9;       // 1
   .CONST $aacdec.SBR_G_filt_ptr                     ($aacdec.TMP_MEM_POOL_LENGTH-1)-11;      // 1
   .CONST $aacdec.SBR_Q_filt_ptr                     ($aacdec.TMP_MEM_POOL_LENGTH-1)-10;      // 1
   .CONST $aacdec.SBR_kx_band                        ($aacdec.TMP_MEM_POOL_LENGTH-1)-11;      // 1
   .CONST $aacdec.SBR_M_band                         ($aacdec.TMP_MEM_POOL_LENGTH-1)-10;      // 1
   .CONST $aacdec.SBR_patch_start_subband            ($aacdec.TMP_MEM_POOL_LENGTH-1)-5;       // 6
   .CONST $aacdec.SBR_patch_num_subbands             ($aacdec.TMP_MEM_POOL_LENGTH-1)-11;      // 6
   .CONST $aacdec.SBR_num_patches                    ($aacdec.TMP_MEM_POOL_LENGTH-1)-12;      // 1


   // These should be moved to other places if possible
   .CONST $aacdec.SBR_bs_frame_class                 0;       // 2
   .CONST $aacdec.SBR_bs_num_env                     2;       // 2
   .CONST $aacdec.SBR_bs_pointer                     4;       // 2
   .CONST $aacdec.SBR_bs_invf_mode                   6;       // 10
   .CONST $aacdec.SBR_bs_add_harmonic_flag           16;      // 2
   .CONST $aacdec.SBR_t_E                            18;      // 12
   .CONST $aacdec.SBR_t_Q                            30;      // 6
   .CONST $aacdec.SBR_E_orig_mantissa_base_ptr       36;      // 2
   .CONST $aacdec.SBR_Q_orig                         38;      // 20
   .CONST $aacdec.SBR_Q_orig2                        58;      // 20
#ifdef AACDEC_ELD_ADDITIONS
   .CONST $aacdec.SBR_bs_transient_position          78;      //2
   .CONST $aacdec.SBR_NP_size                        80;
#else
	.CONST $aacdec.SBR_NP_size                        78;
#endif 


   .CONST $aacdec.SBR_vDk0_length                          0;
   .CONST $aacdec.SBR_vDk1_length                          1;
   .CONST $aacdec.SBR_two_regions                          2;
   .CONST $aacdec.SBR_log2_table_addr                      3;

#ifdef AACDEC_ELD_ADDITIONS
	.CONST $aacdec.SBR_RATE                                1;
	.CONST $aacdec.SBR_tHFGen                              2; /// This has to be changed to 2 as reqd for ELD ////hardcoded to 8 to resolve compiler issues 
#else
	.CONST $aacdec.SBR_RATE                                2;
	.CONST $aacdec.SBR_tHFGen                              8;
#endif 
   .CONST $aacdec.SBR_tHFAdj                               2;

   .CONST $aacdec.SBR_E_deg_offset                         6;


   .CONST $aacdec.SBR_Nq_max                               5;

   .CONST $aacdec.SBR_M_MAX                                49;

   .CONST $aacdec.SBR_est_curr_env_upper_i                 0;
   .CONST $aacdec.SBR_est_curr_env_div                     1;
   .CONST $aacdec.SBR_est_curr_env_k_lower                 2;
   .CONST $aacdec.SBR_est_curr_env_freq_band_loop_bound    3;


   // temporary variables used in sbr_calculate_gain
   .CONST $aacdec.SBR_delta                                      0;
   .CONST $aacdec.SBR_calc_gain_current_t_noise_band             1;
   .CONST $aacdec.SBR_calc_gain_den_mantissa                     2;
   .CONST $aacdec.SBR_calc_gain_den_exponent                     3;
   .CONST $aacdec.SBR_calc_gain_current_acc1_man                 4;
   .CONST $aacdec.SBR_calc_gain_current_acc1_exp                 5;
   .CONST $aacdec.SBR_calc_gain_current_acc2_man                 6;    .CONST $aacdec.SBR_calc_gain_save_ch  6;
   .CONST $aacdec.SBR_calc_gain_current_acc2_exp                 7;    .CONST $aacdec.SBR_calc_gain_save_l   7;
   .CONST $aacdec.SBR_calc_gain_current_res_band                 8;    .CONST $aacdec.SBR_calc_gain_lim_boost_outer_loop_index    8;
   .CONST $aacdec.SBR_calc_gain_current_res_band2                9;
   .CONST $aacdec.SBR_calc_gain_current_f_noise_band             10;
   .CONST $aacdec.SBR_calc_gain_current_hi_res_band              11;
   .CONST $aacdec.SBR_calc_gain_boost_data_per_envelope          12;
   .CONST $aacdec.SBR_calc_gain_g_max_shift_bits                 13;
   .CONST $aacdec.SBR_calc_gain_e_orig_curr_res_band2_shift_bits 14;
   .CONST $aacdec.SBR_calc_gain_e_curr_plus_one_exp              15;
   .CONST $aacdec.SBR_calc_gain_limiter_band_outer_loop_bound    16;
   .CONST $aacdec.SBR_calc_gain_ftable_lim_last_band_ptr         17;
   .CONST $aacdec.SBR_calc_gain_acc_loop_bound                   18;


   .CONST NO_OF_BOOST_GAIN_MANTISSA_BITS                 16;


   // temporary variables used in sbr_hf_assembly
   .CONST $aacdec.SBR_f_index_noise                              0;
   .CONST $aacdec.SBR_f_index_sine                               1;
   .CONST $aacdec.SBR_phi_re_sin_value                           2;
   .CONST $aacdec.SBR_v_noise_real_value                         3;
   .CONST $aacdec.SBR_v_noise_imag_value                         4;
   .CONST $aacdec.SBR_W1_real_value                              5;
   .CONST $aacdec.SBR_W1_imag_value                              6;
   .CONST $aacdec.SBR_H_SL                                       7;

   .CONST $aacdec.SBR_hf_assembly_inner_loop_bound               8;
   .CONST $aacdec.SBR_hf_assembly_save_ch                        9;
   .CONST $aacdec.SBR_hf_assembly_save_l                         10;
   .CONST $aacdec.SBR_hf_assembly_time_envelope_border           11;
   .CONST $aacdec.SBR_hf_assembly_s_m_boost_shift_amount         13;
   .CONST $aacdec.SBR_hf_assembly_noise_component_flag           14;

   .CONST $aacdec.SBR_hf_assembly_v_noise_start                  15;


   .CONST $aacdec.SBR_qmf_synthesis_filterbank_audio_out_scale_factor 11;


   .CONST $aacdec.SBR_V_NOISE_TABLE_SIZE       512;


   .CONST $aacdec.SBR_ANALYSIS_SHIFT_AMOUNT          4; // positive -> attenuation
   .CONST $aacdec.SBR_ANALYSIS_POST_SHIFT_AMOUNT     2; // positive -> gain
   .CONST $aacdec.SBR_AUDIO_OUT_SCALE_AMOUNT   (1<<$aacdec.SBR_ANALYSIS_SHIFT_AMOUNT)*4;


   .CONST $aacdec.SBR_phi_01_r        9;
   .CONST $aacdec.SBR_phi_01_i        10;
   .CONST $aacdec.SBR_phi_02_r        11;
   .CONST $aacdec.SBR_phi_02_i        12;
   .CONST $aacdec.SBR_phi_11_r        8;
   .CONST $aacdec.SBR_phi_12_r        13;
   .CONST $aacdec.SBR_phi_12_i        14;
   .CONST $aacdec.SBR_phi_22_r        15;
   .CONST $aacdec.SBR_alpha_0         16;   // [real, imag]
   .CONST $aacdec.SBR_alpha_1         18;   // [real, imag]


   // value used to add 1 to SBR_E_curr to prevent divide by zero in calculating G
   // as SBR_E_curr stored with mantissa in 12-bits and exponent above the true value
   .CONST $aacdec.SBR_calc_gain_e_curr_plus_one_value_mantissa      (1<<11);
   .CONST $aacdec.SBR_calc_gain_e_curr_plus_one_value_exponent      ($aacdec.SBR_ANALYSIS_SHIFT_AMOUNT*2 + 1) - 15;


   .CONST $aacdec.SBR_calc_gain_g_max_limit_mantissa       4882813;    // currently must equal SBR_calc_gain_current_1e10_man for sbr_calculate_gain to work
   .CONST $aacdec.SBR_calc_gain_g_max_limit_exponent       (11 - 3);


   // fractional form i.e. 1e10 = (4882813 / 2^23) * 2^34
   .CONST $aacdec.SBR_calc_gain_current_1e10_man           4882813;    // currently must equal SBR_calc_gain_g_max_limit_mantissa for sbr_calculate_gain to work
   .CONST $aacdec.SBR_calc_gain_current_1e10_exp           34;

   .CONST $aacdec.SBR_G_boost_max_value                    5267808;    // max value (2.51188643) shifted left 21 bits


   // fractional form i.e. SBR_G_boost_max = (5267808 / 2^23) * 2^2
   .CONST $aacdec.SBR_G_boost_max_mantissa                 5267808;
   .CONST $aacdec.SBR_G_boost_max_exponent                 2;

#ifdef AACDEC_ELD_ADDITIONS
   .CONST $aacdec.SBR_FIXFIX          0;
   .CONST $aacdec.SBR_LDTRAN          1;
#else
   .CONST $aacdec.SBR_FIXFIX          0;
   .CONST $aacdec.SBR_FIXVAR          1;
   .CONST $aacdec.SBR_VARFIX          2;
   .CONST $aacdec.SBR_VARVAR          3;
   .CONST $aacdec.SBR_numTimeSlots       16;
   .CONST $aacdec.SBR_numTimeSlotsRate   32;  // SBR_numTimeSlots * SBR_RATE
#endif
  
  

   .CONST $aacdec.SBR_QMF_STOP_CHANNEL_OFFSET_ROW_LENGTH   14;

   .CONST $aacdec.SBR_OFFSET_ROW_LENGTH   16;

   .CONST $aacdec.SBR_LOG_NATURAL_SHIFT_AMOUNT  3;

   .CONST $aacdec.SBR_LOG2_TABLE_SIZE    216;

   .CONST $aacdec.SBR_POW2_TABLE_SHIFT_AMOUNT  7;  //log2(length(sbr_pow2_table))+1


   // SBR_huffman tables sizes
   .CONST $aacdec.SBR_HUFFMAN_ENV_1_5_DB_SIZE            120;

   .CONST $aacdec.SBR_HUFFMAN_ENV_BAL_1_5_DB_SIZE        48;

   .CONST $aacdec.SBR_HUFFMAN_ENV_3_0_DB_SIZE            62;

   .CONST $aacdec.SBR_HUFFMAN_ENV_BAL_3_0_DB_SIZE        24;

   .CONST $aacdec.SBR_T_HUFFMAN_NOISE_3_0_DB_SIZE        62;

   .CONST $aacdec.SBR_T_HUFFMAN_NOISE_BAL_3_0_DB_SIZE    24;

   .CONST $aacdec.SBR_HUFFMAN_TABLE_SIZE                 0;


   .CONST $aacdec.SBR_LOG_BASE2_SHIFT_AMOUNT  3;

   .CONST $aacdec.SBR_Q_DIV_TABLES_ROW_LENGTH     31;

   // x_input_buffers
   .CONST $aacdec.X_INPUT_BUFFER_LENGTH 320;
   .CONST $aacdec.SBR_LEFT_CH  0;
   .CONST $aacdec.SBR_RIGHT_CH 1;
   .CONST $aacdec.SBR_CHANNELS 2;

   .CONST $aacdec.SBR_NORMALSAMPLED   0;
   .CONST $aacdec.SBR_DOWNSAMPLED     1;

   .CONST $aacdec.SBR_N  128;
   .CONST $aacdec.SBR_K   64;
   .CONST $aacdec.SBR_STEP 1;
   .CONST $aacdec.SBR_DOWNSAMPLED_N   64;
   .CONST $aacdec.SBR_DOWNSAMPLED_K   32;
   .CONST $aacdec.SBR_DOWNSAMPLED_STEP 2;

   .CONST $aacdec.SBR_DCT 0;
   .CONST $aacdec.SBR_DST 1;

   .CONST $aacdec.EXT_SBR_DATA                 13;
   .CONST $aacdec.EXT_SBR_DATA_CRC             14;
   .CONST $aacdec.EXT_FILL                     0;
   .CONST $aacdec.EXT_FILL_DATA                1;
   .CONST $aacdec.EXT_DATA_ELEMENT             2;
   .CONST $aacdec.EXT_DYNAMIC_RANGE            11;
   .CONST $aacdec.ANC_DATA                     0;



   .CONST $aacdec.SBR_SR_INDEX_0_THRESHOLD     92017;
   .CONST $aacdec.SBR_SR_INDEX_1_THRESHOLD     75132;
   .CONST $aacdec.SBR_SR_INDEX_2_THRESHOLD     55426;
   .CONST $aacdec.SBR_SR_INDEX_3_THRESHOLD     46009;
   .CONST $aacdec.SBR_SR_INDEX_4_THRESHOLD     37566;
   .CONST $aacdec.SBR_SR_INDEX_5_THRESHOLD     27713;
   .CONST $aacdec.SBR_SR_INDEX_6_THRESHOLD     23004;
   .CONST $aacdec.SBR_SR_INDEX_7_THRESHOLD     18783;
   .CONST $aacdec.SBR_SR_INDEX_8_THRESHOLD     13856;
   .CONST $aacdec.SBR_SR_INDEX_9_THRESHOLD     11502;
   .CONST $aacdec.SBR_SR_INDEX_10_THRESHOLD    9391;


   .CONST $aacdec.SBR_STOP_MIN_INTER_VALUES_1  6000*128;
   .CONST $aacdec.SBR_STOP_MIN_INTER_VALUES_2  8000*128;
   .CONST $aacdec.SBR_STOP_MIN_INTER_VALUES_3  10000*128;



   .CONST $aacdec.X_SBR_WIDTH 64;
#ifdef AACDEC_ELD_ADDITIONS
   .CONST $aacdec.X_SBR_LEFTRIGHT_SIZE          384; /// Hardcoded - need to have closer look as part of DSPSW-444.
   .CONST $aacdec.X_SBR_SHARED_SIZE             1024;
#else
   .CONST $aacdec.X_SBR_LEFTRIGHT_SIZE          $aacdec.X_SBR_WIDTH * ($aacdec.SBR_tHFGen-$aacdec.SBR_tHFAdj);
   .CONST $aacdec.X_SBR_SHARED_SIZE             $aacdec.X_SBR_WIDTH * $aacdec.SBR_numTimeSlotsRate;
#endif 
   .CONST $aacdec.X_SBR_LEFTRIGHT_2ENV_SIZE     ($aacdec.X_SBR_WIDTH/2) * $aacdec.SBR_tHFAdj;
  

   .CONST $aacdec.SBR_LIM_TABLE_SIZE          100;
   .CONST $aacdec.SBR_PATCH_BORDERS_SIZE       64;

#endif
