#ifndef __SAW_H__
#define __SAW_H__

struct saw {
	float sr;
	float x;
	float inc;
};

struct saw * saw_init(float freq, float sr);

void saw_delete(struct saw *data);

float saw_process(struct saw *data, float input);

void saw_set_freq(struct saw *data, float freq);


#endif