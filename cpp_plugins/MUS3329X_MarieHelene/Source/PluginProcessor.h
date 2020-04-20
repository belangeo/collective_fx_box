/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class RobotVoiceAudioProcessor : public AudioProcessor
{
public:
    //==============================================================================
    RobotVoiceAudioProcessor();
    ~RobotVoiceAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

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
    void setCurrentProgram(int index) override;
    const String getProgramName(int index) override;
    void changeProgramName(int index, const String& newName) override;

    //==============================================================================
    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    //==============================================================================
    //Variables to put together the slider with a value in the processor
    float volumeMeter;
    float freqMeter;
    float wetMeter;
    float compMeter;
    float wetCompMeter;
    float wetAmpMeter;

private:
    //==============================================================================
    //Variables we need to generate sinus
    float gen_amplitude;
    float gen_frequency;
    float gen_phase; //starting point
    float gen_time; //time counter
    float gen_deltaTime;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RobotVoiceAudioProcessor)
};
