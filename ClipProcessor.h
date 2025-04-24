#pragma once
#include <JuceHeader.h>

class ClipProcessor : public juce::AudioProcessor
{
public:
    ClipProcessor();
    ~ClipProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    const juce::String getName() const override { return "ClipProcessor"; }

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    juce::AudioProcessorEditor* createEditor() override { return nullptr; }
    bool hasEditor() const override { return false; }

    double getTailLengthSeconds() const override { return 0.0; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock&) override {}
    void setStateInformation(const void*, int) override {}
    juce::AudioBuffer<float> tempBuffer;

    void loadFile(const juce::File& file);

private:
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioFormatManager formatManager;
    juce::AudioTransportSource transportSource;
    juce::TimeSliceThread backgroundThread{ "clip reader thread" };
};
