#include "MainComponent.h"
#include <juce_audio_processors/juce_audio_processors.h> // для MidiBuffer
#include <juce_audio_utils/juce_audio_utils.h>           // для setAudioChannels

MainComponent::MainComponent()
{
    setSize(800, 600);
    setAudioChannels(2, 2); // стерео вход и выход
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    engine.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    juce::MidiBuffer midi;
    engine.processBlock(*bufferToFill.buffer, midi);
}

void MainComponent::releaseResources()
{
    engine.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black); // фон (можешь изменить)
}

void MainComponent::resized()
{
    // сюда добавим расположение UI-компонентов, если будут
}
