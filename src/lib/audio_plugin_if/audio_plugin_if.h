/****************************************************************************
Copyright (c) 2004 - 2017 Qualcomm Technologies International, Ltd.

FILE NAME
    audio_plugin_if.h

DESCRIPTION

*/

/*!

\defgroup audio_plugin_if audio_plugin_if
\ingroup vm_libs

\brief  Header file for the audio plugin interface.

\section audio_plugin_if_intro INTRODUCTION
    The parameters / enums here define the message interface used for the
    audio plugin.
    i.e This defines the interface between the audio library and the underlying plugin

    The contents of these are similar to the parameters passed into the
    audio library itself

    These messages are generated by the audio library and received in the message handler
    associate with the constant task of an audio plugin.

    The company_name_action_plugin.c / h files contain the meessage handler which
    receives these messages.

    The plugin itself is responsible for acting upon these messages.

@{

*/


#ifndef _AUDIO_PLUGIN_INTERFACE_H_
#define _AUDIO_PLUGIN_INTERFACE_H_

#include <library.h>
#include <power.h>
#include <stream.h>
#include <audio_output.h>

/* Coefficient used by DSP to calculate the actual sample rate from uint16 sent by VM */
#define DSP_RESAMPLING_RATE_COEFFICIENT 10

#define DSP_CODEC_INPUT_PORT    0
#define TONE_VP_MIXING_DSP_PORT 3

/* Kalimba Message IDs */

#define LOW_LATENCY_READY_MSG       (0x1000)
#define LOW_LATENCY_SETMODE_MSG     (0x1001)
#define LOW_LATENCY_VOLUME_MSG      (0x1002)
#define LOW_LATENCY_SETPARAM_MSG    (0x1004)
#define LOW_LATENCY_CODEC_MSG       (0x1006)
#define LOW_LATENCY_PING            (0x1008)
#define LOW_LATENCY_PINGRESP        (0x1009)
#define LOW_LATENCY_CVC_SEC_PASSED  (0x100c)
#define LOW_LATENCY_SETSCOTYPE      (0x100d)
#define LOW_LATENCY_GETPARAM        (0x1010)
#define LOW_LATENCY_GETPARAM_RESP   (0x1011)
#define LOW_LATENCY_LOADPARAMS_MSG  (0x1012)
#define LOW_LATENCY_CVC_SEC_FAILED  (0x1013)
#define LOW_LATENCY_LOAD_PERSIST    (0x1014)
#define LOW_LATENCY_LOAD_PERSIST_RESP (0x1015)
#define LOW_LATENCY_STORE_PARAMS    (0x1033)
#define LOW_LATENCY_APTX_SEC_PASSED (0x1035)
#define LOW_LATENCY_SIGNAL_DET_SET_PARAMS_MSG (0x1018)
#define LOW_LATENCY_SIGNAL_DET_STATUS (0x1019)
#define LOW_LATENCY_SOFT_MUTE       (0x101A)
#define LOW_LATENCY_SET_PLUGIN_MSG  (0x1024)
#define LOW_LATENCY_APTX_SEC_FAILED (0x1034)
#define LOW_LATENCY_CUR_EQ_BANK     (0x1028)
#define LOW_LATENCY_STOREPERSIST_MSG (0x1016)
#define MESSAGE_SET_SAMPLE_RATE     (0x7050)
#define LOW_LATENCY_PARAMS_LOADED_MSG (0xffff)
#define LOW_LATENCY_SET_EQ_MSG      (0x1039)

#define MUSIC_READY_MSG             (0x1000)
#define MUSIC_SETMODE_MSG           (0x1001)
#define MUSIC_SETPARAM_MSG          (0x1004)
#define MUSIC_CODEC_MSG             (0x1006)
#define MUSIC_FORWARD_UNDECODED_MSG (0x1007)
#define MUSIC_PING                  (0x1008)
#define MUSIC_PINGRESP              (0x1009)
#define MUSIC_SETSCOTYPE            (0x100d)
#define MUSIC_SETCONFIG             (0x100e)
#define MUSIC_SETCONFIG_RESP        (0x100f)
#define MUSIC_GETPARAM              (0x1010)
#define MUSIC_GETPARAM_RESP         (0x1011)
#define MUSIC_LOADPARAMS_MSG        (0x1012)
#define MUSIC_CUR_EQ_BANK           (0x1014)
#define MUSIC_PARAMS_LOADED_MSG     (0x1015)
#define MUSIC_SILENCE_DETECTION_PARAMS_MSG (0x1018)
#define MUSIC_SIGNAL_DETECT_STATUS  (0x1019)
#define MUSIC_SET_PLUGIN_MSG        (0x1020)
#define CONFIGURE_LATENCY_REPORTING (0x1027)
#define MUSIC_TONE_COMPLETE         (0x1080)


