#pragma once

#include "PluginProcessor.h"

#include <BinaryData.h>
//==============================================================================
class BitReductionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit BitReductionAudioProcessorEditor (BitReductionAudioProcessor&);
    ~BitReductionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    //*** 18) creo un method directamente en el constructor principal BitReductionAudioProcessorEditor 
    void createGUI();

private:
    juce::Image background;
    // 17)*** creo el slider
    juce::Slider bitSlider;
    //para conectar tanto el EDITOR como el PROCESSOR necesitamos un attachment
    // creamos un pointer + slider attachment y lo llamamos bitAttachment
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bitAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BitReductionAudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitReductionAudioProcessorEditor)
};
