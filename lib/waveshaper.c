/*
	waveshaper.c

	Antoine Lussier - R�mi Coulombe
	21 f�vrier 2020
	MUS3329

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "waveshaper.h"


struct waveshaper* waveshaper_init(float drive, float cutoff, float sr, float q, float dw) {
	struct waveshaper *data = malloc(sizeof(struct waveshaper));
	data->drive = drive;
	// filter init
	data->filter = distoFltr_init(cutoff, sr, q);
	data->dw = dw;
	data->wet = data->dw / 100.0;
	data->dry = 1.0 - data->wet;
	return data;
}

void waveshaper_delete(struct waveshaper* data) {
	free(data);
	distoFltr_delete(data->filter);
}

float waveshaper_process(struct waveshaper* data, float input) {
	float k, out, distoOut;
	k = (2 * data->drive) / (1 - data->drive);
	distoOut = (1.0 + k) * input / (1.0 + k * fabsf(input));
	//out = distoFltr_process(data->filter, distoOut);
	out = distoFltr_process(data->filter, distoOut) * data->wet + input * data->dry;
	return out;
}

void waveshaper_set_drive(struct waveshaper* data, float drive) {
	if (data->drive >= 0.998) {data->drive = 0.998;}
	else if (data->drive < 0.0) {data->drive = 0.0;}
	else {data->drive = drive;}
	data->k = (2.0 * data->drive) / (1.0 - data->drive);
}

void waveshaper_set_Cutoff(struct waveshaper* data, float cutoff) {
	distoFltr_set_Cutoff(data->filter, cutoff);
}

void waveshaper_set_Q(struct waveshaper* data, float q) {
	distoFltr_set_Q(data->filter, q);
}

void waveshaper_set_DryWet(struct waveshaper* data, float dw) {
	if (dw > 100.0) {
		data->dw = 100.0;
	}
	else if (dw < 0.0) {
		data->dw = 0.0;
	}
	else {
		data->dw = dw;
	}
}