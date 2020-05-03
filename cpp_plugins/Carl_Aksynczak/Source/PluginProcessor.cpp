/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

// Ajouter la configuration des parametres ici


// Controle pour le lowShelf
static String freqLsSliderValueToText(float value) {
    return String(value, 2) + String(" Hz");
}

static float freqLsSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String qLsSliderValueToText(float value) {
    return String(value, 2) + String(" q");
}

static float qLsSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String gainLsSliderValueToText(float value) {
    return String(value, 2) + String(" gain");
}

static float gainLsSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

// Controle Notch 1
static String freqN1SliderValueToText(float value) {
    return String(value, 2) + String(" Hz");
}

static float freqN1SliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String qN1SliderValueToText(float value) {
    return String(value, 2) + String(" q");
}

static float qN1SliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String gainN1SliderValueToText(float value) {
    return String(value, 2) + String(" gain");
}

static float gainN1SliderTextToValue(const String& text) {
    return text.getFloatValue();
}

// Controle Notch 2
static String freqN2SliderValueToText(float value) {
    return String(value, 2) + String(" Hz");
}

static float freqN2SliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String qN2SliderValueToText(float value) {
    return String(value, 2) + String(" q");
}

static float qN2SliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String gainN2SliderValueToText(float value) {
    return String(value, 2) + String(" gain");
}

static float gainN2SliderTextToValue(const String& text) {
    return text.getFloatValue();
}

// Controle pour le highShelf
static String freqHsSliderValueToText(float value) {
    return String(value, 2) + String(" Hz");
}

static float freqHsSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String qHsSliderValueToText(float value) {
    return String(value, 2) + String(" q");
}

static float qHsSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String gainHsSliderValueToText(float value) {
    return String(value, 2) + String(" gain");
}

static float gainHsSliderTextToValue(const String& text) {
    return text.getFloatValue();
}


AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    
    parameters.push_back(std::make_unique<Parameter>(String("freqLS"), String("Freq LowShelf"), String("Freq LowShelf"),
                                                            NormalisableRange<float>(0.0f, 400.0f), 60.0f,
                                                            freqLsSliderValueToText, freqLsSliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("qLS"), String("Q LowShelf"), String("Q LowShelf"),
                                                            NormalisableRange<float>(0.0f, 10.0f), 1.0f,
                                                            qLsSliderValueToText, qLsSliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("gainLS"), String("Gain LowShelf"), String("Gain LowShelf"),
                                                            NormalisableRange<float>(0.0f, 5.0f), 1.0f,
                                                            gainLsSliderValueToText, gainLsSliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("freqN1"), String("Freq Notch 1"), String("Freq Notch 1"),
                                                            NormalisableRange<float>(350.0f, 5000.0f), 400.0f,
                                                            freqN1SliderValueToText, freqN1SliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("qN1"), String("Q Notch 1"), String("Q Notch 1"),
                                                            NormalisableRange<float>(0.0f, 10.0f), 1.0f,
                                                            qN1SliderValueToText, qN1SliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("gainN1"), String("Gain Notch 1"), String("Gain Notch 1"),
                                                            NormalisableRange<float>(0.0f, 5.0f), 1.0f,
                                                            gainN1SliderValueToText, gainN1SliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("freqN2"), String("Freq Notch 2"), String("Freq Notch 2"),
                                                            NormalisableRange<float>(4000.0f, 12000.0f), 5000.0f,
                                                            freqN2SliderValueToText, freqN2SliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("qN2"), String("Q Notch 2"), String("Q Notch 2"),
                                                            NormalisableRange<float>(0.0f, 10.0f), 1.0f,
                                                            qN2SliderValueToText, qN2SliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("gainN2"), String("Gain Notch 2"), String("Gain Notch 2"),
                                                            NormalisableRange<float>(0.0f, 5.0f), 1.0f,
                                                            gainN2SliderValueToText, gainN2SliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("freqHS"), String("Freq HighShelf"), String("Freq HighShelf"),
                                                            NormalisableRange<float>(11000.0f, 20000.0f), 15000.0f,
                                                            freqHsSliderValueToText, freqHsSliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("qHS"), String("Q HighShelf"), String("Q HighShelf"),
                                                            NormalisableRange<float>(0.0f, 10.0f), 1.0f,
                                                            qHsSliderValueToText, qHsSliderTextToValue
                                                            ));
    parameters.push_back(std::make_unique<Parameter>(String("gainHS"), String("Gain HighShelf"), String("Gain HighShelf"),
                                                            NormalisableRange<float>(0.0f, 5.0f), 1.0f,
                                                            gainHsSliderValueToText, gainHsSliderTextToValue
                                                            ));
    

    return { parameters.begin(), parameters.end() };
}


//==============================================================================
PluginCarlAksyAudioProcessor::PluginCarlAksyAudioProcessor()
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
    freqLsParameter = parameters.getRawParameterValue("freqLS");
    qLsParameter = parameters.getRawParameterValue("qLS");
    gainLsParameter = parameters.getRawParameterValue("gainLS");
    freqN1Parameter = parameters.getRawParameterValue("freqN1");
    qN1Parameter = parameters.getRawParameterValue("qN1");
    gainN1Parameter = parameters.getRawParameterValue("gainN1");
    freqN2Parameter = parameters.getRawParameterValue("freqN2");
    qN2Parameter = parameters.getRawParameterValue("qN2");
    gainN2Parameter = parameters.getRawParameterValue("gainN2");
    freqHsParameter = parameters.getRawParameterValue("freqHS");
    qHsParameter = parameters.getRawParameterValue("qHS");
    gainHsParameter = parameters.getRawParameterValue("gainHS");
}

PluginCarlAksyAudioProcessor::~PluginCarlAksyAudioProcessor()
{
}

//==============================================================================
const String PluginCarlAksyAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginCarlAksyAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginCarlAksyAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginCarlAksyAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginCarlAksyAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginCarlAksyAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PluginCarlAksyAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PluginCarlAksyAudioProcessor::setCurrentProgram (int index)
{
}

const String PluginCarlAksyAudioProcessor::getProgramName (int index)
{
    return {};
}

void PluginCarlAksyAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void PluginCarlAksyAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void PluginCarlAksyAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginCarlAksyAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void PluginCarlAksyAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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

        // ..do something to the data...
    }
}

//==============================================================================
bool PluginCarlAksyAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PluginCarlAksyAudioProcessor::createEditor()
{
    return new PluginCarlAksyAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void PluginCarlAksyAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PluginCarlAksyAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PluginCarlAksyAudioProcessor();
}
