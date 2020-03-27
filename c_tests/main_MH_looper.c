/*
 * An example of live processing with portaudio. A stereo looper line with an
 * embedded lowpass filter.
 *
 * Compile on linux and MacOS with:
 *  gcc c_tests/main_MH_looper.c lib/looper.c -Ilib -lm -lportaudio -o c_apps/main_MH_looper
 *
 * Compile on Windows with:
 *  gcc c_tests/main_MH_looper.c lib/looper.c -Ilib -lm -lportaudio -o c_apps/main_MH_looper.exe
 *
 * Run on linux and MacOS with:
 *  ./c_apps/main_MH_looper
 *
 * Run on Windows with:
 *  c_apps/main_MH_looper.exe
*/

// System includes.
#include <stdlib.h>     /* malloc, free */
#include <stdio.h>      /* printf, fprintf, getchar, stderr */    

// Include all portaudio functions.
#include "portaudio.h"

// Program-specific includes.
#include "looper.h"
//#include "lp1.h"


// Define global audio parameters.
#define SAMPLE_RATE         44100
#define FRAMES_PER_BUFFER   512
#define NUMBER_OF_CHANNELS  2

// Program-specific parameters.
#define LOOPTIME1 1
#define LOOPTIME2 2
#define LOOPTIME3 2
#define LOOPTIME4 1

#define PLAYRATE1 1
#define PLAYRATE2 1
#define PLAYRATE3 1
#define PLAYRATE4 1

// The DSP structure contains all needed audio processing "objects". 
struct DSP {
    struct looper *loop1[NUMBER_OF_CHANNELS];
	struct looper *loop2[NUMBER_OF_CHANNELS];
	struct looper *loop3[NUMBER_OF_CHANNELS];
	struct looper *loop4[NUMBER_OF_CHANNELS];
};

// This function allocates memory and intializes all dsp structures.
struct DSP * dsp_init() {
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP));
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        dsp->loop1[i] = looper_init(LOOPTIME1, PLAYRATE1, SAMPLE_RATE);
		dsp->loop2[i] = looper_init(LOOPTIME2, PLAYRATE2, SAMPLE_RATE);
		dsp->loop3[i] = looper_init(LOOPTIME3, PLAYRATE3,SAMPLE_RATE);
		dsp->loop4[i] = looper_init(LOOPTIME4, PLAYRATE4,SAMPLE_RATE);
    }
    return dsp;
}

// This function releases memory used by all dsp structures.
void dsp_delete(struct DSP *dsp) {
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        looper_delete(dsp->loop1[i]);
		looper_delete(dsp->loop2[i]);
		looper_delete(dsp->loop3[i]);
		looper_delete(dsp->loop4[i]);
    }
    free(dsp);
}

// This function does the actual processing chain.
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;
    float readval, filtered;
 
    for (i=0; i<framesPerBuffer; i=i+1) {
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {
            index = i * NUMBER_OF_CHANNELS + j;
            out[index] = looper_process(dsp->loop1[j], in[index])+looper_process(dsp->loop2[j], in[index])
						+looper_process(dsp->loop3[j], in[index])+looper_process(dsp->loop4[j], in[index]);
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
    if (paErrorCheck(err)) { return  -1; }

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
	
	/*SECTION MH*/
	int quit=0;
	
	printf("Hit q to stop program.\n");
	while (quit==0)
	{
	int input=getchar();
	Sleep(100); //Pour eviter le clics d enregistrement

	for (int i =0; i < NUMBER_OF_CHANNELS; i++)
	{
		if (input == 0x31 ||input == 0x20 )
		{
			looper_controls(dsp->loop1[i]);
			printf("loop1");
			
		}
		if (input == 0x32||input == 0x20)
		{	
			looper_controls(dsp->loop2[i]);
			printf("loop2");
		}
		if (input == 0x33||input == 0x20)
		{
			looper_controls(dsp->loop3[i]);
			printf("loop3");
		}
		if (input == 0x34||input == 0x20)
		{	
			looper_controls(dsp->loop4[i]);
			printf("loop4");
		}
		else if (input ==0x71)
		{
			quit=1;
		}
	}
	}
	
	/*FIn section MH*/
	
    //printf("Hit ENTER to stop program.\n");	
 

    err = Pa_CloseStream(stream);
    if (paErrorCheck(err)) { return -1; }

    dsp_delete(dsp);

    Pa_Terminate();

    return 0;
}
