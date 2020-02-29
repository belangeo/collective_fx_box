#ifndef __COMPRESS_H__
#define __COMPRESS_H__

#include "delay.h"
/* Compressor : compress an audio signal that rise a given signal
 *
 *  float freq;                 frequency in Hz
 *  float sr;                   sample rate
 *  float thresh;               
 *  float ratio;                
 *  float attack;               
 *  float release;              
 *  float lookahead;            
 *  float y0;                   
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
    struct delay *look;
};

/* Initialize the compress structure.
 *
 */
struct compress * compress_init(float thresh, float ratio, float attack, float release, float lookahead, float sr);

/* Delete compressor structure.
 *
 * struct compress *data: The structure for which to release memory.
 * 
 */
void compress_delete(struct compress *data);

/* Process the next sample of compressor.
 *
 * struct compress *data: The structure for which to compute the next sample.
 * float input:        Input signal
 */
float compress_process(struct compress *data, float input);

/* Change the thressold of compressor.
 *
 * struct compress *data:  The structure for which to set a new frequency.
 * float freq :         New frequency value.

 */
void compress_set_thresh(struct compress *data, float thresh);

void compress_set_ratio(struct compress *data, float ratio);

void compress_set_attack(struct compress *data, float attack);

void compress_set_release(struct compress *data, float release);

void compress_set_lookahead(struct compress *data, float lookahead);

#endif