/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

 ==============================================================================à

    ROBOT VOICE

    1. Compression
    2. Modulation d'amplitude
    3. Modulation de fréquences.
    4. Transposition
    5. Reverb
    6. Gain
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "math.h"

//static FILE* fTrace = NULL;


//==============================================================================
RobotVoiceAudioProcessor::RobotVoiceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    )
#endif
{
    //fTrace = fopen("debug.txt", "w");
}

RobotVoiceAudioProcessor::~RobotVoiceAudioProcessor()
{
}

//==============================================================================
const String RobotVoiceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RobotVoiceAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool RobotVoiceAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool RobotVoiceAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double RobotVoiceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RobotVoiceAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RobotVoiceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RobotVoiceAudioProcessor::setCurrentProgram(int index)
{
}

const String RobotVoiceAudioProcessor::getProgramName(int index)
{
    return {};
}

void RobotVoiceAudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void RobotVoiceAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    //Initializing the generator
    gen_amplitude = 0.5;
    gen_frequency = freqMeter;
    gen_phase = 0.0;
    gen_time = 0.0;
    gen_deltaTime = 1 / sampleRate;

}

void RobotVoiceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RobotVoiceAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
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

void RobotVoiceAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   // fprintf(fTrace, "Freq value %d\n", freqMeter);
   // fflush(fTrace);

    //=====================SIN PROCESSING=========================================================
    //First we process in mono and later we do it for all the output channels.
    if (gen_time >= std::numeric_limits<float>::max())
    {
        gen_time = 0.0;
    }

    float* monoBuffer = new float[buffer.getNumSamples()];

    for (int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        //sin formula : y(t) = A * sin(2Pi * f * t + p)
        float sinValue = gen_amplitude * sin(2 * double_Pi * freqMeter * gen_time + gen_phase);
        monoBuffer[sample] = sinValue;
        gen_time = gen_time + gen_deltaTime;
    }

    //=============================================================================================

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }


    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); i++) {
            channelData[i] = channelData[i] * (1 - wetMeter) + channelData[i] * monoBuffer[i] * wetMeter;
            channelData[i] *= volumeMeter; //Controle du gain tres brute
        }

        // ..do something to the data...
    }
}

//==============================================================================
bool RobotVoiceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RobotVoiceAudioProcessor::createEditor()
{
    return new RobotVoiceAudioProcessorEditor(*this);
}

//==============================================================================
void RobotVoiceAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RobotVoiceAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RobotVoiceAudioProcessor();
}
