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
    setSize (1200, 380);

    setLookAndFeel(&lookAndFeel);

/*  VOLUME 	*/
    addAndMakeVisible(&volumeLabel);
    volumeLabel.setText("VOLUME", NotificationType::dontSendNotification);
    volumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&volumeKnob);
    volumeKnob.setLookAndFeel(&lookAndFeel);
    volumeKnob.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    volumeKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    volumeKnobAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "volume", volumeKnob));

/*  LFO 	*/
    addAndMakeVisible(&lfoRateLabel);
    lfoRateLabel.setText("RATE", NotificationType::dontSendNotification);
    lfoRateLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&lfoRateSlider);
    lfoRateSlider.setLookAndFeel(&lookAndFeel);
    lfoRateSlider.setSliderStyle(Slider::LinearVertical);
    lfoRateSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    lfoRateSliderAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lfo_rate", lfoRateSlider));

    addAndMakeVisible(&lfoDelayLabel);
    lfoDelayLabel.setText("DELAY", NotificationType::dontSendNotification);
    lfoDelayLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&lfoDelaySlider);
    lfoDelaySlider.setLookAndFeel(&lookAndFeel);
    lfoDelaySlider.setSliderStyle(Slider::LinearVertical);
    lfoDelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    lfoDelaySliderAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lfo_delay", lfoDelaySlider));

/*  DCO 	*/
    addAndMakeVisible(&lfoAttenuatorLabel);
    lfoAttenuatorLabel.setText("LFO", NotificationType::dontSendNotification);
    lfoAttenuatorLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&lfoAttenuatorSlider);
    lfoAttenuatorSlider.setLookAndFeel(&lookAndFeel);
    lfoAttenuatorSlider.setSliderStyle(Slider::LinearVertical);
    lfoAttenuatorSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    lfoAttenuatorSliderAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lfo_attenuator", lfoAttenuatorSlider));

    addAndMakeVisible(&pwLabel);
    pwLabel.setText("PW", NotificationType::dontSendNotification);
    pwLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&pwSlider);
    pwSlider.setLookAndFeel(&lookAndFeel);
    pwSlider.setSliderStyle(Slider::LinearVertical);
    pwSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    pwSliderAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw", pwSlider));

    addAndMakeVisible(&pwModulationLabel);
    pwModulationLabel.setText("PW MOD", NotificationType::dontSendNotification);
    pwModulationLabel.setJustificationType(Justification::centred);    
    addAndMakeVisible(&pwModulationSlider);
    pwModulationSlider.setLookAndFeel(&lookAndFeel);
    pwModulationSlider.setSliderStyle(Slider::LinearVertical);
    pwModulationSlider.setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    pwModulationSliderAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "pw_mod", pwModulationSlider));

    addAndMakeVisible(&squareIsOnLabel);
    squareIsOnLabel.setText("[ ]", NotificationType::dontSendNotification);
    squareIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&squareIsOnToggle);
    squareIsOnToggle.setLookAndFeel(&lookAndFeel);
    squareIsOnToggleAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "square_onOff", squareIsOnToggle));

    addAndMakeVisible(&triangleIsOnLabel);
    triangleIsOnLabel.setText("^", NotificationType::dontSendNotification);
    triangleIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&triangleIsOnToggle);
    triangleIsOnToggle.setLookAndFeel(&lookAndFeel);
    triangleIsOnToggleAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "triangle_onOff", triangleIsOnToggle));

    addAndMakeVisible(&subIsOnLabel);
    subIsOnLabel.setText("SUB", NotificationType::dontSendNotification);
    subIsOnLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subIsOnToggle);
    subIsOnToggle.setLookAndFeel(&lookAndFeel);
    subIsOnToggleAttachment.reset (new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "sub_onOff", subIsOnToggle));

    addAndMakeVisible(&subVolumeLabel);
    subVolumeLabel.setText("SUB", NotificationType::dontSendNotification);
    subVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&subVolumeSlider);
    subVolumeSlider.setLookAndFeel(&lookAndFeel);
    subVolumeSlider.setSliderStyle(Slider::LinearVertical);
    subVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    subVolumeSliderAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sub_vol", subVolumeSlider));

    addAndMakeVisible(&noiseVolumeLabel);
    noiseVolumeLabel.setText("NOISE", NotificationType::dontSendNotification);
    noiseVolumeLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(&noiseVolumeSlider);
    noiseVolumeSlider.setLookAndFeel(&lookAndFeel);
    noiseVolumeSlider.setSliderStyle(Slider::LinearVertical);
    noiseVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    noiseVolumeSliderAttachment.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "noise_vol", noiseVolumeSlider));

