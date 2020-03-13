/*
	distoFiltr.c

	Antoine Lussier - Rémi Coulombe
	25 février 2020
	MUS3329

*/

#include <stdlib.h>
#include <math.h>
#include "distoFiltr.h"

struct distoFltr* distoFltr_init(float freq, float sr, float q){
	struct distoFltr* data = malloc(sizeof(struct distoFltr));
	data->sr = sr;
	data->nyquist = sr * 0.499;
	data->lastout = 0.0;
	data->in0 = 0;
	data->in1 = 0;
	data->in2 = 0;
	data->out1 = 0;
	data->out2 = 0;
	data->q = q;
	data->norm;

	return data;
}

void distoFltr_delete(struct distoFltr* data){
	free(data);
}

static void coeff_process(struct distoFltr* data, float freq, float q) {
	// cutoff verification
	if (freq > data->nyquist) {
		data->cutoff = data->nyquist;
	}
	else if (freq < 20) {
		data->cutoff = 20;
	}
	else {
		data->cutoff = freq;
	}

	// cutoff verification
	if (q > 7) {
		data->q = 7;
	}
	else if (q < 0.5) {
		data->q = 0.5;
	}
	else {
		data->q = q;
	}
	// calculation of coefficients
	float c = 1.0 / tan(M_PI * data->cutoff / data->sr);
	data->norm = 1.0 / (1.0 + data->q / data->q + (c * c));
	data->a0 = c * c * data->norm;
	data->a1 = 2.0 * data->a0;
	data->a2 = data->a0;
	data->b1 = 2.0 * (c * c - 1) * data->norm;
	data->b2 = (1 - c / data->q + c * c) * data->norm;
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

void distoFltr_set_params(struct distoFltr* data, float freq, float q){
	coeff_process(data, freq, q);
}