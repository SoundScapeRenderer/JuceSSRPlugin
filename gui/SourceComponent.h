/*
  ==============================================================================

    SourceComponent.h
    Created: 28 Jul 2016 3:12:40pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef SOURCECOMPONENT_H_INCLUDED
#define SOURCECOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "SynthParams.h"
#include "SourceBackgroundComponent.h"

//==============================================================================
/*
*/
class SourceComponent    : public Component
{
public:
    SourceComponent(SynthParams &p)
        : params(p)
    {
        setAlwaysOnTop(true);

        lockImg = ImageCache::getFromMemory(BinaryData::lock_icon_png, BinaryData::lock_icon_pngSize);
        muteImg = ImageCache::getFromMemory(BinaryData::mute_icon_png, BinaryData::mute_icon_pngSize);
    }

    ~SourceComponent()
    {
        menu = nullptr;
    }

    void registerBackground(SourceBackgroundComponent *bg)
    {
        background = bg;
    }

    void registerMenu(DocumentWindow *m)
    {
        menu = m;
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        drawSourceNode(g);

        // draw source lock indicator
        if (params.sourcePositionLock.getStep() == eOnOffState::eOn)
        {
            g.drawImageWithin(lockImg, 5, getHeight() - 24 - 5, 24, 24, RectanglePlacement::centred);
        }

        // draw source mute indicator
        if (params.sourceMute.getStep() == eOnOffState::eOn)
        {
            g.drawImageWithin(muteImg, getWidth() - 24 - 5, getHeight() - 24 - 5, 24, 24, RectanglePlacement::centred);
        }
    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
    }

    //==============================================================================

    void mouseDown (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::leftButtonModifier && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            dragger.startDraggingComponent(this, e);
        }
        else
        {
            // create right-click popup menu and item handling
            if (e.mods == ModifierKeys::rightButtonModifier)
            {
                menu->setVisible(!menu->isVisible());
            }
        }
    }
    
    void mouseDrag (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::leftButtonModifier && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            dragger.dragComponent(this, e, nullptr);

            // parent must be scene UI
            int middleX = getX() + getWidth() / 2;
            int middleY = getY() + getHeight() / 2;
            juce::Point<float> posSource = params.pix2pos(middleX, middleY, getParentWidth(), getParentHeight());
            params.sourceX.setUI(posSource.x);
            params.sourceY.setUI(posSource.y);
        }
    }

    //==============================================================================

    void refreshBackground(bool isPlaneWave)
    {
        background->refreshBackground(isPlaneWave);
    }

    //==============================================================================

private:
    SynthParams &params;
    SourceBackgroundComponent *background;
    DocumentWindow *menu;
    ComponentDragger dragger;
    Image lockImg, muteImg;

    const Colour nodeColour = SynthParams::sourceColourBlue;
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceComponent)
};


#endif  // SOURCECOMPONENT_H_INCLUDED
