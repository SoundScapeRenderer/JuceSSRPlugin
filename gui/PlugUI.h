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
#include "panels/PanelBase.h"
#include "panels/ScenePanel.h"
#include "CustomLookAndFeel.h"
#include "components/OutputLevelComponent.h"
#include "components/ZoomSlider.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    Plugin UI that contains the scene UI, zoomSlider of the scene,
    serialization buttons and output levels (left/right channel).
                                                                    //[/Comments]
*/
class PlugUI  : public PanelBase,
                public SliderListener,
                public ButtonListener
{
public:
    //==============================================================================
    PlugUI (SynthParams &p);
    ~PlugUI();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    /**
     * Resize scene UI panel, use this function whenever zoomFactor has been changed.
     */
    void resizeScenePanel();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SynthParams &params;
    ScopedPointer<CustomLookAndFeel> lnf;

    void timerCallback() override;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ScenePanel> scene;
    ScopedPointer<Label> debugText;
    ScopedPointer<OutputLevelComponent> outputLevel;
    ScopedPointer<ZoomSlider> zoomSlider;
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<TextButton> saveButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlugUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_17F31DC76882C8CC__
