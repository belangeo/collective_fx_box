#include <stdlib.h>
#include <math.h>
#include "sinosc.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

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
