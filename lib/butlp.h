#ifndef __BUTLP_H__
#define __BUTLP_H__

/* Second-order Butterwoth lowpass filter
 *
 *  float freq;                 frequency in Hz
 *  float pi_over_sr;           calcultate pi / sample rate
 *  float nyquist;              calculate Nyquist frequency
 *  float sqrt_2;               calculate square root of 2
 *  float x1, x2, y1, y2;       input and output retained value
 *  float a0, a1, a2, b1, b2;   coefficient calculation
 *  
 */
struct butlp {
    float freq;
    float pi_over_sr;
    float nyquist;
    float sqrt_2;
    float x1, x2, y1, y2;
    float a0, a1, a2, b1, b2;
};

/* Initialize the Butterwoth lowpass filter's structure.
 *
 * freq:    Desired frequency in Hz.
 * sr:      Sampling rate in Hz.
 */
struct butlp * butlp_init(float freq, float sr);

/* Delete Butterwoth lowpass filter's structure.
 *
 * struct butlp *data: The structure for which to release memory.
 */
void butlp_delete(struct butlp *data);

/* Process the next sample of Butterwoth lowpass filter's.
 *
 * struct butlp *data: The structure for which to compute the next sample.
 * float input:        Input signal
 */
float butlp_process(struct butlp *data, float input);

/* Change the frequency of Butterwoth lowpass filter's.
 *
 * struct butlp *data:  The structure for which to set a new frequency.
 * float freq :         New frequency value.

 */
void butlp_set_freq(struct butlp *data, float freq);


#endif