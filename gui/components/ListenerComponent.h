/*
  ==============================================================================

    ListenerComponent.h
    Created: 31 Jul 2016 11:12:51pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef LISTENERCOMPONENT_H_INCLUDED
#define LISTENERCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

#include "ListenerBackgroundComponent.h"

//==============================================================================
/**
 * Reference listener component with reference pointer to ListenerBackgroundComponent.
 * Designed according to SSR's reference listener.
 */
class ListenerComponent    : public ImageComponent
{
public:
    ListenerComponent(ListenerBackgroundComponent *bg)
        : listenerBackground(bg)
    {
        listenerImg = ImageCache::getFromMemory(BinaryData::listener_png, BinaryData::listener_pngSize);
    }

    ~ListenerComponent()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float wHalf = static_cast<float>(getWidth() * 0.5f);
        float hHalf = static_cast<float>(getHeight() * 0.5f);
        float currAngleInRadians = degreesToRadians(-angle);
        
        AffineTransform trans(AffineTransform::rotation(currAngleInRadians, wHalf, hHalf));
        g.addTransform(trans);
        g.drawImageWithin(listenerImg, 0, 0, getWidth(), getHeight(), RectanglePlacement::centred);
    }

    //==============================================================================

    /**
     * Update referecne listener orientation.
     * @param newAngle new angle in degrees
     */
    void updateListenerOrientation(float newAngle)
    {
        // update listenerBackground's shadow orientation
        listenerBackground->updateShadowAngle(newAngle);

        angle = newAngle;
        repaint();
    }

    //==============================================================================

private:
    ListenerBackgroundComponent *listenerBackground;

    Image listenerImg;
    float angle = 0.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListenerComponent)
};


#endif  // LISTENERCOMPONENT_H_INCLUDED
