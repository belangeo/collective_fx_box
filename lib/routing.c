/* routing.c
   Fabien Lamarche-Filion, 02 March 2020
*/

#include<stdlib.h>
#include "routing.h"
#include "utils.h"

struct routing_matrix * routing_matrix_init() {
  struct routing_matrix * matrix = malloc(sizeof(struct routing_matrix));
  for (int i = 0; i < MAX_BUSSES; i++){
    matrix->bus[i].state = OFF; 
  }
  return matrix;
}

void matrix_route(struct routing_matrix * mat, int input, int bus) {
  mat->bus[bus].input = input;
  mat->bus[bus].state = ON;
  mat->bus[bus].type = SINGLE;
}

void matrix_route_mix(struct routing_matrix * mat, int input, int input_alt, float mix, int bus) {
  mat->bus[bus].input = input;
  mat->bus[bus].input_alt = input_alt;
  mat->bus[bus].state = ON;
  mat->bus[bus].type = MIX;
  mat->bus[bus].mix = mix;
}

float matrix_bus_output(struct routing_matrix * mat, int bus, float default_value) {
  if (mat->bus[bus].state == ON) {
    return mat->bus[bus].output;
  }
  return default_value;
}

void matrix_set_bus_mix(struct routing_matrix * mat, int bus, float mix){
  mat->bus[bus].mix = mix;
}

void matrix_kill_bus(struct routing_matrix * mat, int bus){
  mat->bus[bus].state = OFF;
}

void delete_routing_matrix(struct routing_matrix * mat) {
  free(mat);
}

void matrix_update_input(struct routing_matrix * mat, int input, float value) {
  mat->inputs[input] = value;
}

void matrix_update_outputs(struct routing_matrix * mat) {
  for (int i = 0; i < MAX_BUSSES; i++) {
    if (mat->bus[i].state == OFF) continue;
    else if (mat->bus[i].type == SINGLE) {
      mat->bus[i].output = mat->inputs[mat->bus[i].input];
    }
    else if (mat->bus[i].type == MIX) {
      mat->bus[i].output = interp(mat->inputs[mat->bus[i].input],
				   mat->inputs[mat->bus[i].input_alt],
				   mat->bus[i].mix);
    }
  }
}

