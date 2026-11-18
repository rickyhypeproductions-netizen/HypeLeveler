#include "PluginProcessor.h"
#include "PluginEditor.h"

VocalLevelerAudioProcessor::APVTS::ParameterLayout
VocalLevelerAudioProcessor::createParameterLayout()
{
    APVTS::ParameterLayout layout;
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "peakTarget", "Peak Target",
        juce::NormalisableRange<float> (-24.0f, -3.0f, 0.1f), -12.0f, "dB"));
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "levelAmount", "Leveling Amount",
        juce::NormalisableRange<float> (0.0f, 18.0f, 0.1f), 6.0f, "dB"));
    layout.add (std::make_unique<juce::AudioParameterFloat>(
        "breathReduction", "Breath Reduction",
        juce::NormalisableRange<float> (0.0f, 30.0f, 0.1f), 6.0f, "dB"));
    return layout;
}

VocalLevelerAudioProcessor::VocalLevelerAudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      parameters (*this, nullptr, "PARAMETERS", createParameterLayout())
{
}

void VocalLevelerAudioProcessor::prepareToPlay (double, int) {}
void VocalLevelerAudioProcessor::releaseResources() {}

bool VocalLevelerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    const auto& mainIn = layouts.getMainInputChannelSet();
    const auto& mainOut = layouts.getMainOutputChannelSet();
    return mainIn == mainOut &&
           (mainOut == juce::AudioChannelSet::mono() ||
            mainOut == juce::AudioChannelSet::stereo());
}

void VocalLevelerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                                juce::MidiBuffer&)
{
    // Safe pass-through foundation. Analysis and the calculated gain map will be
    // added in the next implementation stage; this prototype does not alter audio.
    juce::ScopedNoDenormals noDenormals;
    juce::ignoreUnused (buffer);
}

juce::AudioProcessorEditor* VocalLevelerAudioProcessor::createEditor()
{
    return new VocalLevelerAudioProcessorEditor (*this);
}

void VocalLevelerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VocalLevelerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary (data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName (parameters.state.getType()))
        parameters.replaceState (juce::ValueTree::fromXml (*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VocalLevelerAudioProcessor();
}
