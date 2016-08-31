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
/**
 * Source background component class.
 * Shows plane waves which direction can be set via updatePlaneWave().
 * For correct drawing results this component should be set exactly double the width 
 * and height of the source node component.
 * Plane wave designed according to SSR's plane wave.
 */
class SourceBackgroundComponent    : public Component
{
public:
    SourceBackgroundComponent()
    {
        // pass all mouse click events to component behind this
        setInterceptsMouseClicks(false, false);

        shadowImg = ImageCache::getFromMemory(BinaryData::source_shadow_png, BinaryData::source_shadow_pngSize);
    }

    ~SourceBackgroundComponent()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float shadowRadius = jmin(getWidth(), getHeight()) * 0.25f * 1.05f;
        float offset = jmin(getWidth(), getHeight()) * 0.25f * 0.08f;

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
            float lineThickness = jmin(getWidth(), getHeight()) * 0.25f * 0.065f;
            float waveSize = static_cast<float>(jmin(getWidth(), getHeight()));

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

            AffineTransform trans(AffineTransform::scale(waveSize, waveSize));
            trans = trans.translated(getWidth() * 0.5f - waveSize * 0.5f, getHeight() * 0.5f - waveSize * 0.5f);
            trans = trans.rotated(degreesToRadians(angle), wHalf, hHalf);

            g.setColour(planeWaveColour);
            g.strokePath(plane, PathStrokeType(lineThickness), trans);
            g.strokePath(waveDirection, PathStrokeType(lineThickness), trans);
            g.strokePath(arc, PathStrokeType(lineThickness), trans);
        }
    }

    //==============================================================================

    float getPlaneWaveAngle()
    {
        return angle;
    }

    /**
     * Update angle of the plane wave direction and repaint.
     * @param newAngle new angle in degrees
     * @param planeWaveVisible false do not show plane wave, true show it
     * @param c colour of plane wave
     */
    void updatePlaneWave(float newAngle, bool planeWaveVisible, Colour c)
    {
        angle = newAngle;
        drawPlaneWave = planeWaveVisible;
        planeWaveColour = c;
        repaint();
    }

    //==============================================================================

private:
    Image shadowImg;
    Colour planeWaveColour;

    bool drawPlaneWave = false;
    float angle = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceBackgroundComponent)
};


#endif  // SOURCEBACKGROUNDCOMPONENT_H_INCLUDED
