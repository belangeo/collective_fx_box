/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//=Constructor=============================================================================
RobotVoiceAudioProcessorEditor::RobotVoiceAudioProcessorEditor(RobotVoiceAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    //Gain Slider

    addAndMakeVisible(&gain);

    gain.setSliderStyle(Slider::LinearBarVertical);
    gain.setRange(0.0, 127.0, 1.0);
    gain.setTextBoxStyle(Slider::TextBoxBelow, false, 90, 20);
    gain.setPopupDisplayEnabled(true, false, this);
    gain.setTextValueSuffix("Gain");
    gain.setValue(1.0);
    gain.addListener(this);

    //Freq Slider of Sinus

    addAndMakeVisible(&freqSine);

    freqSine.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    freqSine.setRange(1.0, 2000, 1.0);
    freqSine.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 20);
    freqSine.setPopupDisplayEnabled(true, false, this);
    freqSine.setTextValueSuffix("Freq");
    freqSine.setValue(500.0);
    freqSine.addListener(this);

    //Wet Slider of Sinus

    addAndMakeVisible(&wetSine);

    wetSine.setSliderStyle(Slider::LinearBarVertical);
    wetSine.setRange(0.0, 1, 0.01);
    wetSine.setTextBoxStyle(Slider::TextBoxBelow, false, 90, 20);
    wetSine.setPopupDisplayEnabled(true, false, this);
    wetSine.setTextValueSuffix("Wet/Dry");
    wetSine.setValue(0.5);
    wetSine.addListener(this);

    //Ratio Compression Slider

    addAndMakeVisible(&compRatio);

    compRatio.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    compRatio.setRange(1.0, 2000, 1.0);
    compRatio.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 20);
    compRatio.setPopupDisplayEnabled(true, false, this);
    compRatio.setTextValueSuffix("Comp");
    compRatio.setValue(500.0);
    compRatio.addListener(this);

    //Wet Slider for Compression

    addAndMakeVisible(&wetComp);

    wetComp.setSliderStyle(Slider::LinearBarVertical);
    wetComp.setRange(0.0, 1, 0.01);
    wetComp.setTextBoxStyle(Slider::TextBoxBelow, false, 90, 20);
    wetComp.setPopupDisplayEnabled(true, false, this);
    wetComp.setTextValueSuffix("Wet/Dry");
    wetComp.setValue(0.5);
    wetComp.addListener(this);

}

RobotVoiceAudioProcessorEditor::~RobotVoiceAudioProcessorEditor()
{
}

//==============================================================================
void RobotVoiceAudioProcessorEditor::paint(Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(Colours::greenyellow);
    g.setFont(20.0f);
    g.drawFittedText("ROBOT VOICE", getLocalBounds(), Justification::centredTop, 1);
}

void RobotVoiceAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    gain.setBounds(40, 30, 20, getHeight() - 60);
    freqSine.setBounds(90, 30, 80, 100);
    wetSine.setBounds(120, 110, 20, getHeight() - 140);
    compRatio.setBounds(170, 30, 80, 100);
    wetComp.setBounds(200, 110, 20, getHeight() - 140);
}

void RobotVoiceAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &gain)
    {
        processor.volumeMeter = gain.getValue() / 127;
    }
    if (slider == &freqSine)
    {
        processor.freqMeter = freqSine.getValue();
    }
    if (slider == &wetSine)
    {
        processor.wetMeter = wetSine.getValue();
    }

    if (slider == &compRatio)
    {
        processor.compMeter = compRatio.getValue();
    }

    if (slider == &wetComp)
    {
        processor.wetCompMeter = wetComp.getValue();
    }

}

