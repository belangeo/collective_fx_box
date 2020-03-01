#include<stdlib.h>
#include "routing.h"

struct bus * init_bus() {
  struct bus * bus = malloc(sizeof(struct bus));
  bus->state = OFF;	    
}

struct routing_matrix * routing_matrix_init() {
  struct routing_matrix * matrix = malloc(sizeof(struct routing_matrix));
  for (int i = 0; i < NB_BUS; i++){
    matrix->bus[i] = init_bus();
  }
  //matrix->inputs = malloc(sizeof(float) * NB_INPUTS);
  return matrix;
}


// TODO: route deleting/turning-off mechanism
void route(struct routing_matrix * mat, enum input_id input, enum bus_id bus) {
  mat->bus[bus]->input = input;
  mat->bus[bus]->state = ON;
}

float matrix_bus_output(struct routing_matrix * mat, enum bus_id bus, float default_value) {
  if (mat->bus[bus]->state == ON) {
    return mat->bus[bus]->output;
  }
  return default_value;
}

void delete_routing_matrix(struct routing_matrix * mat) {
  //free(mat->inputs);
  for (int i = 0; i < NB_BUS; i++) {
    free(mat->bus[i]);
  }
  free(mat);
}

void matrix_update_input(struct routing_matrix * mat, enum input_id input, float value) {
  mat->inputs[input] = value;
}

void matrix_update_outputs(struct routing_matrix * mat) {
  for (int i = 0; i < NB_BUS; i++) {
    mat->bus[i]->output = mat->inputs[mat->bus[i]->input];
  }
}

