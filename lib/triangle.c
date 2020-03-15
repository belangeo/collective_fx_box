#include <stdlib.h>
#include <math.h>
#include "triangle.h"

struct triangle * 
triangle_init(float freq, float sr) {
    struct triangle *data = malloc(sizeof(struct triangle *));
	data->sr = sr;
    data->x = 0.0;
    data->inc = freq / sr;
    return data;
}

void
triangle_delete(struct triangle *data) {
	free(data);
}

float
triangle_process(struct triangle *data, float input) {
    float value = minimum(* data->x, 1 - * data->x)4-1;
    data->x += data->inc;
    if (data->x >= 1.0)
        data->x -= 1.0;

    return value;
}

void
triangle_set_freq(struct triangle *data, float freq) {
    data->inc = freq / data->sr;
}

void
triangle_reset(struct triangle *data) {
    data->x = 0.0;