/*
 * Template file to create a live audio processing program with portaudio, portmidi and ncurses to create a text interface.
 *
 * Compile on linux and MacOS with:
 *  gcc c_fxbox/main_fxbox.c lib/*.c -Ilib -lm -lportaudio -lportmidi -lcurses -o c_apps/main_fxbox
 *
 * Compile on Windows with:
 *  gcc c_fxbox/main_fxbox.c lib/*.c -Ilib -lm -lportaudio -lportmidi -lncurses -o c_apps/main_fxbox.exe
 *
 * Run on linux and MacOS with:
 *  ./c_apps/main_fxbox
 *
 * Run on Windows with:
 *  c_apps\main_fxbox.exe
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
#include <unistd.h>             /* usleep */
#include <curses.h>             /* all ncurses functions. */
#endif

//== Program-specific system includes. ==
// This is where you include the program-specific system headers (if needed) by your program...


#include "portaudio.h"  /* Include all portaudio functions. */
#include "portmidi.h"   /* Include all portmidi functions. */
#include "midimap.h"    /* Include midi mapping functions. */

/* Define global audio parameters, used to setup portaudio. */
#define SAMPLE_RATE         44100
#define FRAMES_PER_BUFFER   1024
#define NUMBER_OF_CHANNELS  2

/* Interface signal constants. */
typedef enum _SIGNAL {S_QUIT, S_RECORD1, S_RECORD2, S_RECORD3, S_RECORD4, S_A, S_B} SIGNAL;

/* Forward declaration of the function for printing messages. */
void output_log(char *msg);

//== Program-specific includes. ==
// This is where you include the specific headers needed by your program...
#include "rms.h"
#include "utils.h"
#include "looper.h"
#include "flanger.h"
#include "moog.h"
#include "delay.h"
#include "dcblock.h"
#include "lp1.h"

//== Program-specific parameters. ==
// This is where you define the specific parameters needed by your program...
#define LOOP_LENGTH_1 1
#define LOOP_LENGTH_2 1
#define LOOP_LENGTH_3 1
#define LOOP_LENGTH_4 1

#define LOOP_RATE_1 1
#define LOOP_RATE_2 1
#define LOOP_RATE_3 1
#define LOOP_RATE_4 1

#define DELAY_1_TIME 0.25
#define DELAY_1_FEED 0.5
#define DELAY_1_GAIN 1.0
#define DELAY_2_TIME 0.01
#define DELAY_2_FEED 0.75
#define DELAY_2_GAIN 0.5
#define DELAY_ROUTING 0

#define FLANGE_MAXDELTIME  0.05
#define FLANGE_CENTERDELAY 0.005
#define FLANGE_FEEDBACK    0.0
#define FLANGE_LFOFREQ     0.1
#define FLANGE_DEPTH       0.5

#define MOOG_FREQ 8000
#define MOOG_RES 0.5

/* The DSP structure contains all needed audio processing "objects". */
struct DSP {
    // This is where you declare the specific processing structures
    // needed by your program...

    struct rms *amp[NUMBER_OF_CHANNELS];
    float amp_f[NUMBER_OF_CHANNELS];

    int bank;               // Banque A (0) ou B (1) pour créer des groupes de CC MIDI.
    float mic_gain;
    float delay_routing;    // Interpolation entre routing parallèle et routing en série.
    float loop_gain_1, loop_gain_2, loop_gain_3, loop_gain_4;

    float delay1_time, delay1_feed, delay1_gain;
    float delay2_time, delay2_feed, delay2_gain;

    struct looper *loop1[NUMBER_OF_CHANNELS];
    struct looper *loop2[NUMBER_OF_CHANNELS];
    struct looper *loop3[NUMBER_OF_CHANNELS];
    struct looper *loop4[NUMBER_OF_CHANNELS];

    // Corrige le DC avant d'entrer dans les délais récursifs.
    struct dcblock *dcblk[NUMBER_OF_CHANNELS];

