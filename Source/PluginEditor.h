/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class MeterComponent;
#include "PluginProcessor.h"
#include "AppInc.h"

//==============================================================================
/**
*/
class Pitchdetect_autocorrelateAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{
public:
    Pitchdetect_autocorrelateAudioProcessorEditor (Pitchdetect_autocorrelateAudioProcessor&);
    ~Pitchdetect_autocorrelateAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;
    void updateWidgetValues(String noteName, float pitchTune);
    enum designFlags {
        GREY = 1,
        ORANGE = 2,
        GREEN = 3
    };

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Pitchdetect_autocorrelateAudioProcessor& processor;

    
    Pitchdetect_autocorrelateAudioProcessor& getProcessor() const
         {
             return static_cast<Pitchdetect_autocorrelateAudioProcessor&> (processor);
         }
    
    
    
    AppLookAndFeelCls aLAF;
    PowerButtonLookAndFeel pbLAF;

    ToggleButton power;
    Label noteNameLabel;
    std::unique_ptr<MeterComponent> flatMeter;
    std::unique_ptr<MeterComponent> sharpMeter;

    int arrowColourFlags;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Pitchdetect_autocorrelateAudioProcessorEditor)
};
