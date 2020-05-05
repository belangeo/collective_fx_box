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

/*  Labels 
    Potentiomètres 
    Attachments    */

/*	VOLUME 	*/
    Label 	volumeLabel;
    Slider 	volumeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> volumeKnobAttachment;

/*	LFO		*//*
    Label 	lfoRateLabel;
    Slider 	lfoRateSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoRateSliderAttachment;

    Label 	lfoDelayLabel;
    Slider 	lfoDelaySlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoDelaySliderAttachment;
*/
/*	DCO		*//*
    Label 	lfoAttenuatorLabel;
    Slider 	lfoAttenuatorSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoAttenuatorSliderAttachment;
*/
    Label 	pwLabel;
    Slider 	pwSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwSliderAttachment;

    Label 	pwModulationLabel;
    Slider 	pwModulationSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwModulationSliderAttachment;

    Label 	squareIsOnLabel;
    ToggleButton squareIsOnToggle;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> squareIsOnToggleAttachment;

    Label 	triangleIsOnLabel;
    ToggleButton triangleIsOnToggle;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> triangleIsOnToggleAttachment;

    Label 	subIsOnLabel;
    ToggleButton subIsOnToggle;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> subIsOnToggleAttachment;

    Label 	subVolumeLabel;
    Slider 	subVolumeSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> subVolumeSliderAttachment;

    Label 	noiseVolumeLabel;
    Slider 	noiseVolumeSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noiseVolumeSliderAttachment;

/*	VCF		*/
    Label  filtFreqMultLabel;
    Slider filtFreqMultSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtFreqMultSliderAttachment;

    Label  filtResLabel;
    Slider filtResSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtResSliderAttachment;

    Label  filtEnvMultLabel;
    Slider filtEnvMultSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtEnvMultSliderAttachment;

    Label  filtKybdLabel;
    Slider filtKybdSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> filtKybdSliderAttachment;

/*	ENVELOPE ADSR	*/
    Label  attackLabel;
    Slider attackSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment;

    Label  decayLabel;
    Slider decaySlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> decaySliderAttachment;

    Label  sustainLabel;
    Slider sustainSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> sustainSliderAttachment;

    Label  releaseLabel;
    Slider releaseSlider;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> releaseSliderAttachment;

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoSynthAudioProcessorEditor)
};
