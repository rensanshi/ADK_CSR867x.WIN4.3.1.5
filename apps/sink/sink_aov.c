/****************************************************************************
Copyright (c) 2017 Qualcomm Technologies International, Ltd.

FILE NAME
    sink_aov.c

DESCRIPTION
    Sink module to support Always-on-Voice (AoV) functionality.

*/
/*!
@file   sink_aov.c
@brief  Sink module to support Always-on-Voice (AoV) functionality.
*/
#include <csrtypes.h>
#include <stdio.h>
#include <string.h>
#include <file.h>
#include <audio.h>
#include <power.h>
#include <audio_plugin_voice_prompts_variants.h>

#include "sink_aov.h"
#include "sink_configmanager.h"
#include "sink_debug.h"
#include "sink_malloc_debug.h"
#include "sink_audio_routing.h"
#include "sink_private_data.h"
#include "sink_tones.h"

#ifdef ENABLE_AOV
#include <aov.h>
#include "sink_aov_config_def.h"


#ifdef DEBUG_AOV
    #define AOV_DEBUG(x) DEBUG(x)
#else
    #define AOV_DEBUG(x) 
#endif

typedef struct
{
    uint16 enable_count;
    audio_instance_t instance;
} aov_state_t;

#define AOV_OFF    -1

uint16 number_of_trigger_phrases = 0;
static int cycle_index = AOV_OFF;

static void sinkAovMessageHandler(Task task, MessageId id, Message message);
static FILE_INDEX sinkAovGetTriggerPhraseFileIndex(uint8 file_id);

static aov_state_t aov = {0, NULL};
const TaskData sink_aov_task = {sinkAovMessageHandler};

/*******************************************************************************
NAME
    getAovIsEnabled

DESCRIPTION
    Check if AoV is enabled in the application config.

RETURNS
    bool TRUE if AoV is enabled, FALSE otherwise.
*/
static bool getAovIsEnabled(void)
{
    bool enabled = FALSE;
    uint16 config_size;
    const sink_aov_readonly_config_def_t *config;

    config_size = configManagerGetReadOnlyConfig(SINK_AOV_READONLY_CONFIG_BLK_ID, (const void **)&config);
    if (config_size)
    {
        enabled = config->aov_config.enabled;

        configManagerReleaseConfig(SINK_AOV_READONLY_CONFIG_BLK_ID);
    }

    return enabled;
}

/*****************************************************************************/
static FILE_INDEX sinkAovGetTriggerPhraseFileIndex(uint8 file_id)
{
#define TRIGGER_DATA_DIR_NAME "trigger_phrase_data"
#define TRIGGER_DATA_FILE_PREFIX "tfd_"
#define TRIGGER_DATA_FILE_EXTENSION ".bin"

    FILE_INDEX directory_index;
    FILE_INDEX file_index;

    char *filename = PanicUnlessMalloc(sizeof(TRIGGER_DATA_FILE_PREFIX) + 4 + sizeof(TRIGGER_DATA_FILE_EXTENSION)); /*4 is max size of file_id as a string + null*/
    sprintf(filename,"%s%d%s",TRIGGER_DATA_FILE_PREFIX, file_id, TRIGGER_DATA_FILE_EXTENSION);

    AOV_DEBUG(("AOV: Loading data file %s\n", filename));

    directory_index = PanicZero(FileFind(FILE_ROOT, TRIGGER_DATA_DIR_NAME, strlen(TRIGGER_DATA_DIR_NAME)));

    file_index = PanicZero(FileFind(directory_index, filename, strlen(filename)));

    free(filename);

    return file_index;
}

/*****************************************************************************/
void sinkAovActivate(bool activate)
{
    AOV_DEBUG(("AOV: sinkAovActivate %d\n", (unsigned)activate));

    /* Ignore any enable/disable commands if the module is not enabled in the
       app config. */
    if (!getAovIsEnabled())
        return;

    if (activate)
    {
        aov.enable_count++;
        if (aov.enable_count == 1)
        {
            AudioPluginFeatures features;

            AOV_DEBUG(("AOV: Connect AoV plugin\n"));

            memset(&features, 0, sizeof(features));

            aov_connect_params_t* aov_params = PanicUnlessMalloc(sizeof(aov_connect_params_t));

            sinkAudioGetCommonMicParams(&aov_params->mic_params);

            aov_params->trigger_phrase_data_file = sinkAovGetTriggerPhraseFileIndex(0);

            aov.instance = AudioConnect((Task)&aov_plugin, 
                                        NULL/*audio_sink*/,
                                        AUDIO_SINK_SIDE_GRAPH/*sink_type*/,
                                        0/*volume*/,
                                        0/*rate*/,
                                        features/*features*/,
                                        AUDIO_MODE_STANDBY/*mode*/,
                                        AUDIO_ROUTE_INTERNAL/*route*/,
                                        POWER_BATT_CRITICAL/*power*/,
                                        aov_params,
                                        (Task)&sink_aov_task/*app_task*/);
        }
    }
    else
    {
        if (aov.enable_count > 0)
        {
            aov.enable_count--;
            if (aov.enable_count == 0)
            {
                AOV_DEBUG(("AOV: Disconnect AoV plugin\n"));

                PanicNull(aov.instance);

                AudioDisconnectInstance(aov.instance);
                aov.instance = NULL;
            }
        }
    }
}

