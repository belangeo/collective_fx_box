#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

struct triangle {
	float sr;
	float x;
	float inc;
};

struct triangle * triangle_init(float freq, float sr);

void triangle_delete(struct triangle *data);

float triangle_process(struct triangle *data, float input);

void triangle_set_freq(struct triangle *data, float freq);


#endif