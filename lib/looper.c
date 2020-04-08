#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "looper.h"

/*

Choses à implémenter :

	1. La variation de la vitesse de lecture. Oui!
	2. Un contrôle pour commencer à sauvegarder en mémoire la loop et un contrôle pour l'arrêter.
	   Optimalement, on aurait donc pas à prédéfénir une longueur de "loop". Quand on repèse sur
	   le contrôle pour enregistrer à nouveau, ça effacerait l'ancienne loop. Oui!
	3. Un contrôle pour le changement de pitch également. Oui!
	4. Que le input soit considéré seulement quand on enregistre un fragment. Sinon, il est off. Oui!

*/

  struct looper *looper_init(float playrate, float sr)
  {
	  struct looper *looper_data =malloc(sizeof(struct looper));
	  looper_data->sr=sr;
	  looper_data->pitch=playrate;
	  looper_data->maxLoop=10*sr;
	  looper_data->writeloop = looper_data->maxLoop;
	  looper_data->readpos=0.0;
	  looper_data->buffer = calloc(looper_data->maxLoop,sizeof(float)); //We are using calloc because he can keep in memory a large enough space to hold lensize elements.
	  looper_data->record=0;
	  return looper_data;
  }
  
  void looper_delete(struct looper *data){
	  free(data->buffer);
	  free(data);
  }
  
  float looper_set_pitch(struct looper *data, float newPitch)
  {
	   data->pitch=newPitch;  
  }
  
  //Controle les differentes loops qu on enregistre.
  float looper_record(struct looper *data) //Dans le cas du programme actuel ce n est pas necessaire de passer le charInput mais c est pour la prochaine etape ou je voudrais controler les choix dans la fonction.
  {
	if (data->record==0 )
	{
		data->readpos=0.0;
		data->writeloop=0;
		data->record=1;
	} 
	else if (data->record==1)
	{
		data->record=0;
		
	}
  }
  
float looper_process(struct looper *data, float input)
{
	long partint;
	float partfloat, output = 0;
	
	if (data->writeloop < data->maxLoop && data->record==1 )
	{
		data->buffer[data->writeloop]=input;
		if (data->writeloop == 0)
		{
			data->buffer[data->maxLoop]=input;	
		}
		data->writeloop=data->writeloop+1;
		output=input;	
	}	
	else {
		partint=(long)data->readpos;
		partfloat=data->readpos-partint;
		output = data->buffer[partint]+(data->buffer[partint+1]-data->buffer[partint])*partfloat;
		data->readpos=data->readpos+data->pitch;
		if (data->readpos < 0)
		{
			data->readpos=data->readpos+data->writeloop;
		}
		else if (data->readpos >= data->writeloop)
		{
			data->readpos=data->readpos-data->writeloop;
		}
			
	}
	return output;
}


