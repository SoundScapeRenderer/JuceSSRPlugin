/*
  ==============================================================================

    ZoomSlider.h
    Created: 10 Aug 2016 11:33:20pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef ZOOMSLIDER_H_INCLUDED
#define ZOOMSLIDER_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/*
*/
class ZoomSlider    : public Slider
{
public:
    ZoomSlider(const juce::String &componentName)
        : Slider(componentName)
    {
    }

    ~ZoomSlider()
    {
    }

    //==============================================================================
    
    void paint (Graphics& g)
    {
        g.fillAll (Colours::white);
        g.setColour(Colours::black);
        g.drawRect(0, 0, getWidth(), getHeight());

        AffineTransform trans(AffineTransform::scale(static_cast<float>(getWidth()), static_cast<float>(getHeight())));
        Path arrow;
        arrow.startNewSubPath(0.75f, 0.425f);
        arrow.lineTo(0.805f, 0.25f);
        arrow.lineTo(0.86f, 0.425f);
        arrow.startNewSubPath(0.75f, 0.575f);
        arrow.lineTo(0.805f, 0.75f);
        arrow.lineTo(0.86f, 0.575f);

        g.strokePath(arrow, PathStrokeType(1.5f), trans);
    }

    //==============================================================================

    void mouseDown(const MouseEvent& e)
    {
        ignoreUnused(e);
        valOnStartDrag = getValue();
    }

    void mouseDrag(const MouseEvent& e)
    {
        double delta = e.getDistanceFromDragStartY() / 2.0;
        setValue(valOnStartDrag - delta);
    }

    //==============================================================================

private:
    double valOnStartDrag = 0.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZoomSlider)
};


#endif  // ZOOMSLIDER_H_INCLUDED
