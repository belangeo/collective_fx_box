#include <stdlib.h>
#include <math.h>
#include "phasor.h"

/* Simple implementatino of a phasor/rampe.
 */
struct phasor * 
phasor_init(float freq, float sr) {
    struct phasor *data = malloc(sizeof(struct phasor)); //Initialisation de l espace memoire
	data->sr = sr; //Nous attribuons le sample rate sr dans l espace memoire lui etant accorde.
    data->phase = 0.0;
    data->inc = freq / sr;
    return data;
}

void
phasor_delete(struct phasor *data) {
	free(data);
}

float
phasor_process(struct phasor *data) {
	float value = data->phase;
    data->phase=data->phase+data->inc;
    if (data->phase >= 1.0)
        data->phase -= 1.0;
    return value;
}

void
phase_set_freq(struct phasor *data, float freq) {
    data->inc = freq / data->sr;
}

void
phase_reset(struct phasor *data) {
    data->phase = 0.0;
}
