#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
BitReductionAudioProcessorEditor::BitReductionAudioProcessorEditor (BitReductionAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 400);
    // *** 22) create GUI
    createGUI();
}

BitReductionAudioProcessorEditor::~BitReductionAudioProcessorEditor()
{
}

//==============================================================================
void BitReductionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //*** AGREGO LA IMAGEN
    background = juce::ImageCache::getFromMemory(BinaryData::pluginBackground0_png, BinaryData::pluginBackground0_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    
    g.setColour (juce::Colours::darkgoldenrod);
    g.setFont (26.0f);
    //g.drawFittedText ("VERA NOIS BIT REDUX", getLocalBounds(), juce::Justification::centredBottom, 1);
    g.drawSingleLineText("VERA NOIS", 280,30);
    //g.drawFittedText ("VERA NOIS", getLocalBounds(), juce::Justification::centredRight, 1);
    g.drawFittedText ("BIT REDUX", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void BitReductionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

//*** 19) invoco el method createGUI (punto 18)
void BitReductionAudioProcessorEditor::createGUI()
{
    //*** 20) creo las propiedades (style) del slider: rotativo / texto / posición / hacerlo visible
    bitSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    bitSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    bitSlider.setBounds(50, 45, 300, 300);
    addAndMakeVisible(bitSlider);
    
    //** 21) necesitamos sincronizarlo con el attachment (que tengan el mismo comportamiento)
    //creo un pointer<sliderAttachment>(referencia audioProcessor(dentro de private: del header PluginEditor)
    // + ID del slider al cual se hace el attachment + a que slider queremos mandar los valores
    bitAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.parameters, "BIT_ID", bitSlider);
}
