/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EqualizerMusAudioProcessorEditor::EqualizerMusAudioProcessorEditor(EqualizerMusAudioProcessor& p, AudioProcessorValueTreeState& vts)
	: AudioProcessorEditor(&p), processor(p), valueTreeState(vts)
{
	setSize(905, 650);
	Colour gainColor = Colour(188, 49, 28);
	Colour freqColor = Colour(230, 245, 3);
	Colour qColor = Colour(43, 106, 70);
	Colour boxbg = Colour(75, 75, 75);
	Colour transparent = Colour::fromFloatRGBA(0, 0, 0, 0);

	setLookAndFeel(&lookAndFeel);
	// labels Comp
	threshLab.setText("Threshold", NotificationType::dontSendNotification);
	threshLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&threshLab);
	ratioLab.setText("Ratio", NotificationType::dontSendNotification);
	ratioLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&ratioLab);
	attLab.setText("Attack", NotificationType::dontSendNotification);
	attLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&attLab);
	relLab.setText("Release", NotificationType::dontSendNotification);
	relLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&relLab);
	lhLab.setText("Look a head", NotificationType::dontSendNotification);
	lhLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&lhLab);
	comp_out.setText("Output", NotificationType::dontSendNotification);
	comp_out.setJustificationType(Justification::centred);
	addAndMakeVisible(&comp_out);
	comp_dwLab.setText("Dry-Wet", NotificationType::dontSendNotification);
	comp_dwLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&comp_dwLab);
	//disto
	inGainLab.setText("INPUT", NotificationType::dontSendNotification);
	inGainLab.setJustificationType(Justification::centred);
	inGainLab.setColour(Label::textColourId, Colours::black);
	inGainLab.setFont(Font(16.0f, Font::bold));
	//addAndMakeVisible(&inGainLab);
	outGainLab.setText("OUTPUT", NotificationType::dontSendNotification);
	outGainLab.setJustificationType(Justification::centred);
	outGainLab.setColour(Label::textColourId, Colours::black);
	outGainLab.setFont(Font(16.0f, Font::bold));
	//addAndMakeVisible(&outGainLab);
	distoLab.setText("DRIVE", NotificationType::dontSendNotification);
	distoLab.setJustificationType(Justification::centred);
	distoLab.setColour(Label::textColourId, Colours::black);
	distoLab.setFont(Font(16.0f, Font::bold));
	//addAndMakeVisible(&distoLab);
	drywetLab.setText("DRY-WET", NotificationType::dontSendNotification);
	drywetLab.setJustificationType(Justification::centred);
	drywetLab.setColour(Label::textColourId, Colours::black);
	drywetLab.setFont(Font(16.0f, Font::bold));
	//addAndMakeVisible(&drywetLab);
	freqLab.setText("FREQ", NotificationType::dontSendNotification);
	freqLab.setJustificationType(Justification::centred);
	freqLab.setColour(Label::textColourId, Colours::black);
	freqLab.setFont(Font(16.0f, Font::bold));
	//addAndMakeVisible(&freqLab);
	//deesser
	de_threshLab.setText("THRESHOLD", NotificationType::dontSendNotification);
	de_threshLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&de_threshLab);
	de_freqLab.setText("FREQUENCY", NotificationType::dontSendNotification);
	de_freqLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&de_freqLab);
	de_outLab.setText("OUTPUT BAND", NotificationType::dontSendNotification);
	de_outLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&de_outLab);
	// limiter
	lim_ceilLab.setText("Threshold", NotificationType::dontSendNotification);
	lim_ceilLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&lim_ceilLab);
	lim_attLab.setText("Attack", NotificationType::dontSendNotification);
	lim_attLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&lim_attLab);
	lim_relLab.setText("Release", NotificationType::dontSendNotification);
	lim_relLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&lim_relLab);
	lim_gainLab.setText("Gain", NotificationType::dontSendNotification);
	lim_gainLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&lim_gainLab);
	lim_peakLab.setText("Peak", NotificationType::dontSendNotification);
	lim_peakLab.setJustificationType(Justification::centred);
	addAndMakeVisible(&lim_peakLab);


	int textBoxSizeX = widthB, textBoxSizeY = 10;
	// low shelf
	ls_gain.setLookAndFeel(&lookAndFeelEq4);
	ls_gain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	ls_gain.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	ls_gain.setColour(Slider::rotarySliderFillColourId, gainColor);
	addAndMakeVisible(&ls_gain);
	ls_gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lsGain", ls_gain));
	ls_freq.setLookAndFeel(&lookAndFeelEq4);
	ls_freq.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	ls_freq.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&ls_freq);
	ls_freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lsFreq", ls_freq));
	ls_q.setLookAndFeel(&lookAndFeelEq4);
	ls_q.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	ls_q.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&ls_q);
	ls_qAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lsQ", ls_q));
	// peak 01
	peak01_gain.setLookAndFeel(&lookAndFeel);
	peak01_gain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak01_gain.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	peak01_gain.setColour(Slider::rotarySliderFillColourId, gainColor);
	addAndMakeVisible(&peak01_gain);
	peak01_gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak01Gain", peak01_gain));
	peak01_freq.setLookAndFeel(&lookAndFeel);
	peak01_freq.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak01_freq.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak01_freq);
	peak01_freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak01Freq", peak01_freq));
	peak01_q.setLookAndFeel(&lookAndFeel);
	peak01_q.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak01_q.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak01_q);
	peak01_qAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak01Q", peak01_q));
	// peak 02
	peak02_gain.setLookAndFeel(&lookAndFeelEq3);
	peak02_gain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak02_gain.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	peak02_gain.setColour(Slider::rotarySliderFillColourId, gainColor);
	addAndMakeVisible(&peak02_gain);
	peak02_gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak02Gain", peak02_gain));
	peak02_freq.setLookAndFeel(&lookAndFeelEq3);
	peak02_freq.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak02_freq.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak02_freq);
	peak02_freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak02Freq", peak02_freq));
	peak02_q.setLookAndFeel(&lookAndFeelEq3);
	peak02_q.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak02_q.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak02_q);
	peak02_qAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak02Q", peak02_q));
	// peak 03
	peak03_gain.setLookAndFeel(&lookAndFeelEq2);
	peak03_gain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak03_gain.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	peak03_gain.setColour(Slider::rotarySliderFillColourId, gainColor);
	addAndMakeVisible(&peak03_gain);
	peak03_gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak03Gain", peak03_gain));
	peak03_freq.setLookAndFeel(&lookAndFeelEq2);
	peak03_freq.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak03_freq.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak03_freq);
	peak03_freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak03Freq", peak03_freq));
	peak03_q.setLookAndFeel(&lookAndFeelEq2);
	peak03_q.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak03_q.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak03_q);
	peak03_qAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak03Q", peak03_q));
	// peak 04
	peak04_gain.setLookAndFeel(&lookAndFeel);
	peak04_gain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak04_gain.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	peak04_gain.setColour(Slider::rotarySliderFillColourId, gainColor);
	addAndMakeVisible(&peak04_gain);
	peak04_gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak04Gain", peak04_gain));
	peak04_freq.setLookAndFeel(&lookAndFeel);
	peak04_freq.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak04_freq.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak04_freq);
	peak04_freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak04Freq", peak04_freq));
	peak04_q.setLookAndFeel(&lookAndFeel);
	peak04_q.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	peak04_q.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&peak04_q);
	peak04_qAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "peak04Q", peak04_q));
	// high shelf
	hs_gain.setLookAndFeel(&lookAndFeelEq5);
	hs_gain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	hs_gain.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	hs_gain.setColour(Slider::rotarySliderFillColourId, gainColor);
	addAndMakeVisible(&hs_gain);
	hs_gainAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "hsGain", hs_gain));
	hs_freq.setLookAndFeel(&lookAndFeelEq5);
	hs_freq.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	hs_freq.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&hs_freq);
	hs_freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "hsFreq", hs_freq));
	hs_q.setLookAndFeel(&lookAndFeelEq5);
	hs_q.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	hs_q.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&hs_q);
	hs_qAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "hsQ", hs_q));

	// disto
	disto_in.setLookAndFeel(&lookAndFeelDist);
	disto_in.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	disto_in.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	disto_in.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&disto_in);
	disto_inAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "distoIn", disto_in));
	disto_amount.setLookAndFeel(&lookAndFeelDist);
	disto_amount.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	disto_amount.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	disto_amount.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&disto_amount);
	disto_amountAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "distoAmount", disto_amount));
	disto_dw.setLookAndFeel(&lookAndFeelDist);
	disto_dw.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	disto_dw.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	disto_dw.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&disto_dw);
	disto_dwAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "distoDW", disto_dw));
	disto_filterF.setLookAndFeel(&lookAndFeelDist);
	disto_filterF.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	disto_filterF.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	disto_filterF.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&disto_filterF);
	disto_freqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "distoFreq", disto_filterF));
	disto_out.setLookAndFeel(&lookAndFeelDist);
	disto_out.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	disto_out.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	disto_out.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&disto_out);
	disto_outAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "distoOut", disto_out));

	// compressor
	comp_Thresh.setLookAndFeel(&lookAndFeelComp);
	comp_Thresh.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	comp_Thresh.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	comp_Thresh.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&comp_Thresh);
	comp_ThreshAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "compThresh", comp_Thresh));

	comp_Ratio.setLookAndFeel(&lookAndFeelComp);
	comp_Ratio.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	comp_Ratio.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	comp_Ratio.setColour(Slider::trackColourId, boxbg);
	comp_Ratio.setColour(Slider::backgroundColourId, boxbg.withAlpha(1.0f));
	addAndMakeVisible(&comp_Ratio);
	comp_RatioAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "compRatio", comp_Ratio));

	comp_Att.setLookAndFeel(&lookAndFeelComp);
	comp_Att.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	comp_Att.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	comp_Att.setColour(Slider::trackColourId, boxbg);
	comp_Att.setColour(Slider::backgroundColourId, boxbg.withAlpha(1.0f));
	addAndMakeVisible(&comp_Att);
	comp_AttAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "compAtt", comp_Att));

	comp_Rel.setLookAndFeel(&lookAndFeelComp);
	comp_Rel.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	comp_Rel.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	comp_Rel.setColour(Slider::trackColourId, boxbg);
	comp_Rel.setColour(Slider::backgroundColourId, boxbg.withAlpha(1.0f));
	addAndMakeVisible(&comp_Rel);
	comp_RelAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "compRel", comp_Rel));

	comp_LH.setLookAndFeel(&lookAndFeelComp);
	comp_LH.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	comp_LH.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	comp_LH.setColour(Slider::trackColourId, boxbg);
	comp_LH.setColour(Slider::backgroundColourId, boxbg);
	addAndMakeVisible(&comp_LH);
	comp_LHAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "compLH", comp_LH));
	// comp gain output
	comp_outGain.setLookAndFeel(&lookAndFeelComp);
	comp_outGain.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	comp_outGain.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	addAndMakeVisible(&comp_outGain);
	comp_OGAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "compOG", comp_outGain));

	comp_dw.setLookAndFeel(&lookAndFeelComp);
	comp_dw.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	comp_dw.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	comp_dw.setColour(Slider::trackColourId, boxbg);
	comp_dw.setColour(Slider::backgroundColourId, boxbg);
	addAndMakeVisible(&comp_dw);
	comp_DWAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "compDW", comp_dw));
	// deesser
	deesser_Thresh.setLookAndFeel(&lookAndFeelDees);
	deesser_Thresh.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	deesser_Thresh.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	deesser_Thresh.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&deesser_Thresh);
	deesser_ThreshAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "deesserThresh", deesser_Thresh));

	deesser_Freq.setLookAndFeel(&lookAndFeelDees);
	deesser_Freq.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	deesser_Freq.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	deesser_Freq.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&deesser_Freq);
	deesser_FreqAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "deesserFreq", deesser_Freq));

	deeser_Out.setLookAndFeel(&lookAndFeelDees);
	deeser_Out.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	deeser_Out.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	deeser_Out.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&deeser_Out);
	deesser_OutAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "deesserOut", deeser_Out));
	// limiter
	/*limiter_Thresh.setLookAndFeel(&lookAndFeelComp);
	limiter_Thresh.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	limiter_Thresh.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	limiter_Thresh.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&limiter_Thresh);
	//limiter_ThreshAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "limiterThresh", limiter_Thresh));
	limiter_Thresh.setValue(0);
	limiter_Thresh.setRange(-60.f, 10.0f, 0.001f);
	limiter_Thresh.onValueChange = [this] {
		processor.lim_Thresh = std::pow(10, (limiter_Thresh.getValue() / 20));
	};

	limiter_Att.setLookAndFeel(&lookAndFeelComp);
	limiter_Att.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	limiter_Att.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	limiter_Att.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&limiter_Att);
	//limiter_AttAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "limiterAtt", limiter_Att));
	limiter_Att.setRange(0.0f, 10.0f, 0.001f);
	limiter_Att.onValueChange = [this] {
		processor.lim_attTime = 1 - std::pow(MathConstants<float>::euler, ((1 / processor.getSampleRate()) * -2.2f) / limiter_Att.getValue());
	};

	limiter_Rel.setLookAndFeel(&lookAndFeelComp);
	limiter_Rel.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	limiter_Rel.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxSizeX, textBoxSizeY);
	limiter_Rel.setColour(Slider::trackColourId, Colours::yellow);
	addAndMakeVisible(&limiter_Rel);
	//limiter_RelAttachment.reset(new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "limiterRel", limiter_Rel));
	limiter_Rel.setRange(0.0f, 10.0f, 0.001f);
	limiter_Rel.onValueChange = [this] {
		processor.lim_relTime = 1 - std::pow(MathConstants<float>::euler, ((1 / processor.getSampleRate()) * -2.2f) / limiter_Rel.getValue());
	};*/
}

