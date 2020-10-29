/*
  ==============================================================================

    Metronome.cpp
    Created: 29 Oct 2020 7:24:25am
    Author:  will

  ==============================================================================
*/

#include "Metronome.h"

void Metronome::countSamples (int bufferSize)
{
    totalSamples += bufferSize;
    std::cout << totalSamples << std::endl;
}

void Metronome::reset ()
{
    totalSamples = 0;
}

void Metronome::prepareToPlay (double appSampleRate)
{
    sampleRate = appSampleRate;
}
