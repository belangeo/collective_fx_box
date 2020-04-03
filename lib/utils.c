#include <math.h>
#include "utils.h"

float interp(float val1, float val2, float mix){
  if (mix > 1.0) return val2;
  else if (mix < 0.0) return val1;;
  return val1 + (val2 - val1) * mix;
}

float cubic(float *buf, int index, float frac, int size) {
    float x0, x3, a0, a1, a2, a3;
    float x1 = buf[index];
    float x2 = buf[index+1];

    if (index == 0) {
        x0 = x1 + (x1 - x2);
        x3 = buf[index + 2];
    }
    else if (index >= (size-2)) {
        x0 = buf[index - 1];
        x3 = x2 + (x2 - x1);
    }
    else {
        x0 = buf[index - 1];
        x3 = buf[index + 2];
    }

    a3 = frac * frac; a3 -= 1.0; a3 *= (1.0 / 6.0);
    a2 = (frac + 1.0) * 0.5; a0 = a2 - 1.0;
    a1 = a3 * 3.0; a2 -= a1; a0 -= a3; a1 -= frac;
    a0 *= frac; a1 *= frac; a2 *= frac; a3 *= frac; a1 += 1.0;

    return (a0 * x0 + a1 * x1 + a2 * x2 + a3 * x3);
}

float scale(float x, float xmin, float xmax, float ymin, float ymax, float ex) {
    x -= xmin;
    x /= (xmax - xmin);
    x = pow(x, ex);
    x *= (ymax - ymin);
    x += ymin;
    return x;
}

float mtof(int midiNote) {
	return 440.0 * pow(2.0, (midiNote - 69) / 12.0);
}
