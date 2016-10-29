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

/**
 * Nothing but custom drawing functions for JUCE components and replacing fonts.
 */
class CustomLookAndFeel : public LookAndFeel_V1
{
public:
    //==============================================================================

    CustomLookAndFeel() : LookAndFeel_V1()
    {
        customFont = Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansMono_ttf, BinaryData::DejaVuSansMono_ttfSize);
    }
    virtual ~CustomLookAndFeel()
    {
    }
    
    /**
     * Very important!!! LookAndFeel_V1 crashes sometimes due to slider's drop shadow effect
     * so do not use it.
     * Crash happens a lot when more than one instance of the plugin is used 
     * and an editor is opened or closed while at least one other editor is already opened.
     * Shadow effect works only occasionally, anyways.
     */
    ImageEffectFilter* getSliderEffect(Slider& s)
    {
        ignoreUnused(s);
        return nullptr;
    }

    //==============================================================================

    Typeface::Ptr getTypefaceForFont(const Font & font)
    {
        ignoreUnused(font);
        return customFont;
    }

    //==============================================================================

    void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown)
    {
        ignoreUnused(backgroundColour);

        float width = static_cast<float>(button.getWidth());
        float height = static_cast<float>(button.getHeight());

        g.fillAll(isButtonDown? Colours::white.darker(0.1f) :
            isMouseOverButton? Colours::white.darker(0.025f) : Colours::white);
        g.setColour(Colours::grey.brighter());
        g.drawRect(0.0f, 0.0f, width, height, 0.5f);
    }

    Font getTextButtonFont(TextButton&, int buttonHeight)
    {
        return Font(buttonHeight * 0.75f);
    }

    //==============================================================================

    void drawTickBox(Graphics &g, Component &c, float x, float y, float width, float height,
                     bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
    {
        ignoreUnused(c, x, y);
        ignoreUnused(isEnabled, isMouseOverButton, isButtonDown);

        g.setColour(Colours::black);
        AffineTransform trans(AffineTransform::scale(width, height));

        // draw tickbox shadow only
        Path box;
        box.startNewSubPath(0.0f, 1.0f);
        box.lineTo(0.0f, 0.0f);
        box.lineTo(1.0f, 0.0f);
        g.strokePath(box, PathStrokeType(3.0f), trans);

        // draw tick if toggle is active
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

    void drawComboBox(Graphics& g, int width, int height, bool isButtonDown,
                      int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box)
    {
        // draw combobox background and outline
        g.fillAll(Colours::white);
        if (box.hasKeyboardFocus(false))
        {
            g.setColour(box.findColour(ComboBox::buttonColourId));
            g.drawRect(0, 0, width, height, 2);
        }
        else
        {
            g.setColour(Colours::grey);
            g.drawRect(0, 0, width, height);
        }

        // draw box with arrow to open drop down selector
        float outlineThickness = isButtonDown ? 1.2f : 0.5f;
        buttonW = jmin(height * 5 / 4, width * 7 / 8) - static_cast<int>(outlineThickness * 2);
        buttonX = width - buttonW;

        g.setColour(Colours::lightgrey.brighter(0.2f));
        g.fillRect(buttonX + outlineThickness, buttonY + outlineThickness,
                   buttonW - outlineThickness, buttonH - outlineThickness * 2.0f);

        Path p;
        p.addTriangle(buttonX + buttonW * 0.25f, buttonY + buttonH * 0.35f,
                      buttonX + buttonW * 0.75f, buttonY + buttonH * 0.35f,
                      buttonX + buttonW * 0.5f, buttonY + buttonH * 0.65f);
        g.setColour(box.isEnabled()? Colours::black : Colours::grey);
        g.fillPath(p);

        // draw drop down button shadow
        AffineTransform trans(AffineTransform::scale(static_cast<float>(buttonW), static_cast<float>(buttonH)));
        trans = trans.translated(static_cast<float>(buttonX), static_cast<float>(buttonY));
        Path shadow;
        shadow.startNewSubPath(0.0f, 1.0f);
        shadow.lineTo(1.0f, 1.0f);
        shadow.lineTo(1.0f, 0.0f);
        g.strokePath(shadow, PathStrokeType(3.0f), trans);
    }

    //==============================================================================

    void drawPopupMenuBackground(Graphics& g, int width, int height)
    {
        g.fillAll(Colours::white);

#if ! JUCE_MAC
        g.setColour(findColour(PopupMenu::textColourId).withAlpha(0.6f));
        g.drawRect(0, 0, width, height);
#endif
    }

    //==============================================================================

private:
    Typeface::Ptr customFont;
};

#endif  // CUSTOMLOOKANDFEEL_H_INCLUDED