/*  VCF 	*/
    addAndMakeVisible(&filtFreqMultLabel);
    filtFreqMultLabel.setText("FREQ", NotificationType::dontSendNotification);
    filtFreqMultLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtFreqMultSlider);
    filtFreqMultSlider.setLookAndFeel(&lookAndFeel);
    filtFreqMultSlider.setSliderStyle(Slider::LinearVertical);
    filtFreqMultSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    filtFreqMultSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filt_freq_mult", filtFreqMultSlider));

    addAndMakeVisible(&filtResLabel);
    filtResLabel.setText("RES", NotificationType::dontSendNotification);
    filtResLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtResSlider);
    filtResSlider.setLookAndFeel(&lookAndFeel);
    filtResSlider.setSliderStyle(Slider::LinearVertical);
    filtResSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    filtResSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filt_res", filtResSlider));

    addAndMakeVisible(&filtEnvMultLabel);
    filtEnvMultLabel.setText("ENV", NotificationType::dontSendNotification);
    filtEnvMultLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtEnvMultSlider);
    filtEnvMultSlider.setLookAndFeel(&lookAndFeel);
    filtEnvMultSlider.setSliderStyle(Slider::LinearVertical);
    filtEnvMultSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    filtEnvMultSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filt_env_mult", filtEnvMultSlider));

    addAndMakeVisible(&filtKybdLabel);
    filtKybdLabel.setText("KYBD", NotificationType::dontSendNotification);
    filtKybdLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&filtKybdSlider);
    filtKybdSlider.setLookAndFeel(&lookAndFeel);
    filtKybdSlider.setSliderStyle(Slider::LinearVertical);
    filtKybdSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    filtKybdSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "filt_kybd", filtKybdSlider));

/*  ENVELOPE ADSR 	*/
    addAndMakeVisible(&attackLabel);
    attackLabel.setText("A", NotificationType::dontSendNotification);
    attackLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&attackSlider);
    attackSlider.setLookAndFeel(&lookAndFeel);
    attackSlider.setSliderStyle(Slider::LinearVertical);
    attackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    attackSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "attack", attackSlider));

    addAndMakeVisible(&decayLabel);
    decayLabel.setText("D", NotificationType::dontSendNotification);
    decayLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&decaySlider);
    decaySlider.setLookAndFeel(&lookAndFeel);
    decaySlider.setSliderStyle(Slider::LinearVertical);
    decaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    decaySliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "decay", decaySlider));

    addAndMakeVisible(&sustainLabel);
    sustainLabel.setText("S", NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&sustainSlider);
    sustainSlider.setLookAndFeel(&lookAndFeel);
    sustainSlider.setSliderStyle(Slider::LinearVertical);
    sustainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    sustainSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "sustain", sustainSlider));

    addAndMakeVisible(&releaseLabel);
    releaseLabel.setText("R", NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(&releaseSlider);
    releaseSlider.setLookAndFeel(&lookAndFeel);
    releaseSlider.setSliderStyle(Slider::LinearVertical);
    releaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 20);
    releaseSliderAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "release", releaseSlider));

/*	KEYBOARD 	*/
    addAndMakeVisible(keyboardComponent);
}

JunoSynthAudioProcessorEditor::~JunoSynthAudioProcessorEditor()
{

    volumeKnob.setLookAndFeel(nullptr);

    lfoRateSlider.setLookAndFeel(nullptr);
    lfoDelaySlider.setLookAndFeel(nullptr);

    lfoAttenuatorSlider.setLookAndFeel(nullptr);
    pwSlider.setLookAndFeel(nullptr);
    pwModulationSlider.setLookAndFeel(nullptr);
    squareIsOnToggle.setLookAndFeel(nullptr);
    triangleIsOnToggle.setLookAndFeel(nullptr);
    subIsOnToggle.setLookAndFeel(nullptr);
    subVolumeSlider.setLookAndFeel(nullptr);
    noiseVolumeSlider.setLookAndFeel(nullptr);

    filtFreqMultSlider.setLookAndFeel(nullptr);
    filtResSlider.setLookAndFeel(nullptr);
    filtEnvMultSlider.setLookAndFeel(nullptr);
    filtKybdSlider.setLookAndFeel(nullptr);
    
    attackSlider.setLookAndFeel(nullptr);
    decaySlider.setLookAndFeel(nullptr);
    sustainSlider.setLookAndFeel(nullptr);
    releaseSlider.setLookAndFeel(nullptr);	

}

