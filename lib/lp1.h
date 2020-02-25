#ifndef __LP1_H__
#define __LP1_H__

struct lp1 {
    float sr;
    float nyquist;
    float lastout;
    float coeff;
};

struct lp1 * lp1_init(float freq, float sr);

void lp1_delete(struct lp1 *data);

float lp1_process(struct lp1 *data, float input);

void lp1_set_freq(struct lp1 *data, float freq);

#endif