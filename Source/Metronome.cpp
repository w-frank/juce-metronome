/*
  ==============================================================================

    Metronome.cpp
    Created: 29 Oct 2020 7:24:25am
    Author:  will

  ==============================================================================
*/

#include "Metronome.h"

Metronome::Metronome()
{

    std::cout << "Constructing Metronome!" << std::endl;
    formatManager.registerBasicFormats();

    juce::File metronomeAudioFile { juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory) };
    auto metronomeSample = metronomeAudioFile.findChildFiles(juce::File::TypesOfFileToFind::findFiles, false, "cowbell.wav");
    
    jassert(metronomeSample[0].exists());

    auto formatReader = formatManager.createReaderFor(metronomeSample[0]);

    if (formatReader != nullptr)
    {
        metronomeSamplePtr.reset(new juce::AudioFormatReaderSource(formatReader, true));
        metronomeSamplePtr->setNextReadPosition(0);
    }
    else
    {
        std::cout << "Metronome audio file doesn't exist" << std::endl;
    }
    

    interval = int(60.0 / bpm * sampleRate);

}

void Metronome::prepareToPlay (int samplesPerBlock, double appSampleRate)
{
    sampleRate = appSampleRate;
    interval = int(60.0 / bpm * sampleRate);
 
    if (metronomeSamplePtr != nullptr)
    {
        metronomeSamplePtr->prepareToPlay(samplesPerBlock, sampleRate);
        std::cout << "File loaded" << std::endl;
    }
}

void Metronome::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{

    auto bufferSize = bufferToFill.numSamples;

    totalSamples += bufferSize;
    samplesRemaining = totalSamples % interval;

    if ((samplesRemaining + bufferSize) >= interval)
    {
        const int timeToClick = interval - samplesRemaining;
        metronomeSamplePtr->setNextReadPosition(0);

        for (int sample = 0; sample < bufferSize; sample++)
        {
            if (sample == timeToClick)
            {
                metronomeSamplePtr->getNextAudioBlock(bufferToFill);
            }
            
        }
    }

    if (metronomeSamplePtr->getNextReadPosition() != 0)
    {
        metronomeSamplePtr->getNextAudioBlock(bufferToFill);
    }
}

void Metronome::reset ()
{
    totalSamples = 0;
    metronomeSamplePtr->setNextReadPosition(0);
}