//==============================================================================
void JunoSynthAudioProcessorEditor::paint (Graphics& g)
{
//  (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    auto area = getLocalBounds();
    area.removeFromBottom(80);
 
    auto areaVol = area.removeFromLeft(area.getWidth() * 2/20).reduced(4, 4);   
    auto areaLFO = area.removeFromLeft(area.getWidth() * 2/18).reduced(4, 4);   
    auto areaDCO = area.removeFromLeft(area.getWidth() * 8/16).reduced(4, 4);
    auto areaVCF = area.removeFromLeft(area.getWidth() * 4/8).reduced(4, 4);   
    auto areaEnv = area.reduced(4, 4);

//  Top and bottom rectanges    
    g.setColour (Colours::darkred);
    Rectangle<int> 	topVol(areaVol.removeFromTop(35)),
    				topLFO(areaLFO.removeFromTop(35)),
    				topDCO(areaDCO.removeFromTop(35)), 
    				topVCF(areaVCF.removeFromTop(35)),
    				topEnv(areaEnv.removeFromTop(35));
    Rectangle<int> 	bottomVol(areaVol.removeFromBottom(10)),
    				bottomLFO(areaLFO.removeFromBottom(10)), 
    				bottomDCO(areaDCO.removeFromBottom(10)), 
    				bottomVCF(areaVCF.removeFromBottom(10)), 
    				bottomEnv(areaEnv.removeFromBottom(10));
    g.fillRect (topVol);	g.fillRect (bottomVol);	
    g.fillRect (topLFO);	g.fillRect (bottomLFO);	
    g.fillRect (topDCO);	g.fillRect (bottomDCO);	
    g.fillRect (topVCF);	g.fillRect (bottomVCF);
    g.fillRect (topEnv);	g.fillRect (bottomEnv);

//  Texts
    g.setColour (getLookAndFeel().findColour (Label::textColourId));
    g.setFont (30.0f);
//  g.drawFittedText ("VOL", topVol, Justification::centred, 1);
    g.drawFittedText ("LFO", topLFO, Justification::centred, 1);
    g.drawFittedText ("DCO", topDCO, Justification::centred, 1);
    g.drawFittedText ("VCF", topVCF, Justification::centred, 1);
    g.drawFittedText ("ENV", topEnv, Justification::centred, 1);
    // 	PW Modulation texts
    Rectangle<int> pwModRect (areaVol.getWidth() + areaLFO.getWidth() + areaDCO.getWidth()*2/8-4, 125, 90, 75);
    g.setFont (10.0f);
    g.drawFittedText ("ENV", pwModRect, Justification::centredTop, 1);
    g.drawFittedText ("LFO", pwModRect, Justification::centred, 1);
    g.drawFittedText ("NONE", pwModRect, Justification::centredBottom, 1);

//  Lines
    g.drawLine (areaVol.getWidth()+8, 40, areaVol.getWidth()+8, area.getHeight()-14);
    g.drawLine (areaVol.getWidth() + areaLFO.getWidth()+16, 40, 
    			areaVol.getWidth() + areaLFO.getWidth()+16, area.getHeight()-14);
    g.drawLine (areaVol.getWidth() + areaLFO.getWidth() + areaDCO.getWidth()+24, 40,  
    			areaVol.getWidth() + areaLFO.getWidth() + areaDCO.getWidth()+24, area.getHeight()-14);
    g.drawLine (areaVol.getWidth() + areaLFO.getWidth() + areaDCO.getWidth() + areaVCF.getWidth()+32, 40,  
    			areaVol.getWidth() + areaLFO.getWidth() + areaDCO.getWidth() + areaVCF.getWidth()+32, area.getHeight()-14);
    // 	DCO Lines
    int x1 = (areaDCO.getWidth() * 1/8 + 37) + areaLFO.getWidth() + areaVol.getWidth()+12;
    int x2 = (areaDCO.getWidth() * 2/8 + 12) + areaLFO.getWidth() + areaVol.getWidth()+12;
    int x3 = (areaDCO.getWidth() * 3/8 + 37) + areaLFO.getWidth() + areaVol.getWidth()+12;
    g.drawLine (x1, 45, x3, 45, 1);
    g.drawLine (x1, 45, x1, 50, 1);
    g.drawLine (x2, 45, x2, 110, 1);
    g.drawLine (x3, 45, x3, 50, 1);
    x1 = (areaDCO.getWidth() * 5/8 + 37) + areaLFO.getWidth() + areaVol.getWidth()+12;
    x2 = (areaDCO.getWidth() * 6/8 + 37) + areaLFO.getWidth() + areaVol.getWidth()+12;
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

    auto areaVol = area.removeFromLeft(area.getWidth() * 2/20).reduced(4, 4);   
    auto areaLFO = area.removeFromLeft(area.getWidth() * 2/18).reduced(4, 4);   
    auto areaDCO = area.removeFromLeft(area.getWidth() * 8/16).reduced(4, 4);
    auto areaVCF = area.removeFromLeft(area.getWidth() * 4/8).reduced(4, 4);   
    auto areaEnv = area.reduced(4, 4);

    float widthVol = areaVol.getWidth();    
    float widthLFO = areaLFO.getWidth();    
    float widthDCO = areaDCO.getWidth();    
    float widthVCF = areaVCF.getWidth();
    float widthEnv = areaEnv.getWidth();

/*	VOLUME 	*/
    auto volArea = areaVol.withSizeKeepingCentre(90, 220);
    volumeLabel.setBounds(volArea.removeFromTop(20));
    volumeKnob.setBounds(volArea.withSizeKeepingCentre(90, 90));

/*	LFO 	*/
    auto lfoRateArea = areaLFO.removeFromLeft(widthLFO/2.0f).withSizeKeepingCentre(90, 220);
    lfoRateLabel.setBounds(lfoRateArea.removeFromTop(20));
    lfoRateSlider.setBounds(lfoRateArea);

    auto lfoDelayArea = areaLFO.removeFromLeft(widthLFO/2.0f).withSizeKeepingCentre(90, 220);
    lfoDelayLabel.setBounds(lfoDelayArea.removeFromTop(20));
    lfoDelaySlider.setBounds(lfoDelayArea);

/*	DCO 	*/
    auto lfoArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);
    lfoAttenuatorLabel.setBounds(lfoArea.removeFromTop(20));
    lfoAttenuatorSlider.setBounds(lfoArea);

    auto pwArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);
    pwLabel.setBounds(pwArea.removeFromTop(20));
    pwSlider.setBounds(pwArea);

    auto pwModoArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 90);
    //pwModulationLabel.setBounds(pwModoArea.removeFromTop(20));
    pwModulationSlider.setBounds(pwModoArea.removeFromLeft(40));

    auto squareArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);
    squareIsOnLabel.setBounds(squareArea.removeFromTop(20));
    squareIsOnToggle.setBounds(squareArea.removeFromRight(75));

    auto triangleArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    triangleIsOnLabel.setBounds(triangleArea.removeFromTop(20));
    triangleIsOnToggle.setBounds(triangleArea.removeFromRight(75));

    auto subArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    subIsOnLabel.setBounds(subArea.removeFromTop(20));
    subIsOnToggle.setBounds(subArea.removeFromRight(75));

    auto subVolArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    subVolumeLabel.setBounds(subVolArea.removeFromTop(20));
    subVolumeSlider.setBounds(subVolArea);

    auto noiseVolArea = areaDCO.removeFromLeft(widthDCO/8.0f).withSizeKeepingCentre(90, 220);    
    noiseVolumeLabel.setBounds(noiseVolArea.removeFromTop(20));
    noiseVolumeSlider.setBounds(noiseVolArea);

