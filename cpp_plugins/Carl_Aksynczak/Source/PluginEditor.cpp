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
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts) /* On ajoute l<initialisation de la variable valueTreeState. */
{

    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]


    freqLsLbl.setText("Freq LowShelf", NotificationType::dontSendNotification);
    freqLsLbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    freqLsLbl.setJustificationType (Justification::centredLeft);
    freqLsLbl.setEditable (false, false, false);
    freqLsLbl.setColour (TextEditor::textColourId, Colours::black);
    freqLsLbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible (&freqLsLbl);

    freqLsLbl.setBounds (32, 48, 88, 16);

    freqLsAttachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "freqLS", freqLsSld));
    //freqLsSld.setRange (0, 400, 0);
    freqLsSld.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    freqLsSld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible (&freqLsSld);

    freqLsSld.setBounds (32, 72, 88, 112);

    freqN1Lbl.setText("Freq Notch 1", NotificationType::dontSendNotification);
    freqN1Lbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    freqN1Lbl.setJustificationType (Justification::centredLeft);
    freqN1Lbl.setEditable (false, false, false);
    freqN1Lbl.setColour (TextEditor::textColourId, Colours::black);
    freqN1Lbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&freqN1Lbl);

    freqN1Lbl.setBounds (128, 48, 88, 16);

    freqN1Attachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "freqN1", freqN1Sld));
    //freqN1Sld.setRange (350, 5000, 0);
    freqN1Sld.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    freqN1Sld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&freqN1Sld);

    freqN1Sld.setBounds (128, 72, 88, 112);

    freqN2Lbl.setText("Freq Notch 2", NotificationType::dontSendNotification);
    freqN2Lbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    freqN2Lbl.setJustificationType (Justification::centredLeft);
    freqN2Lbl.setEditable (false, false, false);
    freqN2Lbl.setColour (TextEditor::textColourId, Colours::black);
    freqN2Lbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&freqN2Lbl);

    freqN2Lbl.setBounds (224, 48, 88, 16);

    freqN2Attachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "freqN2", freqN2Sld));
    //freqN2Sld.setRange (4000, 12000, 0);
    freqN2Sld.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    freqN2Sld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&freqN2Sld);

    freqN2Sld.setBounds (224, 72, 88, 112);

    freqHsLbl.setText("Freq HighShelf", NotificationType::dontSendNotification);
    freqHsLbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    freqHsLbl.setJustificationType (Justification::centredLeft);
    freqHsLbl.setEditable (false, false, false);
    freqHsLbl.setColour (TextEditor::textColourId, Colours::black);
    freqHsLbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&freqHsLbl);
    
    freqHsLbl.setBounds (320, 48, 88, 16);

    freqHsAttachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "freqHS", freqHsSld));
    //freqHsSld.setRange (11000, 20000, 0);
    freqHsSld.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    freqHsSld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&freqHsSld);

    freqHsSld.setBounds (320, 72, 88, 112);

    qLsAttachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "qLS", qLsSld));
    //qLsSld.setRange (0, 10, 0);
    qLsSld.setSliderStyle (Slider::LinearHorizontal);
    qLsSld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&qLsSld);

    qLsSld.setBounds (24, 216, 104, 48);

    qLsLbl.setText("Q LowShelf", NotificationType::dontSendNotification);
    qLsLbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    qLsLbl.setJustificationType (Justification::centredLeft);
    qLsLbl.setEditable (false, false, false);
    qLsLbl.setColour (TextEditor::textColourId, Colours::black);
    qLsLbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&qLsLbl);

    qLsLbl.setBounds (32, 200, 88, 16);

    qN1Lbl.setText("Q Notch 1", NotificationType::dontSendNotification);
    qN1Lbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    qN1Lbl.setJustificationType (Justification::centredLeft);
    qN1Lbl.setEditable (false, false, false);
    qN1Lbl.setColour (TextEditor::textColourId, Colours::black);
    qN1Lbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&qN1Lbl);

    qN1Lbl.setBounds (128, 200, 88, 16);

    qN2Lbl.setText("Q Notch 2", NotificationType::dontSendNotification);
    qN2Lbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    qN2Lbl.setJustificationType (Justification::centredLeft);
    qN2Lbl.setEditable (false, false, false);
    qN2Lbl.setColour (TextEditor::textColourId, Colours::black);
    qN2Lbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&qN2Lbl);

    qN2Lbl.setBounds (224, 200, 88, 16);

    qHsLbl.setText("Q HighShelf", NotificationType::dontSendNotification);
    qHsLbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    qHsLbl.setJustificationType (Justification::centredLeft);
    qHsLbl.setEditable (false, false, false);
    qHsLbl.setColour (TextEditor::textColourId, Colours::black);
    qHsLbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&qHsLbl);

    qHsLbl.setBounds (320, 200, 88, 16);

    qN1Attachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "qN1", qN1Sld));
    //qN1Sld.setRange (0, 10, 0);
    qN1Sld.setSliderStyle (Slider::LinearHorizontal);
    qN1Sld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&qN1Sld);

    qN1Sld.setBounds (120, 216, 104, 48);

    qN2Attachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "qN2", qN2Sld));
    //qN2Sld.setRange (0, 10, 0);
    qN2Sld.setSliderStyle (Slider::LinearHorizontal);
    qN2Sld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&qN2Sld);

    qN2Sld.setBounds (216, 216, 104, 48);

    qHsAttachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "qHS", qHsSld));
    //qHsSld.setRange (0, 10, 0);
    qHsSld.setSliderStyle (Slider::LinearHorizontal);
    qHsSld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&qHsSld);

    qHsSld.setBounds (312, 216, 104, 48);

    gainLsAttachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gainLS", gainLsSld));
    //gainLsSld.setRange (0, 5, 0);
    gainLsSld.setSliderStyle (Slider::LinearHorizontal);
    gainLsSld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gainLsSld);

    gainLsSld.setBounds (24, 288, 104, 48);

    gainLsLbl.setText("Gain LowShelf", NotificationType::dontSendNotification);
    gainLsLbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    gainLsLbl.setJustificationType (Justification::centredLeft);
    gainLsLbl.setEditable (false, false, false);
    gainLsLbl.setColour (TextEditor::textColourId, Colours::black);
    gainLsLbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&gainLsLbl);

    gainLsLbl.setBounds (32, 272, 88, 16);

    gainN1Lbl.setText("Gain Notch 1", NotificationType::dontSendNotification);
    gainN1Lbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    gainN1Lbl.setJustificationType (Justification::centredLeft);
    gainN1Lbl.setEditable (false, false, false);
    gainN1Lbl.setColour (TextEditor::textColourId, Colours::black);
    gainN1Lbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&gainN1Lbl);

    gainN1Lbl.setBounds (128, 272, 88, 16);

    gainN2Lbl.setText("Gain Notch 2", NotificationType::dontSendNotification);
    gainN2Lbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    gainN2Lbl.setJustificationType (Justification::centredLeft);
    gainN2Lbl.setEditable (false, false, false);
    gainN2Lbl.setColour (TextEditor::textColourId, Colours::black);
    gainN2Lbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&gainN2Lbl);

    gainN2Lbl.setBounds (224, 272, 88, 16);

    gainHsLbl.setText("Gain HighShelf", NotificationType::dontSendNotification);
    gainHsLbl.setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    gainHsLbl.setJustificationType (Justification::centredLeft);
    gainHsLbl.setEditable (false, false, false);
    gainHsLbl.setColour (TextEditor::textColourId, Colours::black);
    gainHsLbl.setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    addAndMakeVisible(&gainHsLbl);

    gainHsLbl.setBounds (320, 272, 88, 16);

    gainN1Attachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gainN1", gainN1Sld));
    //gainN1Sld.setRange (0, 5, 0);
    gainN1Sld.setSliderStyle (Slider::LinearHorizontal);
    gainN1Sld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gainN1Sld);

    gainN1Sld.setBounds (120, 288, 104, 48);

    gainN2Attachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gainN2", gainN2Sld));
    //gainN2Sld.setRange (0, 5, 0);
    gainN2Sld.setSliderStyle (Slider::LinearHorizontal);
    gainN2Sld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gainN2Sld);

    gainN2Sld.setBounds (216, 288, 104, 48);

    gainHsAttachement.reset (new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "gainHS", gainHsSld));
    //gainHsSld.setRange (0, 5, 0);
    gainHsSld.setSliderStyle (Slider::LinearHorizontal);
    gainHsSld.setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    addAndMakeVisible(&gainHsSld);

    gainHsSld.setBounds (312, 288, 104, 48);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
    
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
    g.drawFittedText ("Plugin de Carl Aksynczak", getLocalBounds(), Justification::centredTop, 1);
}

void PluginCarlAksyAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    
    freqLsLbl.setBounds (32, 48, 88, 16);
    freqLsSld.setBounds (32, 72, 88, 112);
    freqN1Lbl.setBounds (128, 48, 88, 16);
    freqN1Sld.setBounds (128, 72, 88, 112);
    freqN2Lbl.setBounds (224, 48, 88, 16);
    freqN2Sld.setBounds (224, 72, 88, 112);
    freqHsLbl.setBounds (320, 48, 88, 16);
    freqHsSld.setBounds (320, 72, 88, 112);
    qLsSld.setBounds (24, 216, 104, 48);
    qLsLbl.setBounds (32, 200, 88, 16);
    qN1Lbl.setBounds (128, 200, 88, 16);
    qN2Lbl.setBounds (224, 200, 88, 16);
    qHsLbl.setBounds (320, 200, 88, 16);
    qN1Sld.setBounds (120, 216, 104, 48);
    qN2Sld.setBounds (216, 216, 104, 48);
    qHsSld.setBounds (312, 216, 104, 48);
    gainLsSld.setBounds (24, 288, 104, 48);
    gainLsLbl.setBounds (32, 272, 88, 16);
    gainN1Lbl.setBounds (128, 272, 88, 16);
    gainN2Lbl.setBounds (224, 272, 88, 16);
    gainHsLbl.setBounds (320, 272, 88, 16);
    gainN1Sld.setBounds (120, 288, 104, 48);
    gainN2Sld.setBounds (216, 288, 104, 48);
    gainHsSld.setBounds (312, 288, 104, 48);
    
    
}
