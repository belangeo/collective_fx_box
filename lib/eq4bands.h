#ifndef __EQ4BANDS_H__
#define __EQ4BANDS_H__

#include "parametricEQ.h"


struct eq4Bands {
    struct parametricEQ *lsBand;
    struct parametricEQ *n1Band;
    struct parametricEQ *n2Band;
    struct parametricEQ *hsBand;

};

struct eq4Bands * eq4Bands_init(float freq_ls, float q_ls, float gain_ls,
                                float freq_n1, float q_n1, float gain_n1,
                                float freq_n2, float q_n2, float gain_n2,
                                float freq_hs, float q_hs, float gain_hs, float sr
);

void eq4Bands_delete(struct eq4Bands *data);

void eq4Bands_process(struct eq4Bands *data, float input);

void eq4Bands_set_freq(struct parametricEQ *data, float freq);

void eq4Bands_set_q(struct parametricEQ *data, float q);

void eq4Bands_set_gain(struct parametricEQ *data, float gain);

void eq4Bands_set_filterT(struct parametricEQ *data, filterT type);

#endif
