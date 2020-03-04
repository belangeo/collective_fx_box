#ifndef __LOOPER_H__
#define __LOOPER_H__

#include "sinosc.h"

  
  struct looper {
	  float sr;
	  long lenloop;
	  long writeloop;
	  float *buffer; //It s in memory so we want a location and not directly the float.
	  struct sinosc *sin;
  };
  
  struct looper *looper_init(float lenloop,float sr);
  
  void looper_delete(struct looper *data);
  
  float looper_read(struct looper *data, float time); //To know how many samples we are keeping in memory.
  
  void looper_write(struct looper *data, float input);
  
  //float looper_process(struct looper *data);

	  
  
#endif