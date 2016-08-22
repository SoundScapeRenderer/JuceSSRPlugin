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
#include "ListenerComponent.h"
#include "ListenerBackgroundComponent.h"
#include "SourceNodeComponent.h"
#include "SourceBackgroundComponent.h"
#include "VolLevelSlider.h"
#include "ZoomSlider.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
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
    void childBoundsChanged(Component *child);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void buttonClicked (Button* buttonThatWasClicked);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);
    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    SynthParams &params;
    ScopedPointer<CustomLookAndFeel> lnf;
    Image plusImg; //< http://iconmonstr.com/

    Point<float> dragStartOffset = Point<float>(0.0f, 0.0f);

    void timerCallback() override;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> debugText;
    ScopedPointer<Slider> levelMeterRight;
    ScopedPointer<Slider> levelMeterLeft;
    ScopedPointer<ListenerBackgroundComponent> listenerBackground;
    ScopedPointer<ListenerComponent> listener;
    ScopedPointer<VolLevelSlider> sourceVolSlider;
    ScopedPointer<SourceBackgroundComponent> sourceBackground;
    ScopedPointer<DocumentWindow> sourceMenu;
    ScopedPointer<SourceNodeComponent> sourceNode;
    ScopedPointer<ImageComponent> refPoint;
    ScopedPointer<ZoomSlider> zoomSlider;
    ScopedPointer<TextButton> saveButton;
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<Drawable> drawable1;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlugUI)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_17F31DC76882C8CC__
