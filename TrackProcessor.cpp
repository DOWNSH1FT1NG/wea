#include "TrackProcessor.h"

TrackProcessor::TrackProcessor()
    : AudioProcessor(BusesProperties()
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)) // ❌ убрали вход
{
    clip = std::make_unique<ClipProcessor>();

}

TrackProcessor::~TrackProcessor() {}

void TrackProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    if (clip)
        clip->prepareToPlay(sampleRate, samplesPerBlock);

    // Загрузи любой локальный WAV (укажи путь)
    clip->loadFile(juce::File::getSpecialLocation(juce::File::userDesktopDirectory).getChildFile("test.wav"));
}


void TrackProcessor::releaseResources() {}

void TrackProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    if (clip)
        clip->processBlock(buffer, midi);
}


bool TrackProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
