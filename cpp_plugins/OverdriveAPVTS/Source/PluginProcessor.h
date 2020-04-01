/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/* Pour utiliser les objets de la librairie, on doit évidemment inclure les
   fichiers d'en-tête nécessaires. 

    Notez la configuration dans le projucer : icône d'engrenage (paramètres
    globaux du projet, valide pour toutes les plateformes) -> Header Search Paths:
    ../../../../lib/

    Notez aussi les "#ifdef __cplusplus" dans les headers en C pour prévenir le 
    "name mangling" du C++. Cette fonctionnalité permet à un programme C++ d'avoir
    plusieurs fonctions portant le même nom (les arguments font la différence),
    elles se verront attibuées un suffixe unique avant la compilation. */
#include "waveshaper.h"
#include "moog.h"

//==============================================================================
/**
*/
class OverdriveApvtsAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    OverdriveApvtsAudioProcessor();
    ~OverdriveApvtsAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================

    /*  Le coeur de la gestion des parametres d'un plugin JUCE. */
    AudioProcessorValueTreeState parameters;

    /* Structures stéréo pour la fonction de transfert et le filtre passe-bas résonant. */
    struct waveshaper *disto[2];
    struct moog *lpres[2];
  
    /*  Pointeurs sur les paramètres bruts (pour un accès rapide à la valeur des paramètres).
        Déclarer un pointeur std::atomic assure qu'il ne sera jamais modifié (accès en écriture)
        en même temps par deux parties (dans ce cas-ci, et le séquenceur et le plugin peuvent
        modifier cette valeur).
    */
    std::atomic<float> *driveParameter = nullptr;
    std::atomic<float> *cutoffParameter = nullptr;
    std::atomic<float> *resParameter = nullptr;

    /*  La fréquence d'échantillonnage courante (pour calculer le coefficient du filtre). */
    double currentSampleRate;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverdriveApvtsAudioProcessor)
};