    // Portamento sur les temps de délai.
    struct lp1 *delay1_time_p[NUMBER_OF_CHANNELS];
    struct lp1 *delay2_time_p[NUMBER_OF_CHANNELS];

    struct delay *delay1[NUMBER_OF_CHANNELS];
    struct delay *delay2[NUMBER_OF_CHANNELS];

    struct flanger *flange[NUMBER_OF_CHANNELS];
    struct moog *lowpass[NUMBER_OF_CHANNELS];
};

/* This function allocates memory and intializes all dsp structures. */
struct DSP * dsp_init() {
    int i;

    struct DSP *dsp = malloc(sizeof(struct DSP));   /* Memory allocation for DSP structure. */

    dsp->bank = 0;
    dsp->mic_gain = 0.0;
    dsp->delay_routing = DELAY_ROUTING;
    dsp->loop_gain_1 = dsp->loop_gain_2 = dsp->loop_gain_3 = dsp->loop_gain_4 = 1.0;

    dsp->delay1_time = DELAY_1_TIME; dsp->delay1_feed = DELAY_1_FEED; dsp->delay1_gain = DELAY_1_GAIN;
    dsp->delay2_time = DELAY_2_TIME; dsp->delay2_feed = DELAY_2_FEED; dsp->delay2_gain = DELAY_2_GAIN;

    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you setup the specific processing structures needed by your program,
        // using the provided xxx_init functions.

        dsp->amp[i] = rms_init(FRAMES_PER_BUFFER);

        dsp->loop1[i] = looper_init(LOOP_LENGTH_1, LOOP_RATE_1, SAMPLE_RATE);
		dsp->loop2[i] = looper_init(LOOP_LENGTH_2, LOOP_RATE_2, SAMPLE_RATE);
		dsp->loop3[i] = looper_init(LOOP_LENGTH_3, LOOP_RATE_3, SAMPLE_RATE);
		dsp->loop4[i] = looper_init(LOOP_LENGTH_4, LOOP_RATE_4, SAMPLE_RATE);

        dsp->dcblk[i] = dcblock_init();

        // Fréquence de 1 Hz, filtres utilisés pour lisser la valeur des temps de délai.
        dsp->delay1_time_p[i] = lp1_init(1, SAMPLE_RATE);
        dsp->delay2_time_p[i] = lp1_init(1, SAMPLE_RATE);

        dsp->delay1[i] = delay_init(1.0, SAMPLE_RATE);
        dsp->delay2[i] = delay_init(1.0, SAMPLE_RATE);

        dsp->flange[i] = flanger_init(FLANGE_CENTERDELAY, FLANGE_DEPTH, FLANGE_LFOFREQ, FLANGE_FEEDBACK, SAMPLE_RATE);
        dsp->lowpass[i] = moog_init(MOOG_FREQ, MOOG_RES, SAMPLE_RATE);
    }

    return dsp;
}

/* This function releases memory used by all dsp structures. */
void dsp_delete(struct DSP *dsp) {
    int i;
    for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
        // This is where you release the memory used by the specific processing structure
        // used in the program.

        rms_delete(dsp->amp[i]);

        looper_delete(dsp->loop1[i]);
		looper_delete(dsp->loop2[i]);
		looper_delete(dsp->loop3[i]);
		looper_delete(dsp->loop4[i]);

        dcblock_delete(dsp->dcblk[i]);

        lp1_delete(dsp->delay1_time_p[i]);
        lp1_delete(dsp->delay2_time_p[i]);

        delay_delete(dsp->delay1[i]);
        delay_delete(dsp->delay2[i]);

        flanger_delete(dsp->flange[i]);
        moog_delete(dsp->lowpass[i]);
    }
    free(dsp);
}

