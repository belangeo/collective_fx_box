/*
	waveshaper.c

	Antoine Lussier - Rémi Coulombe
	21 février 2020
	MUS3329

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "waveshaper.h"


struct waveshaper* waveshaper_init(float drive, float cutoff, float sr, float q) {
	struct waveshaper *data = malloc(sizeof(struct waveshaper));
	//struct filter* data = malloc(sizeof(struct filter));
	data->drive = drive;
	data->filter = distoFltr_init(cutoff, sr, q);
	return data;
}

void waveshaper_delete(struct waveshaper* data) {
	free(data);
	distoFltr_delete(data->filter);
}

float waveshaper_process(struct waveshaper* data, float input) {
	float k, out;
	k = (2 * data->drive) / (1 - data->drive);
	out = distoFltr_process(data->filter, (1.0 + k) * input / (1.0 + k * abs(input)));
	
	printf("input: %f\nk: %f\ndata->drive: %f\nout: %f\n-----\n", input, k, data->drive, out);
	
	return out;
}

void waveshaper_set_drive(struct waveshaper* data, float drive) {
	if (data->drive >= 1) {
		data->drive = 0.999;
	}
	else if (data->drive < 0) {
		data->drive = 0;
	}
	else {
		data->drive = drive;
	}
	data->k = (2 * drive) / (1 - drive);
}

void waveshaper_set_cutoff(struct waveshaper* data, float cutoff, float q) {
	distoFltr_set_params(data->filter, cutoff, q);
}