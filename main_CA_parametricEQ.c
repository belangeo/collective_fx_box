/*
 * Parametric eqiing audio processing
 *
 * Compile on linux and MacOS with:
 *  gcc main_CA_parametricEQ.c lib/*.c -Ilib -lm -lportaudio -o main_CA_parametricEQ
 *  gcc main_CA_parametricEQ.c lib/parametricEQ.c -Ilib -lm -lportaudio -o ../app/main_CA_parametricEQ
 * 
 * Compile on Windows with:
 *  gcc main_CA_parametricEQ.c lib/*.c -Ilib -lm -lportaudio -o main_CA_parametricEQ.exe
 *
 * Run on linux and MacOS with:
 *  ./main_CA_parametricEQ
 *
 * Run on Windows with:
 *  main_CA_parametricEQ.exe
*/

/* System includes. */
#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* printf, fprintf, getchar, stderr */

//== Program-specific system includes. ==
// This is where you include the program-specific system headers (if needed) by your program...

/* Include all portaudio functions. */
#include "portaudio.h"

/* Define global audio parameters, used to setup portaudio. */
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512
#define NUMBER_OF_CHANNELS 2

//== Program-specific includes. ==
// This is where you include the specific headers needed by your program...
#include "parametricEQ.h"

//== Program-specific parameters. ==
// This is where you define the specific parameters needed by your program...
#define FREQUENCY   3000 //Hz
#define Q           1
#define GAIN        -18  //dB
#define FILTER_TYPE LOWSHELF

/* The DSP structure contains all needed audio processing "objects". */
struct DSP
{
    // This is where you declare the specific processing structures
    // needed by your program... Each declaration should have the form:

    struct parametricEQ *paraEQ[NUMBER_OF_CHANNELS];

    // Which means a "multi-channel" pointer to the processing structure.
};

/* This function allocates memory and intializes all dsp structures. */
struct DSP *dsp_init()
{
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP)); /* Memory allocation for DSP structure. */
    for (i = 0; i < NUMBER_OF_CHANNELS; i++)
    {
        // This is where you setup the specific processing structures needed by your program,
        // using the provided xxx_init functions. Something like:

        dsp->paraEQ[i] = parametricEQ_init(FREQUENCY, Q, GAIN, FILTER_TYPE, SAMPLE_RATE);
    }
    return dsp;
}

/* This function releases memory used by all dsp structures. */
void dsp_delete(struct DSP *dsp)
{
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++)
    {
        // This is where you release the memory used by the specific processing structure
        // used in the program. Something like:

        parametricEQ_delete(dsp->paraEQ[i]);
    }
    free(dsp);
}

/* This function does the actual processing chain. */
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp)
{
    unsigned int i, j, index; /* Variables used to compute the index of samples in input/output arrays. */

    // Add any variables useful to your processing logic here...

    for (i = 0; i < framesPerBuffer; i++)
    { /* For each sample frame in a buffer size... */
        for (j = 0; j < NUMBER_OF_CHANNELS; j++)
        {                                       /* For each channel in a frame... */
            index = i * NUMBER_OF_CHANNELS + j; /* Compute the index of the sample in the arrays... */

            // This is where you want to put your processing logic... A simple thru is:
            // out[index] = in[index];
            out[index] = parametricEQ_process(dsp->paraEQ[j], in[index]);
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
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags, void *userData)
{
    const float *in = (const float *)inputBuffer;
    float *out = (float *)outputBuffer;
    /* Prevent unused variable warnings. */
    (void)timeInfo;
    (void)statusFlags;

    struct DSP *dsp = (struct DSP *)userData;

    if (inputBuffer == NULL)
    {
        return paAbort;
    }

    dsp_process(in, out, framesPerBuffer, dsp);

    return paContinue;
}

int paErrorCheck(PaError err)
{
    if (err != paNoError)
    {
        Pa_Terminate();
        fprintf(stderr, Pa_GetErrorText(err));
        return 1;
    }
    return 0;
}

int paDefaultDeviceCheck(PaDeviceIndex device, char *direction)
{
    if (device == paNoDevice)
    {
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
    if (paErrorCheck(err))
    {
        return -1;
    }

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (paDefaultDeviceCheck(inputParameters.device, "input"))
    {
        return -1;
    }

    inputParameters.channelCount = NUMBER_OF_CHANNELS;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    printf("device input : %s \n", Pa_GetDeviceInfo(inputParameters.device)->name);
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (paDefaultDeviceCheck(outputParameters.device, "output"))
    {
        return -1;
    }

    outputParameters.channelCount = NUMBER_OF_CHANNELS;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    printf("device output : %s \n", Pa_GetDeviceInfo(outputParameters.device)->name);
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, SAMPLE_RATE,
                        FRAMES_PER_BUFFER, paNoFlag, callback, (void *)dsp);
    if (paErrorCheck(err))
    {
        return -1;
    }

    err = Pa_StartStream(stream);
    if (paErrorCheck(err))
    {
        return -1;
    }

    printf("Hit ENTER to stop program.\n");
    getchar();

    err = Pa_CloseStream(stream);
    if (paErrorCheck(err))
    {
        return -1;
    }

    dsp_delete(dsp);

    Pa_Terminate();

    return 0;
}
