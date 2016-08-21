/*
  ==============================================================================

    ListenerBackgroundComponent.h
    Created: 21 Aug 2016 1:44:44pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef LISTENERBACKGROUNDCOMPONENT_H_INCLUDED
#define LISTENERBACKGROUNDCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/*
*/
class ListenerBackgroundComponent    : public Component
{
public:
    ListenerBackgroundComponent()
    {
        // pass all mouse click events to component behind this
        setInterceptsMouseClicks(false, false);

        listenerBackgroundImg = ImageCache::getFromMemory(BinaryData::listener_background_png, BinaryData::listener_background_pngSize);
        listenerShadowImg = ImageCache::getFromMemory(BinaryData::listener_shadow_png, BinaryData::listener_shadow_pngSize);
    }

    ~ListenerBackgroundComponent()
    {
    }

    //==============================================================================

    void paint(Graphics& g)
    {
        float w = static_cast<float>(getWidth());
        float h = static_cast<float>(getHeight());

        Image bg = listenerBackgroundImg.rescaled(getWidth(), getHeight(), Graphics::highResamplingQuality);
        g.setTiledImageFill(bg, 0, 0, 1.0f);
        g.fillEllipse(0.0f, 0.0f, w, h);

        // draw listener shadow
        float currAngleInRadians = degreesToRadians(-angle);
        float offset = 0.025f * getWidth();
        int shadowW = static_cast<int>(w * 0.6f);
        int shadowH = static_cast<int>(h * 0.6f);
        int shadowMidX = static_cast<int>(w * 0.5f + offset);
        int shadowMidY = static_cast<int>(h * 0.5f + offset);

        AffineTransform trans(AffineTransform::rotation(currAngleInRadians, static_cast<float>(shadowMidX), static_cast<float>(shadowMidY)));
        g.addTransform(trans);
        g.drawImageWithin(listenerShadowImg, shadowMidX - shadowW / 2, shadowMidY - shadowH / 2, shadowW, shadowH, RectanglePlacement::centred);

    }

    //==============================================================================

    void updateShadowAngle(float a)
    {
        angle = a;
        repaint();
    }

    //==============================================================================

private:
    Image listenerShadowImg, listenerBackgroundImg;
    float angle = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListenerBackgroundComponent)
};


#endif  // LISTENERBACKGROUNDCOMPONENT_H_INCLUDED