/*	VCF 	*/
    auto filtFreqMultArea = areaVCF.removeFromLeft(widthVCF/4.0f).withSizeKeepingCentre(90, 220);
    filtFreqMultLabel.setBounds(filtFreqMultArea.removeFromTop(20));
    filtFreqMultSlider.setBounds(filtFreqMultArea);

    auto filtResArea = areaVCF.removeFromLeft(widthVCF/4.0f).withSizeKeepingCentre(90, 220);
    filtResLabel.setBounds(filtResArea.removeFromTop(20));
    filtResSlider.setBounds(filtResArea);

    auto filtEnvMultArea = areaVCF.removeFromLeft(widthVCF/4.0f).withSizeKeepingCentre(90, 220);
    filtEnvMultLabel.setBounds(filtEnvMultArea.removeFromTop(20));
    filtEnvMultSlider.setBounds(filtEnvMultArea);

    auto filtKybdArea = areaVCF.removeFromLeft(widthVCF/4.0f).withSizeKeepingCentre(90, 220);
    filtKybdLabel.setBounds(filtKybdArea.removeFromTop(20));
    filtKybdSlider.setBounds(filtKybdArea);

/*	ADSR 	*/
    auto attackArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    attackLabel.setBounds(attackArea.removeFromTop(20));
    attackSlider.setBounds(attackArea);

    auto decayArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    decayLabel.setBounds(decayArea.removeFromTop(20));
    decaySlider.setBounds(decayArea);

    auto sustainArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    sustainLabel.setBounds(sustainArea.removeFromTop(20));
    sustainSlider.setBounds(sustainArea);

    auto releaseArea = areaEnv.removeFromLeft(widthEnv/4.0f).withSizeKeepingCentre(90, 220);
    releaseLabel.setBounds(releaseArea.removeFromTop(20));
    releaseSlider.setBounds(releaseArea);

/*	KEYBOARD 	*/
    auto areaKeyboard = getLocalBounds();
    areaKeyboard.removeFromTop(300);
	keyboardComponent.setBounds(areaKeyboard.reduced(4, 2));
}
