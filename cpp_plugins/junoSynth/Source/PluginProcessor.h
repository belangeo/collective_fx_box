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
struct JunoSynthSound   : public SynthesiserSound
{
    JunoSynthSound() {}
    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};

//==============================================================================
struct JunoSynthVoice   : public SynthesiserVoice
{
    JunoSynthVoice();

    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}

    bool canPlaySound (SynthesiserSound *sound) override;

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound *, int /*currentPitchWheelPosition*/) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;

    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

    void setLfoAttenuatorParameter(float lfoAttenuator);
    void setPwParameter(float pw);
    void setPwModulationParameter(float pwMod);
    void setSubVolumeParameter(float subVol);
    void setNoiseVolumeParameter(float noiseVol);
    void setSquareIsOnParameter(float squareIsOn);
    void setTriangleIsOnParameter(float triangleIsOn);
    void setSubIsOnParameter(float subIsOn);
    void setEnvelopeParameters(ADSR::Parameters params);

private:
    struct junoDCO *dco;
    ADSR envelope;
};

//==============================================================================
class JunoSynth : public Synthesiser
{
public:
    void setLfoAttenuatorParameter(float lfoAttenuator);
    void setPwParameter(float pw);
    void setPwModulationParameter(float pwMod);
    void setSubVolumeParameter(float subVol);
    void setNoiseVolumeParameter(float noiseVol);
    void setSquareIsOnParameter(float squareIsOn);
    void setTriangleIsOnParameter(float triangleIsOn);
    void setSubIsOnParameter(float subIsOn);
    void setEnvelopeParameters(ADSR::Parameters params);
};

//==============================================================================
class JunoSynthAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JunoSynthAudioProcessor();
    ~JunoSynthAudioProcessor();

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
    AudioProcessorValueTreeState parameters;

    JunoSynth synthesiser;

    std::atomic<float> *lfoAttenuatorParameter = nullptr;
    std::atomic<float> *pwParameter = nullptr;
    std::atomic<float> *pwModulationParameter = nullptr;
    std::atomic<float> *subVolumeParameter = nullptr;
    std::atomic<float> *noiseVolumeParameter = nullptr;
    std::atomic<float> *squareIsOnParameter = nullptr;
    std::atomic<float> *triangleIsOnParameter = nullptr;
    std::atomic<float> *subIsOnParameter = nullptr;

    std::atomic<float> *attackParameter = nullptr;
    std::atomic<float> *decayParameter = nullptr;
    std::atomic<float> *sustainParameter = nullptr;
    std::atomic<float> *releaseParameter = nullptr;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoSynthAudioProcessor)
};
