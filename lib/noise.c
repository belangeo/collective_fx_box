#include <stdlib.h>
#include <math.h>
#include "noise.h"


struct noise * 
noise_init() {
  struct noise *data = malloc(sizeof(struct noise));  
}

void
noise_delete(struct noise *data) {
  free(data);
}

float
noise_process(struct noise *data) {
  float value = 2 * (float)rand()/((float)RAND_MAX) - 1.0;
    return value;
}

void
noise_reset(struct noise *data) {
    data->seed = 0;
}
