#include <stdlib.h>
#include <math.h>
#include "compress.h"
#include "delay.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

struct compress *compress_init(float thresh, float ratio, float attack, float release, float lookahead, float sr){
    //struct delay *data = malloc(sizeof(struct delay));
    
    struct compress *data = malloc(sizeof(struct compress));
    // Avoir des protections sur les valeurs ratio
    data->thresh = thresh;
    data->ratio = ratio;
    data->attack = attack;
    data->release = release;
    data->lookahead = lookahead;
    data->look(sr/8, sr);
    data->y0 = 0.0;
    float freq_ = 1/(attack * 0.001);
    data->acoeff = exp(-2 * M_PI * freq_ / sr);
    freq_ = 1 / (release * 0.001);
    data->rcoeff = exp(-2 * M_PI * freq_ / sr);

}