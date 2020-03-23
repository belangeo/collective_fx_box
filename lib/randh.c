#include <stdlib.h>
#include <math.h>
#include "randh.h"
#include <time.h>   /* time */

#endif

struct randh * 
randh_init(float freq, float sr) {
    struct randh *data = malloc(sizeof(struct randh));
    srand((unsigned int)time(NULL));
	data->sr = sr;
    data->angle = 0.0;
    data->inc = freq / sr;
    return data;
}

void
randh_delete(struct randh *data) {
	free(data);
}

float
randh_process(struct randh *data) {
    data->angle += data->inc;
    if (data->angle >= 1.0) {
        data->angle -= 1.0;
        data->output = (rand() / (float)RAND_MAX) - 0.5;
    }
    return data->output;
}

void
randh_set_freq(struct randh *data, float freq) {
    data->inc = freq / data->sr;
}