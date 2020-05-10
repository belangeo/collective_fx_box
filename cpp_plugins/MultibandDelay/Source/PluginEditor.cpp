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
    setSize (40 + 120 * NB_BANDS, 600);


    setLookAndFeel(&lookAndFeel);

    bandInterface.delayDurationLabel.setText("duration", NotificationType::dontSendNotification);
    bandInterface.delayDurationLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface.delayDurationLabel);

    bandInterface.delayDuration.setLookAndFeel(&lookAndFeel);
    bandInterface.delayDuration.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface.delayDuration.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface.delayDuration);

    bandInterface.delayDurationAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, makeBandParameter("delayDuration", 1), bandInterface.delayDuration));


    bandInterface.delayFeedbackLabel.setText("feedback", NotificationType::dontSendNotification);
    bandInterface.delayFeedbackLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface.delayFeedbackLabel);

    bandInterface.delayFeedback.setLookAndFeel(&lookAndFeel);
    bandInterface.delayFeedback.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface.delayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface.delayFeedback);

    bandInterface.delayFeedbackAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayFeedback", bandInterface.delayFeedback));


    bandInterface.delayWetDryLabel.setText("wet-dry", NotificationType::dontSendNotification);
    bandInterface.delayWetDryLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface.delayWetDryLabel);

    bandInterface.delayWetDry.setLookAndFeel(&lookAndFeel);
    bandInterface.delayWetDry.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface.delayWetDry.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface.delayWetDry);

    bandInterface.delayWetDryAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayWetDry", bandInterface.delayWetDry));


    bandInterface.delayVolumeLabel.setText("volume", NotificationType::dontSendNotification);
    bandInterface.delayVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface.delayVolumeLabel);

    bandInterface.delayVolume.setLookAndFeel(&lookAndFeel);
    bandInterface.delayVolume.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface.delayVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface.delayVolume);

    bandInterface.delayVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delayVolume", bandInterface.delayVolume));

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

    bandInterface.delayVolumeLabel.setBounds(40, 30, 80, 20);
    bandInterface.delayVolume.setBounds(40, 50, 80, 100);

    bandInterface.delayDurationLabel.setBounds(40, 180, 80, 20);
    bandInterface.delayDuration.setBounds(40, 200, 80, 100);

    bandInterface.delayFeedbackLabel.setBounds(40, 330, 80, 20);
    bandInterface.delayFeedback.setBounds(40, 350, 80, 100);

    bandInterface.delayWetDryLabel.setBounds(40, 480, 80, 20);
    bandInterface.delayWetDry.setBounds(40, 500, 80, 100);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
