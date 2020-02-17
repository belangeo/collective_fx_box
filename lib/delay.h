#ifndef __DELAY_H__
#define __DELAY_H__

struct delay {
    float sr;
    long maxsize;
    long writepos;
    float *buffer;
};

/*
 * Doc de la fonction delay_init...
 */
struct delay * delay_init(float maxdur, float sr);

void delay_delete(struct delay *data);

float delay_read(struct delay *data, float deltime);

void delay_write(struct delay *data, float input);

#endif