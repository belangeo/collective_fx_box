/*
 * Template file to create a live audio processing program with portaudio.
 * Choose an lfo type and add variables.
 * Compile on linux and MacOS with:
 *  gcc main_LFO.c lib/*.c -Ilib -lm -lportaudio -o main_LFO
 *
 * Compile on Windows with:
 *  gcc main_LFO.c lib/*.c -Ilib -lm -lportaudio -o main_LFO.exe
 *
 * Run on linux and MacOS with:
 *  ./main_LFO
 *
 * Run on Windows with:
 *  main_LFO.exe
*/

/* System includes. */
#include <stdlib.h>     /* malloc, free */
#include <stdio.h>      /* printf, fprintf, getchar, stderr */    

//== Program-specific system includes. ==
// This is where you include the program-specific system headers (if needed) by your program...


/* Include all portaudio functions. */
#include "portaudio.h"

/* Define global audio parameters, used to setup portaudio. */
#define SAMPLE_RATE         44100
#define FRAMES_PER_BUFFER   512
#define NUMBER_OF_CHANNELS  2


//== Program-specific includes. ==
// This is where you include the specific headers needed by your program...
#include "sinosc.h"
#include "carre.h"
#include "triangle.h"
#include "saw.h"
#include "phas.h"

//== Program-specific parameters. ==
// This is where you define the specific parameters needed by your program...
#define LFO_FREQ 5

/* The DSP structure contains all needed audio processing "objects". */
struct DSP {
    // This is where you declare the specific processing structures
    // needed by your program... Each declaration should have the form:

    struct sinosc *lfo[NUMBER_OF_CHANNELS];
    struct carre *lfo[NUMBER_OF_CHANNELS];
    struct triangle *lfo[NUMBER_OF_CHANNELS];
    struct saw *lfo[NUMBER_OF_CHANNELS];
    struct phasor *lfo[NUMBER_OF_CHANNELS];

    // Which means a "multi-channel" pointer to the processing structure.

};

/* This function allocates memory and intializes all dsp structures. */
struct DSP * dsp_init() {
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP));   /* Memory allocation for DSP structure. */
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you setup the specific processing structures needed by your program,
        // using the provided xxx_init functions. Something like:
        
        // Choose an lfo type
        dsp->lfo[i] = sinosc_init(LFO_FREQ, SAMPLE_RATE);
        dsp->lfo[i] = carre_init(LFO_FREQ, SAMPLE_RATE);
        dsp->lfo[i] = triangle_init(LFO_FREQ, SAMPLE_RATE);
        dsp->lfo[i] = saw_init(LFO_FREQ, SAMPLE_RATE);
        dsp->lfo[i] = phasor_init(LFO_FREQ, SAMPLE_RATE);

    }
    return dsp;
}

/* This function releases memory used by all dsp structures. */
void dsp_delete(struct DSP *dsp) {
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you release the memory used by the specific processing structure
        // used in the program. Something like:

        // Choose an lfo type
        sinosc_delete(dsp->lfo[i]);
        carre_delete(dsp->lfo[i]);
        triangle_delete(dsp->lfo[i]);
        saw_delete(dsp->lfo[i]);
        phasor_delete(dsp->lfo[i]);
    }
    free(dsp);
}

/* This function does the actual processing chain. */
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;   /* Variables used to compute the index of samples in input/output arrays. */

    // Add any variables useful to your processing logic here...

    for (i=0; i<framesPerBuffer; i++) {             /* For each sample frame in a buffer size... */
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {      /* For each channel in a frame... */
            index = i * NUMBER_OF_CHANNELS + j;     /* Compute the index of the sample in the arrays... */

            // This is where you want to put your processing logic... A simple thru is:

            // Choose an lfo type
            lfoval = sinosc_process(dsp->lfo[j]);
            lfoval = carre_process(dsp->lfo[j]);
            lfoval = triangle_process(dsp->lfo[j]);
            lfoval = saw_process(dsp->lfo[j]);
            lfoval = phasor_process(dsp->lfo[j]);

            // Choose a type and add any variables 
            sinosc_set_freq();
            carre_set_freq();
            triangle_set_freq();
            saw_set_freq();
            phasor_set_freq();

            out[index] = in[index] + sinosc_process();
            out[index] = in[index] + carre_process();
            out[index] = in[index] + triangle_process();
            out[index] = in[index] + saw_process();
            out[index] = in[index] + phasor_process();

            // out[index] = in[index];
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
        fprintf(stderr,  Pa_GetErrorText(err));
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
