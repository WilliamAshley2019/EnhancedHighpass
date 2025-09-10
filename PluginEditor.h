#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class EnhancedHighpassAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    EnhancedHighpassAudioProcessorEditor(EnhancedHighpassAudioProcessor&);
    ~EnhancedHighpassAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    EnhancedHighpassAudioProcessor& processorRef;

    juce::Slider cutoffSlider;
    juce::Slider qSlider;
    juce::Slider gainSlider;
    juce::Slider wetDrySlider;

    juce::Label cutoffLabel;
    juce::Label qLabel;
    juce::Label gainLabel;
    juce::Label wetDryLabel;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> cutoffAttachment;
    std::unique_ptr<Attachment> qAttachment;
    std::unique_ptr<Attachment> gainAttachment;
    std::unique_ptr<Attachment> wetDryAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EnhancedHighpassAudioProcessorEditor)
};