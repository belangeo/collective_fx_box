#ifndef __COMPRESS_H__
#define __COMPRESS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../../../../lib/delay.h"

/* Compressor : compress an audio signal that rise a given signal
 *
 *  float freq;                 frequency in Hz
 *  float sr;                   sample rate
 *  float thresh;               Threshold in dB
 *  float ratio;                Ratio
 *  float attack;               Attack time in milliseconds
 *  float release;              Release time in milliseconds
 *  float lookahead;            Lookahead time in miliseconds
 *  float sr;                   samplerate           
 *  float y0;                   y0 out
 *  float acoeff;               a coefficient
 *  float rcoeff;               r coefficient
 *  struct delay look;          delay for lookahead
 *  
 */
struct compress {
    float thresh;
    float ratio;
    float attack;
    float release;
    float lookahead;
    float sr;
    float y0;
    float acoeff;
    float rcoeff;
	float mix;
    struct delay *look;
};

/* Initialize the compressor structure.
 *
 */
struct compress * compress_init(float thresh, float ratio, float attack, float release, float lookahead, float sr, float mix);

/* Delete compressor structure.
 *
 * struct compress *data: The structure for which to release memory.
 * 
 */
void compress_delete(struct compress *data);

/* Process the next sample of compressor.
 *
 * struct compress *data:   The structure for which to compute the next sample.
 * float input:             Input signal
 */
float compress_process(struct compress *data, float input);

/* Change the thressold of compressor.
 *
 * struct compress *data:   The structure for which to set a new thressold.
 * float thresh :           New threshold value.

 */
void compress_set_thresh(struct compress *data, float thresh);

/* Change the ration of compressor.
 *
 * struct compress *data:   The structure for which to set a new ratio.
 * float ratio :            New ratio value. ()

 */
void compress_set_ratio(struct compress *data, float ratio);

/* Change the attack time of compressor.
 *
 * struct compress *data:   The structure for which to set a new attack.
 * float attack :           New attack time value.

 */
void compress_set_attack(struct compress *data, float attack);

/* Change the release time of compressor.
 *
 * struct compress *data:   The structure for which to set a new release.
 * float release :           New release time value.

 */
void compress_set_release(struct compress *data, float release);

/* Change the lookahead time of compressor.
 *
 * struct compress *data:   The structure for which to set a new lookahead.
 * float lookahead :           New lookahead time value.

 */
void compress_set_lookahead(struct compress *data, float lookahead);

float compress_sidechain(struct compress *data, float input);

void compress_set_mix(struct compress *data, float mix);

#ifdef __cplusplus
}
#endif

#endif