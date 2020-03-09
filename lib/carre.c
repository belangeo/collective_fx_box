#include <stdlib.h>
#include <math.h>
#include "carre.h"

struct carre * 
triangle_init(float freq, float sr) {
    struct carre *data = malloc(sizeof(struct carre *));
	data->sr = sr;
    data->x = 0.0;
    data->inc = freq / sr;
    return data;
}

void
carre_delete(struct carre *data) {
	free(data);
}

float
carre_process(struct carre *data, float input) {
    float value = * data->x;
    data->x += data->inc;
    if (data->x >= 1.0)
        data->x -= 1.0;
    if (data->x <0.5)
        value = 1.0;
    else value = -1.0;

    return value;
}

void
carre_set_freq(struct carre *data, float freq) {
    data->inc = freq / data->sr;
}

void
carre_reset(struct carre *data) {
    data->x = 0.0;