#define RELAY_MODE_NONE             (0)
#define RELAY_MODE_SHAREME          (1)
#define RELAY_MODE_TWS_MASTER       (2)
#define RELAY_MODE_TWS_SLAVE        (3)
#define MESSAGE_SET_RELAY_MODE      (0x1028)

#define TWS_ROUTING_STEREO          (0)
#define TWS_ROUTING_LEFT            (1)
#define TWS_ROUTING_RIGHT           (2)
#define TWS_ROUTING_DMIX            (3)
#define MESSAGE_VM_TWS_COMPATIBILITY_MODE (0x715D)
#define MESSAGE_SET_TWS_ROUTING     (0x7157)

#define MESSAGE_SET_DEVICE_TRIMS    (0x7158)
#define MESSAGE_ENABLE_EXT_VOLUME   (0x7159)

#define MESSAGE_SET_BIT_RESOLUTION  (0x10a5)
#define RESOLUTION_MODE_16BIT       (16)          /* 16bit resolution mode */
#define RESOLUTION_MODE_24BIT       (24)          /* 24bit resolution mode */

/*
Received when signal detector status has changed
Param1 == 0 => no audio - go into standby
Param1 == 1 => receiving audio - come out of standby
*/
#define MUSIC_SIGNAL_DETECTOR_STATUS_RESP  (0x1019)

#define MUSIC_PS_BASE               (0x2270) /* PSKEY_USERDSP_24 */
#define MUSIC_PS_BASE_WBS_BACK_CHANNEL (0x2270)  /* PSKEY_USERDSP_24 */

#define APTX_PARAMS_MSG             (0x1016)
#define APTX_SECURITY_MSG           (0x1017)
#define APTX_SECPASSED_MSG          (0x100c)
#define APTX_SECFAILED_MSG          (0x1013)
#define MESSAGE_SET_APTX_LL_PARAMS1 (0x1036)
#define MESSAGE_SET_APTX_LL_PARAMS2 (0x1037)
#define KALIMBA_MSG_LATENCY_REPORT  (0x1023)
#define KALIMBA_MSG_RELAY_MODE_RESP (0x1024)
#define KALIMBA_MSG_EXTERNAL_VOLUME (0x715A)
#define KALIMBA_MSG_TWS_ERROR       (0x715B)

#define MESSAGE_SET_MUSIC_MANAGER_SAMPLE_RATE      (0x1070)
#define MESSAGE_SET_CODEC_SAMPLE_RATE    (0x1071)
#define MESSAGE_SET_TONE_RATE_MESSAGE_ID (0x1072)
#define MESSAGE_SET_SPDIF_CONFIG_MSG     (0x1073)
#define MESSAGE_SET_AC3_CONFIG_MSG       (0x1074)
#define KALIMBA_MSG_DSP_SPDIF_EVENT_MSG  (0x1075)
#define MESSAGE_GET_AC3_USER_INFO_MSG    (0x1077)

#define MESSAGE_SET_I2S_CONFIG_MSG              (0x10a1)
#define MESSAGE_SET_DAC_OUTPUT_RESAMPLER_MSG        (0x10a4)

#define MESSAGE_SET_MULTI_CHANNEL_OUTPUT_TYPES_S    (0x10a6)
#define MESSAGE_MULTI_CHANNEL_MUTE_MAIN_S           (0x10a7)
#define MESSAGE_MULTI_CHANNEL_MUTE_AUX_S            (0x10a8)
#define MUSIC_VOLUME_MSG_S                          (0x10a9)
#define MUSIC_VOLUME_AUX_MSG_S                      (0x10aa)

#define KALIMBA_SET_USER_EQ_PARAM                   (0x121a)
#define KALIMBA_GET_USER_EQ_PARAM                   (0x129a)
#define KALIMBA_SET_USER_EQ_PARAMS                  (0x121b)
#define KALIMBA_GET_USER_EQ_PARAMS                  (0x129b)

