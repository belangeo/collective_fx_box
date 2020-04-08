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
class OverdriveApvtsAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    /*  On ajoute une référence à un objet AudioProcessorValueTreeState en argument de l'éditeur graphique. */
    OverdriveApvtsAudioProcessorEditor (OverdriveApvtsAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~OverdriveApvtsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    OverdriveApvtsAudioProcessor& processor;

    CustomLookAndFeel lookAndFeel;

    /*  On a besoin d'une référence à l'arbre des paramètres dans l'éditeur graphique. */
    AudioProcessorValueTreeState& valueTreeState;

    /*  Labels. */
    Label driveLabel;
    Label cutoffLabel;
    Label resLabel;

    /*  Potentiomètres. */
    Slider distoDrive;
    Slider distoCutoff;
    Slider distoRes;

    /*  L'objet SliderAttachment établi la communication entre le paramètre automatisable,
        contrôlé par le séquenceur, et un potentiomètre dans l'interface graphique. */
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> resAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OverdriveApvtsAudioProcessorEditor)
};
