#include <stdlib.h>
#include <math.h>
#include "lp1.h"

struct lp1 * 
lp1_init(float freq, float sr) {
    struct lp1 *data = malloc(sizeof(struct lp1));
	data->sr = sr;
    data->lastout = 0.0;
    data->coeff = expf(-2.0 * M_PI * freq / sr);
    return data;
}

void
lp1_delete(struct lp1 *data) {
	free(data);
}

float
lp1_process(struct lp1 *data, float input) {
    data->lastout = input + (data->lastout - input) * data->coeff;
    return data->lastout;
}

void
lp1_set_freq(struct lp1 *data, float freq) {
    data->coeff = expf(-2.0 * M_PI * freq / data->sr);
}
