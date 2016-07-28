/*
  ==============================================================================

    SourceComponent.h
    Created: 28 Jul 2016 3:12:40pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef SOURCECOMPONENT_H_INCLUDED
#define SOURCECOMPONENT_H_INCLUDED

#include "../standalone/JuceLibraryCode/JuceHeader.h"
#include "SynthParams.h"

//==============================================================================
/*
*/
class SourceComponent    : public Component
{
public:
    SourceComponent(SynthParams &p, Colour c)
        : params(p)
    {
        setBroughtToFrontOnMouseClick(true);
        setWantsKeyboardFocus(true);
        setNodeColour(c);
    }

    ~SourceComponent()
    {
        gainSlider = nullptr;
    }

    void registerGainSlider(Slider *s)
    {
        gainSlider = s;
    }

    void setNodeColour(Colour c)
    {
        nodeColour = c;
        repaint();
    }

    void setScale(float scale)
    {
        posZoomScale = scale;
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        drawSourceNode(g, nodeColour, ringRatio1, ringRatio2);

        /// \todo draw angle arrows
        if (params.isPlaneSrc.getStep() == eOnOffState::eOn)
        {

        }
    }

    void resized()
    {
    }

    //==============================================================================

    void mouseDown (const MouseEvent& e)
    {
        dragger.startDraggingComponent(this, e);
    }
    
    void mouseDrag (const MouseEvent& e)
    {
        dragger.dragComponent(this, e, nullptr);

        float parentWidth = static_cast<float>(getParentWidth());
        float parentHeight = static_cast<float>(getParentHeight());

        float x = ((getX() + getWidth() * 0.5f) - (parentWidth * 0.5f)) / (parentWidth * posZoomScale);
        float y = ((getY() + getHeight() * 0.5f) - (parentHeight * 0.5f)) / (parentHeight * posZoomScale);

        params.xPos.set(x);
        params.yPos.set(y);
    }

    //==============================================================================

    void focusGained(FocusChangeType cause)
    {
    }

    void focusLost(FocusChangeType cause)
    {
    }

    //==============================================================================

private:
    SynthParams &params;
    Slider *gainSlider;
    ComponentDragger dragger;
    Colour nodeColour;

    const float ringRatio1 = 0.925f, ringRatio2 = 0.875f;
    float posZoomScale = 0.25f;

    /// \todo ssr on right click menu

    //==============================================================================

    void drawSourceNode(Graphics &g, Colour c, float ringRatio1, float ringRatio2)
    {
        float w = getWidth();
        float h = getHeight();

#if USE_RESCALE 1
#if RESCALE_VIA_SETBOUNDS 0
        w *= sizeScale;
        h *= sizeScale;
#endif
#endif
        float paddingL = (getWidth() - w) * 0.5f;
        float paddingT = (getHeight() - h) * 0.5f;

#if 0
        int i = 0;
        do
        {
            g.setColour((i % 2 == 0) ? c : Colours::white);
            g.fillEllipse(paddingL, paddingT, w, h);

            w *= (i % 2 == 0) ? ringRatio1 : ringRatio2;
            h *= (i % 2 == 0) ? ringRatio1 : ringRatio2;
            paddingL = (getWidth() - w) * 0.5f;
            paddingT = (getHeight() - h) * 0.5f;

            i++;
        } while (i < 3);
#else
        g.setColour(c);
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
        g.setColour(c);
        g.fillEllipse(paddingL, paddingT, w, h);
#endif
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceComponent)
};


#endif  // SOURCECOMPONENT_H_INCLUDED
