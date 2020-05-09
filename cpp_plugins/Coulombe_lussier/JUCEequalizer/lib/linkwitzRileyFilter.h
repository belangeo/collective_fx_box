#ifndef __LINKWITZRILEYFILTER_H__
#define __LINKWITZRILEYFILTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "compress.h"
// 4th order Linkwitz-Riley Filter for crossover
typedef enum {
	LOWPASS = 0,
	HIGHPASS = 1,
	CROSS = 2
} filterEQT;

struct filter {
    float freq, sr;
	float fpi;
	float wc, wc2, wc22;
	float k, k2, k22;
	float wck, tmpk;
    float pi_over_sr;
    float nyquist;
    float sqrt_2;
    float x0_lp, x1_lp, y1_lp, y2_lp;
	float x0_hp, x1_hp, y1_hp, y2_hp;
    float a0_lp, a1_lp, a2_lp, a0_hp, a1_hp, a2_hp, b1, b2;
    float last_freq;
	float outGain;
	filterEQT type;
	struct compress* comp;
};

struct filter * filter_init(float freq, float sr, filterEQT type, float thresh, float ratio, float att, float rel, float look, float outGain);

void filter_delete(struct filter *data);

float filter_process(struct filter *data, float input);

void filter_set_freq(struct filter *data, float freq);

void filter_set_compThresh(struct filter *data, float thresh);

void filter_set_outGain(struct filter *data, float gain);

#ifdef __cplusplus
}
#endif

#endif