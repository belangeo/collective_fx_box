/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PlugexLookAndFeel.h"

//==============================================================================
/**
*/
class FloAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    FloAudioProcessorEditor (FloAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~FloAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    FloAudioProcessor& processor;
    
    PlugexLookAndFeel plugexLookAndFeel;

    AudioProcessorValueTreeState& valueTreeState;

    Label title;

    Label  freqLabel;
    Slider freqKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freqAttachment;

    Label  depthLabel;
    Slider depthKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
    
    Label  ffreqLabel;
    Slider ffreqKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ffreqAttachment;
    
    Label  timeLabel;
    Slider timeKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> timeAttachment;

    Label  feedbackLabel;
    Slider feedbackKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;

    Label  balanceLabel;
    Slider balanceKnob;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> balanceAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FloAudioProcessorEditor)
};
