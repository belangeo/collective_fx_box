#ifndef __LOOPER_H__
#define __LOOPER_H__

#include "sinosc.h"
/*
 looper line structure.
 *
 * sr:          Sampling rate in Hz.
 * lenloop:     loop line size in samples.
 * writepos:    Position in samples of the writing pointer.
 * buffer:      Dynamically allocated memory used to store buffer.
 
struct looper {
    float sr;
    long writepos;
	long lenloop;
    float *buffer; //To keep in memory the sample we want to loop
	//float readspeed;
};


 * Initialize a looper line.
 *
 * lenloop:  Maximum looper duration in seconds.
 * sr:      Sampling rate in Hz.
 *
 * Returns a pointer to a looper structure.

struct looper * looper_init(float lenloop, float sr);

Delete a looper line structure and free its allocated memory.
 *
 * struct looper *data: The structure for which to release memory.

void looper_delete(struct looper *data);

Read a sample `deltime` behind the writing pointer in a looper line.
 * It uses a linear interpolation to read at sub-sample positions.
 *
 * struct looper *data:  The looper structure from which to read.
 * deltime:             The looper time in seconds.

float looper_read(struct looper *data, float deltime);

 Write a sample at the current position in a looper line.
 *
 * struct looper *data:  The looper structure where to store the sample.
 * input:               The input signal as a float.

void looper_write(struct looper *data, float input);

*/

/*looper structure
  sr : Samplerate in Hz
  lenloop : size of the loop in samples.
  writeloop : writing position in samples.
  buffer : to keep in memory an indetermined amount of samples.
  */
  
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