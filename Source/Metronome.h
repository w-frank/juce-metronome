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

    void countSamples(int bufferSize);
    void reset ();
    void prepareToPlay(double sampleRate);

private:

    int totalSamples { 0 };
    double sampleRate { 0 };

};
