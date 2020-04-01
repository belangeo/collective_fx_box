#ifndef __MOOG_H__
#define __MOOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/*	Moog Low Pass Filter

	float sr, nyquist;					Sampling rate, Nyquist frequency					
	float freq, res;					Cutoff frequency, Resonance (0 to 2)
	float p, k, r;						Filter coefficients
	float x1, y1, y2, y3, y4;			Stored signal values
	float oldx1. oldy1, oldy2, oldy3;	,,
*/
struct moog {
	float sr, nyquist;
	float freq, res;
	float p, k, r;
	float x1, y1, y2, y3, y4;
	float oldx1, oldy1, oldy2, oldy3;
};

/* Initialize the Moog Low Pass Filter's structure.
 
 	freq:				Filter's cutoff frequency.
 	res:				Filter's resonance (0 to 2).
 	sr:					Sampling rate in Hz.
 */
struct moog * moog_init(float freq, float res, float sr);

/* Delete the Moog Low Pass Filter's structure.

 	struct moog *data: 	The structure for which to release memory.
 */
void moog_delete(struct moog *data);

/* Process the next sample of the Moog Low Pass Filter.
 
 	struct moog *data:	The structure for which to compute the next sample.
 	float input:		The input signal
 */
float moog_process(struct moog *data, float input);

/* Change the cutoff frequency of the Moog Low Pass Filter.
 
 	struct moog *data:	The structure for which to set a new frequency.
 	float freq:			The new cutoff frequency value.
 */
void moog_set_freq(struct moog *data, float freq);

/* Change the resonance of the Moog Low Pass Filter (0 to 2).
 
 	struct moog *data:	The structure for which to set a new frequency.
 	float res:			The new resonnance value.
 */
void moog_set_res(struct moog *data, float res);

#ifdef __cplusplus
}
#endif

#endif