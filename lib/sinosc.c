#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sinosc.h"

struct sinosc * 
sinosc_init(float freq, float sr) {
    struct sinosc *data = malloc(sizeof(struct sinosc));
	data->sr = sr;
    data->inc = freq / sr;
    data->angle = 0.0;
    return data;
}

void
sinosc_delete(struct sinosc *data) {
	free(data);
}

float
sinosc_process(struct sinosc *data) {
    float out = sinf(2.0 * M_PI * data->angle);
    data->angle += data->inc;
    if (data->angle >= 1.0)
        data->angle -= 1.0;
    return out;
}

void
sinosc_set_freq(struct sinosc *data, float freq) {
    data->inc = freq / data->sr;
}
