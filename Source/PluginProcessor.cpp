#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BitReductionAudioProcessor::BitReductionAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                        //*** 12) invoco dentro del constructor el method parameters declarado en el header
                       // *this (apuntador a ESTA class), que empiece con un pointer null (nullptr)
                       // Nombre "PARAMETERS", invoco el method initializeGUI()
                       ), parameters(*this, nullptr, "PARAMETERS", initializeGUI())
//#endif
{       //*** 14) iteración desde 0 al nro total de channels del DAW
    for (int i = 0; i < getTotalNumOutputChannels(); i++)
    {
        //*** 15) invocamos al smart pointer ptrBit declarado en el header.
        //y creo el objeto BitReduction y lo llamo en el processBlock
        ptrBit[i] = std::unique_ptr<BitReduction>(new BitReduction);
    }
}

BitReductionAudioProcessor::~BitReductionAudioProcessor()
{
}

//*** 8) desarrollo el method initializeGUI (slider)
//invoco juce::nombre de main class::nombre class secundaria (declarada en punto 7)
// luego, main class declarada en el header (BitReductionAudioProcessor)::nombre del method (initializeGUI())
// juce::AudioProcessorValueTreeState::ParameterLayout es el tipo de dato que va a retornar este método
juce::AudioProcessorValueTreeState::ParameterLayout BitReductionAudioProcessor::initializeGUI()
{
    //*** 9) creamos un vector del tipo RangedAudioParameter, lo llamamos params;
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    //*** 10)incluyo el vector anterior (punto 9) con el método de push_back
    //referencia: https://cplusplus.com/reference/vector/vector/push_back/
    //agrego los parámetros del slider insertado usando la class
    //AudioParameterInt(name ID, display name, initial value, final value)
    params.push_back(std::make_unique<juce::AudioParameterInt>("BIT_ID",
                                                               "BIT_NAME",
                                                               0,
                                                               64,
                                                               1));
    //*** 11) return del method initializeGUI desde el inicio del vector (params.begin)
    //hasta el final de nuestro vector(params.end)
    return {params.begin(),params.end()};
}
//==============================================================================
const juce::String BitReductionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BitReductionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BitReductionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BitReductionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BitReductionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BitReductionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BitReductionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BitReductionAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String BitReductionAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void BitReductionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void BitReductionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void BitReductionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool BitReductionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}

void BitReductionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        juce::ignoreUnused (channelData);
        // ..do something to the data...
                //*** 16) invoco el smart pointer ptrBit usando la variable channel ya declarada el JUCE (ver arriba)
        // e invoco el method BitRecProcess (declarado en el header BitReduction.h)
        // los parámetros son (ver header BitReduction
        // *inAudio (channelData), *outAudio (channelData), intBitReductions (valor del slider) + ID (paso 10), nsamples
        ptrBit[channel]->bitReducProcess(channelData,
                                         channelData,
                                         *parameters.getRawParameterValue("BIT_ID"),
                                         buffer.getNumSamples());
    }
}

//==============================================================================
bool BitReductionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BitReductionAudioProcessor::createEditor()
{
    return new BitReductionAudioProcessorEditor (*this);
}

//==============================================================================
void BitReductionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    juce::ignoreUnused (destData);
}

void BitReductionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BitReductionAudioProcessor();
}
