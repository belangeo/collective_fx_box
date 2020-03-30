#include <stdio.h>      /* fscanf, snprintf, EOF */
#include <string.h>     /* strcpy, strcmp */

// TODO: replace this "loop over the list" mecanism by a proper hash table.

static char midimap_str[128][128];

void midimap_init() {
    int i, ctlnum;
    char name[128];
    FILE *config;

    for (i=0; i<128; i++) {
        snprintf(name, 128, "%i", i);
        strcpy(midimap_str[i], name);
    }

    config = fopen("midimap.conf", "r");
    if (config == NULL) {
        config = fopen("config/midimap.conf", "r");
    }

    if (config != NULL) {
        while (fscanf(config, "%s %i\n", name, &ctlnum) != EOF) {
            strcpy(midimap_str[ctlnum], name);
        }
    }
}

int midimap_get(char *name) {
    int i;
    for (i=0; i<128; i++) {
        if (strcmp(name, midimap_str[i]) == 0)
            return i;
    }
    return -1;
}
