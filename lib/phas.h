#ifndef __PHAS_H__
#define __PHAS_H__

struct phasor {
	float sr;
	float x;
	float inc;
};

struct phasor * phasor_init(float freq, float sr);

void phasor_delete(struct phasor *data);

float phasor_process(struct phasor *data, float input);

void phasor_set_freq(struct phasor *data, float freq);


#endif
