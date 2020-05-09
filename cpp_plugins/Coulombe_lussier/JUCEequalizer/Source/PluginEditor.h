/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Images.h"
#include "CustomLnF.h"

//==============================================================================
/**
*/
class EqualizerMusAudioProcessorEditor : public AudioProcessorEditor
{
public:
	EqualizerMusAudioProcessorEditor(EqualizerMusAudioProcessor&, AudioProcessorValueTreeState& vts);
	~EqualizerMusAudioProcessorEditor();

	//==============================================================================
	void paint(Graphics&) override;
	void resized() override;

private:


	int widthB = 70;

	
	TextButton bpBtn{"Bypass"};

	CustomLnFRed lookAndFeel;
	CustomLnFBlue lookAndFeelEq2;
	CustomLnFGreen lookAndFeelEq3;
	CustomLnFWhite lookAndFeelEq4;
	CustomLnFBlack lookAndFeelEq5;
	CustomLnFMoog lookAndFeelDist;
	CustomLnFComp lookAndFeelComp;
	CustomLnFDees lookAndFeelDees;

	Image backgroundImg;
	Label inGainLab, outGainLab, distoLab, drywetLab, freqLab;
	Label threshLab, ratioLab, attLab, relLab, lhLab, comp_out, comp_dwLab;
	Label de_threshLab, de_freqLab, de_outLab;
	Label lim_ceilLab, lim_attLab, lim_relLab, lim_gainLab, lim_peakLab;

	AudioProcessorValueTreeState& valueTreeState;

	// low shelf
	Slider ls_gain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ls_gainAttachment;
	Slider ls_freq;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ls_freqAttachment;
	Slider ls_q;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> ls_qAttachment;
	// peak 01
	Slider peak01_gain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak01_gainAttachment;
	Slider peak01_freq;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak01_freqAttachment;
	Slider peak01_q;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak01_qAttachment;
	// peak 02
	Slider peak02_gain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak02_gainAttachment;
	Slider peak02_freq;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak02_freqAttachment;
	Slider peak02_q;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak02_qAttachment;
	// peak 03
	Slider peak03_gain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak03_gainAttachment;
	Slider peak03_freq;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak03_freqAttachment;
	Slider peak03_q;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak03_qAttachment;
	// peak 04
	Slider peak04_gain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak04_gainAttachment;
	Slider peak04_freq;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak04_freqAttachment;
	Slider peak04_q;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> peak04_qAttachment;
	// high shelf
	Slider hs_gain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hs_gainAttachment;
	Slider hs_freq;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hs_freqAttachment;
	Slider hs_q;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> hs_qAttachment;
	// disto
	Slider disto_in;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> disto_inAttachment;
	Slider disto_amount;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> disto_amountAttachment;
	Slider disto_dw;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> disto_dwAttachment;
	Slider disto_filterF;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> disto_freqAttachment;
	Slider disto_out;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> disto_outAttachment;
	// compressor
	Slider comp_Thresh;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> comp_ThreshAttachment;
	Slider comp_Ratio;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> comp_RatioAttachment;
	Slider comp_Att;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> comp_AttAttachment;
	Slider comp_Rel;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> comp_RelAttachment;
	Slider comp_LH;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> comp_LHAttachment;
	Slider comp_outGain;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> comp_OGAttachment;
	Slider comp_dw;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> comp_DWAttachment;
	// deesser
	Slider deesser_Thresh;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> deesser_ThreshAttachment;
	Slider deesser_Freq;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> deesser_FreqAttachment;
	Slider deeser_Out;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> deesser_OutAttachment;
	EqualizerMusAudioProcessor& processor;
	// limiter
	/*Slider limiter_Thresh;
	//std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> limiter_ThreshAttachment;
	Slider limiter_Att;
	//std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> limiter_AttAttachment;
	Slider limiter_Rel;
	//std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> limiter_RelAttachment;
	*/

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerMusAudioProcessorEditor)
};
