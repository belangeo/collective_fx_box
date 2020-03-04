#include"utils.h"

float interp(float val1, float val2, float mix){
  if (mix > 1.0) mix = 1.0;
  if (mix < 0.0) mix = 0.0;
  return (1.0 - mix) * val1 + mix * val2;
}
