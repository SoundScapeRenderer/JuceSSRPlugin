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

        bounds = new ComponentBoundsConstrainer();
    }

    ~ListenerComponent()
    {
        bounds = nullptr;
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

    void resized()
    {
        bounds->setMinimumOnscreenAmounts(getHeight() / 2, getWidth() / 2, getHeight() / 2, getWidth() / 2);
    }
    
    //==============================================================================

    /**
     * Handle mouse down event.
     * Drag on right-click to move this component.
     * Drag on left-click to rotate.
     */
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
    
    /// handle mouse dragging and calculating new position in meter or angle after rotation
    void mouseDrag (const MouseEvent& e)
    {
        // move reference listener
        if (e.mods == ModifierKeys::rightButtonModifier)
        {
            dragger.dragComponent(this, e, bounds);

            int middleX = getX() + getWidth() / 2;
            int middleY = getY() + getHeight() / 2;
            juce::Point<float> pos = params.pix2pos(middleX, middleY, sceneWidth, sceneHeight);
            params.referenceX.setUI(pos.x);
            params.referenceY.setUI(pos.y);
        }
        else
        {
            // rotate reference listener
            if (e.mods == ModifierKeys::leftButtonModifier)
            {
                mouseStartY = static_cast<float>(e.getDistanceFromDragStartY());
                float newAngle = fmod(angleOnStartDrag + mouseStartY, 360.0f);
                if (newAngle > 180.0f)
                {
                    newAngle -= 360.0f;
                }
                else if (newAngle <= -180.0f)
                {
                    newAngle += 360.0f;
                }
                params.referenceOrientation.setUI(newAngle);
                updateBackgroundAngle(newAngle);
                repaint();
            }
        }
    }

    //==============================================================================

    /**
     * Relocate component within its parent component.
     */
    void relocate()
    {
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), sceneWidth, sceneHeight);
        setBounds(pixPosRef.x - getWidth() / 2, pixPosRef.y - getHeight() / 2, getWidth(), getHeight());
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
    ComponentDragger dragger;
    ScopedPointer<ComponentBoundsConstrainer> bounds;
    int sceneWidth;
    int sceneHeight;

    Image listenerImg;
    ListenerBackgroundComponent *listenerBackground;

    float mouseStartY = 0.0f;
    float angleOnStartDrag = 0.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ListenerComponent)
};


#endif  // LISTENERCOMPONENT_H_INCLUDED
