/*
 * 4 Bands Parametric eqiing audio processing
 *
 * Compile on linux and MacOS with:
 *  gcc c_tests/main_CA_eq4Bands.c lib/eq4Bands.c lib/parametricEQ.c -Ilib -lm -lportaudio -o c_apps/main_CA_eq4Bands
 *
 * Compile on Windows with:
 *  gcc c_tests/main_CA_eq4Bands.c lib/eq4Bands.c lib/parametricEQ.c -Ilib -lm -lportaudio -o c_apps/main_CA_eq4Bands.exe
 *
 * Run on linux and MacOS with:
 *  ./c_apps/main_CA_eq4Bands
 *
 * Run on Windows with:
 *  c_apps/main_CA_eq4Bands.exe
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
#include "eq4Bands.h"

//== Program-specific parameters. ==
// This is where you define the specific parameters needed by your program...
#define FREQ_LS         400 //Hz
#define Q_LS            5
#define GAIN_LS         -12  //dB
#define FREQ_N1         1200 //Hz
#define Q_N1            2
#define GAIN_N1         -18  //dB
#define FREQ_N2         2000 //Hz
#define Q_N2            1
#define GAIN_N2         10  //dB
#define FREQ_HS         6000 //Hz
#define Q_HS            6
#define GAIN_HS         -5  //dB

/* The DSP structure contains all needed audio processing "objects". */
struct DSP
{
    // This is where you declare the specific processing structures
    // needed by your program... Each declaration should have the form:

    struct eq4Bands *eq4B[NUMBER_OF_CHANNELS];

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

        dsp->eq4B[i] = eq4Bands_init(FREQ_LS, Q_LS, GAIN_LS,
                                    FREQ_N1, Q_N1, GAIN_N1,
                                    FREQ_N2, Q_N2, GAIN_N2,
                                    FREQ_HS, Q_HS, GAIN_HS,                                        
                                    SAMPLE_RATE);
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

        eq4Bands_delete(dsp->eq4B[i]);
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
            out[index] = eq4Bands_process(dsp->eq4B[j], in[index]);
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
