#ifndef __LOOPER_H__
#define __LOOPER_H__

#ifdef __cplusplus
extern "C" {
#endif

//#include "sinosc.h"

  
  struct looper {
	  float sr;
	  long maxLoop;
    long loopLength;
	  float pitch;
	  long writeloop;
	  float readpos;
	  float *buffer; //It s in memory so we want a location and not directly the float.
	  int record;
  };
  
  struct looper *looper_init(float lenloop, float pitch, float sr);
  
  void looper_delete(struct looper *loop);
  
  float looper_pitch(struct looper *loop, float newPitch);
  
  float looper_controls(struct looper *loop);
  
  float looper_process(struct looper *loop, float input);
	  
#ifdef __cplusplus
}
#endif

#endif