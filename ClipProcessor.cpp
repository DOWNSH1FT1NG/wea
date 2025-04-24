#include "ClipProcessor.h"

ClipProcessor::ClipProcessor()
{
    formatManager.registerBasicFormats();
    backgroundThread.startThread();
}

ClipProcessor::~ClipProcessor()
{
    releaseResources();
}

void ClipProcessor::prepareToPlay(double sampleRate, int samplesPerBlockExpected)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void ClipProcessor::releaseResources()
{
    transportSource.releaseResources();
}

void ClipProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    tempBuffer.setSize(buffer.getNumChannels(), buffer.getNumSamples(), false, false, true);
    tempBuffer.clear();

    juce::AudioSourceChannelInfo info(&tempBuffer, 0, buffer.getNumSamples());
    transportSource.getNextAudioBlock(info);

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        buffer.addFrom(ch, 0, tempBuffer, ch, 0, buffer.getNumSamples());
    }
}


bool ClipProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void ClipProcessor::loadFile(const juce::File& file)
{
    auto* reader = formatManager.createReaderFor(file);
    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, &backgroundThread, reader->sampleRate);
        readerSource.reset(newSource.release());

        transportSource.setPosition(0.0);
        transportSource.start(); // начать воспроизведение при загрузке
    }
}
