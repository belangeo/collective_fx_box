#ifndef __ROUTING_H__
#define __ROUTING_H__

#define MAX_BUSSES 32
#define MAX_INPUTS 32

enum state_id {ON, OFF};

struct routing_matrix {
  float inputs[MAX_INPUTS];
  struct bus * bus[MAX_BUSSES];
};

//struct bus * init_bus();

void matrix_route(struct routing_matrix * mat, int inut, int bus);

struct bus {
  int input;
  enum state_id state;
  float output;
};

float matrix_bus_output(struct routing_matrix * mat, int bus, float default_value);

struct routing_matrix * routing_matrix_init(void);

void delete_routing_matrix(struct routing_matrix * mat);

void matrix_update_input(struct routing_matrix * mat, int input, float value);

void matrix_update_outputs(struct routing_matrix * mat);

#endif
