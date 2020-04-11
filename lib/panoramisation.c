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

float pan(const float input,float* output, int index, int index2, float chnl)
{
		int indexL=index*2;
		int indexR=index*2+1;	
		
		output[indexR]=input*(chnl);
		output[indexL]=input*(1-chnl);	
		
		return output[indexR] + output[indexL];

							
}

/*float robot(const float *input,float* output, int index, float chnl)
{
		int indexL=index*2;
		int indexR=index*2+1;	
				
		output[indexR]=input[indexR]*(chnl);
		output[indexL]=input[indexL]*(1-chnl);
		
		output[index]=output[indexR]+output[indexL];
		
		return output[index];
}*/