	/****************************************************************************
Copyright (c) 2016 Qualcomm Technologies International, Ltd.

FILE NAME
    audio_config.c
DESCRIPTION
    Library to implement a general purpose configuration facility.
    Provide getter and setter functionality to configuration data.
*/

#include <source.h>
#include <string.h>
#include <stdlib.h>
#include <panic.h>
#include "audio_config.h"

typedef struct
{
    bool    fixed_tone_volume;
    int     tone_volume;
    int     master_volume;
} audio_config_volume_t;

#define MAX_USER_EQ_PARAMS 21

typedef struct
{
    A2DP_MUSIC_PROCESSING_T music_processing_mode;
    unsigned music_mode_enhancements;
    audio_config_volume_t volume;
    unsigned number_of_eq_params;
    audio_plugin_user_eq_param_t* eq_params;
    Task app_task;
    uint32 output_sample_rate;
    uint32 wired_audio_output_sample_rate;
    unsigned number_of_concurrent_inputs;
    bool speaker_peq_bypass;
    AUDIO_MUSIC_CHANNEL_MODE_T tws_channel_mode_local;
    AUDIO_MUSIC_CHANNEL_MODE_T tws_channel_mode_remote;
    peq_config_t peq_config_selected;
    AUDIO_MUTE_STATE_T master_mute_state;
    audio_instance pcm_instance;
    audio_quality_t music_quality;
    audio_quality_t voice_quality;
    uint32 dac_output_resampling_rate;
    uint32 dac_output_raw_gain[2];
    peer_mode_t peer_mode;
    ttp_latency_t ttp_latency;
    audio_mic_params va_mic_params;
    sbc_encoder_params_t va_sbc_encoder_params;
} audio_config_t;

#define DEFAULT_MUSIC_PROCESSING_MODE           A2DP_MUSIC_PROCESSING_PASSTHROUGH
#define DEFAULT_MUSIC_MODE_ENHANCEMENTS         0
#define DEFAULT_TONES_ARE_FIXED_VOLUME          TRUE
#define DEFAULT_TONES_VOLUME                    0
#define DEFAULT_MASTER_VOLUME                   0
#define DEFAULT_EQ_PARAMS                       0
#define DEFAULT_NUMBER_OF_EQ_PARAMS             0
#define DEFAULT_APP_TASK                        NULL
#define DEFAULT_OUTPUT_SAMPLE_RATE              48000
#define DEFAULT_WIRED_AUDIO_OUTPUT_SAMPLE_RATE  48000
#define DEFAULT_NUMBER_OF_CONCURRENT_INPUTS     1
#define DEFAULT_SPEAKER_PEQ_BYPASS              1
#define DEFAULT_AUDIO_MUSIC_CHANNEL_MODE        CHANNEL_MODE_STEREO
#define DEFAULT_PEQ_CONFIG_SELECTED             peq_config_default
#define DEFAULT_MASTER_MUTE_STATE               AUDIO_MUTE_DISABLE
#define DEFAULT_PCM_INSTANCE                    AUDIO_INSTANCE_0
#define DEFAULT_AUDIO_QUALITY                   audio_quality_high
#define DEFAULT_DAC_OUTPUT_RESAMPLING_RATE      DAC_OUTPUT_RESAMPLE_RATE_NONE
#define DEFAULT_DAC_OUTPUT_RAW_GAIN             DAC_OUTPUT_RAW_GAIN_NONE
#define DEFAULT_PEER_MODE                       peer_mode_none
#define DEFAULT_MIN_TTP_LATENCY                 100
#define DEFAULT_TARGET_TTP_LATENCY              200
#define DEFAULT_MAX_TTP_LATENCY                 300
#define DEFAULT_VA_MIC_BIASCONFIG               BIAS_CONFIG_MIC_BIAS_0
#define DEFAULT_VA_MIC_DIGITAL                  FALSE
#define DEFAULT_VA_MIC_PREAMP                   1
#define DEFAULT_VA_MIC_PIO                      0
#define DEFAULT_VA_MIC_INSTANCE                 1
#define DEFAULT_VA_MIC_GAIN                     10
#define DEFAULT_VA_MIC_UNUSED                   0
#define DEFAULT_VA_SBCENC_NO_OF_SUBBANDS        0x08
#define DEFAULT_VA_SBCENC_NO_OF_BLOCKS          0x10
#define DEFAULT_VA_SBCENC_SAMPLE_RATE           0x3e80
#define DEFAULT_VA_SBCENC_CHANNEL_MODE          0x00
#define DEFAULT_VA_SBCENC_ALLOCATION_METHOD     0x01
#define DEFAULT_VA_SBC_BITPOOL                  0x001c

