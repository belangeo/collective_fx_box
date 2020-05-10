/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

static String delayDurationSliderValueToText(float value) {
    return String(value, 3) + String(" sec");
}

static float delayDurationSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String delayFeedbackSliderValueToText(float value) {
    return String(value, 3) + String(" feed");
}

static float delayFeedbackSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String delayWetDrySliderValueToText(float value) {
    return String(value, 3) + String(" w/d");
}

static float delayWetDrySliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String delayVolumeSliderValueToText(float value) {
    return String(value, 3) + String(" vol");
}

static float delayVolumeSliderTextToValue(const String& text) {
    return text.getFloatValue();
}


AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    parameters.push_back(std::make_unique<Parameter>(String("delayDuration"), String("delayDuration"), String(),
                                                     NormalisableRange<float>(0.0f, 2.0f),
                                                     0.5f, delayDurationSliderValueToText, delayDurationSliderTextToValue));


    parameters.push_back(std::make_unique<Parameter>(String("delayFeedback"), String("delayFeedback"), String(),
                                                     NormalisableRange<float>(0.0f, 0.99f),
                                                     0.5f, delayFeedbackSliderValueToText, delayFeedbackSliderTextToValue));


    parameters.push_back(std::make_unique<Parameter>(String("delayWetDry"), String("delayWetDry"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.5f, delayWetDrySliderValueToText, delayWetDrySliderTextToValue));


    parameters.push_back(std::make_unique<Parameter>(String("delayVolume"), String("delayVolume"), String(),
                                                     NormalisableRange<float>(0.0f, 2.0f),
                                                     1.0f, delayVolumeSliderValueToText, delayVolumeSliderTextToValue));

    return { parameters.begin(), parameters.end() };
}




MultibandDelayAudioProcessor::MultibandDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), /* <-- ça prend une virgule ici puisque paramters est le second d'une liste de deux objets à initialiser. */
#endif
    /*  Cette ligne initialise la variable parameters (un objet AudioProcessorValueTreeState)
        à la création du AudioProcessor. Notez l'appel de la fonction createParameterLayout()
        pour lui donner la configuration des paramètres.
    */
    parameters (*this, nullptr, Identifier(JucePlugin_Name), createParameterLayout())
{
    /*  On garde une référence directe aux valeurs brutes des paramètres afin d'avoir un accès rapide dans la méthode processBlock. */
  delayDurationParameter = (std::atomic<float>*) parameters.getRawParameterValue("delayDuration");
  delayFeedbackParameter = (std::atomic<float>*) parameters.getRawParameterValue("delayFeedback");
  delayWetDryParameter = (std::atomic<float>*) parameters.getRawParameterValue("delayWetDry");
  delayVolumeParameter = (std::atomic<float>*) parameters.getRawParameterValue("delayVolume");
}

MultibandDelayAudioProcessor::~MultibandDelayAudioProcessor()
{
}

//==============================================================================
const String MultibandDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MultibandDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MultibandDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MultibandDelayAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MultibandDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MultibandDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MultibandDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MultibandDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String MultibandDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void MultibandDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MultibandDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
  int maxDur = 10;
  for (int i = 0; i < 2; i++) {
    delay[i] = delay_init(maxDur, (float) sampleRate);
    bp[i] = bp_init(100, 1.5, (float) sampleRate);
  }

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MultibandDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.

  for (int i = 0; i < 2; i++) {
    delay_delete(delay[i]);
    bp_delete(bp[i]);
  }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MultibandDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MultibandDelayAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int i = 0; i < getBlockSize(); i++) {
          /* On applique le traitement de signal à chacun des échantillons (i) du bloc
             pour chacun des canaux (channel). */

          float dry_wet = *delayWetDryParameter;
          float feedback = *delayFeedbackParameter;;

          float input = channelData[i];

          float filtered_input = bp_process(bp[channel], input);

          float delayVal = delay_read(delay[channel], *delayDurationParameter);

          float output = (1.0 - dry_wet) * filtered_input + dry_wet * delayVal;

          delay_write(delay[channel], filtered_input + feedback * output);

          channelData[i] = *delayVolumeParameter * output;
        }



        // ..do something to the data...
    }
}

//==============================================================================
bool MultibandDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MultibandDelayAudioProcessor::createEditor()
{
    return new MultibandDelayAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void MultibandDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MultibandDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MultibandDelayAudioProcessor();
}
