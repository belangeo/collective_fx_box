/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static const int numberOfVoices = 6;
static const float filtConstFreq = 440.0;

//==============================================================================
JunoSynthVoice::JunoSynthVoice() {
  dco = junoDCO_init(getSampleRate());
  vcf = moog_init(0, 0, getSampleRate());
  envelope.setSampleRate(getSampleRate());
}

bool JunoSynthVoice::canPlaySound(SynthesiserSound *sound) {
  return dynamic_cast<JunoSynthSound *> (sound) != nullptr;
}

void JunoSynthVoice::startNote(int midiNoteNumber, float velocity,
                              SynthesiserSound *, int /*currentPitchWheelPosition*/) {
	envelope.noteOn();
	noteValue = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
	junoDCO_set_freq(dco, noteValue);
}

void JunoSynthVoice::stopNote(float /*velocity*/, bool allowTailOff) {
  	envelope.noteOff();
}

void JunoSynthVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) {
	while (--numSamples >= 0) {

		auto envAmp = envelope.getNextSample();
		float lfoIn = 0;
		float filtFreq = filtFreqMult * (filtConstFreq - (filtConstFreq - noteValue) * filtKybdMult) * (envAmp * filtEnvMult + 1);

		float voiceDCO = junoDCO_process(dco, lfoIn, envAmp);
		moog_set_freq(vcf, filtFreq);
		float currentSample = moog_process(vcf, voiceDCO) * envAmp;

		for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
		  outputBuffer.addSample(i, startSample, currentSample);

		++startSample;

		if (envAmp <= 0.0) {
		  clearCurrentNote();
		  break;
		}
  }
}
//==============================================================================
void JunoSynthVoice::setLfoValue (float lfoIn) {
    lfoValue = lfoIn;
}

void JunoSynthVoice::setLfoAttenuatorParameter(float lfoAttenuator) {
    junoDCO_set_lfoInAttenuator(dco, lfoAttenuator);
}

void JunoSynthVoice::setPwParameter(float pw) {
    junoDCO_set_pw(dco, pw);
}

void JunoSynthVoice::setPwModulationParameter(float pwMod) {
    junoDCO_set_pwModulation(dco, (int)pwMod);
}

void JunoSynthVoice::setSubVolumeParameter(float subVol) {
    junoDCO_set_subVolume(dco, subVol);
}

void JunoSynthVoice::setNoiseVolumeParameter(float noiseVol) {
    junoDCO_set_noiseVolume(dco, noiseVol);
}

void JunoSynthVoice::setSquareIsOnParameter(float squareIsOn) {
    junoDCO_set_squareIsOn(dco, squareIsOn);
}

void JunoSynthVoice::setTriangleIsOnParameter(float triangleIsOn) {
    junoDCO_set_triangleIsOn(dco, triangleIsOn);
}

void JunoSynthVoice::setSubIsOnParameter(float subIsOn) {
    junoDCO_set_subIsOn(dco, subIsOn);
}

void JunoSynthVoice::setFiltFreqMultParameter(float filtFreq) {
	filtFreqMult = filtFreq * 100;
}

void JunoSynthVoice::setFiltResParameter(float filtRes) {
	moog_set_res(vcf, filtRes * 2);
}

void JunoSynthVoice::setFiltEnvMultParameter(float filtEnv) {
	filtEnvMult = filtEnv * 100;
}

void JunoSynthVoice::setFiltKybdParameter(float filtKybd) {
	filtKybdMult = filtKybd;
}

void JunoSynthVoice::setEnvelopeParameters(ADSR::Parameters params) {
    envelope.setParameters(params);
}

//==============================================================================
bool JunoSynth::isAllNotesOff() {
	bool isKeyDown; 
	bool isAllNotesOff = true;
    for (int i = 0; i < getNumVoices(); i++) {
       isKeyDown = dynamic_cast<JunoSynthVoice *> (getVoice(i))->isKeyDown();
       if (isKeyDown == true) {isAllNotesOff = false;}
    }
	return isAllNotesOff;
}

void JunoSynth::setLfoValue (float lfoIn) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setLfoValue(lfoIn);
    }
}

void JunoSynth::setLfoAttenuatorParameter(float lfoAttenuator) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setLfoAttenuatorParameter(lfoAttenuator);
    }
}

void JunoSynth::setPwParameter(float pw) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setPwParameter(pw);
    }
}

void JunoSynth::setPwModulationParameter(float pwMod) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setPwModulationParameter(pwMod);
    }
}

void JunoSynth::setSubVolumeParameter(float subVol) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setSubVolumeParameter(subVol);
    }
}

