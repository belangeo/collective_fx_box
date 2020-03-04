#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "looper.h"

/*

Choses à implémenter :

	1. La variation de la vitesse de lecture.
	2. Un contrôle pour commencer à sauvegarder en mémoire la loop et un contrôle pour l'arrêter.
	   Optimalement, on aurait donc pas à prédéfénir une longueur de "loop". Quand on repèse sur
	   le contrôle pour enregistrer à nouveau, ça effacerait l'ancienne loop.
	3. Un contrôle pour le changement de pitch également.
	4. Que le input soit considéré seulement quand on enregistre un fragment. Sinon, il est off. 

*/

  struct looper *looper_init(float lenloop, float sr)
  {
	  struct looper *looper_data =malloc(sizeof(struct looper));
	  looper_data->sr=sr;
	  looper_data->lenloop=lenloop*sr; //Donc si lenloop = .5 alors looper_data->lenloop = 22050 => .5 seconde de loop.
	  looper_data->writeloop = 0; //Initializing 
	  looper_data->valOsc=0;
	  looper_data->buffer = calloc(looper_data->lenloop,sizeof(float)); //We are using calloc because he can keep in memory a large enough space to hold lensize elements.
	  //looper_data->sin=sinosc_init(10,sr);
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
	  data->valOsc = previous + (data->valOsc - previous)*0.01;//expf(-2);//expf(-2.0 * M_PI * 8000 / data->sr);
	  return previous;
  } 
  void looper_write(struct looper *data, float input){
	  data->buffer[data->writeloop]=input+data->valOsc;
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
  
