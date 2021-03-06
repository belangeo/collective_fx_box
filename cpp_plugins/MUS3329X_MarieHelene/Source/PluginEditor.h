/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class RobotVoiceAudioProcessorEditor : public AudioProcessorEditor, private Slider::Listener
{
public:
    RobotVoiceAudioProcessorEditor(RobotVoiceAudioProcessor&);
    ~RobotVoiceAudioProcessorEditor();

    //==============================================================================
    void paint(Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    void sliderValueChanged(Slider* slider);

    RobotVoiceAudioProcessor& processor;

    Slider gain;
    Slider freqOsc;
    Slider wetSine;
    Slider compRatio;
    Slider wetComp;
    Slider wetAmpMod;
    ComboBox oscMenu;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RobotVoiceAudioProcessorEditor)
};
