/*
 * This program modulates the frequency of a sine based on an interpolation of two lfos
 *
 * Compile on linux and MacOS with:
 *  gcc main_matrix_example.c lib/routing.c lib/sinosc.c lib/utils.c -Ilib -lm -lportaudio -o main_matrix_example
 *
 * Compile on Windows with:
 *  gcc main_matrix_example.c lib/routing.c lib/sinosc.c lib/utils.c -Ilib -lm -lportaudio -o main_matrix_example.exe
 *
 * Run on linux and MacOS with:
 *  ./main_matrix_example
 *
 * Run on Windows with:
 *  main_matrix_example.exe
*/

#include <stdlib.h>
#include <stdio.h>

#include "portaudio.h"

#define SAMPLE_RATE         44100
#define FRAMES_PER_BUFFER   512
#define NUMBER_OF_CHANNELS  2

#define OSC_FREQ            440

#include "sinosc.h"
#include "routing.h"
#include "noise.h"


// the frequencies that will used for the LFOs sent to routing matrix input
#define LFO_FREQ1 8
#define LFO_FREQ2 0.1

struct DSP {

    // 2 LFOs     
    struct sinosc *lfo1;
  //    struct sinosc *lfo2;

    struct noise *noise;

    // sine (stereo)  
    struct sinosc *sin1[NUMBER_OF_CHANNELS];

    // routing matrix
    struct routing_matrix * matrix;   
};

struct DSP * dsp_init() {
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP));

    // Create and initialize the routing matrix
    struct routing_matrix * matrix = routing_matrix_init();

    // assign the routing matrix to the dsp struct
    dsp->matrix = matrix;

    
    
    // select two input "port" from 0 to MAX_INPUTS - 1
    // and copy the interpolated result in
    // a bus identified from 0 to MAX_BUSSES - 1

    // in this case, the signals sent to inputs
    // 0 and 1 are interpolated by a factor
    // of 0.5 (or 50% from each signal)
    
    // the last argument is the default value
    // (used if the route is not yet defined
    // with matrix_route|matrix_route_mix or
    // has been killed by matrix_kill_bus)
    matrix_route_mix(dsp->matrix, 0, 1, 0.82, 0);

    // initialize the LFOs
    dsp->lfo1 = sinosc_init(LFO_FREQ1, SAMPLE_RATE);
    //dsp->lfo2 = sinosc_init(LFO_FREQ2, SAMPLE_RATE);
    dsp->noise = noise_init();
    
    /* Memory allocation for DSP structure. */
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {

      // initialize the sine (stereo)
      dsp->sin1[i] = sinosc_init(OSC_FREQ, SAMPLE_RATE);
    }
    return dsp;
}

void dsp_delete(struct DSP *dsp) {
    int i;

    sinosc_delete(dsp->lfo1);
    //sinosc_delete(dsp->lfo2);
    noise_delete(dsp->noise);
    
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        sinosc_delete(dsp->sin1[i]);
    }

    // the routing matrix must be correctly dealocated.
    delete_routing_matrix(dsp->matrix);
    free(dsp);
}

void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;
    float freq, lfoval1, lfoval2;
    

    for (i=0; i<framesPerBuffer; i++) {
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {
            index = i * NUMBER_OF_CHANNELS + j;

	    // process the next sample for each LFO
            lfoval1 = sinosc_process(dsp->lfo1);
	    lfoval2 = noise_process(dsp->noise);

	    // copy the results into two matrix input 0 and 1
	    matrix_update_input(dsp->matrix, 0, lfoval1);	    
	    matrix_update_input(dsp->matrix, 1, lfoval2);

	    // Once the modulations are processed and stored in the matrix,
	    // they are then copied into their respective  active outputs
	    matrix_update_outputs(dsp->matrix);
	    
	    // the sine frequency is modulated by the value now contained
	    // in the bus 0
	    freq = matrix_bus_output(dsp->matrix, 0, 0) * 100 + OSC_FREQ;
	    
	    // the sine's frequency is updated with the modulated frequency
	    sinosc_set_freq(dsp->sin1[j], freq);	    
	    
            out[index] = sinosc_process(dsp->sin1[j]) * 0.3;
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
