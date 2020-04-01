#ifndef __HARDCLIP_H__
#define __HARDCLIP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* hardclip structure.

0 < THRESH <= 1

Si x est plus grand que THRESH, y = THRESH, sinon y = x.  
Si x est plus petit que -THRESH, y = -THRESH, sinon y = x.  
On normalise en multipliant la sortie par 1/THRESH.

 *
 * sr:      Sampling rate in Hz.
 * thresh:  Limit 
 */
 
struct hardclip {
    float sr;
	float thresh;
};

/* Initialize a hardclip structure.
	thresh:  Desired limit.
	sr:      Sampling rate in Hz.
 */
struct hardclip * hardclip_init(float thresh, float sr);

/* Delete a phasor oscillator structure.
	struct phasor *data: The structure for which to release memory.
 */
void hardclip_delete(struct hardclip *data);

/* Process the next sample of a phasor.
	struct phasor *data: The structure for which to compute the next sample.
 */
float hardclip_process(struct hardclip *data, float input, float thresh, int mode);

#ifdef __cplusplus
}
#endif

#endif