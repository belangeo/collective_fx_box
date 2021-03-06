// Fabien Lamarche-Filion

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
*/

// Structure pour l'interface pour chaque bande frequentielle
struct band_interface{
    /*  Labels. */
    Label freqLabel;
    Label delayDurationLabel;
    Label delayFeedbackLabel;
    Label delayDryWetLabel;
    Label delayVolumeLabel;

    /*  Potentiomètres. */
    Slider delayDuration;
    Slider delayFeedback;
    Slider delayDryWet;
    Slider delayVolume;

    /*  L'objet SliderAttachment établi la communication entre le paramètre automatisable,
        contrôlé par le séquenceur, et un potentiomètre dans l'interface graphique. */
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayDurationAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayFeedbackAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayDryWetAttachment;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> delayVolumeAttachment;
};
class MultibandDelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MultibandDelayAudioProcessorEditor (MultibandDelayAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~MultibandDelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MultibandDelayAudioProcessor& processor;

    CustomLookAndFeel lookAndFeel;

    /*  On a besoin d'une référence à l'arbre des paramètres dans l'éditeur graphique. */
    AudioProcessorValueTreeState& valueTreeState;

    struct band_interface bandInterface[NB_BANDS];
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultibandDelayAudioProcessorEditor)
};
