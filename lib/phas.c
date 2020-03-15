#include <stdlib.h>
#include <math.h>
#include "phas.h"

struct phasor *
phasor_init(float freq, float sr) {
    struct phasor *data = malloc(sizeof(struct phasor *));
	data->sr = sr;
    data->x = 0.0;
    data->inc = freq / sr;
    return data;
}

void
phasor_delete(struct phasor *data) {
	free(data);
}

float
phasor_process(struct phasor *data, float input) {
    float value = * data->x;
    data->x += data->inc;
    if (data->x < 0)
        data->x += 1.0;
    else if (data->x >= 1)
        data->x -= 1.0;
    
    return value;
}

void
phasor_set_freq(struct phasor *data, float freq) {
    data->inc = freq / data->sr;
}

void
phasor_reset(struct phasor *data) {
    data->x = 0.0;
