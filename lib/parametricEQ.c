#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parametricEQ.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

/*  
 * Parametric EQ Type enum
 *  - 0 : peak/notch
 *  - 1 : lowshelf
 *  - 2 : highshelf
 *
 * 
*/

static void parametricEQ_compute_peak_coeffs(struct parametricEQ *data)
{
    float amul = data->alpha * data->a;
    float adiv = data->alpha / data->a;
    data->b0 = 1.0 + amul;
    data->b1 = data->a1 = -2.0 * data->c;
    data->b2 = 1.0 - amul;
    data->a0 = 1 + adiv;
    data->a2 = 1 - adiv;

}

static void parametricEQ_compute_ls_coeffs(struct parametricEQ *data)
{
    float sqrt2a = sqrt(data->a * 2.0) * data->alpha;
    float amin1c = (data->a - 1.0) * data->c;
    float aadd1c = (data->a + 1.0) * data->c;
    data->b0 = data->a * ((data->a + 1.0) - amin1c + sqrt2a);
    data->b1 = 2.0 * data->a * ((data->a - 1.0) - aadd1c);
    data->b2 = data->a * ((data->a + 1.0) - amin1c - sqrt2a);
    data->a0 = (data->a + 1.0) + amin1c + sqrt2a;
    data->a1 = -2.0 * ((data->a - 1.0) + aadd1c);
    data->a2 = (data->a + 1.0) + amin1c - sqrt2a;
}

static void parametricEQ_compute_hs_coeffs(struct parametricEQ *data)
{
    float sqrt2a = sqrt(data->a * 2.0) * data->alpha;
    float amin1c = (data->a - 1.0) * data->c;
    float aadd1c = (data->a + 1.0) * data->c;
    data->b0 = data->a * ((data->a + 1.0) + amin1c + sqrt2a);
    data->b1 = -2.0 * data->a * ((data->a - 1.0) + aadd1c);
    data->b2 = data->a * ((data->a + 1.0) + amin1c - sqrt2a);
    data->a0 = (data->a + 1.0) - amin1c + sqrt2a;
    data->a1 = 2.0 * ((data->a - 1.0) - aadd1c);
    data->a2 = (data->a + 1.0) - amin1c - sqrt2a;
}

static void parametricEQ_compute_vars(struct parametricEQ *data, float freq, float q, float gain)
{
    if (freq < 1.0)
    {
        data->freq = 1.0;
    }
    else if (freq > data->nyquist)
    {
        data->freq = data->nyquist;
    }
    else
    {
        data->freq = freq;
    }

    if (q < 0.1)
    {
        data->q = 0.1;
    }else
    {
        data->q = q;
    }

    data->gain = gain;
    data->a = pow(10, gain / 40);
    float w0 = data->twopi * data->freq / data->sr;
    data->c = cos(w0);
    data->alpha = sin(w0) / (2 * data->q);
    switch (data->type){
    case PEAK:
        parametricEQ_compute_peak_coeffs(data);
        break;
    case LOWSHELF:
        parametricEQ_compute_ls_coeffs(data);
        break;
    case HIGHSHELF:
        parametricEQ_compute_hs_coeffs(data);
        break;
    default:
        break;
    }
        
    

}

struct parametricEQ *parametricEQ_init(float freq, float q, float gain, filterT type, float sr)
{
    struct parametricEQ *data = malloc(sizeof(struct parametricEQ));
    data->nyquist = sr * 0.49;
    data->sr = sr;

    if (freq < 1.0)
    {
        freq = 1.0;
    }
    else if (freq > data->nyquist)
    {
        freq = data->nyquist;
    }

    if (q < 0.1)
    {
        q = 0.1;
    }
    data->x1 = data->x2 = data->y1 = data->y2 = 0.0;
    data->twopi = M_PI * 2; 
    data->type = type;
    parametricEQ_compute_vars(data, freq, q, gain);

    return data;
}

void parametricEQ_delete(struct parametricEQ *data)
{
    free(data);
}

float parametricEQ_process(struct parametricEQ *data, float input)
{
    float value;
    value = (data->b0 * input + data->b1 * data->x1 + data->b2 * data->x2 - data->a1 * data->y1 - data->a2 * data->y2) / data->a0;
    data->x2 = data->x1; 
    data->x1 = input; 
    data->y2 = data->y1; 
    data->y1 = value;

    return value;
}

void parametricEQ_set_freq(struct parametricEQ *data, float freq)
{
    // Verfifie si la frequence de "freq" est différente de la derniere.
    if (freq != data->freq){
        parametricEQ_compute_vars(data, freq, data->q, data->gain);
    }
}

void parametricEQ_set_q(struct parametricEQ *data, float q){
    if (q != data->q){
        parametricEQ_compute_vars(data, data->freq, q, data->gain);
    }
}

void parametricEQ_set_gain(struct parametricEQ *data, float gain){
    if (gain != data->gain){ 
        parametricEQ_compute_vars(data, data->freq, data->q, gain);
    }
}

void parametricEQ_set_filterT(struct parametricEQ *data, filterT type){
    data->type = type;
    parametricEQ_compute_vars(data, data->freq, data->q, data->gain);
}