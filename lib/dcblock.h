#ifndef __DCBLOCK_H__
#define __DCBLOCK_H__

#ifdef __cplusplus
extern "C" {
#endif

struct dcblock {
    float lastin;
    float lastout;
};

struct dcblock * dcblock_init();

void dcblock_delete(struct dcblock *data);

float dcblock_process(struct dcblock *data, float input);

#ifdef __cplusplus
}
#endif

#endif