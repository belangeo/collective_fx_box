/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#define FREQ_INIT 440

static String lfoAttenuatorSliderValueToText(float value) {return String(value, 2);}
static float lfoAttenuatorSliderTextToValue(const String& text) {return text.getFloatValue();}
static String pwSliderValueToText(float value) {return String(value, 2);}
static float pwSliderTextToValue(const String& text) {return text.getFloatValue();}
static String pwModulationSliderValueToText(float value) {return String(value, 0);}
static float pwModulationSliderTextToValue(const String& text) {return text.getFloatValue();}
static String subVolumeSliderValueToText(float value) {return String(value, 2);}
static float subVolumeSliderTextToValue(const String& text) {return text.getFloatValue();}
static String noiseVolumeSliderValueToText(float value) {return String(value, 2);}
static float noiseVolumeSliderTextToValue(const String& text) {return text.getFloatValue();}
static String squareIsOnSliderValueToText(float value) {return String(value, 0);}
static float squareIsOnSliderTextToValue(const String& text) {return text.getFloatValue();}
static String triangleIsOnSliderValueToText(float value) {return String(value, 0);}
static float triangleIsOnSliderTextToValue(const String& text) {return text.getFloatValue();}
static String subIsOnSliderValueToText(float value) {return String(value, 0);}
static float subIsOnSliderTextToValue(const String& text) {return text.getFloatValue();}

/*  Structure des paramètres que l'on désire pouvoir automatiser/sauvegarder.
    Cette fonction est appelée à l'initialisation de l'AudioProcessor et son
    retour (un ParameterLayout) est donné directement à l'objet
    AudioProcessorValueTreeState.
*/

AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    parameters.push_back(std::make_unique<Parameter>(String("lfo_attenuator"), String("LFO Attenuator"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),    //min, max, step, skew
                                                     0.0f, lfoAttenuatorSliderValueToText, lfoAttenuatorSliderTextToValue));//default value

    parameters.push_back(std::make_unique<Parameter>(String("pw"), String("PW"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.0f, pwSliderValueToText, pwSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("pw_mod"), String("PW Modulation"), String(),
                                                     NormalisableRange<float>(0.0f, 2.0f, 1.0f),
                                                     0.0f, pwModulationSliderValueToText, pwModulationSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("sub_vol"), String("Sub Volume"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.0f, subVolumeSliderValueToText, subVolumeSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("noise_vol"), String("Noise Volume"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.0f, noiseVolumeSliderValueToText, noiseVolumeSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("square_onOff"), String("Square On/Off"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                                     0.0f, squareIsOnSliderValueToText, squareIsOnSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("triangle_onOff"), String("Triangle On/Off"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                                     0.0f, triangleIsOnSliderValueToText, triangleIsOnSliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("sub_onOff"), String("Sub On/Off"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                                     0.0f, subIsOnSliderValueToText, subIsOnSliderTextToValue));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
JunoDcopluginAudioProcessor::JunoDcopluginAudioProcessor()
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
    /*  On garde une référence directe aux valeurs brutes des paramètres afin d'avoir un accès rapide dans la méthode processBlock. */
    lfoAttenuatorParameter = parameters.getRawParameterValue("lfo_attenuator");
    pwParameter = parameters.getRawParameterValue("pw");
    pwModulationParameter = parameters.getRawParameterValue("pw_mod");    
    subVolumeParameter = parameters.getRawParameterValue("sub_vol");    
    noiseVolumeParameter = parameters.getRawParameterValue("noise_vol");
    squareIsOnParameter = parameters.getRawParameterValue("square_onOff");    
    triangleIsOnParameter = parameters.getRawParameterValue("triangle_onOff");
    subIsOnParameter = parameters.getRawParameterValue("sub_onOff");

}
JunoDcopluginAudioProcessor::~JunoDcopluginAudioProcessor()
{
}

//==============================================================================
const String JunoDcopluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JunoDcopluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JunoDcopluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JunoDcopluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JunoDcopluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JunoDcopluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JunoDcopluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JunoDcopluginAudioProcessor::setCurrentProgram (int index)
{
}

const String JunoDcopluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void JunoDcopluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JunoDcopluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    /* On initialise les structures de nos objets ici car nous devons connaître la fréquence
      d'échantillonnage. Elle n'est pas disponible à la création du plugin, seulement dans la
      fonction prepareToPlay(). */
    for (int i = 0; i < 2; i++) {
        voiceDCO[i] = junoDCO_init(FREQ_INIT, sampleRate);
    }
}

void JunoDcopluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JunoDcopluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JunoDcopluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
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
        junoDCO_set_lfoInAttenuator(voiceDCO[channel], *lfoAttenuatorParameter);
        junoDCO_set_pw(voiceDCO[channel], *pwParameter);
        junoDCO_set_pwModulation(voiceDCO[channel], *pwModulationParameter);
        junoDCO_set_subVolume(voiceDCO[channel], *subVolumeParameter);
        junoDCO_set_noiseVolume(voiceDCO[channel], *noiseVolumeParameter);
        junoDCO_set_squareIsOn(voiceDCO[channel], *squareIsOnParameter);
        junoDCO_set_triangleIsOn(voiceDCO[channel], *triangleIsOnParameter);
        junoDCO_set_subIsOn(voiceDCO[channel], *subIsOnParameter);
    
        for (int i = 0; i < getBlockSize(); i++) {
            /* On applique le traitement de signal à chacun des échantillons (i) du bloc
               pour chacun des canaux (channel). */
            channelData[i] = junoDCO_process(voiceDCO[channel], 0);
        }
    }
}

//==============================================================================
bool JunoDcopluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JunoDcopluginAudioProcessor::createEditor()
{
    return new JunoDcopluginAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void JunoDcopluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JunoDcopluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JunoDcopluginAudioProcessor();
}
