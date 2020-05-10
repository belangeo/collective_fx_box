/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MarwanFiltreIirAudioProcessor::MarwanFiltreIirAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr), lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))
#endif
{
    NormalisableRange<float> cutoffRange (20.0f, 20000.0f);
    NormalisableRange<float> resRange (0.0f, 1.0f);
    NormalisableRange<float> filterMenuRange (0, 2);
    
    tree.createAndAddParameter("cutoff", "Cutoff", "cutoffLabel", cutoffRange, 600.0f, nullptr, nullptr);
    tree.createAndAddParameter("resonance", "Resonance", "ResonanceLabel", resRange, 2.0f, nullptr, nullptr);
    tree.createAndAddParameter("filterMenu", "FilterMenu", "filterMenuLabel", filterMenuRange, 0, nullptr, nullptr);
}

MarwanFiltreIirAudioProcessor::~MarwanFiltreIirAudioProcessor()
{
}

//==============================================================================
const String MarwanFiltreIirAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MarwanFiltreIirAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MarwanFiltreIirAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MarwanFiltreIirAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MarwanFiltreIirAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MarwanFiltreIirAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MarwanFiltreIirAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MarwanFiltreIirAudioProcessor::setCurrentProgram (int index)
{
}

const String MarwanFiltreIirAudioProcessor::getProgramName (int index)
{
    return {};
}

void MarwanFiltreIirAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MarwanFiltreIirAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
}

void MarwanFiltreIirAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MarwanFiltreIirAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MarwanFiltreIirAudioProcessor::updateFilterLowpass()
{
    float freq = *tree.getRawParameterValue("cutoff");
    float res = *tree.getRawParameterValue("resonance");

    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, freq, res);
}

void MarwanFiltreIirAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    dsp::AudioBlock<float> block (buffer);
    updateFilterLowpass();
    lowPassFilter.process(dsp::ProcessContextReplacing <float> (block));
}

//==============================================================================
bool MarwanFiltreIirAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MarwanFiltreIirAudioProcessor::createEditor()
{
    return new MarwanFiltreIirAudioProcessorEditor (*this);
}

//==============================================================================
void MarwanFiltreIirAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MarwanFiltreIirAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MarwanFiltreIirAudioProcessor();
}
