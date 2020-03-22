/*
    ammodulation.c

    Rémi Hermoso
    Mars 2020
    MUS3329

*/

#include <stdlib.h>
#include <math.h>
#include "modulationam.h"

struct modulationam* modulationam_init(float freq, float sr) {
    struct modulationam *data = malloc(sizeof(struct modulationam));
    data->sr = sr;
    data->freq = freq;
    data->osc = sinosc_init(freq, sr);
    data->inc = freq / sr;
    return data;
}


void modulationam_delete(struct modulationam* data) {
    sinosc_delete(data->osc);
    free(data);
}


float modulationam_process(struct modulationam* data, float input) {
    float out;
    out = sinosc_process(data->osc) * input;
    
    return out;
}

void moadulationam_set_freq(struct modulationam* data, float freq) {
    data->inc = freq / data->sr;
}
