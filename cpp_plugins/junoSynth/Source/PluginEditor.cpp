/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JunoSynthAudioProcessorEditor::JunoSynthAudioProcessorEditor (JunoSynthAudioProcessor& p,
                                                              AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts),
      keyboardComponent (p.keyboardState, MidiKeyboardComponent::horizontalKeyboard)
{
/*  Make sure that before the constructor has finished, you've set the
    editor's size to whatever you need it to be.    */
    setSize (800, 380);

    setLookAndFeel(&lookAndFeel);

/*  DCO 	*/
    addAndMakeVisible(&lfoAttenuatorLabel);
    lfoAttenuatorLabel.setText("LFO", NotificationType::dontSendNotification);
    lfoAttenuatorLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&lfoAttenuator);
    lfoAttenuator.setLookAndFeel(&lookAndFeel);
    lfoAttenuator.setSliderStyle(Slider::LinearVertical);
    lfoAttenuator.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    lfoAttenuatorAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lfo_attenuator", lfoAttenuator));

    addAndMakeVisible(&pwLabel);
    pwLabel.setText("PW", NotificationType::dontSendNotification);
    pwLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&pw);
    pw.setLookAndFeel(&lookAndFeel);
    pw.setSliderStyle(Slider::LinearVertical);
    pw.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    pwAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw", pw));

    addAndMakeVisible(&pwModulationLabel);
    pwModulationLabel.setText("PW MOD", NotificationType::dontSendNotification);
    pwModulationLabel.setJustificationType(Justification::centred);    
    addAndMakeVisible(&pwModulation);
    pwModulation.setLookAndFeel(&lookAndFeel);
    pwModulation.setSliderStyle(Slider::LinearVertical);
    pwModulation.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    pwModulationAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw_mod", pwModulation));

    addAndMakeVisible(&subVolumeLabel);
    subVolumeLabel.setText("SUB", NotificationType::dontSendNotification);
    subVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subVolume);
    subVolume.setLookAndFeel(&lookAndFeel);
    subVolume.setSliderStyle(Slider::LinearVertical);
    subVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    subVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sub_vol", subVolume));

    addAndMakeVisible(&noiseVolumeLabel);
    noiseVolumeLabel.setText("NOISE", NotificationType::dontSendNotification);
    noiseVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&noiseVolume);
    noiseVolume.setLookAndFeel(&lookAndFeel);
    noiseVolume.setSliderStyle(Slider::LinearVertical);
    noiseVolume.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    noiseVolumeAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "noise_vol", noiseVolume));

    addAndMakeVisible(&squareIsOnLabel);
    squareIsOnLabel.setText("[ ]", NotificationType::dontSendNotification);
    squareIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&squareIsOn);
    squareIsOn.setLookAndFeel(&lookAndFeel);
    squareIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "square_onOff", squareIsOn));

    addAndMakeVisible(&triangleIsOnLabel);
    triangleIsOnLabel.setText("^", NotificationType::dontSendNotification);
    triangleIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&triangleIsOn);
    triangleIsOn.setLookAndFeel(&lookAndFeel);
    triangleIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "triangle_onOff", triangleIsOn));

    addAndMakeVisible(&subIsOnLabel);
    subIsOnLabel.setText("SUB", NotificationType::dontSendNotification);
    subIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subIsOn);
    subIsOn.setLookAndFeel(&lookAndFeel);
    subIsOnAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "sub_onOff", subIsOn));

/*  ENVELOPE ADSR 	*/
    addAndMakeVisible(&attackLabel);
    attackLabel.setText("A", NotificationType::dontSendNotification);
    attackLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&attackKnob);
    attackKnob.setLookAndFeel(&lookAndFeel);
    attackKnob.setSliderStyle(Slider::LinearVertical);
    attackKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    attackAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "attack", attackKnob));

    addAndMakeVisible(&decayLabel);
    decayLabel.setText("D", NotificationType::dontSendNotification);
    decayLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&decayKnob);
    decayKnob.setLookAndFeel(&lookAndFeel);
    decayKnob.setSliderStyle(Slider::LinearVertical);
    decayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    decayAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "decay", decayKnob));

    addAndMakeVisible(&sustainLabel);
    sustainLabel.setText("S", NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&sustainKnob);
    sustainKnob.setLookAndFeel(&lookAndFeel);
    sustainKnob.setSliderStyle(Slider::LinearVertical);
    sustainKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    sustainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sustain", sustainKnob));

    addAndMakeVisible(&releaseLabel);
    releaseLabel.setText("R", NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&releaseKnob);
    releaseKnob.setLookAndFeel(&lookAndFeel);
    releaseKnob.setSliderStyle(Slider::LinearVertical);
    releaseKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    releaseAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "release", releaseKnob));

/*	KEYBOARD 	*/
    addAndMakeVisible(keyboardComponent);
}

JunoSynthAudioProcessorEditor::~JunoSynthAudioProcessorEditor()
{
 /*   attackKnob.setLookAndFeel(nullptr);
    decayKnob.setLookAndFeel(nullptr);
    sustainKnob.setLookAndFeel(nullptr);
    releaseKnob.setLookAndFeel(nullptr);	*/
}

