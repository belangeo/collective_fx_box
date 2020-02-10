/*
Guide d'implémentation d'un processus audio-numérique en C pour la 
boîte à effets collective.
 
Un effet par pair de fichiers (.h/.c).

Dans le fichier d'en-tête (header), on place les « déclarations »,
c'est-à-dire la signature des fonctions implémentés dans le fichier 
de code (.c) correspondant. Dans le fichier de code, on retrouve
les « définitions », c'est-à-dire l'implémentation complète des
fonctions disponibles.

Les fichiers d'en-tête (.h) sont la partie visible d'une librairie.
On y retrouve tout ce dont l'utilisateur a besoin pour utiliser 
adéquatement la librairie. Ceci inclut aussi les structures que 
l'utilisateur voudra manipuler. C'est ce fichier qu'on donne à une
instruction « include » de notre code pour avoir accès aux diverses
fonctionnalités. Le fichier .c correspondant doit être compilé et
« linker » au code binaire de notre programme.

*/

/*
Une structure pour rassembler toutes les données nécessaires au bon
fonctionnement de l'effet. On peut considérer cette structure comme 
un « objet » de l'effet implémenté.

*/

// .h
struct lp1 {
	float sr;
	float lastout;
	float coeff;
};

/*
Une série de fonctions serviront à manipuler la structure de l'effet.
Au minimum trois fonctions sont nécessaires, une pour  l'initialisation,
une pour la destruction et une pour appliquer le processus au signal 
d'entrée.
*/

/* Fonction d'initialisation */

// .h
struct lp1 * lp1_init(float freq, float sr);

// .c
struct lp1 * 
lp1_init(float freq, float sr) {
    struct lp1 *data = malloc(sizeof(struct lp1 *));
	data->sr = sr;
    data->lastout = 0.0;
    data->coeff = expf(-2.0 * M_PI * freq / sr);
    return data;
}

/* Fonction de destruction */

//.h
void lp1_delete(struct lp1 *data);

// .c
void
lp1_delete(struct lp1 *data) {
	free(data);
}

/* Fonction pour appliquer le processus */

// .h
float lp1_process(struct lp1 *data, float input);

// .c
float
lp1_process(struct lp1 *data, float input) {
    data->lastout = input + (data->lastout - input) * data->coeff;
    return data->lastout;
}

/* On peut créer des fonction pour modifier les paramètres de l'effet */

// .h
void lp1_set_freq(struct lp1 *data, float freq);

// .c
void
lp1_set_freq(struct lp1 *data, float freq) {
    data->coeff = expf(-2.0 * M_PI * freq / data->sr);
}


/**********************************************************************
Assurer qu'un fichier d'en-tête n'est inclut qu'une seule fois, sinon
il y a des erreurs à la compilation dûes aux déclarations multiples des 
structures et fonctions contenues dans le fichier.

#ifndef __LP1_H__
#define __LP1_H__

// Tout le code va ici...

#endif

**********************************************************************/


/**********************************************************************
Vous avez probablement noté deux syntaxes différentes pour l'inclusion
de fichier d'en-tête (#include <lib.h> et #include "lib.h"). La différence
entre les deux est fort simple.

La première version (avec < >) indique un fichier d'en-tête "système",
c'est-à-dire que sa localisation sur le disque est déterminée par 
l'installation de la suite de compilation.

La seconde version (avec " ") indique un fichier d'en-tête "local",
c'est-à-dire propre à votre programme. Si le fichier se trouve dans le
même dossier que le programme principal, le compilateur le trouvera
automatiqument. S'il se trouve dans un autre dossier, il suffit d'ajouter
un chemin où le compilateur cherchera des "headers" avec le flag -I à
la commande de compilation. Par exemple, si on veut avoir accès aux
headers dans le dossier /usr/local/include, on écrirais:

    gcc myprogram.c -I/usr/local/include -o myprogram

Ou, si un dossier "lib", contenant diverses ressources, se trouve dans 
le même dossier que notre programme principal, et que l'on veut inclure
des fichiers d'en-tête s'y trouvant:

    gcc myprogram.c -Ilib -o myprogram


Petit supplément:

https://www.tutorialspoint.com/cprogramming/c_header_files.htm

La librairie standard en C:

https://www.tutorialspoint.com/c_standard_library/index.htm

**********************************************************************/

/**********************************************************************
Gestion de la mémoire...

**********************************************************************/
