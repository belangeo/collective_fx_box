// Fabien Lamarche-Filion

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "delay.h"
#include "bp.h"

// Le nombre de bandes spectrales. Pour chaque bande, l'interface ajoutera une colonne de potentiometres
// Il faut faire attention, la methode pour determiner le Q en fonction des differentes bandes n'est pas
// tout a fait au point, et certaines combinaisons (e.g. NB_BANDS=5 et ARBITRARY_MAX_FREQ=5000.0f) causent
// des resonnances epouvantables.
#define NB_BANDS 8

#define ARBITRARY_MAX_FREQ 12000.0f

//==============================================================================
/**
*/

float arbitrary_freq(int idx, int nbBands);

float arbitrary_q(int nbBands);

// Structure pour une bande frequencielle. Chaque bande a sa propre
// serie de potentiometres.
struct band {
    struct delay * delay[2];
    struct bp * bp[2];
    std::atomic<float> *delayDurationParameter = nullptr;
    std::atomic<float> *delayFeedbackParameter = nullptr;
    std::atomic<float> *delayDryWetParameter = nullptr;
    std::atomic<float> *delayVolumeParameter = nullptr;
};

class MultibandDelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MultibandDelayAudioProcessor();
    ~MultibandDelayAudioProcessor();

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

    struct band band[NB_BANDS];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandDelayAudioProcessor)
};

String makeBandParameter(String param, int band);