EqualizerMusAudioProcessorEditor::~EqualizerMusAudioProcessorEditor()
{
}

//==============================================================================
void EqualizerMusAudioProcessorEditor::paint(Graphics& g)
{
	backgroundImg = ImageCache::getFromMemory(Images::bg2_png, Images::bg2_pngSize);
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.setColour(Colours::white);
	g.drawImage(backgroundImg, 0, 0, 905, 650, 0, 0, 905, 650);
}

void EqualizerMusAudioProcessorEditor::resized()
{
	int knob_small_w = 70, knob_small_h = 65;
	int knob_big_w = 75, knob_big_h = 70;
	int knob_bigboy_w = 125, knob_bigboy_h = 120;
	int eq_left = 32, eq_right = 133;
	int label_x = 80, label_y = 15;
	// posX, posY, widht, heigh	
	// low shelf
	ls_freq.setBounds(eq_left, 15, knob_small_w, knob_small_h);
	ls_q.setBounds(eq_left, 80, knob_small_w, knob_small_h);
	ls_gain.setBounds(eq_right, 47, knob_small_w, knob_small_h);
	// peak 01
	peak01_freq.setBounds(eq_right, 112, knob_small_w, knob_small_h);
	peak01_q.setBounds(eq_right, 177, knob_small_w, knob_small_h);
	peak01_gain.setBounds(eq_left, 145, knob_small_w, knob_small_h);
	// peak 02
	peak02_freq.setBounds(eq_left, 210, knob_small_w, knob_small_h);
	peak02_q.setBounds(eq_left, 275, knob_small_w, knob_small_h);
	peak02_gain.setBounds(eq_right, 242, knob_small_w, knob_small_h);
	// peak 03
	peak03_freq.setBounds(eq_right, 307, knob_small_w, knob_small_h);
	peak03_q.setBounds(eq_right, 372, knob_small_w, knob_small_h);
	peak03_gain.setBounds(eq_left, 340, knob_small_w, knob_small_h);
	// peak 04
	peak04_freq.setBounds(eq_left, 405, knob_small_w, knob_small_h);
	peak04_q.setBounds(eq_left, 470, knob_small_w, knob_small_h);
	peak04_gain.setBounds(eq_right, 437, knob_small_w, knob_small_h);
	// high shelf
	hs_freq.setBounds(eq_right, 502, knob_small_w, knob_small_h);
	hs_q.setBounds(eq_right, 567, knob_small_w, knob_small_h);
	hs_gain.setBounds(eq_left, 535, knob_small_w, knob_small_h);

	// disto
	int disto_mid = 341, disto_w = 70, disto_h = 80;
	disto_in.setBounds(disto_mid - 80, 450, disto_w, disto_h);
	disto_out.setBounds(disto_mid + 10, 450, disto_w, disto_h);
	disto_amount.setBounds(disto_mid - 80, 100, disto_w, disto_h);
	disto_dw.setBounds(disto_mid + 10, 172, disto_w, disto_h);
	disto_filterF.setBounds(disto_mid - 35, 350, disto_w, disto_h);

	inGainLab.setBounds(disto_mid - 85, 435, label_x, label_y);
	outGainLab.setBounds(disto_mid + 5, 435, label_x, label_y);
	distoLab.setBounds(disto_mid - 85, 85, label_x, label_y);
	drywetLab.setBounds(disto_mid + 5, 157, label_x, label_y);
	freqLab.setBounds(disto_mid - 40, 335, label_x, label_y);

	// compressor
	int comp_mid = 562, comp_w = 66, comp_h = 80;
	comp_Thresh.setBounds(comp_mid - 76, 80, comp_w, comp_h);
	comp_Ratio.setBounds(comp_mid + 10, 80, comp_w, comp_h);
	comp_Att.setBounds(comp_mid - 76, 215, comp_w, comp_h);
	comp_Rel.setBounds(comp_mid + 10, 215, comp_w, comp_h);
	comp_LH.setBounds(comp_mid - 76, 350, comp_w, comp_h);
	comp_outGain.setBounds(comp_mid + 10, 350, comp_w, comp_h);
	comp_dw.setBounds(comp_mid + 10, 485, comp_w, comp_h);

	threshLab.setBounds(comp_mid - 83, 65, label_x, label_y);
	ratioLab.setBounds(comp_mid + 3, 65, label_x, label_y);
	attLab.setBounds(comp_mid - 83, 200, label_x, label_y);
	relLab.setBounds(comp_mid + 3, 200, label_x, label_y);
	lhLab.setBounds(comp_mid - 83, 335, label_x, label_y);
	comp_out.setBounds(comp_mid + 3, 335, label_x, label_y);
	comp_dwLab.setBounds(comp_mid + 3, 470, label_x, label_y);

	// deesser
	int de_mid_btn = (784 - (knob_big_w / 2)), de_mid_btn_bb = (784 - (knob_bigboy_w / 2));
	deesser_Thresh.setBounds(de_mid_btn_bb, 80, knob_bigboy_w, knob_bigboy_h);
	deeser_Out.setBounds(de_mid_btn_bb, 245, knob_bigboy_w, knob_bigboy_h);
	deesser_Freq.setBounds(de_mid_btn_bb, 410, knob_bigboy_w, knob_bigboy_h);

	de_threshLab.setBounds(744, 65, label_x, label_y);
	de_outLab.setBounds(744, 230, label_x, label_y);
	de_freqLab.setBounds(744, 395, label_x, label_y);

	// limiter
	/*int limiter_mid = 1005;
	limiter_Thresh.setBounds	(limiter_mid - 76, 80, comp_w, comp_h);
	limiter_Att.setBounds		(limiter_mid + 10, 80, comp_w, comp_h);
	limiter_Rel.setBounds		(limiter_mid - 76, 215, comp_w, comp_h);

	lim_ceilLab.setBounds		(limiter_mid - 83, 65, 80, 15);
	lim_attLab.setBounds		(limiter_mid + 3, 65, 80, 15);
	lim_relLab.setBounds		(limiter_mid - 83, 200, 80, 15);*/
}