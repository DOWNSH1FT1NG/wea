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
    inputBuffer.makeCopyOf(in);
}

void AudioNode::process() {
    outputBuffer.makeCopyOf(inputBuffer); // пока просто копирует вход в выход
}

const juce::AudioBuffer<float>& AudioNode::getOutputBuffer() const {
    return outputBuffer;
}


