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
	double a0, a1, a2;
	double b1, b2;
	float in0, in1, in2;
	float out0, out1, out2;
	float norm;
	float lastout;
	float q;
};

struct distoFltr* distoFltr_init(float freq, float sr, float q);

void distoFltr_delete(struct distoFltr* data);

float distoFltr_process(struct distoFltr* data, float input);

void distoFltr_set_params(struct distoFltr* data, float freq, float q);

#endif