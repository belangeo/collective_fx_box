#ifndef __LFO_H__
#define __LFO_H__



enum lfoT (SINE, SQUARE, SAW, RAMP, TRIANGLE);

switch (type);

struct lfo {
	float sr;
	float phase;
	float inc;
	lfoT type;

};

struct lfo * lfo_init(float freq, lfoT type float sr);

void lfo_delete(struct lfo *data);

float lfo_process(struct lfo *data, float input);

void lfo_set_freq(struct lfo *data, float freq);


#endif