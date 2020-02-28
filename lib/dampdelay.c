#include <stdlib.h>
#include <stdio.h>
#include "dampdelay.h"

struct dampdelay * 
dampdelay_init(float maxdur, float freq, float sr) {
    struct dampdelay *data = malloc(sizeof(struct dampdelay));

    // Initialisation des objets utilisés par dampdelay.
    // Les fonctions xxx_init allouent de la mémoire, ne pas oublier 
    // de la rendre au système dans la fonction dampdelay_delete.
    data->delayline = delay_init(maxdur, sr);
    data->lowpass = lp1_init(freq, sr);

   return data;
}

void 
dampdelay_delete(struct dampdelay *data) {
    // On appelle les fonctions xxx_delete correspondantes pour
    // détruire proprement les objets "dans" l'objet dampdelay.
    delay_delete(data->delayline);
    lp1_delete(data->lowpass);

    free(data);
}

float
dampdelay_read(struct dampdelay *data, float deltime) {
    return delay_read(data->delayline, deltime);
}

void
dampdelay_write(struct dampdelay *data, float input) {
    delay_write(data->delayline, lp1_process(data->lowpass, input));
}

void
dampdelay_set_freq(struct dampdelay *data, float freq) {
    lp1_set_freq(data->lowpass, freq);
}