static audio_config_t audio_config =
{
    DEFAULT_MUSIC_PROCESSING_MODE,
    DEFAULT_MUSIC_MODE_ENHANCEMENTS,
    {
        DEFAULT_TONES_ARE_FIXED_VOLUME,
        DEFAULT_TONES_VOLUME,
        DEFAULT_MASTER_VOLUME
    },
    DEFAULT_NUMBER_OF_EQ_PARAMS,
    DEFAULT_EQ_PARAMS,
    DEFAULT_APP_TASK,
    DEFAULT_OUTPUT_SAMPLE_RATE,
    DEFAULT_WIRED_AUDIO_OUTPUT_SAMPLE_RATE,
    DEFAULT_NUMBER_OF_CONCURRENT_INPUTS,
    DEFAULT_SPEAKER_PEQ_BYPASS,
    DEFAULT_AUDIO_MUSIC_CHANNEL_MODE,
    DEFAULT_AUDIO_MUSIC_CHANNEL_MODE,
    DEFAULT_PEQ_CONFIG_SELECTED,
    DEFAULT_MASTER_MUTE_STATE,
    DEFAULT_PCM_INSTANCE,
    DEFAULT_AUDIO_QUALITY,
    DEFAULT_AUDIO_QUALITY,
    DEFAULT_DAC_OUTPUT_RESAMPLING_RATE,
    { DEFAULT_DAC_OUTPUT_RAW_GAIN, DEFAULT_DAC_OUTPUT_RAW_GAIN },
    DEFAULT_PEER_MODE,
    {
        DEFAULT_MIN_TTP_LATENCY,
        DEFAULT_TARGET_TTP_LATENCY,
        DEFAULT_MAX_TTP_LATENCY
    },
    {
        DEFAULT_VA_MIC_BIASCONFIG,
        DEFAULT_VA_MIC_PREAMP,
        DEFAULT_VA_MIC_PIO,
        DEFAULT_VA_MIC_GAIN,
        DEFAULT_VA_MIC_DIGITAL,
        DEFAULT_VA_MIC_INSTANCE,
        DEFAULT_VA_MIC_UNUSED
    },
    {
        DEFAULT_VA_SBCENC_NO_OF_SUBBANDS,
        DEFAULT_VA_SBCENC_NO_OF_BLOCKS,
        DEFAULT_VA_SBC_BITPOOL,
        DEFAULT_VA_SBCENC_SAMPLE_RATE,
        DEFAULT_VA_SBCENC_CHANNEL_MODE,
        DEFAULT_VA_SBCENC_ALLOCATION_METHOD
    }
};

void AudioConfigSetMusicEnhancements(unsigned music_mode_enhancements)
{
    audio_config.music_mode_enhancements = music_mode_enhancements;
}

unsigned AudioConfigGetMusicEnhancements(void)
{
    return audio_config.music_mode_enhancements;
}

void AudioConfigSetMusicProcessingMode(A2DP_MUSIC_PROCESSING_T music_processing_mode)
{
    audio_config.music_processing_mode = music_processing_mode;
}

