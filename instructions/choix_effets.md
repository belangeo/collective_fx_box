Distorsion
----------

- écrêtage (hard clip)
- tangente hyperbolique (tanh)
- waveshaper
- effet miroir (folding)
- redresseur d'onde
- quantification (bit crushing)
- ré-échantillonnage (réduction de SR)


Filtrage
--------

- passe-bas IIR ordre 1
- passe-haut IIR ordre 1
- biquad (IIR ordre 2)
- eq (IIR ordre 2)
- passe-bas moog (IIR ordre 4)
- dcblock
- svf


Délai
-----

- delay
- flanger


Stochastique
------------

- randi
- randh
- logistic equation ?
	x[n] = (r + 3) * x[n-1] * (1.0 - x[n-1])
	where 'r' is the randomization factor between 0 and 1.

Oscillateurs
------------

- sinus
- carrée
- triangle
- dent de scie
- rampe
- sample-and-hold
- bruit blanc


Modulation
----------

- ring
- am
- fm


Analyse
-------

- suiveur d'enveloppe (follow)
- compte des passages à zéro (zcross)


Utilitaires
-----------

- interp (interpolation entre deux signaux)
- pan

