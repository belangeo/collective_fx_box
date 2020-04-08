#ifndef __PHASOR_H__
#define __PHASOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Panoramisation structure.
 *
 * chn_out: Le canal de sorti dans lequel nous voulons envoye le son.
 */
 
struct panoramisation {
};

struct panoramisation * pan_init();

void pan_delete(struct panoramisation *pan_data);

float pan(float input, int chnl);



#ifdef __cplusplus
}
#endif

#endif