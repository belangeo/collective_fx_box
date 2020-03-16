/*
	distoFiltr.c

	Antoine Lussier - Rémi Coulombe
	25 février 2020
	MUS3329

	biquad filter for waveshaper
*/

#include <stdlib.h>
#include <math.h>
#include "distoFiltr.h"

#ifndef M_PI
#define M_PI (3.1415926)
#endif


static void coeff_process(struct distoFltr* data, float freq, float q) {
	// cutoff verification
	if (freq > data->nyquist){ data->cutoff = data->nyquist; }
	else if (freq < 20) { data->cutoff = 20; }
	else{ data->cutoff = freq; }
		
	// resonance verification
	if (q > 7) {data->q = 7;}
	else if (q < 0.5) {data->q = 0.5;}
	else {data->q = q;}

	float k = 1.0 / tan(M_PI * data->cutoff / data->sr);
	/*---*/
	data->a0 = 1.0 / (1.0 + data->q * k + k * k);
	data->a1 = 2 * data->a0;
	data->a2 = data->a0;
	data->b1 = 2.0 * (1.0 - k * k) * data->a0;
	data->b2 = (1.0 - data->q * k + k * k) * data->a0;
	//float k = tan(M_PI * data->cutoff);
	/*
	data->norm = 1.0 / (1.0 + k / data->q + k * k);
	data->a0 = k * k * data->norm;
	data->a1 = 2.0 * data->a0;
	data->a2 = data->a0;
	data->b1 = 2.0 * (k * k - 1) * data->norm;
	data->b2 = (1 - k / data->q + k * k) * data->norm;
	*/
}

struct distoFltr* distoFltr_init(float freq, float sr, float q){
	struct distoFltr *data = malloc(sizeof(struct distoFltr));
	data->sr = sr;
	data->nyquist = sr * 0.499;
	data->q = q;
	data->norm;
	data->in0 = data->in1 = data->in2 = data->out0 = data->out1 = data->out2 = 0.0;
	coeff_process(data, freq, q);
	return data;
}

void distoFltr_delete(struct distoFltr* data){
	free(data);
}

float distoFltr_process(struct distoFltr* data, float input){
	double dataA0 = data->a0 * input;
	double dataA1 = data->a1 * data->in1;
	double dataA2 = data->a2 * data->in2;
	double dataB1 = data->b1 * data->out1;
	double dataB2 = data->b2 * data->out2;
	double output = dataA0 + dataA1 + dataA2 - dataB1 - dataB2;

	data->in2 = data->in1;
	data->in1 = input;
	data->out2 = data->out1;
	data->out1 = output;
	return output;
}

void distoFltr_set_Cutoff(struct distoFltr* data, float freq) {
	if (freq != data->lastout) {
		data->lastout = freq;
		coeff_process(data, freq, data->q);
	}
}

void distoFltr_set_Q(struct distoFltr* data, float q) {
	if (q != data->q) {
		data->q = q;
		coeff_process(data, data->cutoff, q);
	}
}

