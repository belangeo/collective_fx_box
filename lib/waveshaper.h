/*
	waveshaper.h

	Antoine Lussier - Rémi Coulombe
	21 février 2020
	MUS3329

*/

#ifndef __WSHAPER_H__
#define __WSHAPER_H__

#include "distoFiltr.h"

struct waveshaper {
	// disto
	float drive, k;
	// filter
	float freq, sr;
	struct distoFltr* filter;
};

struct waveshaper* waveshaper_init(float drive, float cutoff, float sr, float q);

void waveshaper_delete(struct waveshaper* data);

float waveshaper_process(struct waveshaper* data, float input);

void waveshaper_set_drive(struct waveshaper* data, float drive);

void waveshaper_set_Cutoff(struct waveshaper* data, float freq);

void waveshaper_set_Q(struct waveshaper* data, float q);

#endif