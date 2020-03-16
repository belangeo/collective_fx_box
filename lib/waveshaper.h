/*
	waveshaper.h

	Antoine Lussier - Rémi Coulombe
	21 février 2020
	MUS3329

*/

#ifndef __WSHAPER_H__
#define __WSHAPER_H__

#include "distoFiltr.h"
/*
drive = amount of drive
cutoff = cut frequency 
sr = sample rate
q = Q for resonnance
dw = Dry Wet
*/
struct waveshaper {
	// disto
	float drive, k, dry, wet, dw;
	// filter
	float freq, sr;
	struct distoFltr* filter;
};

struct waveshaper* waveshaper_init(float drive, float cutoff, float sr, float q, float dw);

void waveshaper_delete(struct waveshaper* data);

float waveshaper_process(struct waveshaper* data, float input);

void waveshaper_set_drive(struct waveshaper* data, float drive);

void waveshaper_set_Cutoff(struct waveshaper* data, float freq);

void waveshaper_set_Q(struct waveshaper* data, float q);

void waveshaper_set_DryWet(struct waveshaper* data, float dw);
#endif