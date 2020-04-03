/*
	main.c
	waveshaper

	Antoine Lussier - Remi Coulombe
	21 fevrier 2020
	MUS3329

	gcc c_tests/main_waveshaper_Coulombe-Lussier.c lib/waveshaper.c lib/distoFiltr.c lib/utils.c -Ilib -lm -lportaudio -lportmidi -o c_apps/main_Waveshaper_Coulombe-Lussier

*/

// System includes.
#include <stdlib.h>     /* malloc, free */
#include <stdio.h>      /* printf, fprintf, getchar, stderr */    

// Include all portaudio functions.
#include "portaudio.h"
#include "portmidi.h"
#include "waveshaper.h"

// Define global audio parameters.
#define SAMPLE_RATE         44100
#define FRAMES_PER_BUFFER   512
#define NUMBER_OF_CHANNELS  2

// Program-specific parameters.
#define DRIVE 100.0
#define FREQ 8000
#define Q 4.0
#define DRYWET 100.0


// The DSP structure contains all needed audio processing "objects". 
struct DSP {
    struct waveshaper *waveshaper[NUMBER_OF_CHANNELS];
};

// This function allocates memory and intializes all dsp structures.
struct DSP* dsp_init() {
    int i;
    struct DSP* dsp = malloc(sizeof(struct DSP));
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        dsp->waveshaper[i] = waveshaper_init(DRIVE, FREQ, SAMPLE_RATE, Q, DRYWET);
    }
    return dsp;
}

// This function releases memory used by all dsp structures.
void dsp_delete(struct DSP* dsp) {
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        waveshaper_delete(dsp->waveshaper[i]);
    }
    free(dsp);
}

// This function does the actual processing chain.
void dsp_process(const float* in, float* out, unsigned long framesPerBuffer, struct DSP* dsp) {
    unsigned int i, j, index;
    for (i = 0; i < framesPerBuffer; i++) {
        for (j = 0; j < NUMBER_OF_CHANNELS; j++) {
            index = i * NUMBER_OF_CHANNELS + j;

            out[index] = waveshaper_process(dsp->waveshaper[j], in[index]);
        }
    }
}

/**********************************************************************************************
 *
 * You shouldn't need to edit anything below here !
 *
 *********************************************************************************************/

static int callback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags, void* userData)
{
    const float* in = (const float*)inputBuffer;
    float* out = (float*)outputBuffer;
    /* Prevent unused variable warnings. */
    (void)timeInfo;
    (void)statusFlags;

    struct DSP* dsp = (struct DSP*) userData;

    if (inputBuffer == NULL) { return paAbort; }

    dsp_process(in, out, framesPerBuffer, dsp);

    return paContinue;
}

int paErrorCheck(PaError err)
{
    if (err != paNoError) {
        Pa_Terminate();
        fprintf(stderr, Pa_GetErrorText(err));
        return 1;
    }
    return 0;
}

int paDefaultDeviceCheck(PaDeviceIndex device, char* direction)
{
    if (device == paNoDevice) {
        Pa_Terminate();
        fprintf(stderr, "Error: No default %s device.\n", direction);
        return 1;
    }
    return 0;
}

int main(void)
{
    PaStreamParameters inputParameters, outputParameters;
    PaStream* stream;
    PaError err;

    struct DSP* dsp = dsp_init();

    err = Pa_Initialize();
    if (paErrorCheck(err)) { return -1; }

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (paDefaultDeviceCheck(inputParameters.device, "input")) { return -1; }

    inputParameters.channelCount = NUMBER_OF_CHANNELS;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (paDefaultDeviceCheck(outputParameters.device, "output")) { return -1; }

    outputParameters.channelCount = NUMBER_OF_CHANNELS;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, SAMPLE_RATE,
        FRAMES_PER_BUFFER, paNoFlag, callback, (void*)dsp);
    if (paErrorCheck(err)) { return -1; }

    err = Pa_StartStream(stream);
    if (paErrorCheck(err)) { return -1; }

    printf("Hit ENTER to stop program.\n");
    getchar();

    err = Pa_CloseStream(stream);
    if (paErrorCheck(err)) { return -1; }

    dsp_delete(dsp);

    Pa_Terminate();

    return 0;
}
