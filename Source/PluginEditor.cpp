/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//Label==============================================================================
Laulu_a2AudioProcessorEditor::Laulu_a2AudioProcessorEditor (Laulu_a2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setOpaque (true);
    setSize (400, 300);
    

//Mix Slider=================================================================================
    mixSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 12);
    mixSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aquamarine);
    mixSlider.addListener(this);
    mixSlider.setRange(0, 100.0f);
    mixSlider.setTextValueSuffix("%");
    addAndMakeVisible(mixSlider);
    mixSlider.setNumDecimalPlacesToDisplay(2);
    
    addAndMakeVisible(mixLabel);
    addAndMakeVisible(mixSlider);
    mixLabel.setText("wet/Dry Mix", dontSendNotification);
    mixLabel.attachToComponent(&mixSlider, true);
    
//Freq Slider================================================================================
    freqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 80, 12);
    freqSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    freqSlider.setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::aquamarine);
    freqSlider.setRange(20.0f, 2000.0f);
    freqSlider.setTextValueSuffix("Hz");
    freqSlider.addListener(this);
    freqSlider.setNumDecimalPlacesToDisplay(2);
    
    addAndMakeVisible(freqSlider);
    addAndMakeVisible(freqLabel);
    
    freqLabel.setText("Frequency", dontSendNotification);
    freqLabel.attachToComponent(&freqSlider, true);
    
 
    
   
    
    setResizable(true, true);
}

Laulu_a2AudioProcessorEditor::~Laulu_a2AudioProcessorEditor()
{
}

//Paint Editor==============================================================================
void Laulu_a2AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::crimson);
   //greeting
    
    g.setColour(Colours::blanchedalmond);
    g.setFont(Font("Times New Roman", 20.0f, Font::italic));
   // g.drawFittedText("Oh No", 10, 10, getWidth(), 50,Justification::left,1);
    
    //Outer Rectangle ========================================================================
    g.setColour(Colours::honeydew);
    g.drawRect(0, 0, 400, 300, 5);
    //g.fillRect(150, 50, 250, 100);
    
   // g.drawLine(0.0f, 0.0f, getWidth(), getHeight());
    
    //Top Rectangle boarder=====================================================================
    g.setColour(Colours::black);
    g.drawRect(3, 3, 390, 25, 400);
    
    //Bottom Rectangle==========================================================================
    g.setColour(Colours::black);
    g.drawRect(3, 3, 390, 25, 400);
    
    //Header Text===============================================================================
    g.setColour (Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("Laulu_A2", getLocalBounds(), Justification::top, 5);
    g.drawFittedText ("Volume Warning", getLocalBounds(), Justification::bottom, 8);
    // top line of text
    
    
    
}

void Laulu_a2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //make sure this makes sense with the style of slider you make
    mixSlider.setBounds(100, getHeight()-200, getWidth()-80, 80);
    
    freqSlider.setBounds(100, getHeight()-100, getWidth()-80, 80);
    
    

}

void Laulu_a2AudioProcessorEditor::sliderValueChanged(Slider *slider){
    if (slider == &mixSlider)
    {
        //do something, get the value on our current slider, pass the value to our audio processsor
        processor.mixLevel = mixSlider.getValue();
        processor.mixLevel.setTargetValue(mixSlider.getValue());
    
    }
    
        processor.freqLevel = freqSlider.getValue();
        processor.freqLevel.setTargetValue(freqSlider.getValue());
        
    
        
    }

    //else if (slider == &freqSlider) {
            

        
   


