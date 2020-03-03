/*
 * This program adds an FM-synthesis background to the input sound.
 *
 * Compile on linux and MacOS with:
 *  gcc main_matrix_example.c lib/routing.c lib/sinosc.c -Ilib -lm -lportaudio -o main_matrix_example
 *
 * Compile on Windows with:
 *  gcc main_matrix_example.c lib/routing.c lib/sinosc.c -Ilib -lm -lportaudio -o main_matrix_example.exe
 *
 * Run on linux and MacOS with:
 *  ./main_matrix_example
 *
 * Run on Windows with:
 *  main_matrix_example.exe
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

#define OSC_FREQ            440

//== Program-specific includes. ==
// This is where you include the specific headers needed by your program...

#include "sinosc.h"
#include "routing.h"

//== Program-specific parameters. ==
// This is where you define the specific parameters needed by your program...
#define LFO_FREQ1 8
#define LFO_FREQ2 0.1

/* The DSP structure contains all needed audio processing "objects". */
struct DSP {
    // This is where you declare the specific processing structures
    // needed by your program...
    struct sinosc *lfo1;
    struct sinosc *lfo2;
    struct sinosc *sin1[NUMBER_OF_CHANNELS];

    // The routing matrix
    struct routing_matrix * matrix;   
};

/* This function allocates memory and intializes all dsp structures. */
struct DSP * dsp_init() {
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP));

    // Create and initialize the routing matrix
    struct routing_matrix * matrix = routing_matrix_init();
    dsp->matrix = matrix;

    // Route an input to an output. Note that this will be
    // replaced by a config file mechanism
    matrix_route(dsp->matrix, 0, 0);
    
    dsp->lfo1 = sinosc_init(LFO_FREQ1, SAMPLE_RATE);
    dsp->lfo2 = sinosc_init(LFO_FREQ2, SAMPLE_RATE);
    
    /* Memory allocation for DSP structure. */
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you setup the specific processing structures needed by your program,
        // using the provided xxx_init functions.

      // The routing matrix is passed as argument so that the sinosc can use it
      dsp->sin1[i] = sinosc_init(OSC_FREQ, SAMPLE_RATE);
    }
    return dsp;
}

/* This function releases memory used by all dsp structures. */
void dsp_delete(struct DSP *dsp) {
    int i;

    sinosc_delete(dsp->lfo1);
    sinosc_delete(dsp->lfo2);
    
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you release the memory used by the specific processing structure
        // used in the program.
        sinosc_delete(dsp->sin1[i]);
    }

    // the routing matrix must be correctly dealocated.
    delete_routing_matrix(dsp->matrix);
    free(dsp);
}

/* This function does the actual processing chain. */
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;   /* Variables used to compute the index of samples in input/output arrays. */

    // Add any variables useful to your processing logic here...
    float modfreq, modamp, carfreq, lfoval;
    

    for (i=0; i<framesPerBuffer; i++) {             /* For each sample frame in a buffer size... */
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {      /* For each channel in a frame... */
            index = i * NUMBER_OF_CHANNELS + j;     /* Compute the index of the sample in the arrays... */

            // This is where you want to put your processing logic...

	    // Each modulation function is processed here, and it's value passed to
	    // the routing matrix
	    
            lfoval = sinosc_process(dsp->lfo1);

	    matrix_update_input(dsp->matrix, 0, lfoval);
	    
	    lfoval = sinosc_process(dsp->lfo2);

	    matrix_update_input(dsp->matrix, 1, lfoval);

	    float freq = matrix_bus_output(dsp->matrix, 0, 0) * 100 + OSC_FREQ;
	    sinosc_set_freq(dsp->sin1[j], freq);

	    // Once the modulations are processed and stored in the matrix,
	    // they are then copied into their respective  active outputs
	    matrix_update_outputs(dsp->matrix);
	    
            out[index] = sinosc_process(dsp->sin1[j]) * 0.3;
	    //	    printf("out[%d] = %f\n", index, out[index]);
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
