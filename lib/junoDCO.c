#include <stdlib.h>
//#include <math.h>
#include "junoDCO.h"

struct junoDCO * junoDCO_init(float sr) {
    struct junoDCO *data = malloc(sizeof(struct junoDCO));

    data->freq = 0;
    data->sr = sr;
    data->lfoInAttenuator = 0;

    data->ramp = phasor_init(data->freq, data->sr);
    data->rampSub = phasor_init(data->freq, data->sr);
    data->noisy = noise_init();
    
    data->pw = 0.5;
    data->pwModulation = 0;
    
    data->subVolume = 0;
    data->noiseVolume = 0;
    
    data->squareIsOn = 1;
    data->triangleIsOn = 0;
    data->subIsOn = 0;

    return data;
}

void junoDCO_delete(struct junoDCO *data) {
    phasor_delete(data->ramp);
    phasor_delete(data->rampSub);
    noise_delete(data->noisy);

    free(data);
}

float junoDCO_process(struct junoDCO *data, float lfoIn, float envIn) {
	float lfoFreq, pw, phasor, phasorSub, square, triangle, sub, noise, sum;
    //  lfoIn varies between 0 and 1, lfoFreq varies around 1
    lfoFreq = (1.0 + lfoIn * data->lfoInAttenuator) - data->lfoInAttenuator / 2.0;

    phasor_set_freq(data->ramp, data->freq * lfoFreq);
    phasor_set_freq(data->rampSub, data->freq/4 * lfoFreq);

	phasor = phasor_process(data->ramp);
	phasorSub = phasor_process(data->rampSub);
	noise = noise_process(data->noisy);
	// SQUARE WAVE
    switch (data->pwModulation) {
        case 0:
            pw = data->pw;
            break;
        case 1:
            pw = (data->pw - 0.5) * lfoIn + 0.5;
            break;
        case 2:
            pw = (data->pw - 0.5) * envIn + 0.5;
            break;
    }
    if (phasor < pw) {square = -1.0;} else {square = 1.0;}
    if (data->squareIsOn == 1) {square *= 0.2;} else {square *= 0;}
    //  TRIANGLE WAVE
    triangle = phasor * 2.0 - 1.0;
    if (data->triangleIsOn == 1) {triangle *= 0.2;} else {triangle *= 0;}
    // SUB SQUARE WAVE
    if (phasorSub < 0.5) {sub = 1.0;} else {sub = -1.0;}
    if (data->subIsOn == 1) {sub *= 0.2 * data->subVolume;} else {sub *= 0;}
    //	NOISE
    noise *= 0.3 * data->noiseVolume;

    sum = square + triangle + sub + noise;
    return sum;
}

void junoDCO_set_freq(struct junoDCO *data, float freq){
    data->freq = freq;
}

void junoDCO_set_lfoInAttenuator(struct junoDCO *data, float lfoInAttenuator){
	data->lfoInAttenuator = lfoInAttenuator;
}

void junoDCO_set_pw(struct junoDCO *data, float pw){
	float pwValue;

	if (pw <= 0) {pwValue = 0.00;}
	else if (pw >= 1) {pwValue = 0.99;}
	else {pwValue = pw;}
	pwValue = pwValue * 0.5 * 0.95 + 0.5;
	data->pw = pwValue;
}

void junoDCO_set_pwModulation(struct junoDCO *data, int pwModulation){
	if (pwModulation <= 0) {data->pwModulation = 0;}
	else if (pwModulation >= 2) {data->pwModulation = 2;}
	else {data->pwModulation = 1;}
}

void junoDCO_set_subVolume(struct junoDCO *data, float subVolume){
	data->subVolume = subVolume;
}

void junoDCO_set_noiseVolume(struct junoDCO *data, float noiseVolume){
	data->noiseVolume = noiseVolume;
}

void junoDCO_set_squareIsOn(struct junoDCO *data, float squareIsOn){
	data->squareIsOn = squareIsOn;
}

void junoDCO_set_triangleIsOn(struct junoDCO *data, float triangleIsOn){
	data->triangleIsOn = triangleIsOn;
}

void junoDCO_set_subIsOn(struct junoDCO *data, float subIsOn){
	data->subIsOn = subIsOn;
}
