/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
*/
class JunoDcopluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    JunoDcopluginAudioProcessorEditor (JunoDcopluginAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~JunoDcopluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;


private:
/*  This reference is provided as a quick way for your editor to
    access the processor object that created it.    */
    JunoDcopluginAudioProcessor& processor;

    CustomLookAndFeel lookAndFeel;

/*  Référence à l'arbre des paramètres dans l'éditeur graphique.    */
    AudioProcessorValueTreeState& valueTreeState;

/*  Labels. 
    Potentiomètres. 
    SliderAttachment    */
    Label lfoAttenuatorLabel;
    Slider lfoAttenuator;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoAttenuatorAttachment;

    Label pwLabel;
    Slider pw;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwAttachment;

    Label pwModulationLabel;
    Slider pwModulation;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwModulationAttachment;

    Label subVolumeLabel;
    Slider subVolume;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> subVolumeAttachment;

    Label noiseVolumeLabel;
    Slider noiseVolume;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noiseVolumeAttachment;

    Label squareIsOnLabel;
    ToggleButton squareIsOn;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> squareIsOnAttachment;

    Label triangleIsOnLabel;
    ToggleButton triangleIsOn;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> triangleIsOnAttachment;

    Label subIsOnLabel;
    ToggleButton subIsOn;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> subIsOnAttachment;

    MidiKeyboardComponent keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoDcopluginAudioProcessorEditor)
};
