/*
 * Template file to create a live audio processing program with portaudio, portmidi and ncurses to create a text interface.
 *
 * Compile on linux and MacOS with:
 *  gcc c_templates/main_template_midi_stdin.c lib/rms.c lib/midimap.c -Ilib -lm -lportaudio -lportmidi -lcurses -o c_apps/main_template_midi_stdin
 *
 * Compile on Windows with:
 *  gcc c_templates/main_template_midi_stdin.c lib/rms.c lib/midimap.c -Ilib -lm -lportaudio -lportmidi -lncurses -o c_apps/main_template_midi_stdin.exe
 *
 * Run on linux and MacOS with:
 *  ./c_apps/main_template_midi_stdin
 *
 * Run on Windows with:
 *  c_apps\main_template_midi_stdin.exe
*/

/* System includes. */
#include <stdlib.h>     /* malloc, free */
#include <stdio.h>      /* printf, fprintf, getchar, stderr */
#include <math.h>       /* log10f */
#include <string.h>     /* memset, strncpy */

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

/* Interface signal constants. */
typedef enum _SIGNAL {S_QUIT, S_RECORD1, S_RECORD2, S_RECORD3, S_RECORD4} SIGNAL;

/* Forward declaration of the function for printing messages. */
void output_log(char *msg);

//== Program-specific includes. ==
// This is where you include the specific headers needed by your program...
#include "rms.h"

//== Program-specific parameters. ==
// This is where you define the specific parameters needed by your program...


/* The DSP structure contains all needed audio processing "objects". */
struct DSP {
    // This is where you declare the specific processing structures
    // needed by your program... Each declaration should have the form:

    struct rms *amp[NUMBER_OF_CHANNELS];
    float amp_f[NUMBER_OF_CHANNELS];

};

/* This function allocates memory and intializes all dsp structures. */
struct DSP * dsp_init() {
    int i;
    struct DSP *dsp = malloc(sizeof(struct DSP));   /* Memory allocation for DSP structure. */
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you setup the specific processing structures needed by your program,
        // using the provided xxx_init functions. Something like:

        dsp->amp[i] = rms_init(FRAMES_PER_BUFFER);


    }
    return dsp;
}

/* This function releases memory used by all dsp structures. */
void dsp_delete(struct DSP *dsp) {
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you release the memory used by the specific processing structure
        // used in the program. Something like:

        rms_delete(dsp->amp[i]);

    }
    free(dsp);
}

/* This function does the actual processing chain. */
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;   /* Variables used to compute the index of samples in input/output arrays. */

    // Add any variables useful to your processing logic here...
    float modval;

    for (i=0; i<framesPerBuffer; i++) {             /* For each sample frame in a buffer size... */
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {      /* For each channel in a frame... */
            index = i * NUMBER_OF_CHANNELS + j;     /* Compute the index of the sample in the arrays... */

            // This is where you want to put your processing logic... A simple thru is:

            dsp->amp_f[j] = rms_process(dsp->amp[j], in[index] * 0.1);
        }
    }
}

/* This function maps midi controller values to our dsp variables. */
void dsp_midi_ctl_in(struct DSP *dsp, int ctlnum, int value) {
    // print it!
    char msg[25];
    sprintf(msg, "cc: %d %d %d", ctlnum, value);
    output_log(msg);

    // You can compare with midi mapping defined in midimap.conf:
    // if (midimap_get("freq") == ctlnum) { ... }
}

/* This function maps midi noteon values to our dsp variables. */
void dsp_midi_note_in(struct DSP *dsp, int pitch, int velocity) {
    // print it!
    char msg[25];
    sprintf(msg, "noteon: %d %d %d", pitch, velocity, midimap_get("60") == pitch);
    output_log(msg);

    // You can compare with midi mapping defined in midimap.conf:
    // if (midimap_get("rec_loop_1") == pitch) { ... }
}

