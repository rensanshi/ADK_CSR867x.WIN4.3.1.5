/****************************************************************************
Copyright (c) 2016 Qualcomm Technologies International, Ltd.

FILE NAME
    audio_config.c
DESCRIPTION
    Library to implement a general purpose configuration facility.
    Provide getter and setter functionality to configuration data.
*/


#include <source.h>

#ifndef _AUDIO_CONFIG_H_
#define _AUDIO_CONFIG_H_

#include <audio_plugin_music_params.h>
#include <audio_plugin_if.h>
#include <audio_sbc_encoder_params.h>

typedef enum
{
    audio_stream_music,
    audio_stream_voice
} audio_stream_t;

typedef enum
{
    audio_quality_low_power,
    audio_quality_high
} audio_quality_t;

typedef enum
{
    peer_mode_none,
    peer_mode_tws,
    peer_mode_shareme
} peer_mode_t;

/****************************************************************************
DESCRIPTION
    Function store the music enhancements state
*/
void AudioConfigSetMusicEnhancements(unsigned music_mode_enhancements);

/****************************************************************************
DESCRIPTION
    Function return the music enhancements state
*/
unsigned AudioConfigGetMusicEnhancements(void);

/****************************************************************************
DESCRIPTION
    Function store the music processing mode state
*/
void AudioConfigSetMusicProcessingMode(A2DP_MUSIC_PROCESSING_T music_processing_mode);

/****************************************************************************
DESCRIPTION
    Function return the music processing mode state
*/
A2DP_MUSIC_PROCESSING_T AudioConfigGetMusicProcessingMode(void);

/****************************************************************************
DESCRIPTION
    Set if tones are played at fixed volume
*/
void AudioConfigSetTonesAreFixedVolume(bool fixed_tone_volume);

/****************************************************************************
DESCRIPTION
    Check if tones are played at fixed volume
*/
bool AudioConfigGetTonesAreFixedVolume(void);

/****************************************************************************
DESCRIPTION
    Set tone volume
*/
void AudioConfigSetToneVolume(int tone_volume);

/****************************************************************************
DESCRIPTION
    Get tone volume
*/
int AudioConfigGetToneVolume(void);

/****************************************************************************
DESCRIPTION
    Set master volume
*/
void AudioConfigSetMasterVolume(int master_volume);

/****************************************************************************
DESCRIPTION
    Get master volume
*/
int AudioConfigGetMasterVolume(void);

/****************************************************************************
DESCRIPTION
    Get current tone volume for the current fixed tone volume status
*/
int16 AudioConfigGetToneVolumeToUse(void);


/****************************************************************************
DESCRIPTION
    Set a user eq configuration parameter
*/
bool AudioConfigSetUserEqParameter(const audio_plugin_user_eq_param_t* param);

/****************************************************************************
DESCRIPTION
    Get a user eq configuration parameter
*/
audio_plugin_user_eq_param_t* AudioConfigGetUserEqParameter(const unsigned index);

/****************************************************************************
DESCRIPTION
    Get the number of stored user eq parameters
*/
unsigned AudioConfigGetNumberOfEqParams(void);

/****************************************************************************
DESCRIPTION
    Clear stored user eq parameters
*/
void AudioConfigClearUserEqParams(void);

/****************************************************************************
DESCRIPTION
    Set App Task
*/
void AudioConfigSetAppTask(Task app_task);

/****************************************************************************
DESCRIPTION
    Get App Task
*/
Task AudioConfigGetAppTask(void);

/****************************************************************************
DESCRIPTION
    Get output sample rate.
*/
uint32 AudioConfigGetOutputSampleRate(void);

/****************************************************************************
DESCRIPTION
    Set wired audio output sample rate.
*/
void AudioConfigSetWiredAudioOutputSampleRate(uint32 sample_rate);

/****************************************************************************
DESCRIPTION
    Get wired audio output sample rate.
*/
uint32 AudioConfigGetWiredAudioOutputSampleRate(void);

/****************************************************************************
DESCRIPTION
    Set number of concurrent inputs supported
*/
void AudioConfigSetMaximumConcurrentInputs(unsigned number_of_inputs);

/****************************************************************************
DESCRIPTION
    Get number of concurrent inputs supported
*/
unsigned AudioConfigGetMaximumConcurrentInputs(void);

/****************************************************************************
DESCRIPTION
    Set the Speaker PEQ Bypass
*/
void AudioConfigSetSpeakerPeqBypass(bool speaker_peq_bypass);

