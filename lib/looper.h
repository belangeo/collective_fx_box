#ifndef __LOOPER_H__
#define __LOOPER_H__

//#include "sinosc.h"

  
  struct looper {
	  float sr;
	  int maxLoop;
	  float pitch;
	  long writeloop;
	  long readpos;
	  float *buffer; //It s in memory so we want a location and not directly the float.
	  //struct sinosc *sin;
	  int record;
  };
  
  struct looper *looper_init(float lenloop, float pitch, float sr);
  
  void looper_delete(struct looper *loop);
  
  float looper_pitch(struct looper *loop, float newPitch);
  
  float looper_controls(struct looper *loop);
  
  //float looper_midi(struct looper *loop, int midiInput);
  
  float looper_process(struct looper *loop, float input);
	  
  
#endif