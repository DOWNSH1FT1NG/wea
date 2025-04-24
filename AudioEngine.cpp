#include "AudioEngine.h"
#include "TrackProcessor.h"
#include <memory>


AudioEngine::AudioEngine()
{
    setupGraph();
    player.setProcessor(&graph);
    deviceManager.addAudioCallback(&player);
}

AudioEngine::~AudioEngine()
{
    player.setProcessor(nullptr);
    deviceManager.removeAudioCallback(&player);
    graph.releaseResources();
}


void AudioEngine::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player.setProcessor(&graph);

    deviceManager.initialise(2, 2, nullptr, true);
    deviceManager.addAudioCallback(&player);

    graph.clear(); // всегда очищаем граф перед новой настройкой

    // Вход и выход
    //audioInputNode = graph.addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(
    //    juce::AudioProcessorGraph::AudioGraphIOProcessor::audioInputNode));
    audioOutputNode = graph.addNode(std::make_unique<juce::AudioProcessorGraph::AudioGraphIOProcessor>(
        juce::AudioProcessorGraph::AudioGraphIOProcessor::audioOutputNode));

    addTrack();

    // 🛠️ ВОТ ЭТА СТРОКА ОБЯЗАТЕЛЬНА
    graph.prepareToPlay(sampleRate, samplesPerBlockExpected);
}




void AudioEngine::releaseResources()
{
    graph.releaseResources();
}

void AudioEngine::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    graph.processBlock(buffer, midiMessages);
}

void AudioEngine::setupGraph()
{
    // пока граф пустой — позже добавим ноды треков
}

void AudioEngine::addTrack()
{
    auto trackProcessor = std::make_unique<TrackProcessor>();
    auto* rawTrackProcessor = trackProcessor.get();

    auto trackNode = graph.addNode(std::move(trackProcessor));

    trackNodes.push_back(trackNode);

    // Вход → Трек
   // graph.addConnection({ { audioInputNode->nodeID, 0 }, { trackNode->nodeID, 0 } });
   // graph.addConnection({ { audioInputNode->nodeID, 1 }, { trackNode->nodeID, 1 } });

    // Трек → Выход
   graph.addConnection({ { trackNode->nodeID, 0 }, { audioOutputNode->nodeID, 0 } });
   graph.addConnection({ { trackNode->nodeID, 1 }, { audioOutputNode->nodeID, 1 } });
}



void AudioEngine::start() { playing = true; }
void AudioEngine::stop() { playing = false; }
bool AudioEngine::isPlaying() const { return playing; }
