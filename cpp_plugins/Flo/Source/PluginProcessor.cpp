/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PlugexLookAndFeel.h"


#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

static String freqSliderValueToText(float value) {
    return String(value, 2) + String(" Hz");
}

static float freqSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String depthSliderValueToText(float value) {
    return String(value, 2) + String(" x");
}

static float depthSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String ffreqSliderValueToText(float value) {
    return String(value, 2) + String(" Hz");
}

static float ffreqSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String timeSliderValueToText(float value) {
    return String(value, 2) + String(" ms");
}

static float timeSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String feedbackSliderValueToText(float value) {
    return String(value, 2) + String(" %");
}

static float feedbackSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;
    
    parameters.push_back(std::make_unique<Parameter>(String("freq"), String("Freq"), String(),
                                                     NormalisableRange<float>(0.001f, 20.0f, 0.001f, 0.3f),
                                                     1.0f, freqSliderValueToText, freqSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(String("depth"), String("Depth"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.0f, depthSliderValueToText, depthSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(String("ffreq"), String("Ffreq"), String(),
                                                     NormalisableRange<float>(20.0f, 18000.0f, 0.01f, 0.3f),
                                                     1000.0f, ffreqSliderValueToText, ffreqSliderTextToValue));
    
    parameters.push_back(std::make_unique<Parameter>(String("time"), String("Time"), String(),
                                                     NormalisableRange<float>(0.01f, 1000.0f, 0.01f, 0.3f),
                                                     100.0f, timeSliderValueToText, timeSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("feedback"), String("Feedback"), String(),
                                                     NormalisableRange<float>(0.0f, 100.0f, 0.01f, 1.0f),
                                                     0.0f, feedbackSliderValueToText, feedbackSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("balance"), String("Balance"), String(),
                                                     NormalisableRange<float>(0.0f, 100.0f, 0.01f, 1.0f),
                                                     50.0f, feedbackSliderValueToText, feedbackSliderTextToValue));

    
    //parameters.push_back(std::make_unique<Parameter>(String("CHOISE"), String ("Choice"), StringArray ("Choice1", "Choice2", "Choice3"), 0));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
FloAudioProcessor::FloAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
parameters (*this, nullptr, Identifier(JucePlugin_Name), createParameterLayout())

{
    freqParameter = parameters.getRawParameterValue("freq");
    depthParameter = parameters.getRawParameterValue("depth");
    ffreqParameter = parameters.getRawParameterValue("ffreq");
    timeParameter = parameters.getRawParameterValue("time");
    feedbackParameter = parameters.getRawParameterValue("feedback");
    balanceParameter = parameters.getRawParameterValue("balance");

}

FloAudioProcessor::~FloAudioProcessor()
{
}

//==============================================================================
const String FloAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FloAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FloAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FloAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FloAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FloAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FloAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FloAudioProcessor::setCurrentProgram (int index)
{
}

const String FloAudioProcessor::getProgramName (int index)
{
    return {};
}

void FloAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FloAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    currentSampleRate = sampleRate;
    
    freqSmoothed.reset(sampleRate, samplesPerBlock/sampleRate);
    freqSmoothed.setCurrentAndTargetValue(*freqParameter);
    depthSmoothed.reset(sampleRate, samplesPerBlock/sampleRate);
    depthSmoothed.setCurrentAndTargetValue(*depthParameter);
    lfoPhase = 0.0f;
    lfoInc = *freqParameter / sampleRate;
    
    memset(lastFilteredSample, 0, sizeof(float) * 2);

    ffreqSmoothed.reset(sampleRate, samplesPerBlock/sampleRate);
    ffreqSmoothed.setCurrentAndTargetValue(*ffreqParameter);
    
    writePosition = 0;
    crossFadeTime = samplesPerBlock;
    waitingTime = 0;
    waitingClock = 0;
    currentDelay = 1;
    delay1Gain = 0.0f;
    delay2Gain = 1.0f;
    gain1Increment = gain2Increment = 0.0f;

    timeSmoothed.reset(sampleRate, samplesPerBlock/sampleRate);
    timeSmoothed.setCurrentAndTargetValue(*timeParameter);
    feedbackSmoothed.reset(sampleRate, samplesPerBlock/sampleRate);
    feedbackSmoothed.setCurrentAndTargetValue(*feedbackParameter);
    balanceSmoothed.reset(sampleRate, samplesPerBlock/sampleRate);
    balanceSmoothed.setCurrentAndTargetValue(*balanceParameter);

    for (int channel = 0; channel < 2; channel++) {
        delayLine[channel].setup(1.f, currentSampleRate);}
}

void FloAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FloAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void FloAudioProcessor::computeDelayTime(float delayTime) {
    if (waitingClock == 0) {
        currentDelay = (currentDelay + 1) % 2;
        waitingTime = floor(delayTime * currentSampleRate + 0.5);
        if (crossFadeTime > waitingTime) {
            crossFadeTime = waitingTime;
        }
        if (crossFadeTime <= 0) {
            crossFadeTime = 1;
        }
        if (currentDelay == 0) {
            delay1Time = delayTime;
            gain1Increment = 1.0 / crossFadeTime;
            gain2Increment = -gain1Increment;
        } else {
            delay2Time = delayTime;
            gain2Increment = 1.0 / crossFadeTime;
            gain1Increment = -gain2Increment;
        }
    }
    waitingClock += 1;
    if (waitingClock == waitingTime) {
        waitingClock = 0;
    }
}

void FloAudioProcessor::updateAmplitude() {
    delay1Gain += gain1Increment;
    delay1Gain = delay1Gain < 0.0f ? 0.0f : delay1Gain > 1.0f ? 1.0f : delay1Gain;
    delay2Gain += gain2Increment;
    delay2Gain = delay2Gain < 0.0f ? 0.0f : delay2Gain > 1.0f ? 1.0f : delay2Gain;
}

void FloAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    freqSmoothed.setTargetValue(*freqParameter);
    depthSmoothed.setTargetValue(*depthParameter);
    ffreqSmoothed.setTargetValue(*ffreqParameter);
    
    timeSmoothed.setTargetValue(*timeParameter);
    feedbackSmoothed.setTargetValue(*feedbackParameter);
    balanceSmoothed.setTargetValue(*balanceParameter);

    for (int i = 0; i < buffer.getNumSamples(); i++) {
        lfoInc = freqSmoothed.getNextValue() / currentSampleRate;
        lfoPhase += lfoInc;
        if (lfoPhase >= 1.0f) {
            lfoPhase -= 1.0f;
        }
        float lfoValue = 1.0f - (sinf(M_PI * 2.0f * lfoPhase) * 0.5 + 0.5) * depthSmoothed.getNextValue();
        
        float coefficient = expf(lfoValue * (-2.0f * M_PI * ffreqSmoothed.getNextValue() / currentSampleRate));
        
        float currentTime = (timeSmoothed.getNextValue() + lfoValue) * 0.001;
        float currentFeedback = feedbackSmoothed.getNextValue() * 0.01;
        float currentBalance = balanceSmoothed.getNextValue() * 0.01;

        computeDelayTime(currentTime);
        
        for (int channel = 0; channel < totalNumInputChannels; ++channel) {
            float sampleRead = delayLine[channel].read(delay1Time) * delay1Gain;
            sampleRead += delayLine[channel].read(delay2Time) * delay2Gain;
            
            auto* channelData = buffer.getWritePointer (channel);
            
            lastFilteredSample[channel] = channelData[i] + (lastFilteredSample[channel] - channelData[i]) * coefficient;
            channelData[i] = lastFilteredSample[channel];
            
            delayLine[channel].write(channelData[i] + sampleRead * currentFeedback);
            channelData[i] = channelData[i] + (sampleRead - channelData[i]) * currentBalance;
            
        }
        updateAmplitude();

    }
}

//==============================================================================
bool FloAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FloAudioProcessor::createEditor()
{
    return new FloAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void FloAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FloAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FloAudioProcessor();
}



