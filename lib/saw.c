#include <stdlib.h>
#include <math.h>
#include "saw.h"

struct saw * 
saw_init(float freq, float sr) {
    struct saw *data = malloc(sizeof(struct saw *));
	data->sr = sr;
    data->x = 0.0;
    data->inc = 2(freq / sr);
    return data;
}

void
saw_delete(struct saw *data) {
	free(data);
}

float
saw_process(struct saw *data, float input) {
    float value = * data->x;
    data->x -= data->inc;
    if (data->x <= -1.0)
        data->x += 2.0;

    return value;
}

void
saw_set_freq(struct saw *data, float freq) {
    data->inc = 2(freq / data->sr);
}

void
saw_reset(struct saw *data) {
    data->x = 0.0;