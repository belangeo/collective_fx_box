#include <stdlib.h>
#include <math.h> 
#include "compress.h"
//#include "delay.h"
#include "../../../../lib/delay.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

struct compress *compress_init(float thresh, float ratio, float attack, float release, float lookahead, float sr, float mix){
    struct compress *data = malloc(sizeof(struct compress));
	data->mix = mix;
    // Set threshold
    if (thresh > 0.0)
    {
        data->thresh = 0.0;
    }
    else if (thresh < -70.0)
    {
        data->thresh = -70.0;
    }
    else
    {
        data->thresh = thresh;
    }

    // Set ratio
    if (ratio < 1.0)
    {
        data->ratio = 1.0;
    }
    else if (ratio > 20.0)
    {
        data->ratio = 20.0;
    }
    else
    {
        data->ratio = ratio;
    }

    // Set Attack | initialement min : 1 max : 150
    if (attack < 0.03)
    {
        data->attack = 0.03;
    }
    else if (attack > 150.0)
    {
        data->attack = 150.0;
    }
    else
    {
        data->attack = attack;
    }
    float freq1 = 1 / (data->attack * 0.001);
    data->acoeff = exp(-2 * M_PI * freq1 / data->sr);

    // Set Release | initialement min : 1 max : 250
    if (release < 1.0)
    {
        data->release = 1.0;
    }
    else if (release > 2000.0)
    {
        data->release = 2000.0;
    }
    else
    {
        data->release = release;
    }
    float freq2 = 1 / (data->release * 0.001);
    data->rcoeff = exp(-2 * M_PI * freq2 / data->sr);

    data->lookahead = lookahead;    // Set Lookahead
    data->sr = sr;                  // Set Samplerate

    // Set delay struct / obj
    data->look = delay_init(sr/8, sr);
    data->y0 = 0.0;                 // Set Y0 out

    return data;
}

void compress_delete(struct compress *data){
    delay_delete(data->look);
    free(data);
}


float compress_process(struct compress *data, float input){
    float value = delay_read(data->look, data->lookahead * 0.001);
	float mix = data->mix * 0.01f;
    delay_write(data->look, input);
    float absin = fabsf(input);
    if (absin > data->y0)
    {
        data->y0 = absin + (data->y0 - absin) * data->acoeff;
    }else
    {
        data->y0 = absin + (data->y0 - absin) * data->rcoeff;
    }
    float dbin = 20 * log10(data->y0 + 0.0000001);
    if (dbin > data->thresh)
    {
        float diff  = dbin - data->thresh;
        float att = pow(10, (diff - diff / data->ratio) * 0.05);
        value /= att;
    }
	return (((1.0f - mix) * input) + (mix * value));
}

float compress_sidechain(struct compress *data, float input) {
	float absin = fabsf(input), diff;
	if (absin > data->y0){
		data->y0 = absin + (data->y0 - absin) * data->acoeff;
	}else{
		data->y0 = absin + (data->y0 - absin) * data->rcoeff;
	}
	float dbin = 20 * log10(data->y0 + 0.0000001);
	float att = 1.0;
	if (dbin > data->thresh){
		diff = dbin - data->thresh;
		att = pow(10, (diff - diff / data->ratio) * 0.05);
	}
	return att; // attenuation
}

// Threshold en dB de -70 à 0 dB 
void compress_set_thresh(struct compress *data, float thresh){
    if (thresh > 0.0){
        data->thresh = 0.0;
    }else if (thresh < -70.0){
        data->thresh = -70.0;
    }else{
        data->thresh = thresh;
    }
}

// Set ration boundaries between 1.0 and 20.0
void compress_set_ratio(struct compress *data, float ratio){
    if (ratio < 1.0)
    {
        data->ratio = 1.0;
    }else if (ratio > 20.0)
    {
        data->ratio = 20.0;
    }else
    {
        data->ratio = ratio;
    }
}
// Set attack boundaries between 1 and 150 ms (in milliseconds)
void compress_set_attack(struct compress *data, float attack){
    if (attack < 1.0)
    {
        data->attack = 1.0;
    }else if (attack > 150.0)
    {
        data->attack = 150.0;
    }else
    {
        data->attack = attack;
    }
    float freq = 1 / (data->attack * 0.001);
    data->acoeff = exp(-2 * M_PI * freq / data->sr);

}

// Set release boundaries between 1 and 250 ms (in milliseconds)
void compress_set_release(struct compress *data, float release){
    if (release < 1.0)
    {
        data->release = 1.0;
    }else if (release > 250.0)
    {
        data->release = 250.0;
    }else
    {
        data->release = release;
    }
    float freq = 1 / (data->release * 0.001);
    data->rcoeff = exp(-2 * M_PI * freq / data->sr);

}

// Set lookahead boundaries between 0.5 and 10 ms (in milliseconds)
void compress_set_lookahead(struct compress *data, float lookahead){
    if (lookahead < 0.5)
    {
        data->lookahead = 0.5;
    }
    else if (lookahead > 10.0)
    {
        data->lookahead = 10.0;
    }
    else
    {
        data->lookahead = lookahead;
    }
}

void compress_set_mix(struct compress *data, float mix) {
	if (mix < 0.0f) {
		data->mix = 0.0f;
	}
	else if (mix > 100.0f) {
		data->mix = 100.0f;
	}
	else {
		data->mix = mix;
	}
}
