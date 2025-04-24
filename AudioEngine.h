#pragma once
#include <JuceHeader.h>

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();


    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void releaseResources();
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);

    void start();
    void stop();
    bool isPlaying() const;
    void addTrack();

private:
    bool playing = false;
    double currentSampleRate = 44100.0;
    int currentBlockSize = 512;

    juce::AudioProcessorGraph graph;
    juce::AudioProcessorPlayer player;
    juce::AudioDeviceManager deviceManager;

    juce::AudioProcessorGraph::Node::Ptr audioInputNode;
    juce::AudioProcessorGraph::Node::Ptr audioOutputNode;

    std::vector<juce::AudioProcessorGraph::Node::Ptr> trackNodes;
    int nextNodeId = 1;

    void setupGraph();
};
