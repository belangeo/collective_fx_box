/*
	distoFiltr.h

	Antoine Lussier - Rémi Coulombe
	25 février 2020
	MUS3329

	http://www.musicdsp.org/en/latest/Filters/38-lp-and-hp-filter.html

*/
#ifndef __DISTO_FILTER__
#define __DISTO_FILTER__

struct distoFltr {
    float sr;
    float nyquist;
	float cutoff;
	float a1, a2, a3;
	float b1, b2, b3;
	float in0, in1, in2;
	float out0, out1, out2;
	float res;
	float lastout;
};

struct distoFltr* distoFltr_init(float freq, float sr);

void distoFltr_delete(struct distoFltr* data);

float distoFltr_process(struct distoFltr* data, float input);

void distoFltr_set_params(struct distoFltr* data, float freq);

#endif