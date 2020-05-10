/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================


MultibandDelayAudioProcessorEditor::MultibandDelayAudioProcessorEditor (MultibandDelayAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 600);


    setLookAndFeel(&lookAndFeel);

    delayDurationLabel.setText("duration", NotificationType::dontSendNotification);
    delayDurationLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&delayDurationLabel);

    delayDuration.setLookAndFeel(&lookAndFeel);
    delayDuration.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayDuration.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&delayDuration);

    delayDurationAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayDuration", delayDuration));


    delayFeedbackLabel.setText("feedback", NotificationType::dontSendNotification);
    delayFeedbackLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&delayFeedbackLabel);

    delayFeedback.setLookAndFeel(&lookAndFeel);
    delayFeedback.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&delayFeedback);

    delayFeedbackAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayFeedback", delayFeedback));


    delayWetDryLabel.setText("wet-dry", NotificationType::dontSendNotification);
    delayWetDryLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&delayWetDryLabel);

    delayWetDry.setLookAndFeel(&lookAndFeel);
    delayWetDry.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayWetDry.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&delayWetDry);

    delayWetDryAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayWetDry", delayWetDry));


    delayVolumeLabel.setText("volume", NotificationType::dontSendNotification);
    delayVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&delayVolumeLabel);

    delayVolume.setLookAndFeel(&lookAndFeel);
    delayVolume.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    delayVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&delayVolume);

    delayVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayVolume", delayVolume));

}

MultibandDelayAudioProcessorEditor::~MultibandDelayAudioProcessorEditor()
{
}

//==============================================================================
void MultibandDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MultibandDelayAudioProcessorEditor::resized()
{

    delayVolumeLabel.setBounds(40, 30, 80, 20);
    delayVolume.setBounds(40, 50, 80, 100);

    delayDurationLabel.setBounds(40, 180, 80, 20);
    delayDuration.setBounds(40, 200, 80, 100);

    delayFeedbackLabel.setBounds(40, 330, 80, 20);
    delayFeedback.setBounds(40, 350, 80, 100);

    delayWetDryLabel.setBounds(40, 480, 80, 20);
    delayWetDry.setBounds(40, 500, 80, 100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
