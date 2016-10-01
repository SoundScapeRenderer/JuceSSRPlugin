/*
  ==============================================================================

    SourceNodeComponent.h
    Created: 28 Jul 2016 3:12:40pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef SOURCENODECOMPONENT_H_INCLUDED
#define SOURCENODECOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "SynthParams.h"

#include "SourceBackgroundComponent.h"
#include "VolLevelSlider.h"

//==============================================================================
/**
 * Draggable component on left-click which can not be dragged outside of the plugin window.
 * Used as Source node with reference pointers to VolLevelSlider, SourceBackgroundComponent
 * and ResizableWindow (for right-click menu). Menu stays open until right-click again.
 * Designed according to SSR's source node with small changes (mute and fixed state).
 */
class SourceNodeComponent    : public Component
{
public:
    SourceNodeComponent(SynthParams &p, VolLevelSlider *v, SourceBackgroundComponent *bg, ResizableWindow *m)
        : params(p)
        , volSlider(v)
        , sourceBackground(bg)
        , menu(m)
    {
        lockImg = ImageCache::getFromMemory(BinaryData::lock_icon_png, BinaryData::lock_icon_pngSize);
        muteImg = ImageCache::getFromMemory(BinaryData::mute_icon_png, BinaryData::mute_icon_pngSize);
        
        bounds = new ComponentBoundsConstrainer();
    }

    ~SourceNodeComponent()
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

    void setNodeColour(Colour c)
    {
        nodeColour = c;
        sourceBackground->setPlaneWaveColour(c);
    }

    Colour getNodeColour()
    {
        return nodeColour;
    }

    VolLevelSlider* getVolSlider()
    {
        return volSlider;
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        float w = static_cast<float>(getWidth());
        float h = static_cast<float>(getHeight());
        float paddingL = (getWidth() - w) * 0.5f;
        float paddingT = (getHeight() - h) * 0.5f;

        // draw actual node
        g.setColour(nodeColour);
        g.fillEllipse(paddingL, paddingT, w, h);

        w *= ringRatio1;
        h *= ringRatio1;
        paddingL = (getWidth() - w) * 0.5f;
        paddingT = (getHeight() - h) * 0.5f;
        g.setColour(Colours::white);
        g.fillEllipse(paddingL, paddingT, w, h);

        w *= ringRatio2;
        h *= ringRatio2;
        paddingL = (getWidth() - w) * 0.5f;
        paddingT = (getHeight() - h) * 0.5f;
        g.setColour(nodeColour);
        g.fillEllipse(paddingL, paddingT, w, h);

        int nodeSize = jmin(getWidth(), getHeight());
        int imageSize = jmax(10 , jmin(56, nodeSize / 3));
        int padding1 = nodeSize / 20;
        int padding2 = nodeSize - imageSize - padding1;

        // draw source lock indicator
        if (params.sourcePositionLock.getStep() == eOnOffState::eOn)
        {
            g.drawImageWithin(lockImg, padding1, padding2, imageSize, imageSize, RectanglePlacement::centred);
        }

        // draw source mute indicator
        if (params.sourceMute.getStep() == eOnOffState::eOn)
        {
            g.drawImageWithin(muteImg, padding2, padding2, imageSize, imageSize, RectanglePlacement::centred);
        }
    }

    void resized()
    {
        bounds->setMinimumOnscreenAmounts(getHeight() / 2, getWidth() / 2, getHeight() / 2, getWidth() / 2);
    }

    //==============================================================================

    /**
     * Handle mouse down event.
     * Drag on left-click if position is not locked to move.
     * En-/disable popup menu on right-click.
     */
    void mouseDown (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::leftButtonModifier && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            dragger.startDraggingComponent(this, e);
        }
        else
        {
            if (e.mods == ModifierKeys::rightButtonModifier)
            {
                menu->setVisible(!menu->isVisible());
            }
        }
    }
    
    /// handle mouse dragging and calculating new position in meter
    void mouseDrag (const MouseEvent& e)
    {
        // drag on left-click if position is not locked
        if (e.mods == ModifierKeys::leftButtonModifier && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            dragger.dragComponent(this, e, bounds);

            int middleX = getX() + getWidth() / 2;
            int middleY = getY() + getHeight() / 2;
            juce::Point<float> posSource = params.pix2pos(middleX, middleY, sceneWidth, sceneHeight);
            params.sourceX.setUI(posSource.x);
            params.sourceY.setUI(posSource.y);
        }
    }

    //==============================================================================

    /**
     * Relocate component within its parent component.
     */
    void relocate()
    {
        juce::Point<int> pixPosRef = params.pos2pix(params.sourceX.get(), params.sourceY.get(), sceneWidth, sceneHeight);
        setTopLeftPosition(pixPosRef.x - getWidth() / 2, pixPosRef.y - getHeight() / 2);
    }

    //==============================================================================

    /**
     * Set plane wave visibility of sourceBackground component.
     * @param isVisible true for displaying plane waves
     */
    void setPlaneWaveVisible(bool isVisible)
    {
        sourceBackground->setPlaneWaveVisible(isVisible);
    }

    /**
     * Set plane wave direction angle of sourceBackground component.
     * 0.0f for top and +-180.0f for bottom, 90.0f for left and -90.0f for right.
     * @param newAngle new direction angle of plane waves
     */
    void setPlaneWaveAngle(float newAngle)
    {
        sourceBackground->setPlaneWaveAngle(newAngle);
    }

    //==============================================================================

private:
    SynthParams &params;
    ComponentDragger dragger;
    ScopedPointer<ComponentBoundsConstrainer> bounds;
    int sceneWidth;
    int sceneHeight;

    Image lockImg, muteImg; //!< from http://iconmonstr.com/
    ResizableWindow *menu;
    VolLevelSlider *volSlider;
    SourceBackgroundComponent *sourceBackground;

    Colour nodeColour = SynthParams::sourceColourBlue;
    const float ringRatio1 = 0.925f, ringRatio2 = 0.875f;

    //==============================================================================

    void drawSourceNode(Graphics &g)
    {
        float w = static_cast<float>(getWidth());
        float h = static_cast<float>(getHeight());
        float paddingL = (getWidth() - w) * 0.5f;
        float paddingT = (getHeight() - h) * 0.5f;

        // draw actual node
        g.setColour(nodeColour);
        g.fillEllipse(paddingL, paddingT, w, h);

        w *= ringRatio1;
        h *= ringRatio1;
        paddingL = (getWidth() - w) * 0.5f;
        paddingT = (getHeight() - h) * 0.5f;
        g.setColour(Colours::white);
        g.fillEllipse(paddingL, paddingT, w, h);

        w *= ringRatio2;
        h *= ringRatio2;
        paddingL = (getWidth() - w) * 0.5f;
        paddingT = (getHeight() - h) * 0.5f;
        g.setColour(nodeColour);
        g.fillEllipse(paddingL, paddingT, w, h);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceNodeComponent)
};


#endif  // SOURCENODECOMPONENT_H_INCLUDED
