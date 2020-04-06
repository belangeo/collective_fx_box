#include <stdlib.h>
#include <math.h>
#include "lfo.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

struct lfo * 
lfo_init(float freq, lfoT type, sr) {
    struct lfo *data = malloc(sizeof(struct lfo *));
	data->sr = sr;
    data->phase = 0.0;
    data->inc = freq / sr;
    data->type = type;
    return data;
}

void 
lfo_delete(struct lfo *data) {
	free(data);
}

float
lfo_process(struct lfo *data, float input) {
    float value;

    switch (data->type) {

        case SINE:
    		value = sinf(data->phase * M_PI * 2);
    		break;

        case SQUARE:
    		if (data->phase < 0.5)
    			value = -1.;
    		else
    			value = 1.;
    		break;

        case RAMP:
    		value = data->phase * 2 -1;
    		break;

        case SAW:
    		value = (1 - data->phase) * 2 -1;
    		break;

        case TRIANGLE:
    		value = data->phase < (1 - data->phase) ? data->phase : (1 - data->phase);
            value = value * 4 - 1;
    		break;

    }
    
    data->phase += data->inc;
    if (data->phase >= 1.0)
        data->phase -= 1.0;

    return value;
}

void
lfo_set_freq(struct lfo *data, float freq) {
    data->inc = freq / data->sr;
}

void
lfo_reset(struct lfo *data) {
    data->phase = 0.0;

}
