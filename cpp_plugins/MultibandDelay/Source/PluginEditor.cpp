// Fabien Lamarche-Filion

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

    // La taille horizontale est determinee en fonction du nombre de bande frequencielles NB_BANDS
    setSize (40 + 120 * NB_BANDS, 600);

    setLookAndFeel(&lookAndFeel);

    // Pour chacune des bandes, on cree les boutons et on assigne les labels
    for(int i = 0; i < NB_BANDS; i++){

      float freq = arbitrary_freq(i, NB_BANDS);
      bandInterface[i].freqLabel.setText(String(freq) + String(" Hz"), NotificationType::dontSendNotification);
      bandInterface[i].freqLabel.setJustificationType(Justification::centred);
      addAndMakeVisible(&bandInterface[i].freqLabel);

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

      bandInterface[i].delayDryWetLabel.setText("dry/wet", NotificationType::dontSendNotification);
      bandInterface[i].delayDryWetLabel.setJustificationType(Justification::centred);
      addAndMakeVisible(&bandInterface[i].delayDryWetLabel);

      bandInterface[i].delayDryWet.setLookAndFeel(&lookAndFeel);
      bandInterface[i].delayDryWet.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
      bandInterface[i].delayDryWet.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
      addAndMakeVisible(&bandInterface[i].delayDryWet);

      bandInterface[i].delayDryWetAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, makeBandParameter("delayDryWet", i), bandInterface[i].delayDryWet));

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

    bandInterface[i].freqLabel.setBounds(40 + i * 120, 10, 80, 20);

    bandInterface[i].delayVolumeLabel.setBounds(40 + i * 120, 30, 80, 20);
    bandInterface[i].delayVolume.setBounds(40 + i * 120, 50, 80, 100);

    bandInterface[i].delayDurationLabel.setBounds(40 + i * 120, 180, 80, 20);
    bandInterface[i].delayDuration.setBounds(40 + i * 120, 200, 80, 100);

    bandInterface[i].delayFeedbackLabel.setBounds(40 + i * 120, 330, 80, 20);
    bandInterface[i].delayFeedback.setBounds(40 + i * 120, 350, 80, 100);

    bandInterface[i].delayDryWetLabel.setBounds(40 + i * 120, 480, 80, 20);
    bandInterface[i].delayDryWet.setBounds(40 + i * 120, 500, 80, 100);

  }
}
