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

void eq4Bands_delete(struct eq4Bands *data)
{
    parametricEQ_delete(data->lsBand);
    parametricEQ_delete(data->n1Band);
    parametricEQ_delete(data->n2Band);
    parametricEQ_delete(data->hsBand);

    free(data);
}

float eq4Bands_process(struct eq4Bands *data, float input){
    float value;
    value = parametricEQ_process(data->lsBand, input);
    value = parametricEQ_process(data->n1Band, value);
    value = parametricEQ_process(data->n2Band, value);
    value = parametricEQ_process(data->hsBand, value);

    return value;
}

void eq4Bands_set_freq(struct eq4Bands *data, float freq, bandSelect band)
{
    switch (band){
    case BAND_LOWSHELF:
        if (freq != data->lsBand->freq)
            parametricEQ_set_freq(data->lsBand, freq);
        break;
    case BAND_NOTCH1:
        if (freq != data->n1Band->freq)
            parametricEQ_set_freq(data->n1Band, freq);
        break;
    case BAND_NOTCH2:
        if (freq != data->n2Band->freq)
            parametricEQ_set_freq(data->n2Band, freq);
        break;
    case BAND_HIGHSHELF:
        if (freq != data->hsBand->freq)
            parametricEQ_set_freq(data->hsBand, freq);
        break;
    default:
        break;
    }
    
}

void eq4Bands_set_q(struct eq4Bands *data, float q, bandSelect band)
{
    switch (band)
    {
    case BAND_LOWSHELF:
        if (q != data->lsBand->q)
            parametricEQ_set_q(data->lsBand, q);
        break;
    case BAND_NOTCH1:
        if (q != data->n1Band->q)
            parametricEQ_set_q(data->n1Band, q);
        break;
    case BAND_NOTCH2:
        if (q != data->n2Band->q)
            parametricEQ_set_q(data->n2Band, q);
        break;
    case BAND_HIGHSHELF:
        if (q != data->hsBand->q)
            parametricEQ_set_q(data->hsBand, q);
        break;
    default:
        break;
    }
}

void eq4Bands_set_gain(struct eq4Bands *data, float gain, bandSelect band)
{
    switch (band)
    {
    case BAND_LOWSHELF:
        if (gain != data->lsBand->gain)
            parametricEQ_set_gain(data->lsBand, gain);
        break;
    case BAND_NOTCH1:
        if (gain != data->n1Band->gain)
            parametricEQ_set_gain(data->n1Band, gain);
        break;
    case BAND_NOTCH2:
        if (gain != data->n2Band->gain)
            parametricEQ_set_gain(data->n2Band, gain);
        break;
    case BAND_HIGHSHELF:
        if (gain != data->hsBand->gain)
            parametricEQ_set_gain(data->hsBand, gain);
        break;
    default:
        break;
    }
}

