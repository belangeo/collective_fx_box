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
    return data;
}


void modulationam_delete(struct modulationam* data) {
    free(data);
    sinosc_delete(data->osc);
}


float modulationam_process(struct modulationam* data, float input) {
    float out;
    out = sinosc_process(data->osc) * input;
    
    return out;
}