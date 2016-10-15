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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    Source menu panel which can be used to do some settings like mute source or
    changing source model. Further, current values of source position,
    orientation etc. are displayed.
    Designed according to SSR's source menu with minor changes.
                                                                    //[/Comments]
*/
class SourceMenuPanel  : public PanelBase,
                         public ComboBoxListener,
                         public ButtonListener
{
public:
    //==============================================================================
    SourceMenuPanel (PluginParams &p, SourceNodeComponent *s);
    ~SourceMenuPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    /**
     * Repaint source node whenever mute state is enabled or disabled.
     */
    void sourceMutedStateChanged();

    /**
     * Lock source position params and repaint source node whenever fixPosition 
     * state is enabled or disabled.
     */
    void sourceFixedPositionStateChanged();

    /**
     * Update visibility of source plane wave, use this whenever source type has
     * been changed.
     */
    void updatePlaneWaveVisibility();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginParams &params;
    SourceNodeComponent *sourceNode;

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
    ScopedPointer<ComboBox> sourceModelBox;
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
