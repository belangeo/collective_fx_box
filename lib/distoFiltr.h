/*
	distoFiltr.h

	Antoine Lussier - R�mi Coulombe
	25 f�vrier 2020
	MUS3329

	biquad filter for waveshaper
*/
#ifndef __DISTO_FILTER__
#define __DISTO_FILTER__

#ifdef __cplusplus
extern "C" {
#endif

struct distoFltr {
    float sr;
    float nyquist;
	float q;
	float cutoff;
	double a0, a1, a2, b1, b2;
	float in0, in1, in2;
	float out0, out1, out2;
	float norm;
	float lastout;
	
};
float distoFltr_process(struct distoFltr* data, float input);

struct distoFltr* distoFltr_init(float freq, float sr, float q);

void distoFltr_delete(struct distoFltr* data);

void distoFltr_set_Cutoff(struct distoFltr* data, float freq);

void distoFltr_set_Q(struct distoFltr* data, float q);

#ifdef __cplusplus
}
#endif

#endif