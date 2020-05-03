/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*  Commentaire d'Oliveir B.
 
    Pour utiliser les objets de la librairie, on doit évidemment inclure les
    fichiers d'en-tête nécessaires.

    Notez la configuration dans le projucer : icône d'engrenage (paramètres
    globaux du projet, valide pour toutes les plateformes) -> Header Search Paths:
    ../../../../lib/

    Notez aussi les "#ifdef __cplusplus" dans les headers en C pour prévenir le
    "name mangling" du C++. Cette fonctionnalité permet à un programme C++ d'avoir
    plusieurs fonctions portant le même nom (les arguments font la différence),
    elles se verront attibuées un suffixe unique avant la compilation.
 
 **********************************************************************************
 
 */
#include "eq4bands.h"

//==============================================================================
/**
*/
class PluginCarlAksyAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PluginCarlAksyAudioProcessor();
    ~PluginCarlAksyAudioProcessor();

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
    
    AudioProcessorValueTreeState parameters;

    // Struture de la librairie collective_box
    struct eq4Bands *eq4B[2];

    std::atomic<float>* freqLsParameter = nullptr;
    std::atomic<float>* qLsParameter = nullptr;
    std::atomic<float>* gainLsParameter  = nullptr;
    
    std::atomic<float>* freqN1Parameter = nullptr;
    std::atomic<float>* qN1Parameter = nullptr;
    std::atomic<float>* gainN1Parameter  = nullptr;
    
    std::atomic<float>* freqN2Parameter = nullptr;
    std::atomic<float>* qN2Parameter = nullptr;
    std::atomic<float>* gainN2Parameter  = nullptr;
    
    std::atomic<float>* freqHsParameter = nullptr;
    std::atomic<float>* qHsParameter = nullptr;
    std::atomic<float>* gainHsParameter  = nullptr;
       
    /*  La fréquence d'échantillonnage courante (pour calculer le coefficient du filtre). */
    double currentSampleRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginCarlAksyAudioProcessor)
   
};
