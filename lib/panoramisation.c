#include <stdlib.h>
#include <math.h>
#include "panoramisation.h"

/* Implementation of panoramisation.
 */
struct panoramisation * pan_init()
{
	struct panoramisation *pan_data =malloc(sizeof(struct panoramisation));
}

void pan_delete(struct panoramisation *pan_data)
{
	free(pan_data);
}

float pan(float input, int chnl)
{
	float outputL, outputR, output;
	
	outputL=input*(1-chnl);
	outputR=input*chnl;
	
	output=outputL+outputL;
	
	return output;
}