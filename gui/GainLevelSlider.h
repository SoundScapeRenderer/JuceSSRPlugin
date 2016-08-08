/*
  ==============================================================================

    GainLevelSlider.h
    Created: 2 Aug 2016 10:16:08am
    Author:  Nutty

  ==============================================================================
*/

#ifndef GAINLEVELSLIDER_H_INCLUDED
#define GAINLEVELSLIDER_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/**
    Bar slider that draws it's internal gain level. Currently used by calling setGainLevel()
    from the timerCallback() from its parent component.
    Uses a filled arrow thumb to show the current slider value.
*/
class GainLevelSlider    : public Slider
{
public:
    GainLevelSlider(const juce::String &componentName)
        : Slider(componentName)
    {
    }

    ~GainLevelSlider()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        const float heightScale = 3.0f / 5.0f;
        const float boxWidth = static_cast<float>(getWidth());
        const float boxHeight = static_cast<float>(getHeight() * heightScale);
        const float outlineThickness = boxHeight * 0.22f;
        
        const float thumbProportion = static_cast<float>(pow((getValue() - getMinimum()) / (getMaximum() - getMinimum()), getSkewFactor()));
        const float thumbPosition = outlineThickness + thumbProportion * (boxWidth - 2 * outlineThickness);
        const float levelPosition = thumbPosition * gainLevel;

        // use white background for gain level bar
        g.setColour(Colours::white);
        g.fillRect(0.0f, 0.0f, boxWidth, boxHeight);

        // fill up gain level bar up to current level
        g.setColour(SynthParams::sourceLevelColour);
        g.fillRect(0.0f, 0.0f, levelPosition, boxHeight);

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
        Set current gain level and repaint this component with updated values.
     */
    void refreshGainLevel(float gain)
    {
        gainLevel = gain;
        repaint();
    }

    //==============================================================================

private:
    float gainLevel = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainLevelSlider)
};


#endif  // GAINLEVELSLIDER_H_INCLUDED
