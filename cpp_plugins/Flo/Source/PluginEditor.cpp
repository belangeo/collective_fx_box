/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FloAudioProcessorEditor::FloAudioProcessorEditor (FloAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    
    setSize (430, 400);

    setLookAndFeel(&plugexLookAndFeel);
    plugexLookAndFeel.setTheme("blue");

    title.setText("FLOW", NotificationType::dontSendNotification);
    title.setFont(title.getFont().withPointHeight(title.getFont().getHeightInPoints() + 4));
    title.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&title);

    freqLabel.setText("Mod Freq", NotificationType::dontSendNotification);
    freqLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&freqLabel);

    freqKnob.setLookAndFeel(&plugexLookAndFeel);
    freqKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    freqKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&freqKnob);

    freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "freq", freqKnob));

    depthLabel.setText("depth", NotificationType::dontSendNotification);
    depthLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&depthLabel);

    depthKnob.setLookAndFeel(&plugexLookAndFeel);
    depthKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    depthKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&depthKnob);

    depthAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "depth", depthKnob));
    
    ffreqLabel.setText("Ffreq", NotificationType::dontSendNotification);
    ffreqLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&ffreqLabel);

    ffreqKnob.setLookAndFeel(&plugexLookAndFeel);
    ffreqKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ffreqKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&ffreqKnob);

    ffreqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "ffreq", ffreqKnob));
    
    timeLabel.setText("Delay Time", NotificationType::dontSendNotification);
    timeLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&timeLabel);

    timeKnob.setLookAndFeel(&plugexLookAndFeel);
    timeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    timeKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&timeKnob);

    timeAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "time", timeKnob));

    feedbackLabel.setText("Feedback", NotificationType::dontSendNotification);
    feedbackLabel.setJustificationType(Justification::horizontallyCentred);
    
    addAndMakeVisible(&feedbackLabel);
    feedbackKnob.setLookAndFeel(&plugexLookAndFeel);
    feedbackKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    feedbackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&feedbackKnob);

    feedbackAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "feedback", feedbackKnob));

    balanceLabel.setText("Balance", NotificationType::dontSendNotification);
    balanceLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&balanceLabel);

    balanceKnob.setLookAndFeel(&plugexLookAndFeel);
    balanceKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    balanceKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&balanceKnob);

    balanceAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "balance", balanceKnob));
    
    /*Choice
    choiceBox.addItem("Choice1", 1);
    choiceBox.addItem("Choice2", 2);
    choiceBox.addItem("Choice3", 3);
    choiceBox.setJustificationType(Justification::centred);
    addAndMakeVisible(choiceBox);
    
    choiceAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.vts, "CHOICE", choiceBox);
     */

    }

FloAudioProcessorEditor::~FloAudioProcessorEditor()
{
    ffreqKnob.setLookAndFeel(nullptr);
    timeKnob.setLookAndFeel(nullptr);
    feedbackKnob.setLookAndFeel(nullptr);
    balanceKnob.setLookAndFeel(nullptr);
    setLookAndFeel(nullptr);

}

//==============================================================================
void FloAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    Image background = ImageCache::getFromMemory (BinaryData::floww_png, BinaryData::floww_pngSize);
    g.drawImageAt(background, 0, 0);
    //g.fillAll(Colours::black);

}
void FloAudioProcessorEditor::resized()
{
    
    title.setBounds(0, 0, 100, 25);

    freqLabel.setBounds(50, 20, 100, 50);
    freqKnob.setBounds(50, 60, 100, 100);
    
    depthLabel.setBounds(150, 20, 100, 50);
    depthKnob.setBounds(150, 60, 100, 100);
    
    ffreqLabel.setBounds(300, 20, 100, 50);
    ffreqKnob.setBounds(300, 60, 100, 100);
    
    timeLabel.setBounds(50, 160, 100, 50);
    timeKnob.setBounds(50, 200, 100, 100);
    
    feedbackLabel.setBounds(150, 160, 100, 50);
    feedbackKnob.setBounds(150, 200, 100, 100);
    
    balanceLabel.setBounds(300, 160, 100, 50);
    balanceKnob.setBounds(300, 200, 100, 100);
    

}


