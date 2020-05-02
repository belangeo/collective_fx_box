/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginCarlAksyAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    PluginCarlAksyAudioProcessorEditor (PluginCarlAksyAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~PluginCarlAksyAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginCarlAksyAudioProcessor& processor;
    
    /*  On a besoin d'une référence à l'arbre des paramètres dans l'éditeur graphique. */
    AudioProcessorValueTreeState& valueTreeState;

   /*  Labels. */
    Label freqLsLbl;
    Label qLsLbl;
    Label gainLsLbl;
    
    Label freqN1Lbl;
    Label qN1Lbl;
    Label gainN1Lbl;
    
    Label freqN2Lbl;
    Label qN2Lbl;
    Label gainN2Lbl;
    
    Label freqHsLbl;
    Label qHsLbl;
    Label gainHsLbl;

   /*  Potentiomètres. */
    Slider freqLsSld;
    Slider qLsSld;
    Slider gainLsSld;
    
    Slider freqN1Sld;
    Slider qN1Sld;
    Slider gainN1Sld;
    
    Slider freqN2Sld;
    Slider qN2Sld;
    Slider gainN2Sld;
    
    Slider freqHsSld;
    Slider qHsSld;
    Slider gainHsSld;
    
//    /*  L'objet SliderAttachment établi la communication entre le paramètre automatisable,
//        contrôlé par le séquenceur, et un potentiomètre dans l'interface graphique. */
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freqLsAttachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> qLsAttachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainLsAttachement;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freqN1Attachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> qN1Attachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainN1Attachement;

    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freqN2Attachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> qN2Attachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainN2Attachement;
    
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> freqHsAttachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> qHsAttachement;
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> gainHsAttachement;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginCarlAksyAudioProcessorEditor)
};
