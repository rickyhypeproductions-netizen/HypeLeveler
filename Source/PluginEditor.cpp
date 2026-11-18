#include "PluginEditor.h"

VocalLevelerAudioProcessorEditor::VocalLevelerAudioProcessorEditor
    (VocalLevelerAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (520, 300);
    title.setText ("VOCAL LEVELER", juce::dontSendNotification);
    title.setJustificationType (juce::Justification::centred);
    title.setFont (juce::Font (22.0f, juce::Font::bold));
    addAndMakeVisible (title);

    status.setText ("Prototype foundation — analysis engine not yet implemented",
                    juce::dontSendNotification);
    status.setJustificationType (juce::Justification::centred);
    status.setFont (juce::Font (12.0f));
    addAndMakeVisible (status);

    auto setupSlider = [this] (juce::Slider& s)
    {
        s.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
        s.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 76, 22);
        addAndMakeVisible (s);
    };
    setupSlider (peakTarget);
    setupSlider (levelAmount);
    setupSlider (breathReduction);

    peakLabel.setText ("PEAK TARGET", juce::dontSendNotification);
    levelLabel.setText ("LEVELING AMOUNT", juce::dontSendNotification);
    breathLabel.setText ("BREATH REDUCTION", juce::dontSendNotification);
    for (auto* label : { &peakLabel, &levelLabel, &breathLabel })
    {
        label->setJustificationType (juce::Justification::centred);
        addAndMakeVisible (*label);
    }

    auto& state = audioProcessor.parameters;
    peakAttachment = std::make_unique<SliderAttachment> (state, "peakTarget", peakTarget);
    levelAttachment = std::make_unique<SliderAttachment> (state, "levelAmount", levelAmount);
    breathAttachment = std::make_unique<SliderAttachment> (state, "breathReduction", breathReduction);
}

void VocalLevelerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colour (0xff17191d));
    g.setColour (juce::Colour (0xff343941));
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (8.0f), 10.0f, 1.0f);
}

void VocalLevelerAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (18);
    title.setBounds (area.removeFromTop (38));
    status.setBounds (area.removeFromTop (28));
    area.removeFromTop (12);
    auto colW = area.getWidth() / 3;
    auto place = [&] (juce::Label& label, juce::Slider& slider, int x)
    {
        label.setBounds (x, area.getY(), colW, 28);
        slider.setBounds (x + 4, area.getY() + 28, colW - 8, 170);
    };
    place (peakLabel, peakTarget, area.getX());
    place (levelLabel, levelAmount, area.getX() + colW);
    place (breathLabel, breathReduction, area.getX() + 2 * colW);
}