void JunoSynth::setNoiseVolumeParameter(float noiseVol) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setNoiseVolumeParameter(noiseVol);
    }
}

void JunoSynth::setSquareIsOnParameter(float squareIsOn) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setSquareIsOnParameter(squareIsOn);
    }
}

void JunoSynth::setTriangleIsOnParameter(float triangleIsOn) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setTriangleIsOnParameter(triangleIsOn);
    }
}

void JunoSynth::setSubIsOnParameter(float subIsOn) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setSubIsOnParameter(subIsOn);
    }
}

void JunoSynth::setFiltFreqMultParameter(float filtFreq) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setFiltFreqMultParameter(filtFreq);
    }	
}

void JunoSynth::setFiltResParameter(float filtRes) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setFiltResParameter(filtRes);
    }	
}

void JunoSynth::setFiltEnvMultParameter(float filtEnv) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setFiltEnvMultParameter(filtEnv);
    }	
}

void JunoSynth::setFiltKybdParameter(float filtKybd) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setFiltKybdParameter(filtKybd);
    }	
}

void JunoSynth::setEnvelopeParameters(ADSR::Parameters params) {
    for (int i = 0; i < getNumVoices(); i++) {
       dynamic_cast<JunoSynthVoice *> (getVoice(i))->setEnvelopeParameters(params);
    }
}

//==============================================================================
static String gainSliderValueToText(float value) {
    float val = 20.0f * log10f(jmax(0.001f, value));
    return String(val, 2) + String(" dB");
}

static float gainSliderTextToValue(const String& text) {
    float val = jlimit(-60.0f, 18.0f, text.getFloatValue());
    return powf(10.0f, val * 0.05f);
}
static String sliderValueToText(float value) {return String(value, 2);}
static float sliderTextToValue(const String& text) {return text.getFloatValue();}
static String toggleValueToText(float value) {return String(value, 0);}
static float toggleTextToValue(const String& text) {return text.getFloatValue();}

AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    using Parameter = AudioProcessorValueTreeState::Parameter;

    std::vector<std::unique_ptr<Parameter>> parameters;

    parameters.push_back(std::make_unique<Parameter>(String("volume"), String("Volume"), String(),    		//min, max, step, skew
                                                     NormalisableRange<float>(0.001f, 7.94f, 0.001f, 0.3f),
                                                     0.5f, gainSliderValueToText, gainSliderTextToValue));	//default value

    parameters.push_back(std::make_unique<Parameter>(String("lfo_rate"), String("LFO Rate"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.0f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("lfo_delay"), String("LFO Delay"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.0f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("lfo_attenuator"), String("LFO Attenuator"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.0f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("pw"), String("PW"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     0.5f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("pw_mod"), String("PW Modulation"), String(),
                                                     NormalisableRange<float>(0.0f, 2.0f, 1.0f),
                                                     2.0f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("sub_vol"), String("Sub Volume"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     1.0f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("noise_vol"), String("Noise Volume"), String(),
                                                     NormalisableRange<float>(0.001f, 1.0f),
                                                     0.001f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("square_onOff"), String("Square On/Off"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                                     1.0f, toggleValueToText, toggleTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("triangle_onOff"), String("Triangle On/Off"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                                     1.0f, toggleValueToText, toggleTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("sub_onOff"), String("Sub On/Off"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 1.0f),
                                                     1.0f, toggleValueToText, toggleTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("filt_freq_mult"), String("Filter Freq Multiplier"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 0.0001f, 0.3f),
                                                     0.01f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("filt_res"), String("Filter Res"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 0.0001f, 0.5f),
                                                     0.3f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("filt_env_mult"), String("Filter Env Multiplier"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f, 0.0001f, 0.3f),
                                                     0.4f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("filt_kybd"), String("Filter Kybd"), String(),
                                                     NormalisableRange<float>(0.0f, 1.0f),
                                                     1.0f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("attack"), String("Attack"), String(),
                                                     NormalisableRange<float>(0.001f, 1.0f, 0.0001f, 0.3f),
                                                     0.005f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("decay"), String("Decay"), String(),
                                                     NormalisableRange<float>(0.001f, 1.0f, 0.0001f, 0.3f),
                                                     0.1f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("sustain"), String("Sustain"), String(),
                                                     NormalisableRange<float>(0.001f, 1.0f, 0.001f),
                                                     0.33f, sliderValueToText, sliderTextToValue));

    parameters.push_back(std::make_unique<Parameter>(String("release"), String("Release"), String(),
                                                     NormalisableRange<float>(0.001f, 1.0f, 0.0001f, 0.3f),
                                                     0.01f, sliderValueToText, sliderTextToValue));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
JunoSynthAudioProcessor::JunoSynthAudioProcessor()
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
    for (auto i = 0; i < numberOfVoices; ++i)
        synthesiser.addVoice(new JunoSynthVoice());

    synthesiser.addSound(new JunoSynthSound());

    volumeParameter = parameters.getRawParameterValue("volume");

    lfoRateParameter = parameters.getRawParameterValue("lfo_rate");
    lfoDelayParameter = parameters.getRawParameterValue("lfo_delay");

    lfoAttenuatorParameter = parameters.getRawParameterValue("lfo_attenuator");
    pwParameter = parameters.getRawParameterValue("pw");
    pwModulationParameter = parameters.getRawParameterValue("pw_mod");    
    subVolumeParameter = parameters.getRawParameterValue("sub_vol");    
    noiseVolumeParameter = parameters.getRawParameterValue("noise_vol");
    squareIsOnParameter = parameters.getRawParameterValue("square_onOff");    
    triangleIsOnParameter = parameters.getRawParameterValue("triangle_onOff");
    subIsOnParameter = parameters.getRawParameterValue("sub_onOff");

    filtFreqMultParameter = parameters.getRawParameterValue("filt_freq_mult");
    filtResParameter = parameters.getRawParameterValue("filt_res");
    filtEnvMultParameter = parameters.getRawParameterValue("filt_env_mult");
    filtKybdParameter = parameters.getRawParameterValue("filt_kybd");

    attackParameter = parameters.getRawParameterValue("attack");
    decayParameter = parameters.getRawParameterValue("decay");
    sustainParameter = parameters.getRawParameterValue("sustain");
    releaseParameter = parameters.getRawParameterValue("release");
}

JunoSynthAudioProcessor::~JunoSynthAudioProcessor()
{
}

//==============================================================================
const String JunoSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JunoSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JunoSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JunoSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JunoSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JunoSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JunoSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JunoSynthAudioProcessor::setCurrentProgram (int index)
{
}

const String JunoSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void JunoSynthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JunoSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    keyboardState.reset();
    lfo = junoLFO_init(sampleRate);
    synthesiser.setCurrentPlaybackSampleRate(sampleRate);
}

void JunoSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JunoSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JunoSynthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    synthesiser.setLfoAttenuatorParameter(*lfoAttenuatorParameter);
    synthesiser.setPwParameter(*pwParameter);
    synthesiser.setPwModulationParameter(*pwModulationParameter);
    synthesiser.setSubVolumeParameter(*subVolumeParameter);
    synthesiser.setNoiseVolumeParameter(*noiseVolumeParameter);
    synthesiser.setSquareIsOnParameter(*squareIsOnParameter);
    synthesiser.setTriangleIsOnParameter(*triangleIsOnParameter);
    synthesiser.setSubIsOnParameter(*subIsOnParameter);
    synthesiser.setFiltFreqMultParameter(*filtFreqMultParameter);    
    synthesiser.setFiltResParameter(*filtResParameter);    
    synthesiser.setFiltEnvMultParameter(*filtEnvMultParameter);        
    synthesiser.setFiltKybdParameter(*filtKybdParameter);    
    synthesiser.setEnvelopeParameters(ADSR::Parameters{	static_cast<float>(*attackParameter * 3.3), 
    													static_cast<float>(*decayParameter * 21.0), 
    													static_cast<float>(*sustainParameter), 
    													static_cast<float>(*releaseParameter * 21.0)});
 
    synthesiser.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    buffer.applyGainRamp(0, buffer.getNumSamples(), lastVolume, *volumeParameter);
    lastVolume = *volumeParameter;

/*
    if (synthesiser.isAllNotesOff()) {
		junoLFO_reset_ramp(lfo);
	}

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
 
    junoLFO_set_freq(lfo, *lfoRateParameter * 20);
    junoLFO_set_rampLength(lfo, *lfoDelayParameter * 2);


    for (int i = 0; i < getBlockSize(); i++) {
        // On applique le traitement de signal à chacun des échantillons (i) du bloc
        // pour chacun des canaux (channel).

		if (!synthesiser.isAllNotesOff()) {
			junoLFO_process_ramp(lfo);
		} else {
			junoLFO_reset_ramp(lfo);
		}
	 
    	synthesiser.setLfoValue(junoLFO_process(lfo));
    }
*/
}

//==============================================================================
bool JunoSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JunoSynthAudioProcessor::createEditor()
{
    return new JunoSynthAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void JunoSynthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JunoSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JunoSynthAudioProcessor();
}
