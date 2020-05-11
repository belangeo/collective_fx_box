// Fabien Lamarche-Filion

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

static String delayDryWetSliderValueToText(float value) {
    return String(value, 3) + String(" d/w");
}

static float delayDryWetSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

static String delayVolumeSliderValueToText(float value) {
    return String(value, 3) + String(" vol");
}

static float delayVolumeSliderTextToValue(const String& text) {
    return text.getFloatValue();
}

// donne le "ID" d'un parametre en fonction
// du parametre et de l'indice de tranche
// eg:
// param: "delayVolume"
// idx: 1
// output: "delayVolume1"
String makeBandParameter(String param, int band){
  return param + String(band);
}

// Donne la frequence pour chaque bande
// Tente de faire une division logarithmique
// en fonction du de la frequence maximale et
// du nombre de bandes
// La plus basse tranche sera toujours 100 Hz.
float arbitrary_freq(int idx, int nbBands){

  float base = pow(ARBITRARY_MAX_FREQ/100.0, 1/(float) NB_BANDS);

  float freq =  100 * pow(base, idx);
  return freq;
}

// Donne un Q en fonction du nombre de bande.
// TODO: le faire mieux
float arbitrary_q(int nbBands){
  float Q = (float) nbBands / 8.0;
  return Q;
}


AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    // Assignation des valeurs pour chaque tranche de potentiometres
    for (int i = 0; i < NB_BANDS; i++) {

      parameters.push_back(std::make_unique<Parameter>(makeBandParameter("delayDuration", i), String("delayDuration"), String(),
                                                     NormalisableRange<float>(0.0f, 2.0f),
                                                       1.0 * (1 - ((float) i / (float) NB_BANDS)), delayDurationSliderValueToText, delayDurationSliderTextToValue));


      parameters.push_back(std::make_unique<Parameter>(makeBandParameter("delayFeedback", i), String("delayFeedback"), String(),
                                                     NormalisableRange<float>(0.0f, 0.99f),
                                                       1.0 * ((float) i / NB_BANDS) , delayFeedbackSliderValueToText, delayFeedbackSliderTextToValue));


      parameters.push_back(std::make_unique<Parameter>(makeBandParameter("delayDryWet", i), String("delayDryWet"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.2f, delayDryWetSliderValueToText, delayDryWetSliderTextToValue));


      parameters.push_back(std::make_unique<Parameter>(makeBandParameter("delayVolume", i), String("delayVolume"), String(),
                                                     NormalisableRange<float>(0.0f, 2.0f),
                                                     1.0f, delayVolumeSliderValueToText, delayVolumeSliderTextToValue));

    }

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

  for (int i = 0; i < NB_BANDS; i++){
    band[i].delayDurationParameter = (std::atomic<float>*) parameters.getRawParameterValue(makeBandParameter("delayDuration", i));
    band[i].delayFeedbackParameter = (std::atomic<float>*) parameters.getRawParameterValue(makeBandParameter("delayFeedback", i));
    band[i].delayDryWetParameter = (std::atomic<float>*) parameters.getRawParameterValue(makeBandParameter("delayDryWet", i));
    band[i].delayVolumeParameter = (std::atomic<float>*) parameters.getRawParameterValue(makeBandParameter("delayVolume", i));
  }
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
  int maxDur = 2;
  for (int j = 0; j < NB_BANDS; j++){
    for (int i = 0; i < 2; i++) {
      band[j].delay[i] = delay_init(maxDur, (float) sampleRate);
      band[j].bp[i] = bp_init(arbitrary_freq(j, NB_BANDS), arbitrary_q(NB_BANDS), (float) sampleRate);
    }
  }

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MultibandDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
  for (int j = 0; j < NB_BANDS; j++){
    for (int i = 0; i < 2; i++) {
      delay_delete(band[j].delay[i]);
      bp_delete(band[j].bp[i]);
    }
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

          float outputs[NB_BANDS];

          for (int j = 0; j < NB_BANDS; j++){

            float dry_wet = *band[j].delayDryWetParameter;
            float feedback = *band[j].delayFeedbackParameter;;

            float input = channelData[i];

            float filtered_input = bp_process(band[j].bp[channel], input);

            float delayVal = delay_read(band[j].delay[channel], *band[j].delayDurationParameter);

            outputs[j] = (1.0 - dry_wet) * filtered_input + dry_wet * delayVal;

            delay_write(band[j].delay[channel], filtered_input + feedback * outputs[j]);
          }

          float sum = 0.0;
          for (int j = 0; j < NB_BANDS; j++){
            sum += outputs[j] * *band[j].delayVolumeParameter;
          }
          channelData[i] = sum;
        }
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
