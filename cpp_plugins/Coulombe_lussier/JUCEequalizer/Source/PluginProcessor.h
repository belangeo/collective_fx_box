/*
  ==============================================================================

	Remi Coulombe - Antoine Lussier
	MUS3329 - 2020
	------------------------------
	Multi effet
	Eq -> Disto -> Comp. -> De-Esser

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
//#include "parametricEQ.h"
#include "../../../../lib/parametricEQ.h"
#include "compress.h"
#include "linkwitzRileyFilter.h"
#include "disto.h"
#include "distoFiltr.h"
//#include "CircularBuffer.h"

//==============================================================================
/**
*/

class EqualizerMusAudioProcessor : public AudioProcessor
{
public:
	//==============================================================================
	EqualizerMusAudioProcessor();
	~EqualizerMusAudioProcessor();

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(AudioBuffer<float>&, MidiBuffer&) override;

	//==============================================================================
	AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const String getProgramName(int index) override;
	void changeProgramName(int index, const String& newName) override;

	//==============================================================================
	void getStateInformation(MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;
	// limiter values
	//float lim_Thresh = 1, lim_attTime = 0.001, lim_relTime = 0.2;

	
private:
	AudioProcessorValueTreeState parameters;
	
	/*
	eq -> disto -> compressor -> deesser -/-> limiter(RIP)
	*/

	// Eq
	struct parametricEQ *lowShelf[2];
	struct parametricEQ *peak01[2];
	struct parametricEQ *peak02[2];
	struct parametricEQ *peak03[2];
	struct parametricEQ *peak04[2];
	struct parametricEQ *highShelf[2];
	// low shelf
	std::atomic<float> *lsGainParameter;
	std::atomic<float> *lsFreqParameter;
	std::atomic<float> *lsQParameter;
	// peak 01
	std::atomic<float> *peak01GainParameter;
	std::atomic<float> *peak01FreqParameter;
	std::atomic<float> *peak01QParameter;
	// peak 02
	std::atomic<float> *peak02GainParameter;
	std::atomic<float> *peak02FreqParameter;
	std::atomic<float> *peak02QParameter;
	// peak 03
	std::atomic<float> *peak03GainParameter;
	std::atomic<float> *peak03FreqParameter;
	std::atomic<float> *peak03QParameter;
	// peak 04
	std::atomic<float> *peak04GainParameter;
	std::atomic<float> *peak04FreqParameter;
	std::atomic<float> *peak04QParameter;
	// high shelf
	std::atomic<float> *hsGainParameter;
	std::atomic<float> *hsFreqParameter;
	std::atomic<float> *hsQParameter;
	// fold back disto
	struct disto *dist[2];
	std::atomic<float> *distoInParameter;
	std::atomic<float> *distoAmountParameter;
	std::atomic<float> *distoDWParameter;
	std::atomic<float> *distoFreqParameter;
	std::atomic<float> *distoOutParameter;
	// compressor
	struct compress *compressor[2];
	std::atomic<float> *compThreshParameter;
	std::atomic<float> *compRatioParameter;
	std::atomic<float> *compAttParameter;
	std::atomic<float> *compRelParameter;
	std::atomic<float> *compLHParameter;
	std::atomic<float> *compOGParameter;
	std::atomic<float> *compDWParameter;
	// deesser
	struct filter *deesser[2];
	std::atomic<float> *deesserFreqParameter;
	std::atomic<float> *deesserThreshParameter;
	std::atomic<float> *deesserOutParameter;

	// limiter
	/*float lim_Gain, lim_peak;
	Array <CircularBuffer> allBuffers;
	std::atomic<float> *limiterThreshParameter;
	std::atomic<float> *limiterAttParameter;
	std::atomic<float> *limiterRelParameter;
	std::atomic<float> *limiterGainParameter;
	std::atomic<float> *limiterPeakParameter;*/

	

	//==============================================================================
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EqualizerMusAudioProcessor)
};
