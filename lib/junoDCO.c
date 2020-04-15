#include <stdlib.h>
#include <math.h>
#include "junoDCO.h"

struct junoDCO * junoDCO_init(float freq, float sr) {
    struct junoDCO *data = malloc(sizeof(struct junoDCO));

    data->freq = freq;
    data->sr = sr;
    data->lfoInAttenuator = 0;

    data->ramp = phasor_init(freq, sr);
    data->rampSub = phasor_init(freq/4, sr);
    data->noisy = noise_init();
    
    data->pw = 0.50;
    data->pwModulation = 0;
    
    data->subVolume = 0.5;
    data->noiseVolume = 0.1;
    
    data->squareIsOn = 1;
    data->triangleIsOn = 1;
    data->subIsOn = 1;

    return data;
}

void junoDCO_delete(struct junoDCO *data) {
    phasor_delete(data->ramp);
    phasor_delete(data->rampSub);
    noise_delete(data->noisy);

    free(data);
}

float junoDCO_process(struct junoDCO *data, float lfoIn){
	float phasor, phasorSub, square, triangle, sub, noise, sum;

	phasor = phasor_process(data->ramp);
	phasorSub = phasor_process(data->rampSub);
	noise = noise_process(data->noisy);
	//	SQUARE WAVE
    if (phasor < data->pw) {square = -1.0;} else {square = 1.0;}
    if (data->squareIsOn == 1) {square *= 0.2;} else {square *= 0;}
    //	TRIANGLE WAVE
    triangle = phasor * 2.0 - 1.0;
    if (data->triangleIsOn == 1) {triangle *= 0.2;} else {triangle *= 0;}
    // SUB SQUARE WAVE
    if (phasorSub < 0.5) {sub = 1.0;} else {sub = -1.0;}
    if (data->subIsOn == 1) {sub *= 0.2 * data->subVolume;} else {sub *= 0;}
    //	NOISE
    noise *= 0.2 * data->noiseVolume;

    sum = square + triangle + sub + noise;
    return sum;
}

void junoDCO_set_freq(struct junoDCO *data, float freq){
	phasor_set_freq(data->ramp, freq);
	phasor_set_freq(data->rampSub, freq/4);
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
	int pwModulationValue = 0;

	if (pwModulation < 0) {pwModulationValue = 0;}
	else if (pwModulation > 2) {pwModulationValue = 2;}
	else {pwModulation = pwModulationValue;}
	data->pwModulation = pwModulationValue;
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
