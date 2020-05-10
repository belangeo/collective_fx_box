#include <stdlib.h>
#include <math.h>
#include "bp.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


void bp_update(struct bp *data){
  float omega_zero = 2 * M_PI * data->freq/data->sample_rate;
  float alpha = sin(omega_zero)/(2 * data->q);

  data->b0 = data->q * alpha;
  data->b1 = 0;
  data->b2 = -1 * data->q * alpha;
  data->a0 = 1 + alpha;
  data->a1 = -2 * cos(omega_zero);
  data->a2 = 1 - alpha;

  data->b0_a0 = data->b0/data->a0;
  data->b1_a0 = data->b1/data->a0;
  data->b2_a0 = data->b2/data->a0;
  data->a1_a0 = data->a1/data->a0;
  data->a2_a0 = data->a2/data->a0;
}

struct bp * bp_init(float freq, float q, float sr){
  struct bp * data = malloc(sizeof(struct bp));
  data->x1 = 0;
  data->x2 = 0;
  data->y1 = 0;
  data->y2 = 0;
  data->sample_rate = sr;
  data->q = q;
  data->freq = freq;
  bp_update(data);


}

void bp_delete(struct bp *data){
  free(data);
}

float bp_process(struct bp *data, float input){
  float output =  data->b0_a0 * input +
                  data->b1_a0 * data->x1 +
                  data->b2_a0 * data->x2 -
                  data->a1_a0 * data->y1 -
                  data->a2_a0 * data->y2;

  data->x2 = data->x1;
  data->x1 = input;

  data->y2 = data->y1;
  data->y1 = output;

  return output;
}

void bp_set_freq(struct bp *data, float freq){
  data->freq = freq;
  bp_update(data);
}

void bp_set_q(struct bp *data, float q){
  data->q = q;
  bp_update(data);
}
