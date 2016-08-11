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
    SourceBackgroundComponent(Colour c)
    {
        // pass all mouse click events to component behind this
        setInterceptsMouseClicks(false, false);
        planeWaveColour = c;

        shadowImg = ImageCache::getFromMemory(BinaryData::source_shadow_png, BinaryData::source_shadow_pngSize);
    }

    ~SourceBackgroundComponent()
    {
    }

    void setBackgroundProperties(float sourceRadius)
    {
        shadowRadius = sourceRadius * 1.05f;
        offset = sourceRadius * 0.08f;
        lineThickness = sourceRadius * 0.065f;
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float wHalf = static_cast<float>(getWidth() * 0.5f);
        float hHalf = static_cast<float>(getHeight() * 0.5f);
        int paddingL = static_cast<int>(wHalf + offset - shadowRadius);
        int paddingT = static_cast<int>(hHalf + offset - shadowRadius);
        int shadowSize = static_cast<int>(shadowRadius * 2.0f);

        // draw source shadow
        g.drawImageWithin(shadowImg, paddingL, paddingT, shadowSize, shadowSize, RectanglePlacement::centred);

        // draw plane wave
        if (drawPlaneWave)
        {
            Path plane, waveDirection, arc;
            plane.startNewSubPath(0.0f, 0.5f);
            plane.lineTo(0.2075f, 0.5f);
            plane.startNewSubPath(0.7925f, 0.5f);
            plane.lineTo(1.0f, 0.5f);

            waveDirection.startNewSubPath(0.5f, 0.7925f);
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
    Image shadowImg;

    Colour planeWaveColour;
    float shadowRadius;
    float offset;
    float lineThickness;

    bool drawPlaneWave = false;
    float angle = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceBackgroundComponent)
};


#endif  // SOURCEBACKGROUNDCOMPONENT_H_INCLUDED
