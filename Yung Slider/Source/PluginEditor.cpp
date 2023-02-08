/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
YungSliderAudioProcessorEditor::YungSliderAudioProcessorEditor (YungSliderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (100, 100);
    auto& params = processor.getParameters();
    
    // Setting up gain slider
    juce::AudioParameterFloat* gainParameter = (juce::AudioParameterFloat*) params.getUnchecked(0);

    mGainControlSlider.setBounds(0, 0, 100 , 100);
    mGainControlSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mGainControlSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    mGainControlSlider.setRange(gainParameter->range.start, gainParameter->range.end);
    mGainControlSlider.setValue(*gainParameter);
    mGainControlSlider.onValueChange = [this, gainParameter] {
        *gainParameter = mGainControlSlider.getValue();
    };
    mGainControlSlider.onDragStart = [gainParameter] {
        gainParameter->beginChangeGesture();
    };
    mGainControlSlider.onDragEnd = [gainParameter] {
        gainParameter->endChangeGesture();
    };
    addAndMakeVisible(mGainControlSlider);
}

YungSliderAudioProcessorEditor::~YungSliderAudioProcessorEditor()
{
}

//==============================================================================
void YungSliderAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void YungSliderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
