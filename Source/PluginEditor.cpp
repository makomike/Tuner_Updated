/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Pitchdetect_autocorrelateAudioProcessorEditor::Pitchdetect_autocorrelateAudioProcessorEditor (Pitchdetect_autocorrelateAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&aLAF);
    
    addAndMakeVisible (noteNameLabel);
    noteNameLabel.setLookAndFeel(&aLAF);
    noteNameLabel.setText ("--", juce::dontSendNotification);
    noteNameLabel.setColour (juce::Label::textColourId, juce::Colours::orange);
    noteNameLabel.setJustificationType (juce::Justification::centred);
    noteNameLabel.setFont (juce::Font (70.0f, juce::Font::bold));
    
    
    addAndMakeVisible(sliderFlat);
    sliderFlat.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderFlat.setRange(0, 50.00);
    sliderFlat.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    sliderFlat.setScrollWheelEnabled (false);
    
    addAndMakeVisible(sliderSharp);
    sliderSharp.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    sliderSharp.setRange(0, 50.00);
    sliderSharp.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    sliderSharp.setScrollWheelEnabled (false);

    
    
    addAndMakeVisible(power);
    power.setLookAndFeel(&pbLAF);
    power.onClick = [this] {
       //Do something with the ui
        sliderSharp.setEnabled(power.getToggleState());
        sliderFlat.setEnabled(power.getToggleState());
        if(power.getToggleState()){
            startTimer (50);
        }else {
            stopTimer();
            sliderSharp.setValue(0.0f);
            sliderFlat.setValue(0.0f);
            noteNameLabel.setText("--",juce::dontSendNotification);
        }
     
    };
    
    setSize (492, 162);
    
}

Pitchdetect_autocorrelateAudioProcessorEditor::~Pitchdetect_autocorrelateAudioProcessorEditor()
{
}

//==============================================================================
void Pitchdetect_autocorrelateAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
   g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::orange);
    g.setFont (20.0f);
    g.drawFittedText("TUNER", 10, 10, getWidth(), 30, juce::Justification::topLeft, 1);
    
    g.setColour(juce::Colours::grey);
    g.setFont (Font (30.00f, Font::italic));
    g.drawText ("b",
                20, 90, 200, 30,
                Justification::centred, true);                                  

    g.setColour(juce::Colours::grey);
    g.setFont (Font (30.00f, Font::italic));
    g.drawText ("#",
                262, 90, 200, 30,
                Justification::centred, true);

    
}

void Pitchdetect_autocorrelateAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
        noteNameLabel.setBounds (0,  40, getWidth(),  70);
        power.setBounds(10, 40, 50, 50);
    
        sliderFlat.setBounds(70, 20, 100, 100);
        sliderSharp.setBounds(315, 20, 100, 100);
}

double noteFromPitch(float frequency) {
    double noteNum = 12 * (log(frequency / 440) / log(2));
    noteNum = round(noteNum) + 69;
    return noteNum;
}

float frequencyFromNoteNumber(float note) {
    return 440 * pow(2, (note - 69) / 12);
}

double centsOffFromPitch(float frequency, float note) {
    float frqFromNote = frequencyFromNoteNumber(note);
    float logOfPitch = log(frequency / frqFromNote);
    return floor(1200 * logOfPitch) / log(2);
}

void Pitchdetect_autocorrelateAudioProcessorEditor::updateWidgetValues(String noteName, float pitchTune) {
    const String noteDefault = "--";
    noteNameLabel.setColour(juce::Label::textColourId, juce::Colours::orange);
    noteNameLabel.setText(noteDefault,juce::dontSendNotification);
    sliderFlat.setValue(0.0f);
    sliderSharp.setValue(0.0f);
   
    if (pitchTune == 0.0f && noteName == noteDefault)
        return;

    //TODO change colours of text to green
    if (pitchTune == 0.0f && noteName != noteDefault) {

        noteNameLabel.setText(noteName, juce::dontSendNotification);
        noteNameLabel.setColour(juce::Label::textColourId, juce::Colours::green);
        return;

    }

    if(pitchTune < 0.0f){
        sliderFlat.setValue(abs(pitchTune));
    }

    if(pitchTune > 0.0f){
        sliderSharp.setValue(pitchTune);
    }


    noteNameLabel.setText(noteName,juce::dontSendNotification);
}
void Pitchdetect_autocorrelateAudioProcessorEditor::timerCallback()
{
        Pitchdetect_autocorrelateAudioProcessor& ourProcessor = getProcessor();
        double key = ourProcessor.pitch / 2;

        if (key <= 0.0f) {
            updateWidgetValues("--",0.0f);
            return;
        }
        
        
        
        std::array<String, 12> not = { "C","C#","D","Eb","E","F","F#","G","G#","A","Bb","B"};

        int currentKey = noteFromPitch(key);
        int Note = frequencyFromNoteNumber(currentKey);
        float pitchTune = centsOffFromPitch(key, currentKey);
        String noteName = (String)not[currentKey % 12];
        
        updateWidgetValues(noteName, pitchTune);
}
