/*
  ==============================================================================

    ZoomSlider.h
    Created: 10 Aug 2016 11:33:20pm
    Author:  Smoky

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
    ZoomSlider()
        : Slider()
    {
        setRange(25, 200, 1);
        setSliderStyle(Slider::LinearHorizontal);
        setTextBoxStyle(Slider::NoTextBox, false, 80, 24);
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

        String valText = String(getValue()) + getTextValueSuffix();
        g.setFont(getHeight() * 0.8f);
        g.drawFittedText(valText, 0, 0, getWidth() * 7 / 10, getHeight(), Justification::centredRight, 1);

        AffineTransform trans(AffineTransform::scale(static_cast<float>(getWidth()), static_cast<float>(getHeight())));
        Path arrow;
        arrow.startNewSubPath(0.75f, 0.4f);
        arrow.lineTo(0.825f, 0.2f);
        arrow.lineTo(0.9f, 0.4f);
        arrow.startNewSubPath(0.75f, 0.6f);
        arrow.lineTo(0.825f, 0.8f);
        arrow.lineTo(0.9f, 0.6f);

        g.strokePath(arrow, PathStrokeType(2.0f), trans);
    }

    //==============================================================================

    void mouseDown(const MouseEvent& e)
    {
        ignoreUnused(e);
        valOnStartDrag = getValue();
    }

    void mouseDrag(const MouseEvent& e)
    {
        double delta = e.getDistanceFromDragStartY() / 1.0;
        setValue(valOnStartDrag - delta);
    }

    //==============================================================================

private:
    double valOnStartDrag = 0.0;

    ScopedPointer<TextEditor> editor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZoomSlider)
};


#endif  // ZOOMSLIDER_H_INCLUDED
