Distorsion
==========

écrêtage (hard clip)
--------------------

0 < THRESH <= 1

Si x est plus grand que THRESH, y = THRESH, sinon y = x.
Si x est plus petit que -THRESH, y = -THRESH, sinon y = x.
On normalise en multipliant la sortie par 1/THRESH.


effet miroir (folding)
----------------------

0 < THRESH <= 1

Si x est plus grand que THRESH, y = THRESH - (x - THRESH), sinon y = x.
Si x est plus petit que -THRESH, y = -THRESH + (-THRESH - x), sinon y = x.


tangente hyperbolique (tanh)
----------------------------

DRIVE >= 1

y = tanhf(x * DRIVE)


waveshaper
----------

0 <= ALPHA < 1
 
k = (2 * ALPHA) / (1 - ALPHA) 
y = (1 + k) * x / (1 + k * absf(x))



redresseur d'onde
-----------------

0 <= ALPHA <= 1

y = x + (absf(x) - x) * ALPHA

quantification (bit crushing)
-----------------------------

2 < BITS <= 32

k = 2^(BITS-1)
y = roundf(x * k) / k


ré-échantillonnage (réduction de SR)
------------------------------------

0.1 < SCALE <= 1

newsr = sr * SCALE
nsamps = (int)(sr / newsr)

On échantillonne le signal à tous les "nsamps" échantillons et on répète
la valeur échantillonnée entre chaque pige (un sample-and-hold).


Filtrage
========

passe-bas IIR ordre 1
---------------------

Déjà fait dans les fichiers lp1.h/lp1.c


passe-haut IIR ordre 1
----------------------

0 < FREQ < sr/2

c = e^(-2 * pi * FREQ / sr) <===> expf(-2 * pi * FREQ / sr)

y1 = x + (y1 - x) * c
y = x - y1


biquad (IIR ordre 2)
--------------------


eq (IIR ordre 2)
------------------


passe-bas moog (IIR ordre 4)
----------------------------


dcblock
-------


svf (state variable filter)
---------------------------


Délais
======

delay
-----

Déjà fait dans les fichiers delay.h/delay.c


flanger
-------

Signal original mélangé avec une copie de lui-même délayé par un délai
dont la durée oscille lentement (environ 0.1 Hz) entre 0 et 10 ms.


Stochastique
============

randi
-----


randh
-----


logistic equation
-----------------

0 < r < 1  // facteur de chaos
0 < y1 < 1 // valeur initiale

y = (r + 3) * y1 * (1.0 - y1)


Oscillateurs
============

sinus
-----


carrée
------


triangle
--------


dent de scie
------------


rampe
-----


sample-and-hold
---------------


bruit blanc
-----------


Modulation
==========

ring
----


am
--


fm
--


Analyse
=======

suiveur d'enveloppe (follow)
----------------------------


compte des passages à zéro (zcross)
-----------------------------------


Utilitaires
===========

interp (interpolation entre deux signaux)
-----------------------------------------


pan
---


