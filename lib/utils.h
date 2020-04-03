#ifndef __UTILS_H__
#define __UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

float interp(float val1, float val2, float mix);

float cubic(float *buf, int index, float frac, int size);

float scale(float x, float xmin, float xmax, float ymin, float ymax, float ex);

float mtof(float midiNote);

#ifdef __cplusplus
}
#endif

#endif
