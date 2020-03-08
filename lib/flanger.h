#ifndef __Flanger_H__
#define __Flanger_H__

struct lp1 {
	float sr;
	float lastout;
	float coeff;
};

struct lp1 * lp1_init(float freq, float sr);

void lp1_delete(struct lp1 *data);

float lp1_process(struct lp1 *data, float input);

void lp1_set_freq(struct lp1 *data, float freq);

struct delay {
    float sr;
    long maxsize;
    long writepos;
    float *buffer;
};

struct delay * delay_init(float maxdur, float sr);

void delay_delete(struct delay *data);

float delay_read(struct delay *data, float deltime);

void delay_write(struct delay *data, float input);

struct sinosc {
	float sr;
	float angle;
	float inc;
};

struct sinosc * sinosc_init(float freq, float sr);

void sinosc_delete(struct sinosc *data);

float sinosc_process(struct sinosc *data);

void sinosc_set_freq(struct sinosc *data, float freq);

void sinosc_reset(struct sinosc *data);

#endif