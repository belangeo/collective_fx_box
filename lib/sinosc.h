#ifndef __SINOSC_H__
#define __SINOSC_H__

/* Sine oscillator structure.
 *
 * sr:      Sampling rate in Hz.
 * angle:   Normalized current angle between 0 and 1.
 * inc:     Value to add to angle each sampling period.
 */
struct sinosc {
	float sr;
	float angle;
	float inc;
};

/* Initialize a sine oscillator structure.
 *
 * freq:    Desired frequency in Hz.
 * sr:      Sampling rate in Hz.
 */
struct sinosc * sinosc_init(float freq, float sr);

/* Delete a sine oscillator structure.
 *
 * struct sinosc *data: The structure for which to release memory.
 */
void sinosc_delete(struct sinosc *data);

/* Process the next sample of a sine oscillator.
 *
 * struct sinosc *data: The structure for which to compute the next sample.
 */
float sinosc_process(struct sinosc *data);

/* Change the frequency of a sine oscillator.
 *
 * struct sinosc *data: The structure for which to set a new frequency.
 * float freq:          New frequency in Hz.
 */
void sinosc_set_freq(struct sinosc *data, float freq);

/* Instantaneously reset the current angle of a sine oscillator to the
 * beginning of the cycle.
 *
 * struct sinosc *data: The structure for which to reset the angle to 0.
 */
void sinosc_reset(struct sinosc *data);

#endif