/****************************************************************************
DESCRIPTION
    Get the Speaker PEQ Bypass
*/
bool AudioConfigGetSpeakerPeqBypass(void);


/****************************************************************************
DESCRIPTION
    Set the PEER mode
*/
void AudioConfigSetPeerMode(peer_mode_t mode);

/****************************************************************************
DESCRIPTION
    Get the PEER mode
*/
peer_mode_t AudioConfigGetPeerMode(void);

/****************************************************************************
DESCRIPTION
    Set the tws master channel mode
*/
void AudioConfigSetTwsChannelModeLocal(AUDIO_MUSIC_CHANNEL_MODE_T music_channel_mode);

/****************************************************************************
DESCRIPTION
    Get the tws master channel mode
*/
AUDIO_MUSIC_CHANNEL_MODE_T AudioConfigGetTwsChannelModeLocal(void);

/****************************************************************************
DESCRIPTION
    Set the tws slave channel mode
*/
void AudioConfigSetTwsChannelModeRemote(AUDIO_MUSIC_CHANNEL_MODE_T channel_mode);

/****************************************************************************
DESCRIPTION
    Get the tws slave channel mode
*/
AUDIO_MUSIC_CHANNEL_MODE_T AudioConfigGetTwsChannelModeRemote(void);

/****************************************************************************
DESCRIPTION
    Set the selected peq configuration
*/
void AudioConfigSetPeqConfig(peq_config_t peq_config_selected);

/****************************************************************************
DESCRIPTION
    Get the selected peq configuration
*/
peq_config_t AudioConfigGetPeqConfig(void);

/****************************************************************************
DESCRIPTION
    Set the master mute state
*/
void AudioConfigSetMasterMuteState(AUDIO_MUTE_STATE_T mute_state);

/****************************************************************************
DESCRIPTION
    Get the master mute state
*/
AUDIO_MUTE_STATE_T AudioConfigGetMasterMuteState(void);

/****************************************************************************
DESCRIPTION
    Set the PCM hardware instance
*/
void AudioConfigSetPcmInstance(audio_instance instance);

/****************************************************************************
DESCRIPTION
    Get the PCM hardware instance
*/
audio_instance AudioConfigGetPcmInstance(void);

/****************************************************************************
DESCRIPTION
    Set the DAC output re-sampling rate
*/
void AudioConfigSetDacOutputResamplingRate(uint32 resampling_rate);

/****************************************************************************
DESCRIPTION
    Get the DAC output re-sampling rate
*/
uint32 AudioConfigGetDacOutputResamplingRate(void);

/****************************************************************************
DESCRIPTION
    Set the raw gain to be applied at the DAC outputs
*/
void AudioConfigSetRawDacGain(audio_output_t channel, uint32 raw_gain);

/****************************************************************************
DESCRIPTION
    Get the raw gain to be applied at the DAC outputs
*/
uint32 AudioConfigGetRawDacGain(audio_output_t channel);

/****************************************************************************
DESCRIPTION
    Reset any static variables
    This is only intended for unit test and will panic if called in a release build.
*/
void AudioConfigTestReset(void);

/****************************************************************************
DESCRIPTION
    Get the quality setting
*/
audio_quality_t AudioConfigGetQuality(audio_stream_t stream);

/****************************************************************************
DESCRIPTION
    Set the quality setting
*/
void AudioConfigSetQuality(audio_stream_t stream, audio_quality_t quality);

/****************************************************************************
DESCRIPTION
    Get the TTP latency settings
*/
ttp_latency_t AudioConfigGetTtpLatency(void);

/****************************************************************************
DESCRIPTION
    Set the TTP latency settings
*/
void AudioConfigSetTtpLatency(uint16 min, uint16 target, uint16 max);

/****************************************************************************
DESCRIPTION
    Set the mic Params for voice assistant
*/

void AudioConfigSetVaMicParams(audio_mic_params mic_params);

/****************************************************************************
DESCRIPTION
    Get the mic params settings for Voice Assistant
*/
audio_mic_params AudioConfigGetVaMicParams(void);

/****************************************************************************
DESCRIPTION
    set the sbc encoder params settings for Voice Assistant
*/
void AudioConfigSetSbcEncoderParams(sbc_encoder_params_t sbc_encoder_params);

/****************************************************************************
DESCRIPTION
    Get the sbc encoder params settings for Voice Assistant
*/
sbc_encoder_params_t AudioConfigGetSbcEncoderParams(void);

#endif /* _AUDIO_CONFIG_H_ */
