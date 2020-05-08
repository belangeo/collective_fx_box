/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MarwanFiltreIirAudioProcessorEditor::MarwanFiltreIirAudioProcessorEditor (MarwanFiltreIirAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    filterCutoffDial.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    filterResDial.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    filterCutoffDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    filterResDial.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
    
    filterCutoffDial.setNumDecimalPlacesToDisplay(2);
    filterResDial.setNumDecimalPlacesToDisplay(2);
    addAndMakeVisible(&filterResDial);
    addAndMakeVisible(&filterCutoffDial);
}

MarwanFiltreIirAudioProcessorEditor::~MarwanFiltreIirAudioProcessorEditor()
{
}

//==============================================================================
void MarwanFiltreIirAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void MarwanFiltreIirAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    int border = 20;
    int insideWidth = getWidth() - 2 * border;
    int insideHeight = getHeight() - 2 * border;
    filterCutoffDial.setBounds( border + insideWidth/2, border, insideWidth/2, insideHeight);
}
