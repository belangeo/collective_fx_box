#ifndef __DELAY_H__
#define __DELAY_H__

/* Delay line structure.
 *
 * sr:          Sampling rate in Hz.
 * maxsize:     Delay line size in samples.
 * writepos:    Position in samples of the writing pointer.
 * buffer:      Dynamically allocated memory used to store buffer.
 */
struct delay {
    float sr;
    long maxsize;
    long writepos;
    float *buffer;
};

/*
 * Initialize a delay line.
 *
 * maxdur:  Maximum delay duration in seconds.
 * sr:      Sampling rate in Hz.
 *
 * Returns a pointer to a delay structure.
 */
struct delay * delay_init(float maxdur, float sr);

/* Delete a delay line structure and free its allocated memory.
 *
 * struct delay *data: The structure for which to release memory.
 */
void delay_delete(struct delay *data);

/* Read a sample `deltime` behind the writing pointer in a delay line.
 * It uses a linear interpolation to read at sub-sample positions.
 *
 * struct delay *data:  The delay structure from which to read.
 * deltime:             The delay time in seconds.
 */
float delay_read(struct delay *data, float deltime);

/* Write a sample at the current position in a delay line.
 *
 * struct delay *data:  The delay structure where to store the sample.
 * input:               The input signal as a float.
 */
void delay_write(struct delay *data, float input);

#endif