/* routing.c
   Fabien Lamarche-Filion, 02 March 2020
*/

#include <stdlib.h>
#include <stdio.h>
#include "routing.h"
#include "utils.h"

struct routing_matrix * routing_matrix_init() {
  struct routing_matrix * matrix = calloc(1, sizeof(struct routing_matrix));
  for (size_t i = 0; i < MAX_BUSSES; i++){
    matrix->bus[i].state = OFF; 
  }
  return matrix;
}

void matrix_route(struct routing_matrix * mat, int input, int bus) {
  if (input < 0 || input >= MAX_INPUTS ||
      bus < 0 || bus >= MAX_BUSSES){
    printf("[ROUTING MATRIX WARNING] Invalid matrix_route:\n\tinput: %d -> bus: %d\n",
	   input, bus);
    return;
  }
  
  mat->bus[bus].input = input;
  mat->bus[bus].state = ON;
  mat->bus[bus].type = SINGLE;
}

void matrix_route_mix(struct routing_matrix * mat, int input, int input_alt, float mix, int bus) {
  if (input < 0 || input >= MAX_INPUTS ||
      input_alt < 0 || input_alt >= MAX_INPUTS ||
      bus < 0 || bus >= MAX_BUSSES){   
    printf("[ROUTING MATRIX WARNING] Invalid matrix_route_mix:\n\tinput: %d + input_alt: %d -> bus: %d\n",
	   input, input_alt, bus);

    return;
  }

  mat->bus[bus].input = input;
  mat->bus[bus].input_alt = input_alt;
  mat->bus[bus].state = ON;
  mat->bus[bus].type = MIX;
  mat->bus[bus].mix = mix;
}

float matrix_bus_output(struct routing_matrix * mat, int bus, float default_value) {
  if (bus < 0 || bus >= MAX_BUSSES) {
    printf("[ROUTING MATRIX WARNING] Invalid matrix_bus_output:\n\tbus: %d\n", bus);
    return default_value;
  }

  if (mat->bus[bus].state == ON) {
    return mat->bus[bus].output;
  }
  return default_value;
}

void matrix_set_bus_mix(struct routing_matrix * mat, int bus, float mix){
  if (bus < 0 || bus >= MAX_BUSSES) {    
    printf("[ROUTING MATRIX WARNING] Invalid matrix_set_bus_mix:\n\tbus: %d\n", bus);
    return;
  }
  
  mat->bus[bus].mix = mix;
}

void matrix_kill_bus(struct routing_matrix * mat, int bus){
  if (bus < 0 || bus >= MAX_BUSSES) {    
    printf("[ROUTING MATRIX WARNING] Invalid matrix_kill_bus:\n\tbus: %d\n", bus);
    return;
  }

  mat->bus[bus].state = OFF;
}

void delete_routing_matrix(struct routing_matrix * mat) {
  free(mat);
}

void matrix_update_input(struct routing_matrix * mat, int input, float value) {
  if (input < 0 || input >= MAX_INPUTS) {    
    printf("[ROUTING MATRIX WARNING] Invalid matrix_update_input:\n\tinput: %d\n", input);
    return;
  }
  
  mat->inputs[input] = value;
}

void matrix_update_all_outputs(struct routing_matrix * mat) {
  for (int i = 0; i < MAX_BUSSES; i++) {
    matrix_update_output(mat, i);
  }
}

void matrix_update_output(struct routing_matrix * mat, int bus){
  if (bus < 0 || bus >= MAX_BUSSES) {    
    printf("[ROUTING MATRIX WARNING] Invalid matrix_update_output:\n\tbus: %d\n", bus);
    return;
  }

  if (mat->bus[bus].state == OFF) return;
  else if (mat->bus[bus].type == SINGLE) {
    mat->bus[bus].output = mat->inputs[mat->bus[bus].input];
  }
  else if (mat->bus[bus].type == MIX) {
    mat->bus[bus].output = interp(mat->inputs[mat->bus[bus].input],
				mat->inputs[mat->bus[bus].input_alt],
				mat->bus[bus].mix);
  }
}