A2DP_MUSIC_PROCESSING_T AudioConfigGetMusicProcessingMode(void)
{
    return audio_config.music_processing_mode;
}

void AudioConfigSetTonesAreFixedVolume(bool fixed_tone_volume)
{
    audio_config.volume.fixed_tone_volume = fixed_tone_volume;
}

bool AudioConfigGetTonesAreFixedVolume(void)
{
    return audio_config.volume.fixed_tone_volume;
}

void AudioConfigSetToneVolume(int tone_volume)
{
    audio_config.volume.tone_volume = tone_volume;
}

int AudioConfigGetToneVolume(void)
{
    return audio_config.volume.tone_volume;
}

void AudioConfigSetMasterVolume(int master_volume)
{
    audio_config.volume.master_volume = master_volume;
}

int AudioConfigGetMasterVolume(void)
{
    return audio_config.volume.master_volume;
}

int16 AudioConfigGetToneVolumeToUse(void) 
{
    return (AudioConfigGetTonesAreFixedVolume() ? (int16)AudioConfigGetToneVolume() : (int16)AudioConfigGetMasterVolume());
}


void AudioConfigSetSpeakerPeqBypass(bool speaker_peq_bypass)
{
    audio_config.speaker_peq_bypass = speaker_peq_bypass;
}

bool AudioConfigGetSpeakerPeqBypass(void)
{
    return audio_config.speaker_peq_bypass;
}

void AudioConfigSetPeerMode(peer_mode_t mode)
{
    audio_config.peer_mode = mode;
}

peer_mode_t AudioConfigGetPeerMode(void)
{
    return audio_config.peer_mode;
}

/****************************************************************************
DESCRIPTION
    Allocate memory for storing user eq parameters.
    If unable to allocate the required memory subsequent calls to set/get user eq params
    will function as though the number of allowed entries has been exceeded.
*/
static void audioConfigAllocateEqMemory(void)
{
    if (audio_config.number_of_eq_params == 0)
    {
        audio_config.eq_params = calloc(MAX_USER_EQ_PARAMS, sizeof(audio_plugin_user_eq_param_t));
    }
}

bool AudioConfigSetUserEqParameter(const audio_plugin_user_eq_param_t* param)
{
    if (audio_config.number_of_eq_params < MAX_USER_EQ_PARAMS)
    {
        audioConfigAllocateEqMemory();
        if (audio_config.eq_params)
        {
            audio_config.eq_params[audio_config.number_of_eq_params] = *param;
            audio_config.number_of_eq_params++;
            return TRUE;
        }
    }
    return FALSE;
}

audio_plugin_user_eq_param_t* AudioConfigGetUserEqParameter(const unsigned index)
{
    if (index < audio_config.number_of_eq_params)
    {
        if (audio_config.eq_params)
        {
            return &audio_config.eq_params[index];
        }
    }
    return (audio_plugin_user_eq_param_t*)0;
}

void AudioConfigClearUserEqParams(void)
{
    audio_config.number_of_eq_params = DEFAULT_NUMBER_OF_EQ_PARAMS;
    free(audio_config.eq_params);
    audio_config.eq_params = (audio_plugin_user_eq_param_t*)DEFAULT_EQ_PARAMS;
}

unsigned AudioConfigGetNumberOfEqParams(void)
{
    return audio_config.number_of_eq_params;
}

void AudioConfigSetAppTask(Task app_task)
{
    audio_config.app_task = app_task;
}

Task AudioConfigGetAppTask(void)
{
    return audio_config.app_task;
}

uint32 AudioConfigGetOutputSampleRate(void)
{
    return audio_config.output_sample_rate;
}

void AudioConfigSetWiredAudioOutputSampleRate(uint32 sample_rate)
{
    audio_config.wired_audio_output_sample_rate = sample_rate;
}

uint32 AudioConfigGetWiredAudioOutputSampleRate(void)
{
    return audio_config.wired_audio_output_sample_rate;
}

