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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JunoDcopluginAudioProcessor& processor;

    CustomLookAndFeel lookAndFeel;

    /*  On a besoin d'une référence à l'arbre des paramètres dans l'éditeur graphique. */
    AudioProcessorValueTreeState& valueTreeState;

    /*  Labels. */
    //Label lfoInAttenuatorLabel;
    Label lfoAttenuatorLabel;
    Label pwLabel;
    Label pwModulationLabel;
    Label subVolumeLabel;
    Label noiseVolumeLabel;
    Label squareIsOnLabel;
    Label triangleIsOnLabel;
    Label subIsOnLabel;

    /*  Potentiomètres. */
    Slider lfoAttenuator;
    Slider pw;
    Slider pwModulation;
    Slider subVolume;
    Slider noiseVolume;
    ToggleButton squareIsOn;
    ToggleButton triangleIsOn;
    ToggleButton subIsOn;

    /*  L'objet SliderAttachment établi la communication entre le paramètre automatisable,
        contrôlé par le séquenceur, et un potentiomètre dans l'interface graphique. */
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> lfoAttenuatorAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> pwModulationAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> subVolumeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> noiseVolumeAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> squareIsOnAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> triangleIsOnAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> subIsOnAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunoDcopluginAudioProcessorEditor)
};
