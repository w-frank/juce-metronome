#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

    startButton.setRadioGroupId(1);
    startButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    startButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    startButton.setEnabled(true);
    startButton.onClick = [this]() { startMetronome(); };
    addAndMakeVisible(startButton);

    stopButton.setRadioGroupId(1);
    stopButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled(false);
    stopButton.onClick = [this]() { stopMetronome(); };
    addAndMakeVisible(stopButton);


    setSize (200, 200);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

void MainComponent::startMetronome()
{
    metronomeState = MetronomeState::Started;
    startButton.setEnabled(false);
    stopButton.setEnabled(true);
}

void MainComponent::stopMetronome()
{
    metronomeState = MetronomeState::Stopped;
    startButton.setEnabled(true);
    stopButton.setEnabled(false);
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    metronome.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    if (metronomeState == MetronomeState::Started)
    {
       metronome.getNextAudioBlock(bufferToFill);
    }
    else
    {
        metronome.reset();
    }

}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{

    juce::Rectangle<int> bounds = getLocalBounds();

    juce::FlexBox flexBox;
    flexBox.items.add(juce::FlexItem(100, 100, startButton));
    flexBox.items.add(juce::FlexItem(100, 100, stopButton));

    flexBox.performLayout(bounds);

}
