/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JunoDcopluginAudioProcessorEditor::JunoDcopluginAudioProcessorEditor    (JunoDcopluginAudioProcessor& p, 
                                                                        AudioProcessorValueTreeState& vts)
    :   AudioProcessorEditor (&p), processor (p), valueTreeState (vts),
        keyboardComponent (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
/*  Make sure that before the constructor has finished, you've set the
    editor's size to whatever you need it to be.    */
    setSize (650, 380);

    setLookAndFeel(&lookAndFeel);

/*  LFO ATTENUATOR  */
/*  Configuration du label. */
    addAndMakeVisible(&lfoAttenuatorLabel);
    lfoAttenuatorLabel.setText("LFO", NotificationType::dontSendNotification);
    lfoAttenuatorLabel.setJustificationType(Justification::centred);
/*  Configuration du slider. */
    addAndMakeVisible(&lfoAttenuator);
    lfoAttenuator.setLookAndFeel(&lookAndFeel);
    lfoAttenuator.setSliderStyle(Slider::LinearVertical);
    lfoAttenuator.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
/*  On attache le slider a l'arbre de paramètres. */
    lfoAttenuatorAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lfo_attenuator", lfoAttenuator));
/*  PW  */
    addAndMakeVisible(&pwLabel);
    pwLabel.setText("PW", NotificationType::dontSendNotification);
    pwLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&pw);
    pw.setLookAndFeel(&lookAndFeel);
    pw.setSliderStyle(Slider::LinearVertical);
    pw.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    pwAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw", pw));
/*  PW  MODULATION  */
    addAndMakeVisible(&pwModulationLabel);
    pwModulationLabel.setText("PW MOD", NotificationType::dontSendNotification);
    pwModulationLabel.setJustificationType(Justification::centred);    
    addAndMakeVisible(&pwModulation);
    pwModulation.setLookAndFeel(&lookAndFeel);
    pwModulation.setSliderStyle(Slider::LinearVertical);
    pwModulation.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    pwModulationAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw_mod", pwModulation));
/*  SUB VOLUME  */
    addAndMakeVisible(&subVolumeLabel);
    subVolumeLabel.setText("SUB", NotificationType::dontSendNotification);
    subVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subVolume);
    subVolume.setLookAndFeel(&lookAndFeel);
    subVolume.setSliderStyle(Slider::LinearVertical);
    subVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    subVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sub_vol", subVolume));
/*  NOISE VOLUME  */
    addAndMakeVisible(&noiseVolumeLabel);
    noiseVolumeLabel.setText("NOISE", NotificationType::dontSendNotification);
    noiseVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&noiseVolume);
    noiseVolume.setLookAndFeel(&lookAndFeel);
    noiseVolume.setSliderStyle(Slider::LinearVertical);
    noiseVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    noiseVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "noise_vol", noiseVolume));
/*  SQUARE ON / OFF  */
    addAndMakeVisible(&squareIsOnLabel);
    squareIsOnLabel.setText("[ ]", NotificationType::dontSendNotification);
    squareIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&squareIsOn);
    squareIsOn.setLookAndFeel(&lookAndFeel);
    squareIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "square_onOff", squareIsOn));
/*  TRIANGLE ON / OFF  */
    addAndMakeVisible(&triangleIsOnLabel);
    triangleIsOnLabel.setText("^", NotificationType::dontSendNotification);
    triangleIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&triangleIsOn);
    triangleIsOn.setLookAndFeel(&lookAndFeel);
    triangleIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "triangle_onOff", triangleIsOn));
/*  SUB ON / OFF  */
    addAndMakeVisible(&subIsOnLabel);
    subIsOnLabel.setText("SUB", NotificationType::dontSendNotification);
    subIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subIsOn);
    subIsOn.setLookAndFeel(&lookAndFeel);
    subIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "sub_onOff", subIsOn));

    addAndMakeVisible(keyboardComponent);
}

JunoDcopluginAudioProcessorEditor::~JunoDcopluginAudioProcessorEditor()
{
}

//==============================================================================
void JunoDcopluginAudioProcessorEditor::paint (Graphics& g)
{
//  (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
//  Top and bottom rectanges    
    g.setColour (Colours::darkred);
    Rectangle<int> topRect (4, 4, getWidth()-8, 300*0.12);
    Rectangle<int> bottomRect (4, 300-15, getWidth()-8, 11);
    g.fillRect (topRect);
    g.fillRect (bottomRect);
//  Texts
    g.setColour (getLookAndFeel().findColour (Label::textColourId));
    g.setFont (30.0f);
    g.drawFittedText ("DCO", topRect, Justification::centred, 1);
    Rectangle<int> pwModRect (200, 118, 80, 105);
    g.setFont (10.0f);
    g.drawFittedText ("ENV", pwModRect, Justification::centredTop, 1);
    g.drawFittedText ("LFO", pwModRect, Justification::centred, 1);
    g.drawFittedText ("NONE", pwModRect, Justification::centredBottom, 1);
//  Lines
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
/*  This is generally where you'll want to lay out the positions of any
    subcomponents in your editor..  */
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
    taille width et height aux deux arguments suivants. */
    lfoAttenuator.setBounds(30, 90, 80, 190);
    pw.setBounds(110, 90, 80, 190);
    pwModulation.setBounds(170, 110, 80, 120);
    squareIsOn.setBounds(280, 60, 80, 190);
    triangleIsOn.setBounds(340, 60, 80, 190);
    subIsOn.setBounds(400, 60, 80, 190);
    subVolume.setBounds(470, 90, 80, 190);
    noiseVolume.setBounds(550, 90, 80, 190);

    keyboardComponent.setBounds(getLocalBounds().removeFromBottom(80));
}
