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

    for(int i = 0; i < NB_BANDS; i++){

    bandInterface[i].delayDurationLabel.setText("duration", NotificationType::dontSendNotification);
    bandInterface[i].delayDurationLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface[i].delayDurationLabel);

    bandInterface[i].delayDuration.setLookAndFeel(&lookAndFeel);
    bandInterface[i].delayDuration.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface[i].delayDuration.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface[i].delayDuration);

    bandInterface[i].delayDurationAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, makeBandParameter("delayDuration", i), bandInterface[i].delayDuration));


    bandInterface[i].delayFeedbackLabel.setText("feedback", NotificationType::dontSendNotification);
    bandInterface[i].delayFeedbackLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface[i].delayFeedbackLabel);

    bandInterface[i].delayFeedback.setLookAndFeel(&lookAndFeel);
    bandInterface[i].delayFeedback.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface[i].delayFeedback.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface[i].delayFeedback);

    bandInterface[i].delayFeedbackAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, makeBandParameter("delayFeedback", i), bandInterface[i].delayFeedback));


    bandInterface[i].delayWetDryLabel.setText("wet-dry", NotificationType::dontSendNotification);
    bandInterface[i].delayWetDryLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface[i].delayWetDryLabel);

    bandInterface[i].delayWetDry.setLookAndFeel(&lookAndFeel);
    bandInterface[i].delayWetDry.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface[i].delayWetDry.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface[i].delayWetDry);

    bandInterface[i].delayWetDryAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, makeBandParameter("delayWetDry", i), bandInterface[i].delayWetDry));


    bandInterface[i].delayVolumeLabel.setText("volume", NotificationType::dontSendNotification);
    bandInterface[i].delayVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&bandInterface[i].delayVolumeLabel);

    bandInterface[i].delayVolume.setLookAndFeel(&lookAndFeel);
    bandInterface[i].delayVolume.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    bandInterface[i].delayVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&bandInterface[i].delayVolume);

    bandInterface[i].delayVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, makeBandParameter("delayVolume", i), bandInterface[i].delayVolume));
    }
}

MultibandDelayAudioProcessorEditor::~MultibandDelayAudioProcessorEditor()
{
}

//==============================================================================
void MultibandDelayAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MultibandDelayAudioProcessorEditor::resized()
{
  for(int i = 0; i < NB_BANDS; i++){
    bandInterface[i].delayVolumeLabel.setBounds(40 + i * 120, 30, 80, 20);
    bandInterface[i].delayVolume.setBounds(40 + i * 120, 50, 80, 100);

    bandInterface[i].delayDurationLabel.setBounds(40 + i * 120, 180, 80, 20);
    bandInterface[i].delayDuration.setBounds(40 + i * 120, 200, 80, 100);

    bandInterface[i].delayFeedbackLabel.setBounds(40 + i * 120, 330, 80, 20);
    bandInterface[i].delayFeedback.setBounds(40 + i * 120, 350, 80, 100);

    bandInterface[i].delayWetDryLabel.setBounds(40 + i * 120, 480, 80, 20);
    bandInterface[i].delayWetDry.setBounds(40 + i * 120, 500, 80, 100);

  }
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
