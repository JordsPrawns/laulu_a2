/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Laulu_a2AudioProcessor::Laulu_a2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    currentSampleRate = 0.0f;
    currentAngle = 0.0f;
    angleDelta = 0.0f;
    sinFreq = 60.0f;
}

Laulu_a2AudioProcessor::~Laulu_a2AudioProcessor()
{
}

//==============================================================================
const String Laulu_a2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Laulu_a2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Laulu_a2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Laulu_a2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Laulu_a2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Laulu_a2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Laulu_a2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Laulu_a2AudioProcessor::setCurrentProgram (int index)
{
}

const String Laulu_a2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Laulu_a2AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Laulu_a2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    currentSampleRate = sampleRate;
    sinFreq = 60.0f;
    updateAngleDelta();
}

void Laulu_a2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Laulu_a2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Laulu_a2AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (auto i= totalNumInputChannels; i < totalNumInputChannels; i++)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    AudioBuffer<float> wetBuffer(totalNumInputChannels, buffer.getNumSamples());
    wetBuffer.makeCopyOf(buffer);

    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        auto* wetData = wetBuffer.getWritePointer(channel);

        for (int sample = 0; sample < 512; ++sample)
        {
            // generating a set of random values to modulate input amplitude
            // float modulator = random.nextFloat() * 0.25f - 0.125f;
           // wetData[sample[ = wetData[sample] * modulator;
            
            auto currentSinSample = (float) std::sin(currentAngle);
            currentAngle += angleDelta; //currentAngle = currentAngle + angleDelta
           //  wetData[sample] = wetData[sample] * currentSinSample;
            
            //float modulator = random.nextFloat() * 0.25f - 0.125f;
          //  wetData[sample] = wetData[sample] * modulator;
           // wetData[sample] = wetData[sample] * (currentSinSample + modulator);
            wetData[sample] = wetData[sample] * currentSinSample;
            //auto shapedSample = (32767 >> 1) * (float) std::atan (16 * wetData[sample]/32767);
            
            //per sample
            float quantum = powf( 1.0f, 8);
            
            auto shapedSample = floor(wetData[sample] * quantum ) / quantum;
            wetData[sample] = shapedSample;
            
            channelData[sample] = channelData[sample] * 0.4f + wetData[sample] * 0.6f;
        }
        // ..do something to the data...
    }
}

//==============================================================================
bool Laulu_a2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Laulu_a2AudioProcessor::createEditor()
{
    return new Laulu_a2AudioProcessorEditor (*this);
}

//==============================================================================
void Laulu_a2AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Laulu_a2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
//user functions
void Laulu_a2AudioProcessor::updateAngleDelta()
{
    //calculate no. of cycles that we will need to complete for each output sample
    auto cyclesPerSample = sinFreq / currentSampleRate;
    // multiply by the length of a whole sine wave cylce
    angleDelta = cyclesPerSample * 2.0f * MathConstants<float>::twoPi;
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Laulu_a2AudioProcessor();
}