/* This function does the actual processing chain. */
void dsp_process(const float *in, float *out, unsigned long framesPerBuffer, struct DSP *dsp) {
    unsigned int i, j, index;   /* Variables used to compute the index of samples in input/output arrays. */

    // Add any variables useful to your processing logic here...
    float loopmix, del1val, del2val, delsum, delout;

    for (i=0; i<framesPerBuffer; i++) {             /* For each sample frame in a buffer size... */
        for (j=0; j<NUMBER_OF_CHANNELS; j++) {      /* For each channel in a frame... */
            index = i * NUMBER_OF_CHANNELS + j;     /* Compute the index of the sample in the arrays... */

            // This is where you want to put your processing logic...
            loopmix = looper_process(dsp->loop1[j], in[index]) * dsp->loop_gain_1 +
                      looper_process(dsp->loop2[j], in[index]) * dsp->loop_gain_2 +
                      looper_process(dsp->loop3[j], in[index]) * dsp->loop_gain_3 +
                      looper_process(dsp->loop4[j], in[index]) * dsp->loop_gain_4 +
                      in[index] * dsp->mic_gain;

            loopmix = dcblock_process(dsp->dcblk[j], loopmix);

            // Lecture dans les lignes de délai.
            del1val = delay_read(dsp->delay1[j], lp1_process(dsp->delay1_time_p[j], dsp->delay1_time)) * dsp->delay1_gain;
            del2val = delay_read(dsp->delay2[j], lp1_process(dsp->delay2_time_p[j], dsp->delay2_time)) * dsp->delay2_gain;

            // Le premier délai reçoit toujours le signal mic + loops.
            delay_write(dsp->delay1[j], loopmix + del1val * dsp->delay1_feed);
            // Le second délai reçoit l'interpolation entre mic+loops (routing parallèle) et la sortie du premier délai (routing en série).
            delay_write(dsp->delay2[j], (loopmix + (del1val - loopmix) * dsp->delay_routing) + del2val * dsp->delay2_feed);

            // La sortie des délais est l'interpolation entre la sum des deux (routing parallèle) et la sortie du second (routing en série).
            delsum = del1val + del2val;
            delout = delsum + (del2val - delsum) * dsp->delay_routing;

            out[index] = flanger_process(dsp->flange[j], delout);
            out[index] = moog_process(dsp->lowpass[j], out[index]);

            dsp->amp_f[j] = rms_process(dsp->amp[j], out[index]);
        }
    }
}

/* This function maps midi controller values to our dsp variables. */
void dsp_midi_ctl_in(struct DSP *dsp, int ctlnum, int value) {
    int i;
    float fvalue = (float)value;
    // Banque A.
    if (dsp->bank == 0) {
        if (ctlnum == midimap_get("loop_pitch1")) {
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_pitch(dsp->loop1[i], fvalue / 64.0); }
        } else if (ctlnum == midimap_get("loop_pitch2")) {
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_pitch(dsp->loop2[i], fvalue / 64.0); }
        } else if (ctlnum == midimap_get("loop_pitch3")) {
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_pitch(dsp->loop3[i], fvalue / 64.0); }
        } else if (ctlnum == midimap_get("loop_pitch4")) {
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_pitch(dsp->loop4[i], fvalue / 64.0); }
        } else if (ctlnum == midimap_get("loop_gain1")) {
            dsp->loop_gain_1 = fvalue / 64.0;
        } else if (ctlnum == midimap_get("loop_gain2")) {
            dsp->loop_gain_2 = fvalue / 64.0;
        } else if (ctlnum == midimap_get("loop_gain3")) {
            dsp->loop_gain_3 = fvalue / 64.0;
        } else if (ctlnum == midimap_get("loop_gain4")) {
            dsp->loop_gain_4 = fvalue / 64.0;
        } else if (ctlnum == midimap_get("mic_gain")) {
            dsp->mic_gain = fvalue / 127.0;
        } else if (ctlnum == midimap_get("flange")) {
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) {
                flanger_set_freq(dsp->flange[i], (1 - (fvalue / 127.0)) * 0.2 + 0.005);
                flanger_set_depth(dsp->flange[i], fvalue / 128.0);
                flanger_set_feedback(dsp->flange[i], fvalue / 192.0);
            }
        }
        // Banque B.
        else if (ctlnum == midimap_get("lowpass_freq")) {
            fvalue = scale(fvalue, 0.0, 127.0, 100.0, 15000.0, 3.0);
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { moog_set_freq(dsp->lowpass[i], fvalue); }
        }
    } else if (dsp->bank == 1) {
        if (ctlnum == midimap_get("delay1_time")) {
            dsp->delay1_time = fvalue / 128.0;
        } else if (ctlnum == midimap_get("delay1_feed")) {
            dsp->delay1_feed = fvalue / 128.0;
        } else if (ctlnum == midimap_get("delay1_gain")) {
            dsp->delay1_gain = fvalue / 128.0;
        } else if (ctlnum == midimap_get("delay2_time")) {
            dsp->delay2_time = fvalue / 128.0;
        } else if (ctlnum == midimap_get("delay2_feed")) {
            dsp->delay2_feed = fvalue / 128.0;
        } else if (ctlnum == midimap_get("delay2_gain")) {
            dsp->delay2_gain = fvalue / 128.0;
        } else if (ctlnum == midimap_get("delay_routing")) {
            dsp->delay_routing = fvalue / 127.0;
        }
    }
}

