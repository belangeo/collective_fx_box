/*
Remi Coulombe
-24dB/oct filters crossover for de-esser
Possibility of using just lop/hip, even if it's completely useless

ok c'est brisé un peu mais bon...
*/

#include <stdlib.h>
#include <math.h>
#include "linkwitzRileyFilter.h"
//#include "compress.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


static float filter_compute_lop(struct filter *data, float input) {
	float lop_out;
	lop_out = data->a0_lp * input + data->x0_lp;
	data->x0_lp = data->a1_lp * input - data->b1 * lop_out + data->x1_lp;
	data->x1_lp = data->a2_lp * input - data->b2 * lop_out;
	return lop_out;
}
static float filter_compute_hip(struct filter *data, float input) {
	float hip_out;
	hip_out = data->a0_hp * input + data->x0_hp;
	data->x0_hp = data->a1_hp * input - data->b1 * hip_out + data->x1_hp;
	data->x1_hp = data->a2_hp * input - data->b2 * hip_out;
	return hip_out;
}
static float filter_compute_cross(struct filter *data, float input) {
	float deesserIO, lop_out;
	lop_out = filter_compute_lop(data, input);
	deesserIO = compress_process(data->comp, filter_compute_hip(data, input) * -1) * data->outGain;
	// invert phase
	//return lop_out + (deesserIO * -1);
	return lop_out + deesserIO;
	//float filtered = filter_compute_hip(data, compress_process(data->comp, input));
}

static void filter_compute_coeffs(struct filter *data, float freq) {
	if (freq > 16000.0f) {
		data->freq = 16000.0f;
	}
	else if (freq < 2000.0f) {
		data->freq = 2000.0f;
	}
	else {
		data->freq = freq;
	}

	data->fpi = M_PI * data->freq;
	data->wc = data->fpi * 2;
	data->wc2 = data->wc * data->wc;
	data->wc22 = data->wc2 * 2;
	data->k = data->wc / tanf(data->fpi / data->sr);
	data->k2 = data->k * data->k;
	data->k22 = data->k2 * 2;
	data->wck = 2 * data->wc * data->k;
	data->tmpk = data->k2 + data->wc2 + data->wck;
	data->b1 = ((-1 * data->k22) + data->wc22) / data->tmpk;
	data->b2 = ((-1 * data->wck) + data->k2 + data->wc2) / data->tmpk;
	// lop
	data->a0_lp = data->wc2 / data->tmpk;
	data->a1_lp = data->wc22 / data->tmpk;
	data->a2_lp = data->a0_lp;
	// hip
	data->a0_hp = data->k2 / data->tmpk;
	data->a1_hp = (-1 * data->k22) / data->tmpk;
	data->a2_hp = data->a0_hp;
}

struct filter * filter_init(float freq, float sr, filterEQT type, float thresh, float ratio, float att, float rel, float look, float outGain) {
	struct filter *data = malloc(sizeof(struct filter));
	data->outGain = outGain;
	data->type = type;
	data->sr = sr;
	data->nyquist = sr * 0.499;
	data->x0_lp = data->x1_lp = data->x0_hp = data->x1_hp = 0.0;
	filter_compute_coeffs(data, freq);
	filter_set_outGain(data, outGain);

	data->comp = compress_init(thresh, ratio, att, rel, look, sr, 100.0f);
	return data;
}

void filter_delete(struct filter *data) {
	free(data);
	compress_delete(data->comp);
}

float filter_process(struct filter *data, float input) {
	float lop_out, hip_out, deesserIO, output;
	
	switch (data->type) {
	case LOWPASS:
		output = filter_compute_lop(data, input);
		break;
	case HIGHPASS:
		output = filter_compute_hip(data, input);
		break;
	case CROSS:
		output = filter_compute_cross(data, input);
		break;
	default:
		break;
	}
	return output;
}

void filter_set_freq(struct filter *data, float freq) {
	if (freq != data->freq) {
		filter_compute_coeffs(data, freq);
	}
}

void filter_set_compThresh(struct filter *data, float thresh) {
	compress_set_thresh(data->comp, thresh);
}

void filter_set_outGain(struct filter *data, float gain) {
	if (gain > 63.0f) {
		data->outGain = 63.0f;
	}
	else if (gain < 0.015873f) {
		data->outGain = 0.015873f;
	}
	else {
		data->outGain = gain;
	}
}


