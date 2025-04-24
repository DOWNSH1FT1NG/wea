/*
  ==============================================================================

    AudioNode.cpp
    Created: 24 Apr 2025 2:26:46pm
    Author:  rainlike

  ==============================================================================
*/


#include "AudioNode.h"

AudioNode::AudioNode() {}

void AudioNode::resizeIfNeeded(int numChannels, int numSamples) {
    if (inputBuffer.getNumChannels() != numChannels ||
        inputBuffer.getNumSamples() != numSamples) {
        inputBuffer.setSize(numChannels, numSamples, false, false, true);
        outputBuffer.setSize(numChannels, numSamples, false, false, true);
    }
}

void AudioNode::setInputBuffer(const juce::AudioBuffer<float>& in) {
    resizeIfNeeded(in.getNumChannels(), in.getNumSamples());
    for (int ch = 0; ch < in.getNumChannels(); ++ch)
        inputBuffer.copyFrom(ch, 0, in, ch, 0, in.getNumSamples());
}

void AudioNode::process() {
    // Простой passthrough: input -> output
    for (int ch = 0; ch < inputBuffer.getNumChannels(); ++ch)
        outputBuffer.copyFrom(ch, 0, inputBuffer, ch, 0, inputBuffer.getNumSamples());
}

const juce::AudioBuffer<float>& AudioNode::getOutputBuffer() const {
    return outputBuffer;
}


