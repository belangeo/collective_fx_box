/*
Remi Coulombe
tanh / atan disto
*/
#ifndef __DISTO_H__
#define __DISTO_H__

#include "../../../../lib/distoFiltr.h"


#ifdef __cplusplus
extern "C" {
#endif

struct disto {
	float drive;
	float mix;
	struct distoFltr* filter;
	float freq;
	float sr;
	float q;
};

struct disto * disto_init(float drive, float mix, float freq, float q, float sr);

void disto_delete(struct disto *data);

float disto_process(struct disto *data, float input);

void disto_set_drive(struct disto *data, float newDrive);

void disto_set_mix(struct disto *data, float mix);

void disto_set_freq(struct disto *data, float newFreq);

void disto_set_q(struct disto *data, float newQ);

#ifdef __cplusplus
}
#endif

#endif