void AudioConfigSetMaximumConcurrentInputs(unsigned number_of_inputs)
{
    audio_config.number_of_concurrent_inputs = number_of_inputs;
}

unsigned AudioConfigGetMaximumConcurrentInputs(void)
{
    return audio_config.number_of_concurrent_inputs;
}

void AudioConfigSetTwsChannelModeLocal(AUDIO_MUSIC_CHANNEL_MODE_T channel_mode)
{
    audio_config.tws_channel_mode_local = channel_mode;
}

AUDIO_MUSIC_CHANNEL_MODE_T AudioConfigGetTwsChannelModeLocal(void)
{
    return audio_config.tws_channel_mode_local;
}

void AudioConfigSetTwsChannelModeRemote(AUDIO_MUSIC_CHANNEL_MODE_T channel_mode)
{
    audio_config.tws_channel_mode_remote = channel_mode;
}

AUDIO_MUSIC_CHANNEL_MODE_T AudioConfigGetTwsChannelModeRemote(void)
{
    return audio_config.tws_channel_mode_remote;
}

void AudioConfigSetPeqConfig(peq_config_t peq_config_selected)
{
    audio_config.peq_config_selected = peq_config_selected;
}

peq_config_t AudioConfigGetPeqConfig(void)
{
    return audio_config.peq_config_selected;
}

void AudioConfigSetMasterMuteState(AUDIO_MUTE_STATE_T mute_state)
{
    audio_config.master_mute_state = mute_state;
}

AUDIO_MUTE_STATE_T AudioConfigGetMasterMuteState(void)
{
    return audio_config.master_mute_state;
}

void AudioConfigSetPcmInstance(audio_instance instance)
{
    audio_config.pcm_instance = instance;
}

audio_instance AudioConfigGetPcmInstance(void)
{
    return audio_config.pcm_instance;
}

audio_quality_t AudioConfigGetQuality(audio_stream_t stream)
{
    if(stream == audio_stream_voice)
        return audio_config.voice_quality;
    else if(stream == audio_stream_music)
        return audio_config.music_quality;
    
    /* Invalid stream */
    Panic();
    return audio_quality_high;
}

void AudioConfigSetQuality(audio_stream_t stream, audio_quality_t quality)
{
    if(stream == audio_stream_voice)
        audio_config.voice_quality = quality;
    else if(stream == audio_stream_music)
        audio_config.music_quality = quality;
}

ttp_latency_t AudioConfigGetTtpLatency(void)
{
    return audio_config.ttp_latency;
}

void AudioConfigSetTtpLatency(uint16 min, uint16 target, uint16 max)
{
    audio_config.ttp_latency.min_in_ms = min;
    audio_config.ttp_latency.target_in_ms = target;
    audio_config.ttp_latency.max_in_ms = max;
}

void AudioConfigSetDacOutputResamplingRate(uint32 resampling_rate)
{
    audio_config.dac_output_resampling_rate = resampling_rate;
}

uint32 AudioConfigGetDacOutputResamplingRate(void)
{
    return audio_config.dac_output_resampling_rate;
}

void AudioConfigSetRawDacGain(audio_output_t channel, uint32 raw_gain)
{
    PanicFalse(channel <= audio_output_primary_right);

    audio_config.dac_output_raw_gain[channel] = raw_gain;
}

uint32 AudioConfigGetRawDacGain(audio_output_t channel)
{
    PanicFalse(channel <= audio_output_primary_right);

    return audio_config.dac_output_raw_gain[channel];
}

void AudioConfigSetVaMicParams(audio_mic_params mic_params)
{
    audio_config.va_mic_params = mic_params;
}

audio_mic_params AudioConfigGetVaMicParams(void)
{
    return audio_config.va_mic_params;
}

void AudioConfigSetSbcEncoderParams(sbc_encoder_params_t sbc_encoder_params)
{
    audio_config.va_sbc_encoder_params = sbc_encoder_params;
}

