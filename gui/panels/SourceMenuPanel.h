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

#ifndef __JUCE_HEADER_3862032697A0F124__
#define __JUCE_HEADER_3862032697A0F124__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"

#include "PanelBase.h"
#include "SynthParams.h"
#include "SourceComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SourceMenuPanel  : public PanelBase,
                         public ComboBoxListener,
                         public ButtonListener
{
public:
    //==============================================================================
    SourceMenuPanel (SynthParams &p, SourceComponent *s);
    ~SourceMenuPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SynthParams &params;
    SourceComponent *source;

    void timerCallback() override;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> positionLabel;
    ScopedPointer<Label> distanceLabel;
    ScopedPointer<Label> azimuthLabel;
    ScopedPointer<Label> fixLabel;
    ScopedPointer<Label> volLabel;
    ScopedPointer<Label> muteLabel;
    ScopedPointer<Label> modelLabel;
    ScopedPointer<Label> inputLabel;
    ScopedPointer<ComboBox> inputBox;
    ScopedPointer<ComboBox> modelBox;
    ScopedPointer<ToggleButton> muteToggle;
    ScopedPointer<ToggleButton> fixToggle;
    ScopedPointer<Label> volLabel2;
    ScopedPointer<Label> azimuthLabel2;
    ScopedPointer<Label> distanceLabel2;
    ScopedPointer<Label> positionLabel2;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceMenuPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_3862032697A0F124__