#define KALIMBA_GET_USER_EQ_PARAM_RESP              (0x329a)
#define KALIMBA_GET_USER_EQ_PARAMS_RESP             (0x329b)

#define MUSIC_SYSMODE_STANDBY        0
#define MUSIC_SYSMODE_PASSTHRU       1
#define MUSIC_SYSMODE_FULLPROC       2
#define MUSIC_SYSMODE_FULLPROC_MONO  3
#define MUSIC_SYSMODE_PASSTHRU_MONO  4
#define MUSIC_SYSMODE_STANDBY_MONO   5
#define MUSIC_SYSMODE_BASSMANAGEMENT 6
#define MUSIC_SYSMODE_BASSMANAGEMENT_MONO 7

#define MUSIC_DO_NOT_CHANGE_EQ_BANK      0
#define MUSIC_NEXT_EQ_BANK               1
#define MUSIC_SET_EQ_BANK                2

/* Mesage parameter selection masks */
#define MUSIC_RATE_MATCH_DISABLE        0x80
#define MUSIC_AUDIO_IF_MASK             0x00ff
#define MUSIC_LOCAL_PLAYBACK_MASK       0x0100
#define LOCAL_FILE_PLAYBACK             0x100
#define PCM_PLAYBACK                    0x200

/* Params for word 1 of MESSAGE_SET_TONE_RATE_MESSAGE_ID */
#define MONO_PROMPT                     0x0     /* 0 = mono */
#define PROMPT_STEREO                   0x1     /* 1= stereo */
#define NO_EXTRA_GAIN                   0x2     /* 1= no-extra gain required, 0 = use 3bits extra gain */

/* when using a subwoofer, fix the DAC/I2S output rate at 48KHz to
   allow resampling for I2S outputs to work */
#define FIXED_SUBWOOFER_DAC_SAMPLE_RATE 48000

/* operating status of the DSP */
typedef enum  DspStatusTag
{
    DSP_NOT_LOADED,
    DSP_LOADING,
    DSP_LOADED_IDLE,
    DSP_RUNNING,
    DSP_ERROR
}DSP_STATUS_INFO_T;

/*the Mode*/
typedef enum AudioModeTag
{
    AUDIO_MODE_MUTE_MIC       ,
    AUDIO_MODE_MUTE_SPEAKER   ,
    AUDIO_MODE_UNMUTE_SPEAKER ,
    AUDIO_MODE_MUTE_BOTH      ,
    AUDIO_MODE_CONNECTED      ,   /* (FULL_PROCESSING) */
    AUDIO_MODE_LEFT_PASSTHRU  ,
    AUDIO_MODE_RIGHT_PASSTHRU ,
    AUDIO_MODE_LOW_VOLUME     ,
    AUDIO_MODE_STANDBY
}AUDIO_MODE_T ;

/*the audio route*/
typedef enum AudioRouteTag
{
    AUDIO_ROUTE_INTERNAL,
    AUDIO_ROUTE_I2S,
    AUDIO_ROUTE_SPDIF,
    AUDIO_ROUTE_INTERNAL_AND_RELAY
}AUDIO_ROUTE_T;

/*the audio sink type*/
typedef enum AudioSinkTag
{
    AUDIO_SINK_INVALID  ,
    AUDIO_SINK_SCO      ,
    AUDIO_SINK_ESCO     ,
    AUDIO_SINK_AV       ,
    AUDIO_SINK_USB      ,
    AUDIO_SINK_ANALOG   ,
    AUDIO_SINK_SPDIF    ,
    AUDIO_SINK_I2S      ,
    AUDIO_SINK_FM       ,
    AUDIO_SINK_SIDE_GRAPH
} AUDIO_SINK_T ;

/* operating modes of the soundbar sub connection */
typedef enum AudioSubTypeTag
{
    AUDIO_SUB_WOOFER_NONE ,
    AUDIO_SUB_WOOFER_ESCO ,
    AUDIO_SUB_WOOFER_L2CAP
} AUDIO_SUB_TYPE_T;

/* Soft mute modes supported by the low latency DSP applications */
typedef enum AudioSoftMuteTypeTag
{
    unmute_sink_and_sub = 0,    /* Unmute both Sink and Sub */
    mute_sink_not_sub = 1,      /* Mute sink but not sub (only unmute sub) */
    mute_sub_not_sink = 2,      /* Mute sub but not sink (only unmute sink) */
    mute_sink_and_sub = 3       /* Mute both sink and sub */
} AUDIO_LL_SOFT_MUTE_TYPE_T;

