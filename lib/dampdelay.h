#ifndef __DAMPDELAY_H__
#define __DAMPDELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

// ne pas oublier d'inclure les headers appropriés.
#include "delay.h"
#include "lp1.h"

struct dampdelay {
    // On déclare ici les objets dont on a besoin.
    struct delay *delayline;
    struct lp1 *lowpass;
};

struct dampdelay * dampdelay_init(float maxdur, float freq, float sr);

void dampdelay_delete(struct dampdelay *data);

float dampdelay_read(struct dampdelay *data, float deltime);

void dampdelay_write(struct dampdelay *data, float input);

void dampdelay_set_freq(struct dampdelay *data, float freq);

#ifdef __cplusplus
}
#endif

#endif