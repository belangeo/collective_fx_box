// Fabien Lamarche-Filion
#ifndef __BP_H__
#define __BP_H__

#ifdef __cplusplus
extern "C" {
#endif

struct bp {
  float freq;
  float q;
  float sample_rate;
  float x1, x2, y1, y2;
  float a0, a1, a2, b0, b1, b2;
  float b0_a0;
  float b1_a0;
  float b2_a0;
  float a1_a0;
  float a2_a0;
};

struct bp * bp_init(float freq, float q, float sr);

void bp_delete(struct bp *data);

float bp_process(struct bp *data, float input);

void bp_set_freq(struct bp *data, float freq);

void bp_set_q(struct bp *data, float freq);

#ifdef __cplusplus
}
#endif

#endif
