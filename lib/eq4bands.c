#include <stdlib.h>
#include <stdio.h>
#include "eq4bands.h"

struct eq4Bands * eq4Bands_init(float freq_ls, float q_ls, float gain_ls,
                                float freq_n1, float q_n1, float gain_n1,
                                float freq_n2, float q_n2, float gain_n2,
                                float freq_hs, float q_hs, float gain_hs, float sr){


    struct eq4Bands *data = malloc(sizeof(struct eq4Bands));

    data->lsBand = parametricEQ_init(freq_ls, q_ls, gain_ls, LOWSHELF, sr);
    data->n1Band = parametricEQ_init(freq_n1, q_n1, gain_n1, NOTCH, sr);
    data->n2Band = parametricEQ_init(freq_n2, q_n2, gain_n2, NOTCH, sr);
    data->hsBand = parametricEQ_init(freq_hs, q_hs, gain_hs, HIGHSHELF, sr);

    return data;

}

dampdelay_delete(struct eq4Bands *data) {
    parametricEQ_delete(data->lsBand);
    parametricEQ_delete(data->n1Band);
    parametricEQ_delete(data->n2Band);
    parametricEQ_delete(data->hsBand);

    free(data);
}

void eq4Bands_process(struct eq4Bands *data, float input){
    float v1, v2, v3, v4;
    
    v1 = parametricEQ_process(data->lsBand, input);
    v2 = parametricEQ_process(data->n1Band, input);
    v3 = parametricEQ_process(data->n2Band, input);
    v4 = parametricEQ_process(data->hsBand, input);

    return v1 + v2 + v3 + v4;
}

void eq4Bands_set_freq(struct parametricEQ *data, float freq){
    if (freq != data->freq)
        parametricEQ_set_freq(data, freq);
}

void eq4Bands_set_q(struct parametricEQ *data, float q){
    if (q != data->q)
        parametricEQ_set_q(data, q);
}

void eq4Bands_set_gain(struct parametricEQ *data, float gain){
    if (gain != data->gain)
        parametricEQ_set_q(data, gain);
}

void eq4Bands_set_filterT(struct parametricEQ *data, filterT type){
    if (type != data->type)
        parametricEQ_set_q(data, type);
}