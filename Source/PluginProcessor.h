#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

//*** 6) incluir el header de nuestra class BitReduction
#include "BitReduction.h"

//==============================================================================
class BitReductionAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    BitReductionAudioProcessor();
    ~BitReductionAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //*** 7) creación de un slider de control (parameter)
    //invoco la class de JUCE AudioProcessorValueTreeState, con un string ID (nombre) "parameters;"
    juce::AudioProcessorValueTreeState parameters;
    //invoco la class ParameterLayout, con el ID (nombre arbitratio) "initializeGUI"
    juce::AudioProcessorValueTreeState::ParameterLayout initializeGUI();
private:
    //*** 13) creamos 2 pointers inteligentes llamados ptrBit
    // smart pointers reference: https://www.geeksforgeeks.org/smart-pointers-cpp/
    std::unique_ptr<BitReduction> ptrBit[2];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BitReductionAudioProcessor)
};
