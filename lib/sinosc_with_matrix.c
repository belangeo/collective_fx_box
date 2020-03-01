#include <stdlib.h>
#include <math.h>
#include "sinosc_with_matrix.h"

#include <stdio.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

// The routing matrix is passed as argument when creating the sinosc
struct sinosc_with_matrix * 
sinosc_with_matrix_init(float freq, float sr, struct routing_matrix * mat) {
    struct sinosc_with_matrix *data = malloc(sizeof(struct sinosc_with_matrix));
    data->sr = sr;
    data->freq = freq;
    data->angle = 0.0;
    data->matrix = mat;
    return data;
}

void
sinosc_with_matrix_delete(struct sinosc_with_matrix *data) {
	free(data);
}

float
sinosc_with_matrix_process(struct sinosc_with_matrix *data) {
    float value = sinf(2 * M_PI * data->angle);

    // The bus output value is fetched.
    // If the channel state is OFF, the third argument is used istead
    float mod_freq = matrix_bus_output(data->matrix, BUS0, 0) * 100 + data->freq;
    
    float inc = mod_freq / data->sr;
    
    data->angle += inc;
    if (data->angle >= 1.0)
        data->angle -= 1.0;
    return value;
}

void
sinosc_with_matrix_set_freq(struct sinosc_with_matrix *data, float freq) {
  data->freq = freq;
}

void
sinosc_with_matrix_reset(struct sinosc_with_matrix *data) {
    data->angle = 0.0;
}
