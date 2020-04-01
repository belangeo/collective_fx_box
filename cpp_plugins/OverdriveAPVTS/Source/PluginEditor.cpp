/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OverdriveApvtsAudioProcessorEditor::OverdriveApvtsAudioProcessorEditor (OverdriveApvtsAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts) /* On ajoute l<initialisation de la variable valueTreeState. */
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    /*  Configuration du slider pour la quantité de distorsion. */
    distoDrive.setSliderStyle(Slider::LinearBarVertical);
    distoDrive.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    distoDrive.setPopupDisplayEnabled(true, true, this);
    distoDrive.setTextValueSuffix(" Drive");
    addAndMakeVisible(&distoDrive);

    /*  On attache le slider a l'arbre de paramètres. */
    driveAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "drive", distoDrive));

    /*  Configuration du slider pour la fréquence de coupure du filtre passe-bas. */
    distoCutoff.setSliderStyle(Slider::LinearBarVertical);
    distoCutoff.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    distoCutoff.setPopupDisplayEnabled(true, true, this);
    distoCutoff.setTextValueSuffix(" Cutoff");
    addAndMakeVisible(&distoCutoff);

    /*  On attache le slider a l'arbre de paramètres. */
    cutoffAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoff", distoCutoff));

    /*  Configuration du slider pour la résonance du filtre passe-bas. */
    distoRes.setSliderStyle(Slider::LinearBarVertical);
    distoRes.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    distoRes.setPopupDisplayEnabled(true, true, this);
    distoRes.setTextValueSuffix(" Res");
    addAndMakeVisible(&distoRes);

    /*  On attache le slider a l'arbre de paramètres. */
    resAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "res", distoRes));
}

OverdriveApvtsAudioProcessorEditor::~OverdriveApvtsAudioProcessorEditor()
{
}

//==============================================================================
void OverdriveApvtsAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::steelblue);
    g.setFont (20.0f);
    g.drawFittedText ("My Super Overdriver!", getLocalBounds(), Justification::centredTop, 1);
}

void OverdriveApvtsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    /*  On place nos sliders dans l'interface. La méthode setBounds() (disponible pour pratiquement
        tous les objets de JUCE, prend une position x et y aux deux premiers arguments et une 
        taille width et height aux deux arguments suivants.
    */
    distoDrive.setBounds(40, 30, 20, getHeight() - 60);
    distoCutoff.setBounds(80, 30, 20, getHeight() - 60);
    distoRes.setBounds(120, 30, 20, getHeight() - 60);

}
