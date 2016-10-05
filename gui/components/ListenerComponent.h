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
#include "ListenerBackgroundComponent.h"

//==============================================================================
/**
 * Draggable component on right-click which can not be dragged outside of the plugin window.
 * Used as reference listener which can be rotated by vertical left-click dragging.
 * Has a reference pointer to its background component to update shadow orientation.
 * Designed according to SSR's reference listener.
 */
class ListenerComponent    : public ImageComponent
{
public:
    ListenerComponent(SynthParams &p, ListenerBackgroundComponent *bg)
        : params(p)
        , listenerBackground(bg)
    {
        listenerImg = ImageCache::getFromMemory(BinaryData::listener_png, BinaryData::listener_pngSize);
    }

    ~ListenerComponent()
    {
    }

    //==============================================================================

    /**
    * Let this component know the size in pixel of the scene in which it is,
    * so that the pixel to meter conversion can be done correctly.
    * @param w scene width in pixel
    * @param h scene height in pixel
    */
    void setSceneSize(int w, int h)
    {
        sceneWidth = w;
        sceneHeight = h;
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float wHalf = static_cast<float>(getWidth() * 0.5f);
        float hHalf = static_cast<float>(getHeight() * 0.5f);
        float currAngleInRadians = degreesToRadians(-(params.referenceOrientation.get() + params.refOrientationOffset));
        
        AffineTransform trans(AffineTransform::rotation(currAngleInRadians, wHalf, hHalf));
        g.addTransform(trans);
        g.drawImageWithin(listenerImg, 0, 0, getWidth(), getHeight(), RectanglePlacement::centred);
    }

    //==============================================================================

    /**
     * Handle mouse down event and prepare for dragging.
     */
    void mouseDown (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::rightButtonModifier)
        {
            dragStartPosition = Point<float>(params.referenceX.get(), params.referenceY.get());
        }
    }
    
    /**
     * Handle mouse drag event.
     * On right-click, calculate the new position in meter and relocate()
     * this component if position is not fixed.
     * On left-click, calculate the new angle and rotate this component.
     */
    void mouseDrag(const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::rightButtonModifier)
        {
            // move reference listener to current position
            float deltaX = e.getDistanceFromDragStartX() / params.getScaledPixelPerMeter();
            float deltaY = e.getDistanceFromDragStartY() / params.getScaledPixelPerMeter();
            params.referenceX.setUI(dragStartPosition.x + deltaX);
            params.referenceY.setUI(dragStartPosition.y - deltaY);
            relocate();
        }
        else if (e.mods == ModifierKeys::leftButtonModifier) 
        {
            // rotate reference listener towards mouse position
            Point<float> mousePosition = Point<float>(static_cast<float>(e.getPosition().x), static_cast<float>(e.getPosition().y));
            Point<float> listenerCenterPosition = Point<float>(static_cast<float>(getWidth() / 2), static_cast<float>(getHeight() / 2));
            float newAngle = -radiansToDegrees(listenerCenterPosition.getAngleToPoint(mousePosition));

            params.referenceOrientation.setUI(newAngle);
            updateBackgroundAngle(newAngle);
            repaint();
        }
    }

    //==============================================================================

    /**
     * Relocate component within its parent component.
     */
    void relocate()
    {
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), sceneWidth, sceneHeight);
        setTopLeftPosition(pixPosRef.x - getWidth() / 2, pixPosRef.y - getHeight() / 2);
    }

    /**
     * Update listenerBackground's shadow orientation.
     * @param newAngle new angle in degrees
     */
    void updateBackgroundAngle(float newAngle)
    {
        listenerBackground->updateShadowAngle(newAngle + params.refOrientationOffset);
    }

    //==============================================================================

private:
    SynthParams &params;
    Point<float> dragStartPosition = Point<float>(0.0f, 0.0f);
    int sceneWidth;
    int sceneHeight;

    Image listenerImg;
    ListenerBackgroundComponent *listenerBackground;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListenerComponent)
};


#endif  // LISTENERCOMPONENT_H_INCLUDED
