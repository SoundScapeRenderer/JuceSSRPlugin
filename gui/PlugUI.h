/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.2.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_17F31DC76882C8CC__
#define __JUCE_HEADER_17F31DC76882C8CC__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "SynthParams.h"
#include "panels/PanelBase.h"
#include "CustomLookAndFeel.h"
#include "GainLevelSlider.h"
#include "ListenerComponent.h"
#include "SourceComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PlugUI  : public PanelBase,
                public SliderListener
{
public:
    //==============================================================================
    PlugUI (SynthParams &p);
    ~PlugUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

    /**
        Derived small window class only to implement closeButtonPressed for now.
        In this, we only need to set the window invisible if the close button was pressed.
     */
    class InfoWindow : public DocumentWindow
    {
    public:
        InfoWindow(const String &name, Colour c, int requiredButtons, bool addToDesktop = true) : DocumentWindow(name, c, requiredButtons, addToDesktop) {}

        ~InfoWindow() {}

        virtual void closeButtonPressed() { this->setVisible(false); }
    };

    void childBoundsChanged(Component *child);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SynthParams &params;
    ScopedPointer<CustomLookAndFeel> lnf;

    Image ssrLogo;

    void timerCallback() override;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GainLevelSlider> gainSlider;
    ScopedPointer<SourceComponent> source;
    ScopedPointer<Slider> levelMeterLeft;
    ScopedPointer<Slider> levelMeterRight;
    ScopedPointer<ListenerComponent> listener;
    ScopedPointer<Label> debugText;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlugUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_17F31DC76882C8CC__
