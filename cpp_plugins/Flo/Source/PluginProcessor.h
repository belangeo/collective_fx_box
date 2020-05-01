/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DelayLine.h"


//==============================================================================
/**
*/
class FloAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    FloAudioProcessor();
    ~FloAudioProcessor();

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
    AudioProcessorValueTreeState parameters;
    
    std::atomic<float> *freqParameter = nullptr;
    SmoothedValue<float> freqSmoothed;

    std::atomic<float> *depthParameter = nullptr;
    SmoothedValue<float> depthSmoothed;

    float currentSampleRate;
    float lfoPhase;
    float lfoInc;
    
    float lastFilteredSample[2];
    
    int writePosition;
    int crossFadeTime;
    int waitingTime;
    int waitingClock;
    int currentDelay;
    float delay1Time;
    float delay2Time;
    float delay1Gain;
    float delay2Gain;
    float gain1Increment;
    float gain2Increment;

    std::atomic<float> *ffreqParameter = nullptr;
    SmoothedValue<float> ffreqSmoothed;
    
    std::atomic<float> *timeParameter = nullptr;
    SmoothedValue<float> timeSmoothed;

    std::atomic<float> *feedbackParameter = nullptr;
    SmoothedValue<float> feedbackSmoothed;

    std::atomic<float> *balanceParameter = nullptr;
    SmoothedValue<float> balanceSmoothed;

    DelayLine delayLine[2];

    void computeDelayTime(float delayTime);
    void updateAmplitude();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FloAudioProcessor)
};
