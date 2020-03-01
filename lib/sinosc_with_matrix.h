#ifndef __SINOSC_WITH_MATRIX_H__
#define __SINOSC_WITH_MATRIX_H__

#include "routing.h"
/* Sine oscillator structure.
 *
 * sr:      Sampling rate in Hz.
 * angle:   Normalized current angle between 0 and 1.
 * inc:     Value to add to angle each sampling period.
 */
struct sinosc_with_matrix {
	float sr;
	float angle;
	float freq;
        struct routing_matrix * matrix;
};

/* Initialize a sine oscillator structure.
 *
 * freq:    Desired frequency in Hz.
 * sr:      Sampling rate in Hz.
 *
 * Returns a pointer to a sinosc_with_matrix structure.
 */
struct sinosc_with_matrix * sinosc_with_matrix_init(float freq, float sr, struct routing_matrix * mat);

/* Delete a sine oscillator structure.
 *
 * struct sinosc_with_matrix *data: The structure for which to release memory.
 */
void sinosc_with_matrix_delete(struct sinosc_with_matrix *data);

/* Process the next sample of a sine oscillator.
 *
 * struct sinosc_with_matrix *data: The structure for which to compute the next sample.
 */
float sinosc_with_matrix_process(struct sinosc_with_matrix *data);

/* Change the frequency of a sine oscillator.
 *
 * struct sinosc_with_matrix *data: The structure for which to set a new frequency.
 * float freq:          New frequency in Hz.
 */
void sinosc_with_matrix_set_freq(struct sinosc_with_matrix *data, float freq);

/* Instantaneously reset the current angle of a sine oscillator to the
 * beginning of the cycle.
 *
 * struct sinosc_with_matrix *data: The structure for which to reset the angle to 0.
 */
void sinosc_with_matrix_reset(struct sinosc_with_matrix *data);

#endif
