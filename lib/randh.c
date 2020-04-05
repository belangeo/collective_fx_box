#include <stdlib.h>
#include <math.h>
#include <time.h>   /* time */
#include "randh.h"

struct randh * 
randh_init(float freq, float min, float max, float sr) {
    struct randh *data = malloc(sizeof(struct randh));
    srand((unsigned int)time(NULL));
	data->sr = sr;
    data->angle = 0.0;
    data->inc = freq / sr;
    min = 10;
    max = 1000;
    return data;
}

void
randh_delete(struct randh *data) {
	free(data);
}

float
randh_process(struct randh *data) {
    data->angle += data->inc;
    if (data->angle >= 1.0) {
        data->angle -= 1.0;
        data->output = (rand() / (float)RAND_MAX) * 2 - 1;
    }
    return data->output;
}

void
randh_set_freq(struct randh *data, float freq) {
    data->inc = freq / data->sr;
}