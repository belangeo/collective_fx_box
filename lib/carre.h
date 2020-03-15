#ifndef __CARRE_H__
#define __CARRE_H__

struct carre {
	float sr;
	float x;
	float inc;
};

struct carre * carre_init(float freq, float sr);

void carre_delete(struct carre *data);

float carre_process(struct carre *data, float input);

void carre_set_freq(struct carre *data, float freq);


#endif