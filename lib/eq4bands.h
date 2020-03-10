#ifndef __EQ4BANDS_H__
#define __EQ4BANDS_H__

#include "parametricEQ.h"

typedef enum {
    BAND_LOWSHELF,
    BAND_NOTCH1,
    BAND_NOTCH2,
    BAND_HIGHSHELF
} bandSelect;

/* 
 *  EQ with 4 bands parametric object
 *  struct eq4Bands{
 *    struct parametricEQ *lsBand;      Lowshelf band object
 *    struct parametricEQ *n1Band;      Notch one band object
 *    struct parametricEQ *n2Band;      Notch two band object
 *    struct parametricEQ *hsBand;      Highshef band object
 *  }; 
*/

struct eq4Bands {
    struct parametricEQ *lsBand;
    struct parametricEQ *n1Band;
    struct parametricEQ *n2Band;
    struct parametricEQ *hsBand;

};

/* Initialize the filter's EQ structure.
 *
 * Lowshelf vars ***********************
 * freq_ls:     Desired frequency in Hz.
 * q_ls:        filter Q
 * Gain_ls:     Filter gain in dB (cut is negative to boost)
 * Notch 1 vars ************************
 * freq_n1:     Desired frequency in Hz.
 * q_n1:        filter Q
 * Gain_n1:     Filter gain in dB (cut is negative to boost)
 * Notch 2 vars ************************
 * freq_n2:     Desired frequency in Hz.
 * q_n2:        filter Q
 * Gain_n2:     Filter gain in dB (cut is negative to boost)
 * sr:      Sampling rate in Hz.
 * Lowshelf vars ************************
 * freq_hs:     Desired frequency in Hz.
 * q_hs:        filter Q
 * Gain_hs:     Filter gain in dB (cut is negative to boost)
 */
struct eq4Bands * eq4Bands_init(float freq_ls, float q_ls, float gain_ls,
                                float freq_n1, float q_n1, float gain_n1,
                                float freq_n2, float q_n2, float gain_n2,
                                float freq_hs, float q_hs, float gain_hs, float sr
);

/* Delete  filter's structure.
 *
 * struct parametricEQ *data: The structure for which to release memory.
 */
void eq4Bands_delete(struct eq4Bands *data);

/* Process the next sample of filter.
 *
 * struct parametricEQ *data: The structure for which to compute the next sample.
 * float input:        Input signal
 * 
 */
float eq4Bands_process(struct eq4Bands *data, float input);

/* Change the frequency of filter.
 *
 * struct parametricEQ *data:  The structure for which to set a new frequency.
 * float freq :         New frequency value.
 * 
 */
void eq4Bands_set_freq(struct eq4Bands *data, float freq, bandSelect band);

/* Change the q of filter.
 *
 * struct parametricEQ *data:   The structure for which to set a new frequency.
 * float q :                    New q value.
 * 
 */
void eq4Bands_set_q(struct eq4Bands *data, float q, bandSelect band);

/* Change the gain/boost of filter.
 *
 * struct parametricEQ *data:   The structure for which to set a new frequency.
 * float gain :                 New gain value.
 * 
 */
void eq4Bands_set_gain(struct eq4Bands *data, float gain, bandSelect band);

#endif
