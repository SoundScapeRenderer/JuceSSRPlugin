/*
  ==============================================================================

    VolLevelSlider.h
    Created: 2 Aug 2016 10:16:08am
    Author:  Nutty

  ==============================================================================
*/

#ifndef VOLLEVELSLIDER_H_INCLUDED
#define VOLLEVELSLIDER_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/**
    Bar slider that draws its internal volume level. Currently used by calling 
    refreshVolLevel() from a timerCallback().
    Uses an arrow thumb to show the current slider value.
*/
class VolLevelSlider    : public Slider
{
public:
    VolLevelSlider(const juce::String &componentName)
        : Slider(componentName)
    {
        // default settings
        setSliderStyle(Slider::LinearBar);
        setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
        setRange(-96, 12, 0);
        setSkewFactor(3);
    }

    ~VolLevelSlider()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float heightScale = 3.0f / 5.0f;
        float boxWidth = static_cast<float>(getWidth());
        float boxHeight = static_cast<float>(getHeight() * heightScale);
        float outlineThickness = boxHeight * 0.22f;
        
        float thumbProportion = static_cast<float>(pow((getValue() - getMinimum()) / (getMaximum() - getMinimum()), getSkewFactor()));
        float thumbPosition = outlineThickness + thumbProportion * (boxWidth - 2 * outlineThickness);

        // use white background for volume level bar
        g.setColour(Colours::white);
        g.fillRect(0.0f, 0.0f, boxWidth, boxHeight);

        // fill up volume level bar up to current level
        g.setColour(SynthParams::sourceLevelColour);
        g.fillRect(0.0f, 0.0f, thumbPosition * volLevel, boxHeight);

        // draw bar slider outline
        g.setColour(SynthParams::sourceColourBlue);
        g.drawRect(0.0f, 0.0f, boxWidth, boxHeight, outlineThickness);

        // draw arrow thumb at current position
        Path triangle;
        triangle.addTriangle(thumbPosition, boxHeight + 2,
                             thumbPosition - outlineThickness, boxHeight * (1.0f / heightScale),
                             thumbPosition + outlineThickness, boxHeight * (1.0f / heightScale));
        g.fillPath(triangle);
    }

    //==============================================================================

    /**
        Set current volume level and repaint this component with updated values.
     */
    void refreshVolLevel(float level)
    {
        volLevel = level;
        repaint();
    }

    //==============================================================================

private:
    float volLevel = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolLevelSlider)
};


#endif  // VOLLEVELSLIDER_H_INCLUDED
