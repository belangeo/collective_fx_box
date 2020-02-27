#include <stdlib.h>
#include <math.h>
#include "butlp.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


/* Calculate de coefficient of Butterwoth lowpass filter's 
 * on with a new frequency.
 * 
 * struct butlp *data: to uptade all coefficients
 * float freq :        set new frequency
 */
static void butlp_compute_coeffs(struct butlp *data, float freq){
    if (freq < 1.0) {
        data->freq = 1.0;
    }else if (freq > data->nyquist){
        data->freq = data->nyquist;
    }else{
        data->freq = freq;
    }
    float c_ = 1.0 / tan(data->pi_over_sr * data->freq);
    float c2_ = c_ * c_;
    data->a0 = data->a2 = 1.0 / (1.0 + data->sqrt_2 * c_ + c2_);
    data->a1 = 2.0 * data->a0;
    data->b1 = data->a1 * (1.0-c2_);
    data->b2 = data->a0 * (1.0 - data->sqrt_2 * c_ + c2_);
}

struct butlp * butlp_init(float freq, float sr) {
    struct butlp *data = malloc(sizeof(struct butlp));
    data->x1 = data->x2 = data->y1 = data->y2 = 0.0;
    data->pi_over_sr = M_PI / sr;
    data->sqrt_2 = sqrt(2.0);
    data->nyquist = sr * 0.49;
    butlp_compute_coeffs(data, freq);
    
    return data;
}

void butlp_delete(struct butlp *data) {
    free(data);
}

float butlp_process(struct butlp *data, float input) {
    float value = data->a0 * input + data->a1 * data->x1 + data->a2 * data->x2 - data->b1 * data->y1 - data->b2 * data->y2;
    data->x2 = data->x1;
    data->x1 = input;
    data->y2 = data->y1;
    data->y1 = value;

    return value;
}

void butlp_set_freq(struct butlp *data, float freq) {
    // Verfifie si la frequence de "freq" est différente de la derniere.
    if (freq != data->last_freq){
        butlp_compute_coeffs(data, freq);
        data->last_freq = freq;
    }
        
}


