#include <stdlib.h>
#include <math.h>
#include "moog.h"

static void moog_compute_coeffs(struct moog *data)
{
    if (data->freq < 0.1)
        data->freq = 0.1;
    else if (data->freq > data->nyquist)
        data->freq = data->nyquist;
    if (data->res < 0.0)
        data->res = 0.0;
    else if (data->res > 2.0)
        data->res = 2.0;

    float f = 2.0 * data->freq / data->sr;
    float fi = 1.0 - f;
    data->p = f * (1.8 - 0.8 * f);
    data->k = 2.0 * sinf(f * M_PI * 0.5) - 1.0;
    float t = (1.0 - data->p) * 1.386249;
    float t2 = 12.0 + t * t;
    data->r = data->res * 0.5 * (t2 + 6.0 * t) / (t2 - 6.0 * t);
    data->r *= fi * fi * fi * 0.9 + 0.1;
}

struct moog * moog_init(float freq, float res, float sr) 
{
    struct moog *data = malloc(sizeof(struct moog));
    data->sr = sr;
    data->nyquist = sr * 0.5;
    data->freq = freq;
    data->res = res;
    data->x1 = data->y1 = data->y2 = data->y3 = data->y4 = data->oldx1 = data->oldy1 = data->oldy2 = data->oldy3 = 0.0;
    moog_compute_coeffs(data);

    return data;
}

void moog_delete(struct moog *data) 
{
    free(data);
}

float moog_process(struct moog *data, float input) 
{
    data->x1 = input - data->r * data->y4;
    data->y1 = (data->x1 + data->oldx1) * data->p - data->k * data->y1;
    data->y2 = (data->y1 + data->oldy1) * data->p - data->k * data->y2;
    data->y3 = (data->y2 + data->oldy2) * data->p - data->k * data->y3;
    data->y4 = (data->y3 + data->oldy3) * data->p - data->k * data->y4;
    data->y4 -= (data->y4 * data->y4 * data->y4) * 0.16666666666666666;
    data->oldx1 = data->x1; data->oldy1 = data->y1; data->oldy2 = data->y2; data->oldy3 = data->y3;

    return data->y4;
}

void moog_set_freq(struct moog *data, float freq)
{
    if (freq != data->freq)
        data->freq = freq;
        moog_compute_coeffs(data);
}

void moog_set_res(struct moog *data, float res) 
{
    if (res != data->res)
        data->res = res;
        moog_compute_coeffs(data);
}