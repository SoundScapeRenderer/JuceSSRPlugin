/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 28 Jul 2016 3:27:28pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

#include "../standalone/JuceLibraryCode/JuceHeader.h"

class CustomLookAndFeel : public LookAndFeel_V2
{
public:
    //==============================================================================
    CustomLookAndFeel(): LookAndFeel_V2()
    {
    }
    virtual ~CustomLookAndFeel()
    {
    }
    //==============================================================================

    void CustomLookAndFeel::drawLinearSlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    // use bar slider to draw vol and pan instead
    if (style == Slider::LinearBar)
    {
        const bool isMouseOver = s.isMouseOverOrDragging() && s.isEnabled();
        const float posX = static_cast<float>(x);
        const float posY = static_cast<float>(y);
        float boxWidth = static_cast<float>(width);
        const float boxHeight = static_cast<float>(height);

        Colour bgColour(s.findColour(Slider::thumbColourId));
        Colour outlineColour(s.findColour(Slider::textBoxOutlineColourId));
        float outlineThickness = boxHeight * 0.2f;

        g.setColour(bgColour);
        g.fillRect(posX, posY, sliderPos, boxHeight);

        g.setColour(outlineColour);
        g.drawRect(posX, posY, boxWidth, boxHeight, outlineThickness);
        
        drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
    }
    else
    {
        // draw linear slider
        LookAndFeel_V2::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
    }
}

void CustomLookAndFeel::drawLinearSliderThumb(Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider &s)
{
    const float sliderRadius = (float)(jmin(10, width / 2, height / 2) - 2);
    const float outlineThickness = s.isEnabled() ? 0.8f : 0.3f;
    float centreX, centreY;

    Colour thumbColour(s.findColour(Slider::textBoxOutlineColourId));

    // draw thumb at current position
    if (style == Slider::LinearBar)
    {

    }
    else
    {
        LookAndFeel_V2::drawLinearSliderThumb(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, s);
    }
}

    //==============================================================================
    
private:

};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
