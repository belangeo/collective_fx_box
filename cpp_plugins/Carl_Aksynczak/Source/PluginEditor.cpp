/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PluginCarlAksyAudioProcessorEditor::PluginCarlAksyAudioProcessorEditor (PluginCarlAksyAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts) /* On ajoute l<initialisation de la variable valueTreeState. */
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    freqLsLbl.setText("Freq LowShelf", NotificationType::dontSendNotification);
    
}

PluginCarlAksyAudioProcessorEditor::~PluginCarlAksyAudioProcessorEditor()
{
}

//==============================================================================
void PluginCarlAksyAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::steelblue);
    g.setFont (20.0f);
    g.drawFittedText ("Plugin de Carl Aksynczak", getLocalBounds(), Justification::centred, 1);
}

void PluginCarlAksyAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    
    
    
}