/*  Mute groups supported by the soft mute interface, for normal DSP applications.
    Also used to define the bits in mute state bit-fields.
 */
typedef enum
{
    audio_mute_group_main = 0,
    audio_mute_group_aux,
    audio_mute_group_mic,
    audio_mute_group_max    /*! Not valid */
} AUDIO_MUTE_GROUP_T;

/* States each mute group can be in (bit-field bit values) */
typedef enum
{
    AUDIO_MUTE_DISABLE = 0,
    AUDIO_MUTE_ENABLE
} AUDIO_MUTE_STATE_T;

/* Macros representing a mute state bit-field with all bits enabled/disabled */
#define AUDIO_MUTE_DISABLE_ALL  (0x0)
#define AUDIO_MUTE_ENABLE_ALL   ((AUDIO_MUTE_ENABLE << audio_mute_group_max) - 1)

/* Function macro to generate a mute mask for a specific mute group bit */
#define AUDIO_MUTE_MASK(mute_group) (1 << mute_group)

typedef enum
{
    INPUT_TYPE_PCM = 0,
    INPUT_TYPE_AC3 = 1,
    INPUT_TYPE_AAC = 2,
    INPUT_TYPE_MP3 = 4
} AUDIO_SPDIF_INPUT_TYPE_T;

typedef enum
{
    DUT_MIC_A = 0,
    DUT_MIC_B = 1,
    DUT_MIC_C = 2,
    DUT_MIC_D = 3,
    DUT_I2S_INPUT = 4
} AUDIO_DUT_MIC_T;

/*  TWS buffer levels have been increased to give better performance in scatternet
    operation, to maintain baackwards compatibility with older products it is
    now necessary to send a message to the DSP to select the amount of internal
    buffering to be used, legacy products using 250ms, TWS version 3.1 and above
    using 350ms */
typedef enum
{
    PEER_BUFFER_350MS = 0,
    PEER_BUFFER_250MS = 1,
    PEER_BUFFER_NON_PEER_DEVICE
}peer_buffer_level;

/* peq_config_t can be cast to an unsigned type and passed directly to a call to select a PEQ filter bank.
 * This does not apply to peq_config_default
 * Keep the entries in the enum sequential */
typedef enum
{
    peq_config_default = 0xff,
    peq_config_0       = 0x00,
    peq_config_1       = 0x01,
    peq_config_2       = 0x02,
    peq_config_3       = 0x03,
    peq_config_4       = 0x04,
    peq_config_5       = 0x05,
    peq_config_6       = 0x06
} peq_config_t;


/* feature bits supplied to the audio plugins */
typedef struct
{
    unsigned manual_source_selection:1;
    unsigned stereo:1;
    AUDIO_ROUTE_T audio_input_routing:2;
    AUDIO_SPDIF_INPUT_TYPE_T spdif_supported_data_types:4;
    AUDIO_DUT_MIC_T dut_input:3;
    unsigned force_resampling_of_tones:1;
    unsigned unused1:2;
    unsigned use_one_mic_back_channel:1;
    unsigned use_two_mic_back_channel:1;
} AudioPluginFeatures;

/* spdif ac3 decoder configuration */
typedef struct
{
    BITFIELD compression_mode:2;
    BITFIELD boost_ratio:7;
    BITFIELD cut_ratio:7;
}spdif_ac3_config_word1;

typedef struct
{
    BITFIELD unused:2;
    BITFIELD output_mode:1;
    BITFIELD stereo_mixing_mode:2;
    BITFIELD channel_to_route_right:3;
    BITFIELD channel_to_route_left:3;
    BITFIELD enable_channel_routing:1;
    BITFIELD dual_mode_mono:2;
    BITFIELD karaoke_enable:1;
    BITFIELD lfe_output_enable:1;
}spdif_ac3_config_word2;

typedef struct
{
    uint16 configuration_word_1;
    uint16 configuration_word_2;
}spdif_ac3_configuration;

typedef struct
{
    BITFIELD unusued:7;
    BITFIELD enable_24_bit_audio_input:1;
    BITFIELD target_latency:8;  /* Target latency, valid range of 0 to 150 */
}spdif_configuration;

