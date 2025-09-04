#include "PluginEditor.h"

GGGainAudioProcessorEditor::GGGainAudioProcessorEditor(GGGainAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(300, 220);

    auto makeRotary = [this](juce::Slider& s, juce::String suffix)
        {
            addAndMakeVisible(s);
            s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
            s.setTextValueSuffix(suffix);
        };

    makeRotary(gainSlider, " dB");
    makeRotary(ageSlider, " yrs");
    makeRotary(feelSlider, "");

    gainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "gain", gainSlider);
    ageAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "age", ageSlider);
    feelAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.apvts, "feel", feelSlider);
}

GGGainAudioProcessorEditor::~GGGainAudioProcessorEditor() = default;

void GGGainAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawFittedText("GGGain", getLocalBounds().removeFromTop(30), juce::Justification::centred, 1);
}

void GGGainAudioProcessorEditor::resized()
{
    auto b = getLocalBounds().reduced(10);
    b.removeFromTop(30);
    gainSlider.setBounds(b.removeFromLeft(100));
    ageSlider.setBounds(b.removeFromLeft(100));
    feelSlider.setBounds(b);
}