/*
 * An example of live processing with portaudio. Outputs a sine wave signal.
 *
 * Compile on linux and MacOS with:
 *  gcc main_randh.c sinosc.c randh.c -Ilib -lm -lportaudio -o main_randh
 *
 * Compile on Windows with:
 *  gcc main_randh.c lib/sinosc.c lib/randh.c -Ilib -lm -lportaudio -o main_randh.exe
 *
 * Run on linux and MacOS with:
 *  ./main_randh
 *
 * Run on Windows with:
 *  main_randh.exe
*/

// System includes.
#include <stdlib.h>     /* malloc, free */
#include <stdio.h>      /* printf, fprintf, getchar, stderr */    
#include <math.h>
#include <time.h>   /* time */

// Include all portaudio functions.
#include "portaudio.h"

// Program-specific includes.
#include "sinosc.h"
#include "randh.h"

// Define global audio parameters.
#define SAMPLE_RATE         44100
#define FRAMES_PER_BUFFER   512
#define NUMBER_OF_CHANNELS  2

// Program-specific parameters.
#define FREQUENCY 440
#define RAND_SPEED 5
#define MIN 20
#define MAX 20000

// The DSP structure contains all needed audio processing "objects". 
struct DSP {
    struct sinosc * osc[NUMBER_OF_CHANNELS];
    struct randh * rand[NUMBER_OF_CHANNELS];
};

// This function allocates memory and intializes all dsp structures.
struct DSP * dsp_init() {
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP));
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        dsp->osc[i] = sinosc_init(FREQUENCY, SAMPLE_RATE);
    }
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        dsp->rand[i] = randh_init(RAND_SPEED, MIN, MAX, SAMPLE_RATE);
    }
    return dsp;
}

// This function releases memory used by all dsp structures.
void dsp_delete(struct DSP *dsp) {
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        sinosc_delete(dsp->osc[i]);
    }
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        randh_delete(dsp->rand[i]);
    }
    free(dsp);
}

// This function does the actual processing chain.
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;
    float readval, filtered;
    for (i=0; i<framesPerBuffer; i++) {
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {
            index = i * NUMBER_OF_CHANNELS + j;
            out[index] = sinosc_process(dsp->osc[j]) * randh_process(dsp->rand[j]) * 0.25;
        }
    }
}

/**********************************************************************************************
 *
 * You shouldn't need to edit anything below here !
 *
 *********************************************************************************************/

static int callback(const void *inputBuffer, void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags, void *userData) 
{
    const float *in = (const float *)inputBuffer;
    float *out = (float *)outputBuffer;
    /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;

    struct DSP *dsp = (struct DSP *) userData;

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

int paDefaultDeviceCheck(PaDeviceIndex device, char *direction)
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
    PaStream *stream;
    PaError err;

    struct DSP *dsp = dsp_init();
    
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
                        FRAMES_PER_BUFFER, paNoFlag, callback, (void *)dsp);
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