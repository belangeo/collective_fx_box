#ifndef __ROUTING_H__
#define __ROUTING_H__

enum bus_id {BUS0, BUS1, NB_BUS}; //Dirty hack. NB_BUS must always be last

enum input_id {LFO1, LFO2, RANDI, RANDH, NB_INPUTS}; //Same for NB_INPUTS

enum state_id {ON, OFF};

struct routing_matrix {
  float inputs[NB_INPUTS];
  struct bus * bus[NB_BUS];
};

//struct bus * init_bus();

void route(struct routing_matrix * mat, enum input_id inut, enum bus_id bus);

struct bus {
  enum input_id input;
  enum state_id state;
  float output;
};

float matrix_bus_output(struct routing_matrix * mat, enum bus_id bus, float default_value);

struct routing_matrix * routing_matrix_init(void);

void delete_routing_matrix(struct routing_matrix * mat);

void matrix_update_input(struct routing_matrix * mat, enum input_id input, float value);

void matrix_update_outputs(struct routing_matrix * mat);

#endif
