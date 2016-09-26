/*
  ==============================================================================

    OutputLevelComponent.h
    Created: 1 Sep 2016 4:31:53pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef OUTPUTLEVELCOMPONENT_H_INCLUDED
#define OUTPUTLEVELCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/**
 * Component to draw output level of two channels e.g. left and right.
 * Refreshing the level values uses smooth decaying if new levels are
 * lower then the current levels.
 */
class OutputLevelComponent    : public Component
{
public:
    OutputLevelComponent()
    {
    }

    ~OutputLevelComponent()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float boxWidth = static_cast<float>(getWidth());
        float boxHeight = static_cast<float>(getHeight());
        float outlineThickness = 1.0f;

        g.fillAll (Colours::white);

        // fill level bars up to current levels
        float levelLeftProportion = static_cast<float>(pow((currentLevelLeft - minLevel) / (maxLevel - minLevel), skewFactor));
        float levelLeftPosition = outlineThickness + levelLeftProportion * (boxWidth - 2 * outlineThickness);

        float levelRightProportion = static_cast<float>(pow((currentLevelRight - minLevel) / (maxLevel - minLevel), skewFactor));
        float levelRightPosition = outlineThickness + levelRightProportion * (boxWidth - 2 * outlineThickness);

        Colour c = currentLevelLeft > clipLevel || currentLevelRight > clipLevel ? Colours::red : levelColour;
        g.setColour(c);
        g.fillRect(0.0f, 0.0f, levelLeftPosition, boxHeight / 2.0f);
        g.fillRect(0.0f, boxHeight / 2.0f, levelRightPosition, boxHeight / 2.0f);

        // draw component outline and separating line
        g.setColour(Colours::lightgrey.brighter());
        Path line;
        line.startNewSubPath(0.0f, boxHeight / 2.0f - outlineThickness / 2.0f);
        line.lineTo(boxWidth, boxHeight / 2.0f - outlineThickness / 2.0f);
        g.strokePath(line, PathStrokeType(outlineThickness));
        g.drawRect(0.0f, 0.0f, boxWidth, boxHeight, outlineThickness);
    }

    //==============================================================================

    /**
     * Set current output level and repaint this component with updated values.
     * If new level is smaller then current level then draw smooth decaying instead.
     * @param levelLeft new level of left channel to draw
     * @param levelRight new level of right channel to draw
     */
    void refreshOutputLevel(float levelLeft, float levelRight)
    {
        // left level
        if (levelLeft > currentLevelLeft)
        {
            currentLevelLeft = levelLeft;
        }
        else
        {
            currentLevelLeft -= decaySpeed;
            currentLevelLeft = jmax(minLevel, currentLevelLeft);
        }

        // right level
        if (levelRight > currentLevelRight)
        {
            currentLevelRight = levelRight;
        }
        else
        {
            currentLevelRight -= decaySpeed;
            currentLevelRight = jmax(minLevel, currentLevelRight);
        }

        repaint();
    }

    /**
     * Use custom colour for level bar.
     * @param c custom level colour to use, deefault is juce::Colours::green
     */
    void setLeveLColour(Colour c)
    {
        levelColour = c;
    }

    /**
     * Set a new skew factor to display level values logarithmically (see juce::Slider).
     * Default is 1.0f, which is linear scaling.
     * @param skew new skew factor
     */
    void setSkewFactor(float skew)
    {
        skewFactor = skew;
    }

    //==============================================================================

private:
    Colour levelColour = Colours::green;
    float skewFactor = 1.0f;
    float currentLevelLeft = -96.0f;
    float currentLevelRight = -96.0f;

    const float minLevel = -96.0f;
    const float maxLevel = 12.0f;
    const float clipLevel = 0.0f;
    const float decaySpeed = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputLevelComponent)
};


#endif  // OUTPUTLEVELCOMPONENT_H_INCLUDED
