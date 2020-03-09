/* routing.h
   Fabien Lamarche-Filion, 02 March 2020
*/


#ifndef __ROUTING_H__
#define __ROUTING_H__

#define MAX_BUSSES 32
#define MAX_INPUTS 32

enum state_id {ON, OFF};
enum type_id {SINGLE, MIX};

struct bus {
  int input;
  int input_alt;
  enum type_id type;
  enum state_id state;
  float mix;
  float output;
};

struct routing_matrix {
  float inputs[MAX_INPUTS];
  struct bus bus[MAX_BUSSES];
};

struct routing_matrix * routing_matrix_init(void);

void delete_routing_matrix(struct routing_matrix * mat);

float matrix_bus_output(struct routing_matrix * mat, int bus, float default_value);

void matrix_route(struct routing_matrix * mat, int input, int bus);

void matrix_route_mix(struct routing_matrix * mat, int input, int input_alt, float mix,  int bus);

void matrix_set_bus_mix(struct routing_matrix * mat, int bus, float mix);

void matrix_kill_bus(struct routing_matrix * mat, int bus);

void matrix_update_input(struct routing_matrix * mat, int input, float value);

void matrix_update_outputs(struct routing_matrix * mat);

#endif
