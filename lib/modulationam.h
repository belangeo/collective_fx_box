/*
	modulationam.h

	Rémi Hermoso
	Mars 2020
	MUS3329

*/

#ifndef __MODULATIONAM_H__
#define __MODULATIONAM_H__


#include "sinosc.h"

struct modulationam {
	float freq, sr;
	float inc;
	struct sinosc* osc;
};

struct modulationam * modulationam_init(float freq, float sr);

void modulationam_delete(struct modulationam * data);

float modulationam_process(struct modulationam * data, float input);

#endif