/*
	distoFiltr.c

	Antoine Lussier - Rémi Coulombe
	25 février 2020
	MUS3329

*/

#include <stdlib.h>
#include <math.h>
#include "distoFiltr.h"

struct distoFltr* distoFltr_init(float freq, float sr){
	struct distoFltr* data = malloc(sizeof(struct distoFltr));
	data->sr = sr;
	data->nyquist = sr * 0.499;
	data->lastout = 0.0;
	data->in0 = 0;
	data->in1 = 0;
	data->in2 = 0;
	data->out1 = 0;
	data->out2 = 0;
	data->res = 2;

	return data;
}

void distoFltr_delete(struct distoFltr* data){
	free(data);
}

static void coeff_process(struct distoFltr* data, float freq) {
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
	// calculation of coefficients
	float c = 1.0 / tan(M_PI * data->cutoff / data->sr);
	data->a1 = 1.0 / (1.0 + data->res * c + (c * c));
	data->a2 = 2.0 * data->a1;
	data->a3 = data->a1;
	data->b1 = 2.0 * (1.0 - (c * c)) * data->a1;
	data->b2 = (1.0 - (data->res * c) + (c * c));
}

float distoFltr_process(struct distoFltr* data, float input){
	float dataA1 = data->a1 * input;
	float dataA2 = data->a2 * data->in1;
	float dataA3 = data->a3 * data->in2;
	float dataB1 = data->b1 * data->out1;
	float dataB2 = data->b2 * data->out2;
	float output = dataA1 + dataA2 + dataA3 - dataB1 - dataB2;

	data->in2 = data->in1;
	data->in1 = input;
	data->out2 = data->out1;
	data->out1 = output;

	return output;
}

void distoFltr_set_params(struct distoFltr* data, float freq){
	coeff_process(data, freq);
}