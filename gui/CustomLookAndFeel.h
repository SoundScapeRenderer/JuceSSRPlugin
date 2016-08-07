/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 28 Jul 2016 3:27:28pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef CUSTOMLOOKANDFEEL_H_INCLUDED
#define CUSTOMLOOKANDFEEL_H_INCLUDED

#include "JuceHeader.h"

class CustomLookAndFeel : public LookAndFeel_V2
{
public:
    //==============================================================================
    CustomLookAndFeel(): LookAndFeel_V2()
    {
        customFont = Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansMono_ttf, BinaryData::DejaVuSansMono_ttfSize);
    }
    virtual ~CustomLookAndFeel()
    {
    }
    //==============================================================================

    Typeface::Ptr getTypefaceForFont(const Font & /*font*/)
    {
        return customFont;
    }

    //==============================================================================

    void drawTickBox(Graphics &g, Component &/*c*/, float /*x*/, float /*y*/, float width, float height, bool ticked, bool /*isEnabled*/, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
    {
        g.setColour(Colours::black);
        const AffineTransform trans(AffineTransform::scale(width, height));
        
        Path box;
        box.startNewSubPath(0.0f, 1.0f);
        box.lineTo(0.0f, 0.0f);
        box.lineTo(1.0f, 0.0f);
        g.strokePath(box, PathStrokeType(2.5f), trans);

        if (ticked)
        {
            Path tick;
            tick.startNewSubPath(0.25f, 0.5f);
            tick.lineTo(0.5f, 0.75f);
            tick.lineTo(0.9f, 0.15f);
            g.strokePath(tick, PathStrokeType(2.5f), trans);
        }
    }

    //==============================================================================

private:
	Typeface::Ptr customFont;

};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
