#ifndef __PHASOR_H__
#define __PHASOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Phasor structure.
 *
 * sr:      Sampling rate in Hz.
 * phase:   Varie to 0 to 1.
 * inc:     Value to add to phase each sampling period.
 */
 
struct phasor {
    float sr;
    float phase;
    float inc;
};

/* Initialize a phasor structure.
	freq:    Desired frequency in Hz.
	sr:      Sampling rate in Hz.
 */
struct phasor * phasor_init(float freq, float sr);

/* Delete a phasor oscillator structure.
	struct phasor *data: The structure for which to release memory.
 */
void phasor_delete(struct phasor *data);

/* Process the next sample of a phasor.
	struct phasor *data: The structure for which to compute the next sample.
 */
float phasor_process(struct phasor *data);

/* Change the frequency of a phasor.
 *
 * struct phasor *data: The structure for which to set a new frequency.
 * float freq:          New frequency in Hz.
 */
void phasor_set_freq(struct phasor *data, float freq);

/* Instantaneously reset the current angle of a phasor to the
 * beginning of the cycle.
 * struct sinosc *data: The structure for which to reset the angle to 0.
 */
void phasor_reset(struct phasor *data);

#ifdef __cplusplus
}
#endif

#endif