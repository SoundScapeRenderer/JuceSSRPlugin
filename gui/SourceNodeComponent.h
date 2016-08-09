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
#include "GainLevelSlider.h"
#include "SourceBackgroundComponent.h"

//==============================================================================
/*
*/
class SourceNodeComponent    : public Component
{
public:
    SourceNodeComponent(SynthParams &p)
        : params(p)
    {
        setAlwaysOnTop(true);

        lockImg = ImageCache::getFromMemory(BinaryData::lock_icon_png, BinaryData::lock_icon_pngSize);
        muteImg = ImageCache::getFromMemory(BinaryData::mute_icon_png, BinaryData::mute_icon_pngSize);
    }

    ~SourceNodeComponent()
    {
    }

    void registerGainLevelSlider(GainLevelSlider *s)
    {
        gainLevelSlider = s;
    }

    void registerBackground(SourceBackgroundComponent *bg)
    {
        background = bg;
        background->setPlaneWaveColour(nodeColour);
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

    void refreshGainLevel(float level)
    {
        gainLevelSlider->refreshGainLevel(level);
    }

    void refreshBackground(bool isPlaneWave)
    {
        background->refreshBackground(isPlaneWave);
    }

    void refreshBackground(float angle, bool isPlaneWave)
    {
        background->refreshBackground(angle, isPlaneWave);
    }

    //==============================================================================

private:
    SynthParams &params;
    GainLevelSlider *gainLevelSlider;
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceNodeComponent)
};


#endif  // SOURCENODECOMPONENT_H_INCLUDED
