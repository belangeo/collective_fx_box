/*
	waveshaper.h

	Antoine Lussier - Rémi Coulombe
	21 février 2020
	MUS3329

*/

/*
http://www.musicdsp.org/en/latest/Effects/114-waveshaper-simple-description.html

abs --> return absolute value of int. always positive. flip into positive value.

*/

#ifndef __WSHAPER_H__
#define __WSHAPER_H__

struct waveshaper {
	float sr;
	float lastout;
	float coeff;
};

struct waveshaper* lp1_init(float freq, float sr);

void waveshaper_delete(struct waveshaper* data);

float waveshaper_process(struct waveshaper* data, float input);

void waveshaper_set_freq(struct waveshaper* data, float freq);



#endif