sbc_encoder_params_t AudioConfigGetSbcEncoderParams(void)
{
    return audio_config.va_sbc_encoder_params;
}
void AudioConfigTestReset(void)
{
#ifndef AUDIO_TEST_BUILD
    Panic();
#else
    audio_config.music_processing_mode = DEFAULT_MUSIC_PROCESSING_MODE;
    audio_config.music_mode_enhancements = DEFAULT_MUSIC_MODE_ENHANCEMENTS;
    audio_config.volume.fixed_tone_volume = DEFAULT_TONES_ARE_FIXED_VOLUME;
    audio_config.volume.tone_volume = DEFAULT_TONES_VOLUME;
    audio_config.volume.master_volume = DEFAULT_MASTER_VOLUME;
    audio_config.number_of_eq_params = DEFAULT_NUMBER_OF_EQ_PARAMS;
    audio_config.eq_params = DEFAULT_EQ_PARAMS;
    audio_config.app_task = DEFAULT_APP_TASK;
    audio_config.output_sample_rate = DEFAULT_OUTPUT_SAMPLE_RATE;
    audio_config.wired_audio_output_sample_rate = DEFAULT_WIRED_AUDIO_OUTPUT_SAMPLE_RATE;
    audio_config.number_of_concurrent_inputs = DEFAULT_NUMBER_OF_CONCURRENT_INPUTS;
    audio_config.tws_channel_mode_local = DEFAULT_AUDIO_MUSIC_CHANNEL_MODE;
    audio_config.tws_channel_mode_remote = DEFAULT_AUDIO_MUSIC_CHANNEL_MODE;
    audio_config.peq_config_selected = DEFAULT_PEQ_CONFIG_SELECTED;
    audio_config.master_mute_state = DEFAULT_MASTER_MUTE_STATE;
    audio_config.pcm_instance = DEFAULT_PCM_INSTANCE;
    audio_config.music_quality = DEFAULT_AUDIO_QUALITY;
    audio_config.voice_quality = DEFAULT_AUDIO_QUALITY;
    audio_config.dac_output_resampling_rate = DEFAULT_DAC_OUTPUT_RESAMPLING_RATE;
    audio_config.dac_output_raw_gain[audio_output_primary_left] = DEFAULT_DAC_OUTPUT_RAW_GAIN;
    audio_config.dac_output_raw_gain[audio_output_primary_right] = DEFAULT_DAC_OUTPUT_RAW_GAIN;
    audio_config.va_mic_params.bias_config = DEFAULT_VA_MIC_BIASCONFIG;
    audio_config.va_mic_params.is_digital = DEFAULT_VA_MIC_DIGITAL;
    audio_config.va_mic_params.pre_amp = DEFAULT_VA_MIC_PREAMP;
    audio_config.va_mic_params.pio = DEFAULT_VA_MIC_PIO;
    audio_config.va_mic_params.instance = DEFAULT_VA_MIC_INSTANCE;
    audio_config.va_mic_params.gain = DEFAULT_VA_MIC_GAIN;
    audio_config.va_sbc_encoder_params.allocation_method = DEFAULT_VA_SBCENC_ALLOCATION_METHOD;
    audio_config.va_sbc_encoder_params.channel_mode = DEFAULT_VA_SBCENC_CHANNEL_MODE;
    audio_config.va_sbc_encoder_params.number_of_blocks = DEFAULT_VA_SBCENC_NO_OF_BLOCKS;
    audio_config.va_sbc_encoder_params.number_of_subbands = DEFAULT_VA_SBCENC_NO_OF_SUBBANDS;
    audio_config.va_sbc_encoder_params.sample_rate = DEFAULT_VA_SBCENC_SAMPLE_RATE;
    audio_config.va_sbc_encoder_params.bitpool_size= DEFAULT_VA_SBC_BITPOOL;
#endif
}