//==============================================================================
void JunoSynthAudioProcessorEditor::paint (Graphics& g)
{
//  (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    auto area = getLocalBounds();
    area.removeFromBottom(80);
    //auto areaWidth = area.getWidth(); 
    
    auto areaDCO = area.removeFromLeft(area.getWidth() * 0.66).reduced(4, 4);
    auto areaEnv = area.reduced(4, 4);

//  Top and bottom rectanges    
    g.setColour (Colours::darkred);
    Rectangle<int> topDCO(areaDCO.removeFromTop(35)), topEnv(areaEnv.removeFromTop(35));
    Rectangle<int> bottomDCO(areaDCO.removeFromBottom(10)), bottomEnv(areaEnv.removeFromBottom(10));
    g.fillRect (topDCO);	g.fillRect (topEnv);
    g.fillRect (bottomDCO);	g.fillRect (bottomEnv);

//  Texts
    g.setColour (getLookAndFeel().findColour (Label::textColourId));
    g.setFont (30.0f);
    g.drawFittedText ("DCO", topDCO, Justification::centred, 1);
    g.drawFittedText ("ENV", topEnv, Justification::centred, 1);
    
    Rectangle<int> pwModRect (areaDCO.getWidth()*2/8-8, 125, 90, 75);
    g.setFont (10.0f);
    g.drawFittedText ("ENV", pwModRect, Justification::centredTop, 1);
    g.drawFittedText ("LFO", pwModRect, Justification::centred, 1);
    g.drawFittedText ("NONE", pwModRect, Justification::centredBottom, 1);

//  Lines
    int x1 = areaDCO.getWidth() * 1/8 + 37;
    int x2 = areaDCO.getWidth() * 2/8 + 12;
    int x3 = areaDCO.getWidth() * 3/8 + 37;
    g.drawLine (x1, 45, x3, 45, 1);
    g.drawLine (x1, 45, x1, 50, 1);
    g.drawLine (x2, 45, x2, 110, 1);
    g.drawLine (x3, 45, x3, 50, 1);
    x1 = areaDCO.getWidth() * 5/8 + 37;
    x2 = areaDCO.getWidth() * 6/8 + 37;
    g.drawLine (x1, 45, x2, 45, 1);
    g.drawLine (x1, 45, x1, 50, 1);
    g.drawLine (x2, 45, x2, 50, 1);
}

void JunoSynthAudioProcessorEditor::resized()
{
/*  This is generally where you'll want to lay out the positions of any
    subcomponents in your editor..  */
    auto area = getLocalBounds();
    area.removeFromBottom(90);
    area.removeFromTop(35);
    //auto areaWidth = area.getWidth(); 
    
    auto areaDCO = area.removeFromLeft(area.getWidth() * 0.66).reduced(4, 4);
    auto areaEnv = area.reduced(4, 4);
    float widthDCO = areaDCO.getWidth();    
    float widthEnv = areaEnv.getWidth();

/*	DCO 	*/
    auto lfoArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);
    lfoAttenuatorLabel.setBounds(lfoArea.removeFromTop(20));
    lfoAttenuator.setBounds(lfoArea);

    auto pwArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);
    pwLabel.setBounds(pwArea.removeFromTop(20));
    pw.setBounds(pwArea);

    auto pwModoArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 90);
    //pwModulationLabel.setBounds(pwModoArea.removeFromTop(20));
    pwModulation.setBounds(pwModoArea.removeFromLeft(40));

    auto squareArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);
    squareIsOnLabel.setBounds(squareArea.removeFromTop(20));
    squareIsOn.setBounds(squareArea.removeFromRight(75));

    auto triangleArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    triangleIsOnLabel.setBounds(triangleArea.removeFromTop(20));
    triangleIsOn.setBounds(triangleArea.removeFromRight(75));

    auto subArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    subIsOnLabel.setBounds(subArea.removeFromTop(20));
    subIsOn.setBounds(subArea.removeFromRight(75));

    auto subVolArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    subVolumeLabel.setBounds(subVolArea.removeFromTop(20));
    subVolume.setBounds(subVolArea);

    auto noiseVolArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    noiseVolumeLabel.setBounds(noiseVolArea.removeFromTop(20));
    noiseVolume.setBounds(noiseVolArea);
       
/*	ADSR 	*/
    auto attackArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    attackLabel.setBounds(attackArea.removeFromTop(20));
    attackKnob.setBounds(attackArea);

    auto decayArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    decayLabel.setBounds(decayArea.removeFromTop(20));
    decayKnob.setBounds(decayArea);

    auto sustainArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    sustainLabel.setBounds(sustainArea.removeFromTop(20));
    sustainKnob.setBounds(sustainArea);

    auto releaseArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    releaseLabel.setBounds(releaseArea.removeFromTop(20));
    releaseKnob.setBounds(releaseArea);

    auto areaKeyboard = getLocalBounds();
    areaKeyboard.removeFromTop(300);
//    keyboardComponent.setBounds(areaKeyboard.removeFromBottom(76));
	keyboardComponent.setBounds(areaKeyboard.reduced(4, 2));
}
