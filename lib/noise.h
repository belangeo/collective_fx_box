#ifndef __NOISE_H__
#define __NOISE_H__

#ifdef __cplusplus
extern "C" {
#endif

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

/* Instantaneously reset the current angle of a sine oscillator to the
 * beginning of the cycle.
 *
 * struct noise *data: The structure for which to reset the angle to 0.
 */
void noise_reset(struct noise *data);

#ifdef __cplusplus
}
#endif

#endif
