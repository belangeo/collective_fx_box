/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "phasor.h"
#include "noise.h"
#include "junoDCO.h"
//==============================================================================
/**
*/
class JunoDcopluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JunoDcopluginAudioProcessor();
    ~JunoDcopluginAudioProcessor();

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

    MidiKeyboardState keyboardState;

private:
    //==============================================================================
    /*  Le coeur de la gestion des parametres d'un plugin JUCE. */
    
    AudioProcessorValueTreeState parameters;

    /* Structures stéréo pour la fonction de transfert et le filtre passe-bas résonant. */
    struct junoDCO *voiceDCO[2];
  
    /*  Pointeurs sur les paramètres bruts (pour un accès rapide à la valeur des paramètres).
        Déclarer un pointeur std::atomic assure qu'il ne sera jamais modifié (accès en écriture)
        en même temps par deux parties (dans ce cas-ci, et le séquenceur et le plugin peuvent
        modifier cette valeur).
    */
    std::atomic<float> *lfoAttenuatorParameter = nullptr;
    std::atomic<float> *pwParameter = nullptr;
    std::atomic<float> *pwModulationParameter = nullptr;
    std::atomic<float> *subVolumeParameter = nullptr;
    std::atomic<float> *noiseVolumeParameter = nullptr;
    std::atomic<float> *squareIsOnParameter = nullptr;
    std::atomic<float> *triangleIsOnParameter = nullptr;
    std::atomic<float> *subIsOnParameter = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoDcopluginAudioProcessor)
};
