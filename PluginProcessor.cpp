#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
EnhancedHighpassAudioProcessor::EnhancedHighpassAudioProcessor()
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    apvts(*this, nullptr, "Parameters", createParameterLayout()),
    dryWetMixer(256)
{
    auto* cutoffParam = apvts.getRawParameterValue("cutoff");
    auto* qParam = apvts.getRawParameterValue("q");
    auto* gainParam = apvts.getRawParameterValue("gain");
    auto* wetDryParam = apvts.getRawParameterValue("wetdry");

    cutoffSmoothed.reset(currentSampleRate, smoothingSeconds);
    qSmoothed.reset(currentSampleRate, smoothingSeconds);
    gainSmoothed.reset(currentSampleRate, smoothingSeconds);
    wetDrySmoothed.reset(currentSampleRate, smoothingSeconds);

    cutoffSmoothed.setCurrentAndTargetValue(*cutoffParam);
    qSmoothed.setCurrentAndTargetValue(*qParam);
    gainSmoothed.setCurrentAndTargetValue(*gainParam);
    wetDrySmoothed.setCurrentAndTargetValue(*wetDryParam);

    // Initialize dithering (inspired by Airwindows Highpass)
    while (fpdL < 16386) fpdL = rand() * UINT32_MAX;
    while (fpdR < 16386) fpdR = rand() * UINT32_MAX;
}

EnhancedHighpassAudioProcessor::~EnhancedHighpassAudioProcessor() {}

AudioProcessorValueTreeState::ParameterLayout EnhancedHighpassAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>(
        "cutoff", "Cutoff",
        NormalisableRange<float>(20.0f, 20000.0f, 0.01f, 0.3f), 200.0f)); // Default 200 Hz for highpass

    params.push_back(std::make_unique<AudioParameterFloat>(
        "q", "Resonance",
        NormalisableRange<float>(0.1f, 10.0f, 0.01f), 0.707f));

    params.push_back(std::make_unique<AudioParameterFloat>(
        "gain", "Gain",
        NormalisableRange<float>(-24.0f, 24.0f, 0.1f), 0.0f)); // dB gain

    params.push_back(std::make_unique<AudioParameterFloat>(
        "wetdry", "Dry/Wet",
        NormalisableRange<float>(0.0f, 1.0f, 0.01f), 1.0f)); // Fully wet by default

    return { params.begin(), params.end() };
}

//==============================================================================
const juce::String EnhancedHighpassAudioProcessor::getName() const { return "EnhancedHighpass"; }
bool EnhancedHighpassAudioProcessor::acceptsMidi() const { return false; }
bool EnhancedHighpassAudioProcessor::producesMidi() const { return false; }
bool EnhancedHighpassAudioProcessor::isMidiEffect() const { return false; }
double EnhancedHighpassAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int EnhancedHighpassAudioProcessor::getNumPrograms() { return 1; }
int EnhancedHighpassAudioProcessor::getCurrentProgram() { return 0; }
void EnhancedHighpassAudioProcessor::setCurrentProgram(int) {}
const juce::String EnhancedHighpassAudioProcessor::getProgramName(int) { return {}; }
void EnhancedHighpassAudioProcessor::changeProgramName(int, const juce::String&) {}

//==============================================================================
void EnhancedHighpassAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    currentSampleRate = static_cast<float>(sampleRate); // Explicit cast to avoid C4244

    dsp::ProcessSpec spec{ static_cast<double>(currentSampleRate), static_cast<uint32>(samplesPerBlock), 2 };
    filter.prepare(spec);
    filter.reset();

    dryWetMixer.prepare(spec);
    dryWetMixer.setWetMixProportion(apvts.getRawParameterValue("wetdry")->load());

    cutoffSmoothed.reset(currentSampleRate, smoothingSeconds);
    qSmoothed.reset(currentSampleRate, smoothingSeconds);
    gainSmoothed.reset(currentSampleRate, smoothingSeconds);
    wetDrySmoothed.reset(currentSampleRate, smoothingSeconds);

    auto* cutoffParam = apvts.getRawParameterValue("cutoff");
    auto* qParam = apvts.getRawParameterValue("q");
    auto* gainParam = apvts.getRawParameterValue("gain");
    auto* wetDryParam = apvts.getRawParameterValue("wetdry");

    cutoffSmoothed.setCurrentAndTargetValue(*cutoffParam);
    qSmoothed.setCurrentAndTargetValue(*qParam);
    gainSmoothed.setCurrentAndTargetValue(*gainParam);
    wetDrySmoothed.setCurrentAndTargetValue(*wetDryParam);

    // Set initial filter coefficients
    *filter.state = *dsp::IIR::Coefficients<float>::makeHighPass(static_cast<double>(currentSampleRate), *cutoffParam, *qParam);
}

void EnhancedHighpassAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EnhancedHighpassAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
}
#endif

void EnhancedHighpassAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const int numSamples = buffer.getNumSamples();

    // Get target parameter values
    const float targetCutoff = apvts.getRawParameterValue("cutoff")->load();
    const float targetQ = apvts.getRawParameterValue("q")->load();
    const float targetGain = apvts.getRawParameterValue("gain")->load();
    const float targetWetDry = apvts.getRawParameterValue("wetdry")->load();

    // Update smoothed values
    cutoffSmoothed.setTargetValue(targetCutoff);
    qSmoothed.setTargetValue(targetQ);
    gainSmoothed.setTargetValue(targetGain);
    wetDrySmoothed.setTargetValue(targetWetDry);

    // Process block
    dsp::AudioBlock<float> block(buffer);
    dryWetMixer.pushDrySamples(block); // Store dry signal

    // Update filter coefficients
    *filter.state = *dsp::IIR::Coefficients<float>::makeHighPass(static_cast<double>(currentSampleRate), cutoffSmoothed.getNextValue(), qSmoothed.getNextValue());
    filter.process(dsp::ProcessContextReplacing<float>(block));

    // Apply gain (converted from dB)
    const float gainLinear = juce::Decibels::decibelsToGain(gainSmoothed.getNextValue());
    block.multiplyBy(gainLinear);

    // Apply Airwindows-style dithering
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* data = buffer.getWritePointer(channel);
        uint32_t* fpd = (channel == 0) ? &fpdL : &fpdR;

        for (int sample = 0; sample < numSamples; ++sample)
        {
            *fpd ^= *fpd << 13;
            *fpd ^= *fpd >> 17;
            *fpd ^= *fpd << 5;
            float dither = static_cast<float>(*fpd - uint32_t(0x7fffffff)) * 5.5e-36f * pow(2, 23);
            data[sample] += dither;
        }
    }

    // Apply dry/wet mix
    dryWetMixer.setWetMixProportion(wetDrySmoothed.getCurrentValue());
    dryWetMixer.mixWetSamples(block);
}

//==============================================================================
bool EnhancedHighpassAudioProcessor::hasEditor() const { return true; }
AudioProcessorEditor* EnhancedHighpassAudioProcessor::createEditor() { return new EnhancedHighpassAudioProcessorEditor(*this); }

//==============================================================================
void EnhancedHighpassAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    if (auto xml = apvts.state.createXml())
        copyXmlToBinary(*xml, destData);
}

void EnhancedHighpassAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        apvts.state = juce::ValueTree::fromXml(*xml);
}

// Factory
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EnhancedHighpassAudioProcessor();
}