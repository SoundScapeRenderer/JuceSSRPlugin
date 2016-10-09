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

#include "SourceBackgroundComponent.h"

//==============================================================================
/**
 * Source node component with reference pointer to SourceBackgroundComponent.
 * Designed according to SSR's source node with small changes (mute and fixed state).
 */
class SourceNodeComponent    : public Component
{
public:
    SourceNodeComponent(SourceBackgroundComponent *bg)
        : sourceBackground(bg)
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
        if (sourcePositionFixed)
        {
            g.drawImageWithin(lockImg, padding1, padding2, imageSize, imageSize, RectanglePlacement::centred);
        }

        // draw source mute indicator
        if (sourceMuted)
        {
            g.drawImageWithin(muteImg, padding2, padding2, imageSize, imageSize, RectanglePlacement::centred);
        }
    }

    //==============================================================================

    /**
     * Change colour of source node and sourceBackground.
     */
    void setNodeColour(Colour c)
    {
        nodeColour = c;
        sourceBackground->setPlaneWaveColour(c);
        repaint();
    }

    /**
     * If set true, source node will be drawn with lock icon.
     */
    void setSourcePositionFixed(bool positionFixed)
    {
        sourcePositionFixed = positionFixed;
        repaint();
    }

    /**
     * If set true, source node will be drawn with mute icon.
     */
    void setSourceMute(bool muteSource)
    {
        sourceMuted = muteSource;
        repaint();
    }

    /**
     * Set plane wave visibility of sourceBackground component.
     * @param isVisible true for displaying plane waves
     */
    void setPlaneWaveVisible(bool isVisible)
    {
        sourceBackground->setPlaneWaveVisible(isVisible);
    }

    //==============================================================================

private:
    SourceBackgroundComponent *sourceBackground;

    Image lockImg, muteImg; //!< from http://iconmonstr.com/
    Colour nodeColour = Colours::blue;
    bool sourcePositionFixed = false;
    bool sourceMuted = false;

    const float ringRatio1 = 0.925f, ringRatio2 = 0.875f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceNodeComponent)
};


#endif  // SOURCENODECOMPONENT_H_INCLUDED
