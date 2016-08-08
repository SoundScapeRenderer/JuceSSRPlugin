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

    void setPlaneWaveColour(Colour c)
    {
        planeWaveColour = c;
        repaint();
    }

    void setShadowRadius(float sourceRadius)
    {
        shadowRadius = sourceRadius * 1.05f;
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float wHalf = static_cast<float>(getWidth() * 0.5f);
        float hHalf = static_cast<float>(getHeight() * 0.5f);
        float shadowCentreX = wHalf + offset;
        float shadowCentreY = hHalf + offset;

        // draw source shadow
        Colour c1(Colours::black);
        Colour c2(Colours::transparentWhite);
        ColourGradient gradient(c1, shadowCentreX, shadowCentreY, c2, shadowCentreX, shadowCentreY + shadowRadius, true);
        gradient.addColour(0.65, c1);
        g.setGradientFill(gradient);
        g.fillEllipse(shadowCentreX - shadowRadius, shadowCentreY - shadowRadius, shadowRadius * 2.0f, shadowRadius * 2.0f);

        // draw plane wave
        if (drawPlaneWave)
        {
            Path plane, waveDirection, arc;
            plane.startNewSubPath(0.0f, 0.5f);
            plane.lineTo(0.205f, 0.5f);
            plane.startNewSubPath(0.795f, 0.5f);
            plane.lineTo(1.0f, 0.5f);

            waveDirection.startNewSubPath(0.5f, 0.795f);
            waveDirection.lineTo(0.5f, 0.98f);
            waveDirection.startNewSubPath(0.44f, 0.9f);
            waveDirection.lineTo(0.5f, 0.98f);
            waveDirection.lineTo(0.56f, 0.9f);

            arc.addPieSegment(0.2f, 0.2f, 0.6f, 0.6f, float_Pi * 0.5f, float_Pi * 1.0f, 1.0f);
            arc.addPieSegment(0.2f, 0.2f, 0.6f, 0.6f, float_Pi * 1.06f, float_Pi * 1.5f, 1.0f);

            AffineTransform trans(AffineTransform::scale(static_cast<float>(getWidth()), static_cast<float>(getHeight())));
            trans = trans.rotated(degreesToRadians(angle), wHalf, hHalf);

            g.setColour(planeWaveColour);
            g.strokePath(plane, PathStrokeType(lineThickness), trans);
            g.strokePath(waveDirection, PathStrokeType(lineThickness), trans);
            g.strokePath(arc, PathStrokeType(lineThickness), trans);
        }
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
    Colour planeWaveColour = Colours::black;
    float shadowRadius = 0.0f;
    const float offset = 4.0f;
    const float lineThickness = 2.5f;

    bool drawPlaneWave = false;
    float angle = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceBackgroundComponent)
};


#endif  // SOURCEBACKGROUNDCOMPONENT_H_INCLUDED
