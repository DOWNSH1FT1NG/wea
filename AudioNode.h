/*
  ==============================================================================

    AudioNode.h
    Created: 24 Apr 2025 2:26:46pm
    Author:  rainlike

  ==============================================================================
*/



#pragma once
#include <JuceHeader.h>

class AudioNode {
public:
    AudioNode();
    void setInputBuffer(const juce::AudioBuffer<float>& in);
    void process();
    const juce::AudioBuffer<float>& getOutputBuffer() const;
    void resizeIfNeeded(int numChannels, int numSamples);

private:
    juce::AudioBuffer<float> inputBuffer;
    juce::AudioBuffer<float> outputBuffer;
};



