/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
*/
class JunoSynthAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    JunoSynthAudioProcessorEditor (JunoSynthAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~JunoSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
/*  This reference is provided as a quick way for your editor to
    access the processor object that created it.    */
    JunoSynthAudioProcessor& processor;

    CustomLookAndFeel lookAndFeel;
/*  Référence à l'arbre des paramètres dans l'éditeur graphique.    */
    AudioProcessorValueTreeState& valueTreeState;

/*  Labels. 
    Potentiomètres. 
    SliderAttachment    */
/*	DCO		*/
    Label lfoAttenuatorLabel;
    Slider lfoAttenuator;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoAttenuatorAttachment;

    Label pwLabel;
    Slider pw;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwAttachment;

    Label pwModulationLabel;
    Slider pwModulation;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwModulationAttachment;

    Label subVolumeLabel;
    Slider subVolume;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> subVolumeAttachment;

    Label noiseVolumeLabel;
    Slider noiseVolume;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noiseVolumeAttachment;

    Label squareIsOnLabel;
    ToggleButton squareIsOn;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> squareIsOnAttachment;

    Label triangleIsOnLabel;
    ToggleButton triangleIsOn;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> triangleIsOnAttachment;

    Label subIsOnLabel;
    ToggleButton subIsOn;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> subIsOnAttachment;

/*	ENVELOPE ADSR	*/
    Label  attackLabel;
    Slider attackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackAttachment;

    Label  decayLabel;
    Slider decayKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decayAttachment;

    Label  sustainLabel;
    Slider sustainKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainAttachment;

    Label  releaseLabel;
    Slider releaseKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseAttachment;

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoSynthAudioProcessorEditor)
};