/*****************************************************************************/
static void sinkAovMessageHandler(Task task, MessageId id, Message message)
{
    UNUSED(task);
    UNUSED(message);

    switch(id)
    {
        case AOV_MESSAGE_TRIGGERED:
            AOV_DEBUG(("AOV: SVA Triggered\n"));
            MessageSend(sinkGetMainTask(), EventUsrInitateVoiceRecognition, NULL);
            break;

        case AOV_MESSAGE_RESET_TIMEOUT:
            AOV_DEBUG(("AOV: Reset Timeout Triggered\n"));
            MessageSend(sinkGetMainTask(), EventSysVoiceRecognitionRequestTimeout, NULL);
            break;

        default:
            AOV_DEBUG(("AOV: Unknown message from plugin\n"));
            break;
    }
}

/*****************************************************************************/
static uint16 sinkAovgetNumberOfTriggerPharses(void)
{
    char filename[31];
    uint16 numberOfFiles = 0;
    uint16 fileIndex = 0;

    sprintf(filename, "trigger_phrase_data/tfd_%d.bin", fileIndex);

    while (FileFind(FILE_ROOT, filename, (uint16)strlen(filename)) != FILE_NONE)
    {
        fileIndex++;
        numberOfFiles++;
        sprintf(filename, "trigger_phrase_data/tfd_%d.bin", fileIndex);
    }

    AOV_DEBUG(("Number of Files is %d", numberOfFiles))

    return numberOfFiles;
}

/*****************************************************************************/
void sinkAovInit(void)
{
    number_of_trigger_phrases = sinkAovgetNumberOfTriggerPharses();
}

/*****************************************************************************/
static void sinkAovGetPromptFileIndexes(int16 prompt_index, FILE_INDEX *prompt_file_index, FILE_INDEX *prompt_header_file_index)
{
    char filename[31];

    sprintf(filename, "aov/prompts/%d.prm", prompt_index);
    *prompt_file_index = FileFind(FILE_ROOT, filename, (uint16)strlen(filename));

    sprintf(filename, "aov/prompts/%d.idx", prompt_index);
    *prompt_header_file_index = FileFind(FILE_ROOT, filename, (uint16)strlen(filename));
}

/*****************************************************************************/
static void sinkAovGetPhraseFileIndex(int16 phrase_index, FILE_INDEX *phrase_file_index)
{
    char filename[31];

    if (phrase_index == AOV_OFF)
    {
        *phrase_file_index = FILE_NONE;
    }
    else
    {
        sprintf(filename, "trigger_phrase_data/tfd_%d.bin", phrase_index);
        *phrase_file_index = FileFind(FILE_ROOT, filename, (uint16)strlen(filename));
    }
}

/*****************************************************************************/
static void sinkAovPlayPhrasePrompt(int16 prompt_index)
{
    FILE_INDEX prompt_file_index = FILE_NONE;
    FILE_INDEX prompt_file_header_file_index = FILE_NONE;

    sinkAovGetPromptFileIndexes(prompt_index, &prompt_file_index, &prompt_file_header_file_index);

    temporaryEnableAudioAmp();

}

/*****************************************************************************/
static void sinkAovLoadPhrase(int16 phrase_index)
{
    FILE_INDEX phrase_file_index = FILE_NONE;
    MAKE_AUDIO_MESSAGE(AUDIO_PLUGIN_CHANGE_TRIGGER_PHRASE_MSG, message);

    sinkAovGetPhraseFileIndex(phrase_index, &phrase_file_index);

    message->trigger_phrase_data_file = phrase_file_index;

    MessageSend((Task)&aov_plugin, AUDIO_PLUGIN_CHANGE_TRIGGER_PHRASE_MSG, message);
}

/*****************************************************************************/
void sinkAovCyclePhrase(void)
{
    cycle_index++;

    if (cycle_index >= number_of_trigger_phrases)
        cycle_index = AOV_OFF;

    sinkAovLoadPhrase(cycle_index);
    sinkAovPlayPhrasePrompt(cycle_index);
}

#endif /* ENABLE_AOV */
