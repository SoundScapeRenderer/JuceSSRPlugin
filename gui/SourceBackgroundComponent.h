/*
  ==============================================================================

    SourceBackgroundComponent.h
    Created: 7 Aug 2016 10:11:07pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef SOURCEBACKGROUNDCOMPONENT_H_INCLUDED
#define SOURCEBACKGROUNDCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/*
*/
class SourceBackgroundComponent    : public Component
{
public:
    SourceBackgroundComponent()
    {
        // pass all mouse click events to component behind this
        setInterceptsMouseClicks(false, false);
    }

    ~SourceBackgroundComponent()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float wHalf = static_cast<float>(getWidth() / 2);
        float hHalf = static_cast<float>(getHeight() / 2);
        float shadowCentreX = wHalf + offset;
        float shadowCentreY = hHalf + offset;

        // draw source shadow
        Colour c(Colours::black);
        ColourGradient gradient(c, shadowCentreX, shadowCentreY, Colours::transparentWhite, shadowCentreX, shadowCentreY + shadowRadius, true);
        gradient.addColour(0.65, c);
        g.setGradientFill(gradient);
        g.fillEllipse(shadowCentreX - shadowRadius, shadowCentreY - shadowRadius, shadowRadius * 2.0f, shadowRadius * 2.0f);

        // draw plane wave
        if (drawPlaneWave)
        {
            const AffineTransform trans(AffineTransform::scale(getWidth(), getHeight()).rotated(degreesToRadians(angle), wHalf, hHalf));
            Path plane, waveDirection, arc;
            plane.startNewSubPath(0.0f, 0.5f);
            plane.lineTo(0.2f, 0.5f);
            plane.startNewSubPath(0.8f, 0.5f);
            plane.lineTo(1.0f, 0.5f);

            waveDirection.startNewSubPath(0.5f, 0.8f);
            waveDirection.lineTo(0.5f, 0.98f);
            waveDirection.startNewSubPath(0.44f, 0.9f);
            waveDirection.lineTo(0.5f, 0.98f);
            waveDirection.lineTo(0.56f, 0.9f);

            arc.addPieSegment(0.2f, 0.2f, 0.6f, 0.6f, float_Pi * 0.5f, float_Pi * 1.0f, 1.0f);
            arc.addPieSegment(0.2f, 0.2f, 0.6f, 0.6f, float_Pi * 1.06f, float_Pi * 1.5f, 1.0f);

            g.setColour(sourceColour);
            g.strokePath(plane, PathStrokeType(lineThickness), trans);
            g.strokePath(waveDirection, PathStrokeType(lineThickness), trans);
            g.strokePath(arc, PathStrokeType(lineThickness), trans);
        }
    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

    //==============================================================================

    void refreshBackground(bool planeWaveVisible)
    {
        drawPlaneWave = planeWaveVisible;
        repaint();
    }

    void refreshBackground(float newangle, bool planeWaveVisible)
    {
        angle = newangle;
        refreshBackground(planeWaveVisible);
    }

    //==============================================================================

private:
    float shadowRadius = 52.5f;
    Colour sourceColour = Colours::blue;
    const float offset = 4.0f;
    const float lineThickness = 2.5f;

    bool drawPlaneWave = false;
    float angle = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceBackgroundComponent)
};


#endif  // SOURCEBACKGROUNDCOMPONENT_H_INCLUDED
