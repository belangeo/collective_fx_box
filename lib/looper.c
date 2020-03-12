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
	  looper_data->writeloop = looper_data->lenloop; //Initializing 
	  looper_data->pitch=1;
	  looper_data->readpos=0.0;
	  looper_data->buffer = calloc(looper_data->lenloop,sizeof(float)); //We are using calloc because he can keep in memory a large enough space to hold lensize elements.
	  return looper_data;
  }
  
  void looper_delete(struct looper *data){
	  free(data->buffer);
	  free(data);
  }
  
  float looper_record(struct looper *data)
  {
	  data->readpos=0.0;
	  data->writeloop=0;
  }
  
float looper_process(struct looper *data, float input)
{
	long partint;
	float partfloat, output = 0;
	
	if (data->writeloop < data->lenloop)
	{
		data->buffer[data->writeloop]=input;
		if (data->writeloop == 0)
		{
			data->buffer[data->lenloop]=input;
			
		}
		data->writeloop=data->writeloop+1;
		output=input;
	}
	else{
		partint=(long)data->readpos;
		partfloat=data->readpos-partint;
		output = data->buffer[partint]+(data->buffer[partint+1]-data->buffer[partint])*partfloat;
		data->readpos=data->readpos+data->pitch;
		if (data->readpos < 0)
		{
			data->readpos=data->readpos+data->lenloop;
		}
		else if (data->readpos >= data->lenloop)
		{
			data->readpos=data->readpos-data->lenloop;
		}
			
	}
	return output;
}
