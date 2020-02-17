#ifndef __SINOSC_H__
#define __SINOSC_H__

struct sinosc {
	float sr;
	float inc;
	float angle;
};

struct sinosc * sinosc_init(float freq, float sr);

void sinosc_delete(struct sinosc *data);

float sinosc_process(struct sinosc *data);

void sinosc_set_freq(struct sinosc *data, float freq);

#endif