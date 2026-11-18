#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class VocalLevelerAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit VocalLevelerAudioProcessorEditor (VocalLevelerAudioProcessor&);
    ~VocalLevelerAudioProcessorEditor() override = default;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    VocalLevelerAudioProcessor& audioProcessor;
    juce::Label title;
    juce::Label status;
    juce::Slider peakTarget;
    juce::Slider levelAmount;
    juce::Slider breathReduction;
    juce::Label peakLabel, levelLabel, breathLabel;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> peakAttachment, levelAttachment, breathAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VocalLevelerAudioProcessorEditor)
};
