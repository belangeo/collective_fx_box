#include <stdlib.h>
#include <math.h>
#include "hardclip.h"

/* Distorsion avec differents modes.
	->mode 0 = hardclip
	->mode 1 = mirroir

 */
struct hardclip * 
hardclip_init(float thresh, float sr) {
    struct hardclip *data = malloc(sizeof(struct hardclip)); //Initialisation de l espace memoire
	data->sr = sr; //Nous attribuons le sample rate sr dans l espace memoire lui etant accorde.
	data->thresh=thresh;
    return data;
}

void
hardclip_delete(struct hardclip *data) {
	free(data);
}

float
hardclip_process(struct hardclip *data, float input, float thresh,int mode) {
	float value;
	if (mode ==0)
	{		
		if (input>thresh)
		{
			value = thresh;
		}
		if (input<thresh)
		{
			value=input;
		}
		if (input<-(thresh))
		{
			value = -(thresh);
		}
		value = value * (1/thresh);
	}
	
	if (mode ==1)
	{
		//Si x est plus grand que THRESH, y = THRESH - (x - THRESH), sinon y = x.  
//Si x est plus petit que -THRESH, y = -THRESH + (-THRESH - x), sinon y = x.
		if (input>thresh)
		{
			value=thresh-(input-thresh);
		}
		if (input<thresh)
		{
			value=input;
		}
		if (input< -(thresh))
		{
			value=-(thresh)+(-thresh-input);
		}
		
	}
	return value;
}

/*void
hardclip_set_thresh(struct hardclip *data, float thresh) {
    data->inc = freq / data->sr;
}*/

/*void
phase_reset(struct phasor *data) {
    data->phase = 0.0;
}*/
