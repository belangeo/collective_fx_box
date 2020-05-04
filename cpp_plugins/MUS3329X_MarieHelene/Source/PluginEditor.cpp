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
    gain.setRange(-60.0, 12.0, 1.0);
    gain.setTextBoxStyle(Slider::TextBoxBelow, false, 90, 20);
    gain.setPopupDisplayEnabled(true, false, this);
    gain.setTextValueSuffix("Gain");
    gain.setValue(1.0);
    gain.addListener(this);

    //Freq Slider of Oscillator

    addAndMakeVisible(&freqOsc);

    freqOsc.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    freqOsc.setRange(1, 2000, 1);
    freqOsc.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 20);
    freqOsc.setPopupDisplayEnabled(true, false, this);
    freqOsc.setTextValueSuffix("Freq");
    freqOsc.setValue(500.0);
    freqOsc.addListener(this);

    //Wet Slider of Osc

    addAndMakeVisible(&wetSine);

    wetSine.setSliderStyle(Slider::LinearBarVertical);
    wetSine.setRange(0.0, 1, 0.01);
    wetSine.setTextBoxStyle(Slider::TextBoxBelow, false, 90, 20);
    wetSine.setPopupDisplayEnabled(true, false, this);
    wetSine.setTextValueSuffix("Wet/Dry");
    wetSine.setValue(0.5);
    wetSine.addListener(this);

    //Menu Osc

    addAndMakeVisible(&oscMenu);

    oscMenu.addItem("Sinus", 1);
    oscMenu.addItem("Saw tooth", 2);
    oscMenu.setSelectedId(1);


    //Ratio Compression Slider

    addAndMakeVisible(&compRatio);

    compRatio.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    compRatio.setRange(0.01, 1.0, 0.001);
    compRatio.setTextBoxStyle(Slider::TextBoxAbove, false, 80, 20);
    compRatio.setPopupDisplayEnabled(true, false, this);
    compRatio.setTextValueSuffix("Comp");
    compRatio.setValue(0.5);
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

 
    //Wet Slider for modulation amplitude

    addAndMakeVisible(&wetAmpMod);

    wetAmpMod.setSliderStyle(Slider::LinearBarVertical);
    wetAmpMod.setRange(0.0, 1, 0.01);
    wetAmpMod.setTextBoxStyle(Slider::TextBoxAbove, false, 90, 20);
    wetAmpMod.setPopupDisplayEnabled(true, false, this);
    wetAmpMod.setTextValueSuffix("Amp Mod");
    wetAmpMod.setValue(0.5);
    wetAmpMod.addListener(this);

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
    freqOsc.setBounds(90, 80, 80, 100);
    wetSine.setBounds(120, 150, 20, getHeight() - 180);
    oscMenu.setBounds(120, 30, 20, 30);
    compRatio.setBounds(170, 80, 80, 100);
    wetComp.setBounds(200, 150, 20, getHeight() - 180);
    wetAmpMod.setBounds(280, 30, 20, getHeight() - 60);
    
    
}

void RobotVoiceAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &gain)
    {
        processor.volumeMeter = gain.getValue();
    }
    if (slider == &freqOsc)
    {
        processor.freqMeter = freqOsc.getValue();
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

    if (slider == &wetAmpMod)
    {
        processor.wetAmpMeter = wetAmpMod.getValue();
    }

    processor.oscChoice = oscMenu.getSelectedId();
       

}

