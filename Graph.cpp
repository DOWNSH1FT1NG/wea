/*
  ==============================================================================

    Graph.cpp
    Created: 24 Apr 2025 2:41:17pm
    Author:  rainlike

  ==============================================================================
*/

#include "Graph.h"
#include "AudioNode.h"
#include <JuceHeader.h>

Graph::Graph()
    : node(2, 512) // или любые стартовые значения
{}


void Graph::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) {
    static AudioNode node(buffer.getNumChannels(), buffer.getNumSamples());
    node.setInputBuffer(buffer);
    node.process();
    buffer.makeCopyOf(node.getOutputBuffer());
}
