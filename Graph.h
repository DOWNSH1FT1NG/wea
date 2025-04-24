/*
  ==============================================================================

    Graph.h
    Created: 24 Apr 2025 2:41:17pm
    Author:  rainlike

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioNode.h"

class Graph {
public:
    Graph();
    ~Graph() = default;

    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi);

private:
    AudioNode node;
};