/*the audio power level - taken from power library*/
#define AUDIO_POWER_T power_battery_level

/* Macros for creating messages */
#include <panic.h>
#define MAKE_AUDIO_MESSAGE(TYPE, pointer_name) TYPE##_T *pointer_name = PanicUnlessNew(TYPE##_T)
#define MAKE_AUDIO_MESSAGE_WITH_LEN(TYPE, LEN, pointer_name) TYPE##_T *pointer_name = (TYPE##_T *) PanicUnlessMalloc(sizeof(TYPE##_T) + (((LEN) - (unsigned)1)*sizeof(uint16)))
/* Warning! Use MAKE_AUDIO_MESSAGE rather than MAKE_AUDIO_MESSAGE_WITH_LEN
 * unless your message is variable length.*/

/* Due to compiler restrictions the number of parameters must always be at least 1 as flexible arrays are not supported */
#define CALC_MESSAGE_LENGTH_WITH_VARIABLE_PARAMS(TYPE, NUMBER_OF_PARAMS, VARIABLE_TYPE) (sizeof(TYPE) + (((NUMBER_OF_PARAMS) - (unsigned)1) * (sizeof(VARIABLE_TYPE))))

/*!  Audio Plugin Downstream Interface Messages

    These messages are sent to the audio plugin modules.

    An Audio plugin must implement all of the messages below.

*/
typedef enum audio_plugin_interface_message_type_tag
{
    AUDIO_PLUGIN_CONNECT_MSG    = AUDIO_DOWNSTREAM_MESSAGE_BASE,
    AUDIO_PLUGIN_DISCONNECT_MSG,
    AUDIO_PLUGIN_SET_MODE_MSG,
    AUDIO_PLUGIN_SET_MUSIC_ENHANCEMENTS_MSG,
    AUDIO_PLUGIN_SET_VOLUME_MSG,
    AUDIO_PLUGIN_START_FORWARDING_MSG,
    AUDIO_PLUGIN_STOP_FORWARDING_MSG,
    AUDIO_PLUGIN_PLAY_TONE_MSG,
    AUDIO_PLUGIN_STOP_TONE_AND_PROMPT_MSG,
    AUDIO_PLUGIN_PLAY_AUDIO_PROMPT_MSG,
    AUDIO_PLUGIN_TONE_END_NOTIFICATION_MSG,
    AUDIO_PLUGIN_MIC_SWITCH_MSG,
    AUDIO_PLUGIN_SET_POWER_MSG,
    AUDIO_PLUGIN_RESET_VOLUME_MSG,
    AUDIO_PLUGIN_SET_SUB_WOOFER_MSG,
    AUDIO_PLUGIN_START_ASR,
    AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG,
    AUDIO_PLUGIN_DELAY_VOLUME_SET_MSG,
    AUDIO_PLUGIN_SET_SOFT_MUTE_MSG,
    AUDIO_PLUGIN_DISCONNECT_DELAYED_MSG,
    AUDIO_PLUGIN_ALLOW_VOLUME_CHANGES_MSG,
    AUDIO_PLUGIN_SUBWOOFER_CONNECTION_TIMEOUT_MSG,
    AUDIO_PLUGIN_SET_INPUT_AUDIO_MUTE_MSG,
    AUDIO_PLUGIN_OUTPUT_SWITCH_MSG,
    AUDIO_PLUGIN_SET_USER_EQ_PARAMETER_MSG,
    AUDIO_PLUGIN_APPLY_USER_EQ_PARAMETERS_MSG,
    AUDIO_PLUGIN_CLEAR_USER_EQ_PARAMETERS_MSG,
    AUDIO_PLUGIN_GET_USER_EQ_PARAMETER_MSG,
    AUDIO_PLUGIN_GET_USER_EQ_PARAMETERS_MSG,
    AUDIO_PLUGIN_GET_USER_EQ_PARAMETER_RESPONSE_MSG,
    AUDIO_PLUGIN_GET_USER_EQ_PARAMETERS_RESPONSE_MSG,
    AUDIO_PLUGIN_SET_CHANNEL_MODE_MSG,
    AUDIO_PLUGIN_TEST_RESET_MSG,
    AUDIO_PLUGIN_CHANGE_TRIGGER_PHRASE_MSG,
    AUDIO_PLUGIN_START_VOICE_CAPTURE_MSG,
    AUDIO_PLUGIN_STOP_VOICE_CAPTURE_MSG,
     /* Library message limit */
    AUDIO_DOWNSTREAM_MESSAGE_TOP

} audio_plugin_interface_message_type_t;


