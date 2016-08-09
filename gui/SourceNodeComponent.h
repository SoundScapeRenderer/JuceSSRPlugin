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

//==============================================================================
/*
*/
class SourceNodeComponent    : public Component
{
public:
    SourceNodeComponent(SynthParams &p, DocumentWindow *m, Colour c)
        : params(p)
        , menu(m)
        , nodeColour(c)
    {
        lockImg = ImageCache::getFromMemory(BinaryData::lock_icon_png, BinaryData::lock_icon_pngSize);
        muteImg = ImageCache::getFromMemory(BinaryData::mute_icon_png, BinaryData::mute_icon_pngSize);
    }

    ~SourceNodeComponent()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        drawSourceNode(g);

        int nodeSize = getWidth();
        int imageSize = jmin(24, nodeSize / 3);
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

    //==============================================================================

    void mouseDown (const MouseEvent& e)
    {
        // drag on left-click if position is not locked
        if (e.mods == ModifierKeys::leftButtonModifier && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            dragger.startDraggingComponent(this, e);
        }
        else
        {
            // en-/disable popup menu on right-click 
            if (e.mods == ModifierKeys::rightButtonModifier)
            {
                menu->setVisible(!menu->isVisible());
            }
        }
    }
    
    void mouseDrag (const MouseEvent& e)
    {
        // drag on left-click if position is not locked
        if (e.mods == ModifierKeys::leftButtonModifier && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            dragger.dragComponent(this, e, nullptr);

            // parent must be scene UI or of same size as scene UI
            int middleX = getX() + getWidth() / 2;
            int middleY = getY() + getHeight() / 2;
            juce::Point<float> posSource = params.pix2pos(middleX, middleY, getParentWidth(), getParentHeight());
            params.sourceX.setUI(posSource.x);
            params.sourceY.setUI(posSource.y);
        }
    }

    //==============================================================================

private:
    SynthParams &params;
    DocumentWindow *menu;
    ComponentDragger dragger;
    Image lockImg, muteImg;

    Colour nodeColour;
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
