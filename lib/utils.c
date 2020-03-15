#include "utils.h"

float interp(float val1, float val2, float mix){
  if (mix > 1.0) return val2;
  else if (mix < 0.0) return val1;;
  return val1 + (val2 - val1) * mix;
}