typedef enum
{
    A2DP_MUSIC_PROCESSING_PASSTHROUGH,
    A2DP_MUSIC_PROCESSING_FULL,
    A2DP_MUSIC_PROCESSING_FULL_NEXT_EQ_BANK,
    A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK0,
    A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK1,
    A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK2,
    A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK3,
    A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK4,
    A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK5,
    A2DP_MUSIC_PROCESSING_FULL_SET_EQ_BANK6
}A2DP_MUSIC_PROCESSING_T;

typedef enum
{
    CHANNEL_MODE_STEREO,
    CHANNEL_MODE_LEFT,
    CHANNEL_MODE_RIGHT,
    CHANNEL_MODE_DOWNMIX,
    CHANNEL_MODE_INVALID
} AUDIO_MUSIC_CHANNEL_MODE_T;

#define SAMPLE_RATE_48000   (48000)
#define SAMPLE_RATE_96000   (96000)
#define SAMPLE_RATE_192000  (192000)

#define DAC_OUTPUT_RESAMPLE_RATE_NONE   (0)
#define DAC_OUTPUT_RESAMPLE_RATE_96K    SAMPLE_RATE_96000
#define DAC_OUTPUT_RESAMPLE_RATE_192K   SAMPLE_RATE_192000

#define DAC_OUTPUT_RAW_GAIN_NONE        (0xFFFFFFFFUL)

typedef enum
{
    DAC_OUTPUT_RESAMPLING_MODE_OFF,
    DAC_OUTPUT_RESAMPLING_MODE_96K,
    DAC_OUTPUT_RESAMPLING_MODE_192K
} DAC_OUTPUT_RESAMPLING_MODE_T;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
    The plugin module should connect the Synchronous connection to its pre
    defined outputs.
*/
typedef struct PACK_STRUCT
{
    /*! The audio sink to connect*/
    Sink            audio_sink ;
    /*! The type of the audio sink to connect*/
    AUDIO_SINK_T    sink_type ;
    /*! The codec task to use to connect the audio*/
    /*! The volume at which to set the audio */
    int16          volume ;
    /*! The rate of the audio stream */
    uint32          rate ;
    /*! additional features that can be used in the audio plugins */
    AudioPluginFeatures features ;
    /*! The audio mode of connection required*/
    AUDIO_MODE_T    mode ;
    /*! The audio route of connection required*/
    AUDIO_ROUTE_T   route ;
    /*! The audio route of connection required*/
    AUDIO_POWER_T   power ;
    /*!plugin specific parameters*/
    void *    params ;
    /*! The application task to route upstream plugin messages to*/
    Task            app_task ;
}AUDIO_PLUGIN_CONNECT_MSG_T ;


/*!
    @brief Structure common to CVC and A2DP plugins, used to pass
    the USB Microphone Sink to the plugin.
*/
typedef struct
{
    Sink usb_sink;
} usb_common_params;


typedef enum
{
    BIAS_CONFIG_DISABLE,
    BIAS_CONFIG_MIC_BIAS_0,
    BIAS_CONFIG_MIC_BIAS_1,
    BIAS_CONFIG_PIO
} bias_config_t;

typedef struct PACK_STRUCT
{
    BITFIELD pre_amp:1;
    BITFIELD gain:5;
    BITFIELD instance:2;
    unsigned enable_24_bit_resolution:1;
    BITFIELD unused:7;
} analogue_input_params;

typedef struct PACK_STRUCT
{
    bias_config_t bias_config:2;
    BITFIELD pre_amp:1;
    BITFIELD pio:7;
    BITFIELD gain:5;
    BITFIELD is_digital:1;
    BITFIELD instance:2;
    BITFIELD unused:14;
} audio_mic_params;

/*!
    @brief Structure common to all plugins, used to pass the Microphone
    setup to the plugin.
*/
typedef struct
{
    /*! Mic A settings */
    audio_mic_params mic_a;
    /*! Mic B settings */
    audio_mic_params mic_b;
}voice_mic_params_t;

typedef struct
{
    usb_common_params        usb_params;
    const voice_mic_params_t* voice_mic_params;
} hfp_common_plugin_params_t;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
    The plugin module should connect the Synchronous connection to its pre
    defined outputs.
