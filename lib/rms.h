#ifndef __RMS_H__
#define __RMS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Envelope follower structure.
 *
 * size:    Window size in samples (same as buffer size).
 * count:   Sample count.
 * value:   Current sample block RMS value.
 * buffer:  Buffer to hold a block of samples.
 */
struct rms {
    int size;
    int count;
    float value;
    float *buffer;
};

/* Initialize an envelope follower structure.
 *
 * bufsize: Current buffer size in samples.
 *
 * Returns a pointer to a rms structure.
 */
struct rms * rms_init(int bufsize);

/* Delete a envelope follower structure.
 *
 * struct rms *data: The structure for which to release memory.
 */
void rms_delete(struct rms *data);

/* Process the next sample of an envelope follower.
 *
 * struct rms *data: The structure for which to compute the next sample.
 *
 * Returns the current block amplitude value.
 */
float rms_process(struct rms *data, float input);

#ifdef __cplusplus
}
#endif

#endif