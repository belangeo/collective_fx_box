#ifndef __LFO_H__
#define __LFO_H__

#ifdef __cplusplus
extern "C" {
#endif


enum lfoT {SINE, SQUARE, SAW, RAMP, TRIANGLE};


struct lfo {
	float sr;
	float phase;
	float inc;
	enum lfoT type;

};

struct lfo * lfo_init(float freq, enum lfoT type, float sr);

void lfo_delete(struct lfo *data);

float lfo_process(struct lfo *data);

void lfo_set_freq(struct lfo *data, float freq);

#ifdef __cplusplus
}
#endif

#endif
