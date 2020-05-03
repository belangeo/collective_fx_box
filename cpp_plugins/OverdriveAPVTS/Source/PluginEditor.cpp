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

    setLookAndFeel(&lookAndFeel);

    driveLabel.setText("Drive", NotificationType::dontSendNotification);
    driveLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&driveLabel);

    cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
    cutoffLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&cutoffLabel);

    resLabel.setText("Resonance", NotificationType::dontSendNotification);
    resLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&resLabel);

    /*  Configuration du slider pour la quantité de distorsion. */
    distoDrive.setLookAndFeel(&lookAndFeel);
    distoDrive.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    distoDrive.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&distoDrive);

    /*  On attache le slider a l'arbre de paramètres. */
    driveAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "drive", distoDrive));

    /*  Configuration du slider pour la fréquence de coupure du filtre passe-bas. */
    distoCutoff.setLookAndFeel(&lookAndFeel);
    distoCutoff.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    distoCutoff.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&distoCutoff);

    /*  On attache le slider a l'arbre de paramètres. */
    cutoffAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "cutoff", distoCutoff));

    /*  Configuration du slider pour la résonance du filtre passe-bas. */
    distoRes.setLookAndFeel(&lookAndFeel);
    distoRes.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    distoRes.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
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

    driveLabel.setBounds(40, 30, 80, 20);
    cutoffLabel.setBounds(130, 30, 80, 20);
    resLabel.setBounds(220, 30, 80, 20);

    /*  On place nos sliders dans l'interface. La méthode setBounds() (disponible pour pratiquement
        tous les objets de JUCE, prend une position x et y aux deux premiers arguments et une 
        taille width et height aux deux arguments suivants.
    */
    distoDrive.setBounds(40, 50, 80, 100);
    distoCutoff.setBounds(130, 50, 80, 100);
    distoRes.setBounds(220, 50, 80, 100);

}
