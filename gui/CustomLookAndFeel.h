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
        //customFont = Typeface::createSystemTypefaceFor(BinaryData::world_of_water_ttf, BinaryData::world_of_water_ttfSize);
    }
    virtual ~CustomLookAndFeel()
    {
    }
    //==============================================================================

    Typeface::Ptr getTypefaceForFont(const Font & font)
    {
        //return customFont;
        Font f("Calibri", 14, Font::FontStyleFlags::plain);
        return LookAndFeel_V2::getTypefaceForFont(f);
    }

    //==============================================================================
    
private:
	Typeface::Ptr customFont;

};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