/* This function handles control signals sent by the interface. */
void dsp_handle_signal(struct DSP *dsp, SIGNAL signal) {
    switch (signal) {
        case S_QUIT:
            break;
        case S_RECORD1:
            output_log("Recording loop 1...");
            break;
        case S_RECORD2:
            output_log("Recording loop 2...");
            break;
        case S_RECORD3:
            output_log("Recording loop 3...");
            break;
        case S_RECORD4:
            output_log("Recording loop 4...");
            break;
    }
}

/**********************************************************************************************
 *
 * You shouldn't need to edit anything below here !
 *
 *********************************************************************************************/

/*** Portmidi functions. ***/
/***************************/

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
                    } else if ((status & 0xF0) == 0x90) {
                        int pitch = Pm_MessageData1(buffer.message);
                        int velocity = Pm_MessageData2(buffer.message);
                        dsp_midi_note_in(dsp, pitch, velocity);
                    }
                }
            }
        } while (result);
    }
}

/*** Portaudio functions. ***/
/****************************/

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

/*** ncurses util functions. ***/
/*******************************/

void make_box(int y1, int x1, int y2, int x2) {
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

void draw_meter(struct DSP *dsp) {
    int i, j, dbi, col = 21, row = 3;
    float dbf;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        dbf = 20.0 * log10f(dsp->amp_f[i] + 0.0000001);
        dbf = dbf > 0.0 ? 0.0 : dbf < -72.0 ? -72.0 : dbf;
        dbi = (int)(dbf / 3 + 24);
        mvaddstr(col+i, row, "                        ");
        for (j = 0; j < 24; j++) {
            if (j > dbi)
                break;
            if (j < 20) {
                mvaddch(col+i, row+j, '=' | A_BOLD | COLOR_PAIR(3)); refresh();
            } else if (j < 23) {
                mvaddch(col+i, row+j, '=' | A_BOLD | COLOR_PAIR(2)); refresh();
            } else {
                mvaddch(col+i, row+j, '=' | A_BOLD | COLOR_PAIR(1)); refresh();
            }
        }
    }
}

void repl(struct DSP *dsp) {
    int key, running = 1, polltime = 50;

    while (running) {
        key = getch();
        switch (key) {
            case '1':
                dsp_handle_signal(dsp, S_RECORD1);
                mvaddch(6, 8 + (key - 49) * 5, 'x');
                break;
            case '2':
                dsp_handle_signal(dsp, S_RECORD2);
                mvaddch(6, 8 + (key - 49) * 5, 'x');
                break;
            case '3':
                dsp_handle_signal(dsp, S_RECORD3);
                mvaddch(6, 8 + (key - 49) * 5, 'x');
                break;
            case '4':
                dsp_handle_signal(dsp, S_RECORD4);
                mvaddch(6, 8 + (key - 49) * 5, 'x');
                break;
            case 'q':
                running = 0;
                output_log("Quitting...");
                dsp_handle_signal(dsp, S_QUIT);
                break;
        }

        draw_meter(dsp);

#ifdef _WIN32
        Sleep(polltime);
    }
    Sleep(1000);
#else
        usleep(polltime * 1000);
    }
    usleep(1000000);
#endif
}

void output_log(char *msg) {
    char tmp[25];
    memset(tmp, ' ', 24);
    tmp[24] = '\0';
    mvaddstr(23, 3, tmp);
    strncpy(tmp, msg, 24);
    mvaddstr(23, 3, tmp);
}

void create_window(struct DSP *dsp) {
    int i;

    /* Screen initialization. */
    WINDOW *w = initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(w, TRUE);
    nodelay(w, TRUE);

    /* Set colors if available. */
    start_color();
    if (has_colors()) {
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
    }

    /* Draw static interface components. */
    make_box(1, 1, 24, 30);

    mvaddstr(2, 6, "COLLECTIVE FX BOX !");
    mvaddstr(3, 6, "-------------------");

    mvaddstr(5, 6, "------ LOOPS ------");
    for (i = 0; i < 4; i++) {
        mvaddch(6, 6 + i * 5, 49+i);
        mvaddstr(6, 7 + i * 5, "- -");
    }

    /* Start Read - Eval - Print - Loop. */
    repl(dsp);

    /* Close window. */
    endwin();
}

/*** Main program. ***/
/*********************/

int main(void) {
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
