#include <stdlib.h>
#include <math.h>
#include "flanger.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif


struct flanger * 
flanger_init(float centerdelay, float depth, float lfofreq, float feedback, float sr) {
    struct flanger *data = malloc(sizeof(struct flanger));
	data->lfo = sinosc_init(lfofreq, sr);
    data->delayline/*delaymax*/ = delay_init(0.1, sr);
    data->feedback = 0.1 ;
    data->depth = 0.3;
    data->centerdelay = 0.07;

    //OU VA CECI????
   //float readval, float delaytime, float output;
    return data;
}

void
flanger_delete(struct flanger *data) {
	sinosc_delete(data->lfo);
    delay_delete(data->delayline);
    free(data);
}

float
flanger_process(struct flanger *data, float input), float readval, float delaytime, float output  {
    delaytime = sinosc_process(data->lfo) * data->centerdelay * data->depth + data->centerdelay;
    readval = delay_read(data->delayline, delaytime);
    delay_write(data->delayline, input + readval * data->feedback);
    output = input + readval;
    return output;
}

void
flanger_set_freq(struct flanger *data, float freq){
	sinosc_set_freq(data->lfo, freq);
}

void 
flanger_set_depth(struct flanger * data, float depth){
    data->depth = depth;
}

void 
flanger_set_centerdelay(struct flanger * data, float centerdelay){
	data->centerdelay = centerdelay;
}

void 
flanger_set_feedback(struct flanger * data, float feedback){
	data->feedback = feedback;
}




