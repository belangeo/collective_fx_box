#include <stdlib.h>
#include <stdio.h>
#include "looper.h"

/*struct looper * 
looper_init(float lenloop, float sr) {
    struct looper *data = malloc(sizeof(struct looper));
	data->sr = sr;
    data->lenloop = (long)(lenloop * sr + 0.5);
    data->writepos = 0;
    data->buffer = (float *)calloc(data->lenloop + 1, sizeof(float));
	//data->readspeed=1;
    return data;
}

void 
looper_delete(struct looper *data) {
    free(data->buffer);
    free(data);
}

float
looper_read(struct looper *data, float deltime) {
    int ipos;
    float frac, samples, readpos, previous, next;
    samples = deltime * data->sr;
    readpos = data->writepos - samples;
    if (readpos < 0) {
        readpos += data->lenloop;
    } else if (readpos >= data->lenloop) {
        readpos -= data->lenloop;
    }
    ipos = (int)readpos;
    frac = readpos - ipos;
    previous = data->buffer[ipos];
    next = data->buffer[ipos + 1];
    return previous + (next - previous) * frac;
}

void
looper_write(struct looper *data, float input) {
    data->buffer[data->writepos] = input;
    if (data->writepos == 0) {
        data->buffer[data->lenloop] = input;
    }
    data->writepos=data->writepos+1;
    if (data->writepos == data->lenloop) {
        data->writepos = 0;
    }
}
*/

  struct looper *looper_init(float lenloop, float sr)
  {
	  struct looper *looper_data =malloc(sizeof(struct looper));
	  looper_data->sr=sr;
	  looper_data->lenloop=lenloop*sr; //Donc si lenloop = .5 alors looper_data->lenloop = 22050 => .5 seconde de loop.
	  looper_data->writeloop = 0; //Initializing 
	  looper_data->buffer = calloc(looper_data->lenloop,sizeof(float)); //We are using calloc because he can keep in memory a large enough space to hold lensize elements.
	  looper_data->sin=sinosc_init(0.1,sr);
	  return looper_data;
  }
  
  void looper_delete(struct looper *data){
	  free(data->buffer);
	  free(data);
  }
  
  float looper_read(struct looper *data, float time){
	  int i;
	  float samples, previous, next, position;
	  samples = time*data->sr; //Donc le temps en seconde voulu * le sample rate pour obtenir le nombre d echantillons a lire et garder en memoire.
	  position = data->writeloop-samples; //Initialement, la position est donc negative;
	  if(position <0)
	  {
		  position=position+data->lenloop; //La position va etre ramenee positive.
	  }
	  else if (position>=data->lenloop)
	  {
		  position=position-data->lenloop; //Ainsi on reste toujours dans la longueur de la loop desiree
	  }
	  i=position;
	  previous = data->buffer[i];
	  next=data->buffer[i+1];
	  return previous;
  } 
  void looper_write(struct looper *data, float input){
	  data->buffer[data->writeloop]=input+sinosc_process(data->sin); //On ecrit les valeurs donnees en input.
	  if (data->writeloop==0)
	  {
		  data->buffer[data->lenloop] = input;
	  }
	  data->writeloop=data->writeloop+1;
	  if (data->writeloop == data->lenloop)
	  {
		  data->writeloop=0;
	  }
  }
  
  /*float looper_process(struct looper *data) {
    float value = sinf(2 * M_PI * data->angle);
    data->angle += data->inc;
    if (data->angle >= 1.0)
        data->angle -= 1.0;
    return value;
}*/