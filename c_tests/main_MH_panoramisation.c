/*
 * Template file to create a live audio processing program with portaudio AND portmidi.
 *
 * Compile on linux and MacOS with:
 *  gcc c_tests/main_MH_panoramisation.c lib/panoramisation.c lib/midimap.c -Ilib -lm -lportaudio -lportmidi -lncurses -o c_apps/main_MH_pan
 *
 * Compile on Windows with:
 *  gcc c_tests/main_MH_panoramisation.c lib/panoramisation.c lib/midimap.c -Ilib -lm -lportaudio -lportmidi -lncurses -o c_apps/main_MH_pan.exe
 *
 * Run on linux and MacOS with:
 *  ./c_apps/main_MH_pan
 *
 * Run on Windows with:
 *  c_apps/main_MH_pan.exe
*/

/* System includes. */
#include <stdlib.h>     /* malloc, free */
#include <stdio.h>      /* printf, fprintf, getchar, stderr */

#ifdef _WIN32
#include <Windows.h>            /* Sleep */
#include <ncurses/curses.h>     /* all ncurses functions. */
#else
#include <unistd.h>     /* usleep */
#include <curses.h>     /* all ncurses functions. */
#endif

//== Program-specific system includes. ==
// This is where you include the program-specific system headers (if needed) by your program...


/* Include all portaudio functions. */
#include "portaudio.h"

/* Include all portmidi functions. */
#include "portmidi.h"

/* Include midi mapping functions. */
#include "midimap.h"

/* Define global audio parameters, used to setup portaudio. */
#define SAMPLE_RATE         44100
#define FRAMES_PER_BUFFER   512
#define NUMBER_OF_CHANNELS  2


//== Program-specific includes. ==
#include "panoramisation.h"

//== Program-specific parameters. ==

/* The DSP structure contains all needed audio processing "objects". */
struct DSP {
    struct panoramisation *pan[NUMBER_OF_CHANNELS];
	

};

/* This function allocates memory and intializes all dsp structures. */
struct DSP * dsp_init() {
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP));
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        dsp->pan[i] = pan_init();
    }
    return dsp;
}

/* This function releases memory used by all dsp structures. */
void dsp_delete(struct DSP *dsp) {
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        pan_delete(dsp->pan[i]);
    }
    free(dsp);
}

/* This function does the actual processing chain. */
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;
    float readval, filtered;
 
    for (i=0; i<framesPerBuffer; i=i+1) {
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {
            index = i * NUMBER_OF_CHANNELS + j;
			out[index]= pan_set_chnl(dsp->pan[j], in[index], 0);
            //out[index] = looper_process(dsp->loop1[j], in[index])+looper_process(dsp->loop2[j], in[index])
						//+looper_process(dsp->loop3[j], in[index])+looper_process(dsp->loop4[j], in[index]);
        }
    }
}

/* This function maps midi controller values to our dsp variables. */
void dsp_midi_ctl_in(struct DSP *dsp, int ctlnum, int value) {

	/*for (int i =0; i < NUMBER_OF_CHANNELS; i++)
	{
		if (ctlnum == 60 ||ctlnum == 59 )
		{
			looper_midi(dsp->loop1[i], ctlnum);
			printf("loop1");
			
		}
		if (ctlnum == 61||ctlnum == 59)
		{	
			looper_midi(dsp->loop2[i], ctlnum);
			printf("loop2");
		}
		if (ctlnum == 62||ctlnum == 59)
		{
			looper_midi(dsp->loop3[i], ctlnum);
			printf("loop3");
		}
		if (ctlnum == 63||ctlnum == 59)
		{	
			looper_midi(dsp->loop4[i], ctlnum);
			printf("loop4");
		}
	}*/
    printf("%d %d %d\n", ctlnum, value, midimap_get("2") == ctlnum);
}

/**********************************************************************************************
 *
 * You shouldn't need to edit anything below here !
 *
 *********************************************************************************************/

/* Portmidi global variables (not the best way to do it, but clearly the simpler for now! */
PmStream *pm_input_streams[32];
static int pm_initialized = 0;
static int pm_num_of_devices = 0;

/* Portmidi input handler (only continuous controllers). */
static void handle_midi_input(struct DSP *dsp) {
    int i;
    PmError result, length;
    PmEvent buffer;

    for (i=0; i<pm_num_of_devices; i++) {
        do {
            result = Pm_Poll(pm_input_streams[i]);
            if (result) {
                length = Pm_Read(pm_input_streams[i], &buffer, 1);
                if (length > 0) {
                    int status = Pm_MessageStatus(buffer.message);
                    if ((status & 0xF0) == 0xB0) {
                        int ctlnum = Pm_MessageData1(buffer.message);
                        int value = Pm_MessageData2(buffer.message);
                        dsp_midi_ctl_in(dsp, ctlnum, value);
                    }
                }
            }
        } while (result);
    }
}

/* Portaudio realtime callback. */
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

    if (inputBuffer == NULL) { return paAbort; } // mmm...?

    if (pm_initialized == 1) {
        handle_midi_input(dsp);
    }

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

void create_window(struct DSP *dsp) {
    int running, key, polltime = 20;
    WINDOW *w;

    /* Screen initialization. */
    w = initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(w, TRUE);
    nodelay(w, TRUE);
    mvaddstr(2, 2, "COLLECTIVE FX BOX !");
    mvaddstr(3, 2, "-------------------");


#ifdef _WIN32
        Sleep(polltime);
#else
        usleep(polltime * 1000);
#endif
    }

    polltime = 1000;
#ifdef _WIN32
    Sleep(polltime);
#else
    usleep(polltime * 1000);
#endif

    endwin();
}

int main(void)
{
    int i;
        
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream;
    PaError err;
    PmError pmerr;

    struct DSP *dsp = dsp_init();

    /********* Portmidi initialization *********/
    pmerr = Pm_Initialize();
    if (pmerr) {
        printf("Can't initialize portmidi...\n");
    } else {
        int num_devices = Pm_CountDevices();
        if (num_devices > 0) {
            for (i=0; i<num_devices; i++) {
                const PmDeviceInfo *info = Pm_GetDeviceInfo(i);
                if (info != NULL) {
                    if (info->input) {
                        pmerr = Pm_OpenInput(&pm_input_streams[pm_num_of_devices], i, NULL, 100, NULL, NULL);
                        if (pmerr) {
                            printf("Portmidi warning: could not open midi input %d (%s): %s\n",
                                   0, info->name, Pm_GetErrorText(pmerr));
                        }
                        else {
                            Pm_SetFilter(pm_input_streams[pm_num_of_devices], PM_FILT_ACTIVE | PM_FILT_CLOCK);
                            pm_num_of_devices++;
                        }
                    }
                }
            }
        }
        if (pm_num_of_devices > 0) {
            pm_initialized = 1;
            midimap_init();
        }
    }

    /********* Portaudio initialization *********/
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

    create_window(dsp);

    printf("Hit ENTER to stop program.\n");
    getchar(); 
	
    err = Pa_CloseStream(stream);
    if (paErrorCheck(err)) { return -1; }

    dsp_delete(dsp);

    Pa_Terminate();

    if (pm_initialized == 1) {
        for (i=0; i<pm_num_of_devices; i++) {
            Pm_Close(pm_input_streams[i]);
        }
        Pm_Terminate();
    }

    return 0;
}
