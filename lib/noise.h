#ifndef __NOISE_H__
#define __NOISE_H__

/* Noise structure */

struct noise {
  int seed;
};

/* Initialize a noise structure.*/
struct noise * noise_init();

/* Delete a sine oscillator structure.
 *
 * struct noise *data: The structure for which to release memory.
 */
void noise_delete(struct noise *data);

/* Process the next sample of noise
 *
 * struct noise *data: The structure for which to compute the next sample.
 */
float noise_process(struct noise *data);

/* Change the frequency of a sine oscillator.
 *
 * struct noise *data: The structure for which to set a new frequency.
 * float freq:          New frequency in Hz.
 */
void noise_set_freq(struct noise *data, float freq);
/* Instantaneously reset the current angle of a sine oscillator to the
 * beginning of the cycle.
 *
 * struct noise *data: The structure for which to reset the angle to 0.
 */
void noise_reset(struct noise *data);

#endif
