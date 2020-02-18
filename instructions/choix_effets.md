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

Voir "Cookbook formulae for audio EQ biquad filter coefficients" de RBJ


eq (IIR ordre 2)
------------------

Voir "Cookbook formulae for audio EQ biquad filter coefficients" de RBJ


passe-bas moog (IIR ordre 4)
----------------------------

0.1 < FREQ < sr/2  
0 < RES < 10

f = (FREQ + FREQ) / sr  
fi = 1.0 - f

p = f * (1.8 - 0.8 * f)  
k = 2.0 * sinf(f * pi * 0.5) - 1.0  
t = (1.0 - p) * 1.386249  
t2 = 12.0 + t * t  
r = RES * 0.5 * (t2 + 6.0 * t) / (t2 - 6.0 * t)  
r *= fi * fi * fi * 0.9 + 0.1  // Resonance compensation according to normalized frequency.

// Needs p, k, r

x1 = x - r * y4  
y1 = (x1 + oldX1) * p - k * y1  
y2 = (y1 + oldY1) * p - k * y2  
y3 = (y2 + oldY2) * p - k * y3  
y4 = (y3 + oldY3) * p - k * y4  
y4 -= (y4 * y4 * y4) * 0.16666666666666666  
oldX1 = x1; oldY1 = y1; oldY2 = y2; oldY3 = y3  
y = y4


dcblock
-------

y = y1 = x - x1 + 0.995 * y1  
x1 = x


svf (state variable filter)
---------------------------

0 < FREQ < sr/2  
Q >= 0.5

w = 2.0 * sinf(FREQ * pi / sr)  
q1 = 1 / Q

low = y2 + w * y1  
high = x - low - q1 * y1  
band = w * high + y1  
y1 = band  
y2 = low  

0 <= TYPE <= 1

lowgain = (type <= 0.5) ? (0.5 - type) : 0.0  
highgain = (type >= 0.5) ? (type - 0.5) : 0.0  
bandgain = (type <= 0.5) ? type : (1.0 - type)


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

Déjà fait dans les fichiers sincosc.h/sinosc.c


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


