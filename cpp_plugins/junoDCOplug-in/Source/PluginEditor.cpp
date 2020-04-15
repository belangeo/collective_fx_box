/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JunoDcopluginAudioProcessorEditor::JunoDcopluginAudioProcessorEditor (JunoDcopluginAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (650, 300);

    setLookAndFeel(&lookAndFeel);

    lfoAttenuatorLabel.setText("LFO", NotificationType::dontSendNotification);
    lfoAttenuatorLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&lfoAttenuatorLabel);

    pwLabel.setText("PW", NotificationType::dontSendNotification);
    pwLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&pwLabel);

    pwModulationLabel.setText("PW MOD", NotificationType::dontSendNotification);
    pwModulationLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&pwModulationLabel);

    subVolumeLabel.setText("SUB", NotificationType::dontSendNotification);
    subVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subVolumeLabel);

    noiseVolumeLabel.setText("NOISE", NotificationType::dontSendNotification);
    noiseVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&noiseVolumeLabel);

    squareIsOnLabel.setText("[ ]", NotificationType::dontSendNotification);
    squareIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&squareIsOnLabel);

    triangleIsOnLabel.setText("^", NotificationType::dontSendNotification);
    triangleIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&triangleIsOnLabel);

    subIsOnLabel.setText("SUB", NotificationType::dontSendNotification);
    subIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subIsOnLabel);

    /*  Configuration du slider pour la quantité de distorsion. */
    lfoAttenuator.setLookAndFeel(&lookAndFeel);
    lfoAttenuator.setSliderStyle(Slider::LinearVertical);
    lfoAttenuator.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&lfoAttenuator);

    /*  On attache le slider a l'arbre de paramètres. */
    lfoAttenuatorAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lfo_attenuator", lfoAttenuator));

    /*  Configuration du slider pour la quantité de distorsion. */
    pw.setLookAndFeel(&lookAndFeel);
    pw.setSliderStyle(Slider::LinearVertical);
    pw.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&pw);

    /*  On attache le slider a l'arbre de paramètres. */
    pwAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw", pw));

    /*  Configuration du slider pour la fréquence de coupure du filtre passe-bas. */
    pwModulation.setLookAndFeel(&lookAndFeel);
    pwModulation.setSliderStyle(Slider::LinearVertical);
    pwModulation.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    addAndMakeVisible(&pwModulation);

    /*  On attache le slider a l'arbre de paramètres. */
    pwModulationAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw_mod", pwModulation));

    /*  Configuration du slider pour la résonance du filtre passe-bas. */
    subVolume.setLookAndFeel(&lookAndFeel);
    subVolume.setSliderStyle(Slider::LinearVertical);
    subVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&subVolume);

    /*  On attache le slider a l'arbre de paramètres. */
    subVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sub_vol", subVolume));

    /*  Configuration du slider pour la quantité de distorsion. */
    noiseVolume.setLookAndFeel(&lookAndFeel);
    noiseVolume.setSliderStyle(Slider::LinearVertical);
    noiseVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&noiseVolume);

    /*  On attache le slider a l'arbre de paramètres. */
    noiseVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "noise_vol", noiseVolume));

    /*  Configuration du slider pour la fréquence de coupure du filtre passe-bas. */
    squareIsOn.setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(&squareIsOn);

    /*  On attache le slider a l'arbre de paramètres. */
    squareIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "square_onOff", squareIsOn));

    /*  Configuration du slider pour la résonance du filtre passe-bas. */
    triangleIsOn.setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(&triangleIsOn);

    /*  On attache le slider a l'arbre de paramètres. */
    triangleIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "triangle_onOff", triangleIsOn));

    /*  Configuration du slider pour la résonance du filtre passe-bas. */
    subIsOn.setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(&subIsOn);

    /*  On attache le slider a l'arbre de paramètres. */
    subIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "sub_onOff", subIsOn));
}

JunoDcopluginAudioProcessorEditor::~JunoDcopluginAudioProcessorEditor()
{
}

//==============================================================================
void JunoDcopluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::darkred);
    Rectangle<int> topRect (4, 4, getWidth()-8, getHeight()*0.12);
    Rectangle<int> bottomRect (4, getHeight()-15, getWidth()-8, 11);
    g.fillRect (topRect);
    g.fillRect (bottomRect);

    g.setColour (getLookAndFeel().findColour (Label::textColourId));
    g.setFont (30.0f);
    g.drawFittedText ("DCO", topRect, Justification::centred, 1);
    Rectangle<int> pwModRect (200, 118, 80, 105);
    g.setFont (10.0f);
    g.drawFittedText ("ENV", pwModRect, Justification::centredTop, 1);
    g.drawFittedText ("LFO", pwModRect, Justification::centred, 1);
    g.drawFittedText ("NONE", pwModRect, Justification::centredBottom, 1);

    g.drawLine (150, 60, 310, 60, 1);
    g.drawLine (150, 60, 150, 65, 1);
    g.drawLine (210, 60, 210, 110, 1);
    g.drawLine (310, 60, 310, 90, 1);
    g.drawLine (430, 60, 510, 60, 1);
    g.drawLine (430, 60, 430, 90, 1);
    g.drawLine (510, 60, 510, 65, 1);
}

void JunoDcopluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    lfoAttenuatorLabel.setBounds(30, 70, 80, 20);
    pwLabel.setBounds(110, 70, 80, 20);
    //pwModulationLabel.setBounds(190, 70, 80, 20);
    squareIsOnLabel.setBounds(270, 100, 80, 20);
    triangleIsOnLabel.setBounds(330, 100, 80, 20);
    subIsOnLabel.setBounds(390, 100, 80, 20);
    subVolumeLabel.setBounds(470, 70, 80, 20);
    noiseVolumeLabel.setBounds(550, 70, 80, 20);


    /*  On place nos sliders dans l'interface. La méthode setBounds() (disponible pour pratiquement
        tous les objets de JUCE, prend une position x et y aux deux premiers arguments et une 
        taille width et height aux deux arguments suivants.
    */
    lfoAttenuator.setBounds(30, 90, 80, 190);
    pw.setBounds(110, 90, 80, 190);
    pwModulation.setBounds(170, 110, 80, 120);
    squareIsOn.setBounds(280, 60, 80, 190);
    triangleIsOn.setBounds(340, 60, 80, 190);
    subIsOn.setBounds(400, 60, 80, 190);
    subVolume.setBounds(470, 90, 80, 190);
    noiseVolume.setBounds(550, 90, 80, 190);

}
