#ifndef __JUNO_DCO__
#define __JUNO_DCO__

#ifdef __cplusplus
extern "C" {
#endif

#include "phasor.h"
#include "noise.h"
/////////////////////////////////////////////////////
////*	Juno DCO: 3 Oscillators + 1 Noise 		*////
////*											*////	
////*	Inspired by the Digitally Controlled  	*////
////*	Oscillators (DCO) section of the Juno-60*////	
/////////////////////////////////////////////////////
/*	QUESTIONS:
	- Compilation: pointer being freed was not allocated (verifier avec une autre main)
	- Comment faire un PW sur un sinus
	MODIFS
	- Square wave a un timbre instable
	- Changer square brutal pour une onde sinusoidale avec une fonction arctan
	- Ajouter LFO sur freq
	- Ajouter PW modulations (LFO, ENV)
	- Se débarraser eventuellement de l'argument freq ds junoDCO_init?
*/
struct junoDCO {
	float 	sr;				//	Sampling rate				
	float 	freq;			//	Voice frequency
	float 	lfoInAttenuator;//	Control over the intensity of the lfo input		(0 to 1)

	struct 	phasor* ramp;		//	A ramp to generate the square and triangle waves
	struct 	phasor* rampSub;	//	A ramp to generate the sub square wave
	struct 	noise* noisy;		//	A noise generator

	float 	pw;				//	Pulse width of the square wave					(0 to 1)
	int 	pwModulation;	//	Type of modulation applied to the square wave 	(0: None, 1: lfo, 2: envellope)

	float 	subVolume;		//	The volume of the the sub square wave	(0 to 1)
	float 	noiseVolume;	//	The volume of the Noise 				(0 to 1)

	int 	squareIsOn;		//	On/off on the square wave				(0 or 1)
	int 	triangleIsOn;	//	On/off on the triangle wave				(0 or 1)
	int 	subIsOn;		//	On/off on the sub square wave			(0 or 1)
};

struct junoDCO * junoDCO_init(float sr);

void junoDCO_delete(struct junoDCO *data);

float junoDCO_process(struct junoDCO *data, float lfoIn);

void junoDCO_set_freq(struct junoDCO *data, float freq);

void junoDCO_set_lfoInAttenuator(struct junoDCO *data, float lfoInAttenuator);

void junoDCO_set_pw(struct junoDCO *data, float pw);

void junoDCO_set_pwModulation(struct junoDCO *data, int pwModulation);

void junoDCO_set_subVolume(struct junoDCO *data, float subVolume);

void junoDCO_set_noiseVolume(struct junoDCO *data, float noiseVolume);

void junoDCO_set_squareIsOn(struct junoDCO *data, float squareIsOn);

void junoDCO_set_triangleIsOn(struct junoDCO *data, float triangleIsOn);

void junoDCO_set_subIsOn(struct junoDCO *data, float subIsOn);

#ifdef __cplusplus
}
#endif

#endif
