#include <stdlib.h>
#include <stdio.h>
#include "delay.h"
#include "utils.h"

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
    float frac, samples, readpos;
    samples = deltime * data->sr;
    readpos = data->writepos - samples;
    if (readpos < 0) {
        readpos += data->maxsize;
    } else if (readpos >= data->maxsize) {
        readpos -= data->maxsize;
    }
    ipos = (int)readpos;
    frac = readpos - ipos;
    return cubic(data->buffer, ipos, frac, data->maxsize);
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
