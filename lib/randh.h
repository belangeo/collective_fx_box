#ifndef __RANDH_H__
#define __RANDH_H__

/* Random and hold structure.
 *
 * sr:      Sampling rate in Hz.
 * angle:   Normalized current angle between 0 and 1.
 * inc:     Value to add to angle each sampling period.
 */
struct randh {
	float sr;
	float angle;
	float inc;
	float output;
};

/* Initialize a randh structure.
 *
 * freq:    Desired frequency in Hz.
 * sr:      Sampling rate in Hz.
 *
 * Returns a pointer to a randh structure.
 */
struct randh * randh_init(float freq, float sr);

/* Delete a randh structure.
 *
 * struct randh *data: The structure for which to release memory.
 */
void randh_delete(struct randh *data);

/* Process the next sample of a randh.
 *
 * struct randh *data: The structure for which to compute the next sample.
 */
float randh_process(struct randh *data);

/* Change the frequency of a randh.
 *
 * struct randh *data: The structure for which to set a new frequency.
 * float freq:          New frequency in Hz.
 */
void randh_set_freq(struct randh *data, float freq);

#endif