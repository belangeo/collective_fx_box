/*
	waveshaper.c

	Antoine Lussier - Rémi Coulombe
	21 février 2020
	MUS3329

*/

#include <stdlib.h>
#include <math.h>
#include "waveshaper.h"


struct waveshaper* waveshaper_init(float drive, float sr) {
	struct waveshaper *data = malloc(sizeof(struct waveshaper));
	data->sr = sr;
	data->drive = drive;
	return data;
}

void waveshaper_delete(struct waveshaper* data) {
	free(data);
}

float waveshaper_process(struct waveshaper* data, float input, float drive) {
	float out, k;
	k = (2 * drive) / (1 - drive);
	out = (1 + k) * input / (1 + k * abs(input));
	return out;
}

//void waveshaper_set_drive(struct waveshaper* data, float drive);