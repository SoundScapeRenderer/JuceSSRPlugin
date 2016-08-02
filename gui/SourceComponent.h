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

//==============================================================================
/*
*/
class SourceComponent    : public Component
{
public:
    SourceComponent(SynthParams &p)
        : params(p)
    {
        setBroughtToFrontOnMouseClick(true);
    }

    ~SourceComponent()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        drawSourceNode(g);

        /// \todo draw angle arrows
        if (params.isSourceTypePlane.getStep() == eSourceType::ePlane)
        {

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
        /// \todo ssr on right click menu
        dragger.startDraggingComponent(this, e);
    }
    
    void mouseDrag (const MouseEvent& e)
    {
        dragger.dragComponent(this, e, nullptr);

        // parent must be scene UI
        int middleX = getX() + getWidth() / 2;
        int middleY = getY() + getHeight() / 2;
        juce::Point<float> posSource = params.pix2pos(middleX, middleY, getParentWidth(), getParentHeight());
        params.sourceX.setUI(posSource.x);
        params.sourceY.setUI(posSource.y);
    }

    //==============================================================================

private:
    SynthParams &params;
    ComponentDragger dragger;
    const Colour nodeColour = SynthParams::sourceColourBlue;

    const float ringRatio1 = 0.925f, ringRatio2 = 0.875f;

    //==============================================================================

    void drawSourceNode(Graphics &g)
    {
        float w = static_cast<float>(getWidth());
        float h = static_cast<float>(getHeight());
        float paddingL = (getWidth() - w) * 0.5f;
        float paddingT = (getHeight() - h) * 0.5f;

        /// \todo draw shadow
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
