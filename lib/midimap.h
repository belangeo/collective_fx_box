/*
 * Allow the user to define a midi config file to map parameter
 * names to midi controller number. Config file must be located
 * in the same directory than the main program and named
 * "midimap.conf". The file must contain one mapping per line.
 * A mapping is the name of the parameter followed by a space,
 * then the controller number. Something like:
 *
 * cutoff 16
 * resonance 17
*/

/* Initialize midi mapping array. */
void midimap_init();

/* Retrieve a controller number from name mapping. */
int midimap_get(char *name);
