#include <stdlib.h>
#include <math.h>
#include "rms.h"

struct rms * 
rms_init(int bufsize) {
    struct rms *data = malloc(sizeof(struct rms));
	data->size = bufsize;
    data->count = 0;
    data->value = 0.0;
    data->buffer = (float *)calloc(bufsize, sizeof(float));
    return data;
}

void
rms_delete(struct rms *data) {
    free(data->buffer);
	free(data);
}

float
rms_process(struct rms *data, float input) {
    int i;
    float sum = 0.0;
    data->buffer[data->count++] = input;
    if (data->count == data->size) {
        data->count = 0;
        for (i = 0; i < data->size; i++) {
            sum += data->buffer[i] * data->buffer[i];
        }
        data->value = sqrtf(sum / data->size);
    }
    return data->value;
}
