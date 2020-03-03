#ifndef __PARAMETRICEQ_H__
#define __PARAMETRICEQ_H__

enum filterT {PEAK=0, NOTCH=0, LOWSHELF=1, HIGHSHELF=2};


/* Parametric EQ filter
 *
 *  float freq;                 frequency in Hz
 *  float q;                    q
 *  float gain;                 Makup gain (boost)
 *  enum filterT;               Filter Type
 *  PEAK=0, NOTCH=0, LOWSHELF=1, HIGHSHELF=2
 * 
 */
struct parametricEQ
{
    float freq;
    float q;
    float gain;
    enum filterT;

};

/* Initialize the filter's structure.
 *
 * freq:    Desired frequency in Hz.
 * sr:      Sampling rate in Hz.
 */
struct parametricEQ * parametricEQ_init(float freq, float q, float gain, enum filterT, float sr);

/* Delete  filter's structure.
 *
 * struct parametricEQ *data: The structure for which to release memory.
 */
void parametricEQ_delete(struct parametricEQ *data);

/* Process the next sample of filter.
 *
 * struct parametricEQ *data: The structure for which to compute the next sample.
 * float input:        Input signal
 * 
 */
float parametricEQ_process(struct parametricEQ *data, float input);

/* Change the frequency of filter.
 *
 * struct parametricEQ *data:  The structure for which to set a new frequency.
 * float freq :         New frequency value.
 * 
 */
void parametricEQ_set_freq(struct parametricEQ *data, float freq);

/* Change the q of filter.
 *
 * struct parametricEQ *data:   The structure for which to set a new frequency.
 * float q :                    New q value.
 * 
 */
void parametricEQ_set_q(struct parametricEQ *data, float q);

/* Change the gain/boost of filter.
 *
 * struct parametricEQ *data:   The structure for which to set a new frequency.
 * float gain :                 New gain value.
 * 
 */
void parametricEQ_set_gain(struct parametricEQ *data, float gain);

/* Change the type of filter.
 *
 * struct parametricEQ *data:  The structure for which to set a new frequency.
 * float type  :               New type value.
 * 
 * Choices :
 * PEAK=0, NOTCH=0, LOWSHELF=1, HIGHSHELF=2
 * 
 */
void parametricEQ_set_filterT(struct parametricEQ *data, enum filterT);