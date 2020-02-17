Fichier principal
-----------------

=> structure DSP
    -> déclaration des processeurs de la "lib"

=> fonctions d'initialisation, de destruction et de traitement

=> fonction "main"
    -> créer une structure DSP
    -> initialisation de portaudio
        -> donner la structure DSP en argument "userData"
    -> activer portaudio
    -> lancer une boucle infinie qui garde le programme vivant et permet d'enter des commandes de contrôle