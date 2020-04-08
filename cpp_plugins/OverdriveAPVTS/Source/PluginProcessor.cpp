/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static String driveSliderValueToText(float value) {
    return String(value, 3) + String(" drv");
}

static float driveSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String cutoffSliderValueToText(float value) {
    return String(value, 2) + String(" Hz");
}

static float cutoffSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String resSliderValueToText(float value) {
    return String(value, 3) + String(" res");
}

static float resSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

/*  Structure des paramètres que l'on désire pouvoir automatiser/sauvegarder.
    Cette fonction est appelée à l'initialisation de l'AudioProcessor et son
    retour (un ParameterLayout) est donné directement à l'objet
    AudioProcessorValueTreeState.
*/
AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    parameters.push_back(std::make_unique<Parameter>(String("drive"), String("Drive"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.5f, driveSliderValueToText, driveSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("cutoff"), String("Cutoff"), String(),
                                                     NormalisableRange<float>(50.0f, 15000.0f, 0.01f, 0.25f),
                                                     1000.0f, cutoffSliderValueToText, cutoffSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("res"), String("Res"), String(),
                                                     NormalisableRange<float>(0.0f, 2.0f),
                                                     0.5f, resSliderValueToText, resSliderTextToValue));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
OverdriveApvtsAudioProcessor::OverdriveApvtsAudioProcessor()
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
    driveParameter = parameters.getRawParameterValue("drive");
    cutoffParameter = parameters.getRawParameterValue("cutoff");    
    resParameter = parameters.getRawParameterValue("res");    
}

OverdriveApvtsAudioProcessor::~OverdriveApvtsAudioProcessor()
{
}

//==============================================================================
const String OverdriveApvtsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OverdriveApvtsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OverdriveApvtsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OverdriveApvtsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OverdriveApvtsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OverdriveApvtsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OverdriveApvtsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OverdriveApvtsAudioProcessor::setCurrentProgram (int index)
{
}

const String OverdriveApvtsAudioProcessor::getProgramName (int index)
{
    return {};
}

void OverdriveApvtsAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OverdriveApvtsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    /*  On garde la fréquence d'échantillonnage courante en mémoire. */
    currentSampleRate = sampleRate;

    /* On initialise les structures de nos objets ici car nous devons connaître la fréquence
      d'échantillonnage. Elle n'est pas disponible à la création du plugin, seulement dans la
      fonction prepareToPlay(). */
    for (int i = 0; i < 2; i++) {
        disto[i] = waveshaper_init(*driveParameter, 15000, sampleRate, 1, 100);
        lpres[i] = moog_init(*cutoffParameter, *resParameter, sampleRate);
    }
}

void OverdriveApvtsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OverdriveApvtsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void OverdriveApvtsAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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

        /* Avant le calcul de chacun des blocs d'échantillons, on ajuste le drive
           de la distorsion ainsi que la fréquence et la résonance du filtre. */
        waveshaper_set_drive(disto[channel], *driveParameter);
        moog_set_freq(lpres[channel], *cutoffParameter);
        moog_set_res(lpres[channel], *resParameter);
    
        for (int i = 0; i < getBlockSize(); i++) {
            /* On applique le traitement de signal à chacun des échantillons (i) du bloc
               pour chacun des canaux (channel). */
            channelData[i] = waveshaper_process(disto[channel], channelData[i]);
            channelData[i] = moog_process(lpres[channel], channelData[i]);
        }
    }
}

//==============================================================================
bool OverdriveApvtsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OverdriveApvtsAudioProcessor::createEditor()
{
    return new OverdriveApvtsAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void OverdriveApvtsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OverdriveApvtsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OverdriveApvtsAudioProcessor();
}