/* This function maps midi noteon values to our dsp variables. */
void dsp_midi_note_in(struct DSP *dsp, int pitch, int velocity) {
    // You can compare with midi mapping defined in midimap.conf:
    // if (midimap_get("rec_loop_1") == pitch) { ... }
    int i;
    if (pitch == midimap_get("rec_loop_1")) {
        output_log("Recording loop 1...\0");
        for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop1[i]); }
    } else if (pitch == midimap_get("rec_loop_2")) {
        output_log("Recording loop 2...\0");
        for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop2[i]); }
    } else if (pitch == midimap_get("rec_loop_3")) {
        output_log("Recording loop 3...\0");
        for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop3[i]); }
    } else if (pitch == midimap_get("rec_loop_4")) {
        output_log("Recording loop 4...\0");
        for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop4[i]); }
    }
}

/* This function handles control signals sent by the interface. */
void dsp_handle_signal(struct DSP *dsp, SIGNAL signal) {
    int i;
    switch (signal) {
        case S_QUIT:
            break;
        case S_RECORD1:
            output_log("Recording loop 1...\0");
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop1[i]); }
            break;
        case S_RECORD2:
            output_log("Recording loop 2...\0");
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop2[i]); }
            break;
        case S_RECORD3:
            output_log("Recording loop 3...\0");
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop3[i]); }
            break;
        case S_RECORD4:
            output_log("Recording loop 4...\0");
            for (i = 0; i < NUMBER_OF_CHANNELS; i++) { looper_controls(dsp->loop4[i]); }
            break;
        case S_A:
            output_log("Switching to bank A\0");
            dsp->bank = 0;
            break;
        case S_B:
            output_log("Switching to bank B\0");
            dsp->bank = 1;
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
                    PaStreamCallbackFlags statusFlags, void *userData) {
    const float *in = (const float *)inputBuffer;
    float *out = (float *)outputBuffer;
    /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;

    struct DSP *dsp = (struct DSP *) userData;

    if (pm_initialized == 1) {
        handle_midi_input(dsp);
    }

    dsp_process(in, out, framesPerBuffer, dsp);
    
    return paContinue;
}

int paErrorCheck(PaError err) {
    if (err != paNoError) {
        Pa_Terminate();
        fprintf(stderr,  Pa_GetErrorText(err));
        return 1;
    }
    return 0;
}

int paDefaultDeviceCheck(PaDeviceIndex device, char *direction) {
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
            case 'a':
                dsp_handle_signal(dsp, S_A);
                break;
            case 'b':
                dsp_handle_signal(dsp, S_B);
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
