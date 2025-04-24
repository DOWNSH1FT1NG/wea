/*
  ==============================================================================

    AudioNode.cpp
    Created: 24 Apr 2025 2:26:46pm
    Author:  rainlike

  ==============================================================================
*/


#include "AudioNode.h"

AudioNode::AudioNode(int numChannels, int bufferSize)
    : inputBuffer(numChannels, bufferSize),
    outputBuffer(numChannels, bufferSize)
{
    inputBuffer.clear();
    outputBuffer.clear();
}

void AudioNode::setInputBuffer(const juce::AudioBuffer<float>& in) {
    if (inputBuffer.getNumChannels() != in.getNumChannels() ||
        inputBuffer.getNumSamples() != in.getNumSamples()) {
        inputBuffer.setSize(in.getNumChannels(), in.getNumSamples(), false, false, true);
        outputBuffer.setSize(in.getNumChannels(), in.getNumSamples(), false, false, true);
    }
    inputBuffer.makeCopyOf(in);
}

void AudioNode::process() {
    for (int channel = 0; channel < inputBuffer.getNumChannels(); ++channel) {
        outputBuffer.copyFrom(channel, 0, inputBuffer, channel, 0, inputBuffer.getNumSamples());
    }
}


const juce::AudioBuffer<float>& AudioNode::getOutputBuffer() const {
    return outputBuffer;
}


