/*
  ==============================================================================

    Metronome.h
    Created: 29 Oct 2020 7:24:25am
    Author:  will

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Metronome
{
public:
    Metronome();

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void reset();
    void prepareToPlay(int samplesPerBlock, double sampleRate);

private:

    int totalSamples { 0 };
    double sampleRate { 0 };
    int interval { 0 };
    double bpm { 132.0 };
    int samplesRemaining { 0 };

    juce::AudioFormatManager formatManager;
    std::unique_ptr <juce::AudioFormatReaderSource> metronomeSamplePtr { nullptr };

};
