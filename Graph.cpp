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


Graph::Graph() {}

void Graph::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) {
    node.setInputBuffer(buffer);
    node.process();
    const auto& output = node.getOutputBuffer();

    for (int ch = 0; ch < output.getNumChannels(); ++ch)
        buffer.copyFrom(ch, 0, output, ch, 0, output.getNumSamples());
}