*/
typedef struct
{
    /*! The volume at which to set the audio */
    int16          volume ;
    /*! The volume at which to set the tones/vp */
    int16          tone_volume;
}AUDIO_PLUGIN_SET_VOLUME_MSG_T ;


/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
*/
typedef struct PACK_STRUCT
{
    /*! The audio connection mode */
    uint16          mode ;
    /*! plugin specific parameters*/
    void *    params ;
}AUDIO_PLUGIN_SET_MODE_MSG_T ;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
    It enables/disables the music processing functionality
*/
typedef struct
{
    A2DP_MUSIC_PROCESSING_T music_processing_mode;
    uint16                  music_processing_enhancements;
}AUDIO_PLUGIN_SET_MUSIC_ENHANCEMENTS_MSG_T ;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
*/
typedef struct
{
    /*! The sub audio link mode */
    AUDIO_SUB_TYPE_T  sub_woofer_type ;
    /* sub link sink */
    Sink sub_sink ;
}AUDIO_PLUGIN_SET_SUB_WOOFER_MSG_T;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
*/
typedef struct
{
    /*! The mute states to apply */
    BITFIELD    mute_states:3;
    BITFIELD    unused:13;
}AUDIO_PLUGIN_SET_SOFT_MUTE_MSG_T;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
*/
typedef struct PACK_STRUCT
{
    /*! The sink used to forward undecoded audio frames */
    Sink  forwarding_sink ;
    /*! Flag indicating if support for content protection is required */
    bool  content_protection ;
    /*! whether backwards compatibility mode of the DSP app is required, this
       controls the internal buffering delay within the DSP app, 250 or 350ms */
    uint8 peer_dsp_required_buffering_level ;
    /*! Plug-in to control output (may be NULL if output is controlled by
        the relay plug-in) */
    Task output_plugin;
}AUDIO_PLUGIN_START_FORWARDING_MSG_T ;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
*/
typedef struct PACK_STRUCT
{
    /*! the tone to be played*/
    const  ringtone_note * tone;
    /*! Whether or not to queue the requested tone*/
    bool        can_queue ;
    /*! The volume at which to play the tone 0 - current volume*/
    int16      tone_volume ;
    /* features such as stereo and i2s output */
    AudioPluginFeatures features;
}AUDIO_PLUGIN_PLAY_TONE_MSG_T ;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module.
*/
typedef struct PACK_STRUCT
{
    /*! the index of the audio prompt file to be played*/
    FILE_INDEX prompt_index;
    /*! the index of the audio prompt index file to be played*/
    FILE_INDEX prompt_header_index;
    /*! Whether or not to queue the requested audio prompt*/
    bool        can_queue ;
    /*! The application task to route upstream plugin messages to*/
    Task        app_task;
    /*! The volume at which to play the audio prompt  0 - current volume*/
    int16      ap_volume ;
    /*! features such as stereo and i2s output */
    AudioPluginFeatures features;
}AUDIO_PLUGIN_PLAY_AUDIO_PROMPT_MSG_T ;


typedef enum
{
    voice_prompts_codec_pcm_8khz,
    voice_prompts_codec_ima_adpcm,
    voice_prompts_codec_sbc,
    voice_prompts_codec_mp3,
    voice_prompts_codec_aac,
    voice_prompts_codec_pcm,
    voice_prompts_codec_tone    /* internally generated tone */
} voice_prompts_codec_t;


/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module to configure it's power level
*/
typedef struct
{
    /*! the power level selected */
    AUDIO_POWER_T power;
}AUDIO_PLUGIN_SET_POWER_MSG_T ;


/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module to start or restart the ASR engine
*/
typedef struct
{
    /*! The audio connection mode */
    uint16          mode ;
}AUDIO_PLUGIN_START_ASR_T ;

typedef enum
{
    DSP_VOLUME_CONTROL,
    DAC_VOLUME_CONTROL,
    MIXED_VOLUME_CONTROL,
    EXTERNAL_VOLUME_CONTROL
}volumeType_t;

/* Parameters for AudioSetGroupVolume */

typedef struct
{
    int16                   master;    /*! The requested master gain in dB/60 */
    int16                     tone;    /*! The requested tone gain in dB/60 */
    /*! The codec task to use to connect the audio*/
    int16       device_trim_master;    /*! TWS master trim */
    int16        device_trim_slave;    /*! TWS slave trim*/
} audio_plugin_main_vol_t;

