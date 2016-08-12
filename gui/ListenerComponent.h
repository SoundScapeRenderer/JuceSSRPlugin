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
#include "SynthParams.h"

//==============================================================================
/*
*/
class ListenerComponent    : public ImageComponent
{
public:
    ListenerComponent(SynthParams &p)
        : params(p)
    {
        listenerImg = ImageCache::getFromMemory(BinaryData::listener_png, BinaryData::listener_pngSize);
        listenerBackgroundImg = ImageCache::getFromMemory(BinaryData::listener_background_png, BinaryData::listener_background_pngSize);
        listenerShadowImg = ImageCache::getFromMemory(BinaryData::listener_shadow_png, BinaryData::listener_shadow_pngSize);
    }

    ~ListenerComponent()
    {
    }

    void setScreenSize(int w, int h)
    {
        screenWidth = w;
        screenHeight = h;
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float wHalf = static_cast<float>(getWidth() * 0.5f);
        float hHalf = static_cast<float>(getHeight() * 0.5f);
        float currAngleInRadians = degreesToRadians(-params.referenceOrientation.get());
        
        AffineTransform trans(AffineTransform::rotation(currAngleInRadians, wHalf, hHalf));
        g.addTransform(trans);
        g.drawImageWithin(listenerImg, 0, 0, getWidth(), getHeight(), RectanglePlacement::centred);
    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
    }
    
    //==============================================================================

    void mouseDown (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::rightButtonModifier)
        {
            dragger.startDraggingComponent(this, e);
        }
        else
        {
            if (e.mods == ModifierKeys::leftButtonModifier)
            {
                angleOnStartDrag = params.referenceOrientation.get();
            }
        }
    }
    
    void mouseDrag (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::rightButtonModifier)
        {
            dragger.dragComponent(this, e, nullptr);

            // parent must be scene UI
            int middleX = getX() + getWidth() / 2;
            int middleY = getY() + getHeight() / 2;
            juce::Point<float> pos = params.pix2pos(middleX, middleY, getParentWidth(), getParentHeight());
            params.referenceX.setUI(pos.x);
            params.referenceY.setUI(pos.y);
        }
        else
        {
            if (e.mods == ModifierKeys::leftButtonModifier)
            {
                mouseStartY = static_cast<float>(e.getDistanceFromDragStartY());
                float newAngle = fmod(angleOnStartDrag + mouseStartY, 360.0f);
                if (newAngle < 0.0f)
                {
                    newAngle = 360.0f + newAngle;
                }
                params.referenceOrientation.setUI(newAngle);
                repaint();
            }
        }
    }

    //==============================================================================

    void relocate()
    {
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), screenWidth, screenHeight);
        setBounds(pixPosRef.x - getWidth() / 2, pixPosRef.y - getHeight() / 2, getWidth(), getHeight());
    }

    //==============================================================================

private:
    SynthParams &params;
    ComponentDragger dragger;
    int screenWidth;
    int screenHeight;
    Image listenerImg, listenerBackgroundImg, listenerShadowImg;

    float mouseStartY = 0.0f;
    float angleOnStartDrag = 0.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListenerComponent)
};


#endif  // LISTENERCOMPONENT_H_INCLUDED
