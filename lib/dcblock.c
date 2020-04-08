#include <stdlib.h>
#include "dcblock.h"

struct dcblock * 
dcblock_init() {
    struct dcblock *data = malloc(sizeof(struct dcblock));
    data->lastin = 0.0;
    data->lastout = 0.0;
    return data;
}

void
dcblock_delete(struct dcblock *data) {
	free(data);
}

float
dcblock_process(struct dcblock *data, float input) {
    data->lastout = input - data->lastin + data->lastout * 0.995;
    data->lastin = input;
    return data->lastout;
}
