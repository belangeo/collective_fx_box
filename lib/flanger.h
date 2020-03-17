#ifndef __Flanger_H__
#define __Flanger_H__

#include "delay.h"
#include "sinosc.h"

struct flanger {
	struct delay * delayline;
	struct sinosc * lfo;
	float feedback;
	float depth;
	float sr;
	float centerdelay;
	
};

struct flanger * flanger_init(float centerdelay, float depth, float lfofreq, float feedback, float sr);

void flanger_delete(struct flanger * data);

float flanger_process(struct flanger *data, float input);

void flanger_set_depth(struct flanger * data, float depth);

void flanger_set_centerdelay(struct flanger * data, float centerdelay);

void flanger_set_freq(struct flanger * data, float freq);

void flanger_set_feedback(struct flanger * data, float feedback);



#endif