#include <stdlib.h>
#include <math.h>
#include "flanger.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

/*sinosc*/
struct sinosc * 
sinosc_init(float freq, float sr) {
    struct sinosc *data = malloc(sizeof(struct sinosc));
	data->sr = sr;
    data->angle = 0.0;
    data->inc = freq / sr;
    return data;
}

void
sinosc_delete(struct sinosc *data) {
	free(data);
}

float
sinosc_process(struct sinosc *data) {
    float value = sinf(2 * M_PI * data->angle);
    data->angle += data->inc;
    if (data->angle >= 1.0)
        data->angle -= 1.0;
    return value;
}

void
sinosc_set_freq(struct sinosc *data, float freq) {
    data->inc = freq / data->sr;
}

void
sinosc_reset(struct sinosc *data) {
    data->angle = 0.0;
}

/*lp1*/
struct lp1 * 
lp1_init(float freq, float sr) {
    struct lp1 *data = malloc(sizeof(struct lp1));
	data->sr = sr;
    data->lastout = 0.0;
    data->coeff = expf(-2.0 * M_PI * freq / sr);
    return data;
}

void
lp1_delete(struct lp1 *data) {
	free(data);
}

float
lp1_process(struct lp1 *data, float input) {
    data->lastout = input + (data->lastout - input) * data->coeff;
    return data->lastout;
}

void
lp1_set_freq(struct lp1 *data, float freq) {
    data->coeff = expf(-2.0 * M_PI * freq / data->sr);
}


/*Delay*/
struct delay * 
delay_init(float maxdur, float sr) {
    struct delay *data = malloc(sizeof(struct delay));
	data->sr = sr;
    data->maxsize = (long)(maxdur * sr + 0.5);
    data->writepos = 0;
    data->buffer = (float *)calloc(data->maxsize + 1, sizeof(float));
    return data;
}

void 
delay_delete(struct delay *data) {
    free(data->buffer);
    free(data);
}

float
delay_read(struct delay *data, float deltime) {
    int ipos;
    float frac, samples, readpos, previous, next;
    samples = deltime * data->sr;
    readpos = data->writepos - samples;
    if (readpos < 0) {
        readpos += data->maxsize;
    } else if (readpos >= data->maxsize) {
        readpos -= data->maxsize;
    }
    ipos = (int)readpos;
    frac = readpos - ipos;
    previous = data->buffer[ipos];
    next = data->buffer[ipos + 1];
    return previous + (next - previous) * frac;
}

void
delay_write(struct delay *data, float input) {
    data->buffer[data->writepos] = input;
    if (data->writepos == 0) {
        data->buffer[data->maxsize] = input;
    }
    data->writepos++;
    if (data->writepos == data->maxsize) {
        data->writepos = 0;
    }
}

