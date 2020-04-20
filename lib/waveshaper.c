/*
	waveshaper.c

	Antoine Lussier - Remi Coulombe
	21 fevrier 2020
	MUS3329

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "waveshaper.h"
#include "utils.h"

void waveshaper_set_drive(struct waveshaper* data, float drive) {
	if (drive > 0.998){
		data->drive = 0.998;
	}else if (drive < 0.0){
		data->drive = 0.0;
	}else {
		data->drive = drive;
	}
	data->k = (2.0 * data->drive) / (1.0 - data->drive);
}

struct waveshaper* waveshaper_init(float drive, float cutoff, float sr, float q, float dw) {
	struct waveshaper *data = malloc(sizeof(struct waveshaper));
	waveshaper_set_drive(data, drive);
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
	float out, distoOut;
	distoOut = (1.0 + data->k) * input / (1.0 + data->k * fabsf(input));
	float compensation = scale(data->drive, 0.0, 0.998, 1.0, 0.017, 3.0);
	out = (distoFltr_process(data->filter, distoOut) * data->wet * compensation) + (input * data->dry);
	return out;
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