typedef struct
{
    int16                   master;    /*! The requested master gain in dB/60 */
    int16                     tone;    /*! The requested tone gain in dB/60 */
} audio_plugin_aux_vol_t;

typedef struct
{
    audio_output_group_t group;     /*! The group (main/aux/all) to adjust volume */
    audio_plugin_main_vol_t   main;     /*! Use this struct for audio_output_group_main/all */
    audio_plugin_aux_vol_t     aux;     /*! Use this struct for audio_output_group_aux/all */
}AUDIO_PLUGIN_SET_GROUP_VOLUME_MSG_T;

/* Message struct used for delayed application of master volume in hardware */
typedef struct
{
    audio_output_group_t group; /*! The group (main/aux) to adjust volume */
    int16                   master; /*! The requested master gain in dB/60 */
} AUDIO_PLUGIN_DELAY_VOLUME_SET_MSG_T;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module to mute or unmute the input audio port.
*/

typedef struct PACK_STRUCT
{
    unsigned unused:15;
    unsigned input_audio_port_mute_active:1;           /* TRUE when input audio port is muted for all audio sources except tones */
} AUDIO_PLUGIN_SET_INPUT_AUDIO_MUTE_MSG_T;

typedef enum
{
    eq_param_type_filter = 0,
    eq_param_type_cutoff_freq = 1,
    eq_param_type_gain = 2,
    eq_param_type_q = 3,
    /* Do not edit */
    eq_param_max_param_types
} eq_param_type_t;

/* Structure to define an individual eq parameter */
typedef struct
{
    uint16          bank;
    uint16          band;
    eq_param_type_t param_type;
} audio_plugin_user_eq_param_id_t;

/* Structure to define an individual eq parameter */
typedef struct
{
    audio_plugin_user_eq_param_id_t id;
    uint32 value;
} audio_plugin_user_eq_param_t;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module to update a user peq parameter
*/
typedef struct
{
    audio_plugin_user_eq_param_t param;
} AUDIO_PLUGIN_SET_USER_EQ_PARAMETER_MSG_T;
/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module to update a group of user peq parameters
*/
typedef struct
{
    bool recalculate_coefficients;
} AUDIO_PLUGIN_APPLY_USER_EQ_PARAMETERS_MSG_T;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module to get a user peq parameter
*/
typedef struct
{
    audio_plugin_user_eq_param_id_t param_id;
    Task callback_task;
} AUDIO_PLUGIN_GET_USER_EQ_PARAMETER_MSG_T;

/*!
    @brief This message is generated by the audio manager and is issued
    to an audio plugin module to get a group of user peq parameters
*/
typedef struct
{
    Task callback_task;
    uint16 number_of_params;
    audio_plugin_user_eq_param_id_t param_ids[1];
} AUDIO_PLUGIN_GET_USER_EQ_PARAMETERS_MSG_T;

/*!
    @brief This message is generated by the audio library and is issued
    to an audio plugin module in response to a dsp message with the same information
*/
typedef struct
{
    bool data_valid;
    audio_plugin_user_eq_param_t param[1];
} AUDIO_PLUGIN_GET_USER_EQ_PARAMETER_RESPONSE_MSG_T;

/*!
    @brief This message is generated by the audio library and is issued
    to an audio plugin module in response to a dsp message with the same information
*/
typedef struct
{
    bool data_valid;
    uint16 number_of_params;
    audio_plugin_user_eq_param_t params[1];
} AUDIO_PLUGIN_GET_USER_EQ_PARAMETERS_RESPONSE_MSG_T;

/*!
    @brief This message is passed to the AoV plugin to instruct it
    to change the trigger phrase it is currently responding to.
*/
typedef struct
{
    FILE_INDEX trigger_phrase_data_file;
}AUDIO_PLUGIN_CHANGE_TRIGGER_PHRASE_MSG_T;

/*!
    @brief This message is passed to the VA plugin for initiating 
    a voice capture session
*/

typedef struct
{
    /*! The application task to route upstream plugin messages to*/
    Task       app_task ;
}AUDIO_PLUGIN_START_VOICE_CAPTURE_MSG_T;

#endif  /*  _AUDIO_PLUGIN_INTERFACE_H_ */

/** @} */
