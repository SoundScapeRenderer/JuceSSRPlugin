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

#ifndef __JUCE_HEADER_ED666CC7E31F9094__
#define __JUCE_HEADER_ED666CC7E31F9094__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"

#include "PluginAudioProcessor.h"
#include "PanelBase.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    Configuration panel used for global settings e.g. rendering algorithm,
    IR file or amplitude reference distance. This panel is not finished yet
    since many configuration options are still not implemented.
                                                                    //[/Comments]
*/
class ConfigPanel  : public PanelBase,
                     public SliderListener,
                     public ComboBoxListener
{
public:
    //==============================================================================
    ConfigPanel (PluginAudioProcessor &p);
    ~ConfigPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PluginAudioProcessor &processor; //!< plugin processor
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> ampRefDistanceSlider;
    ScopedPointer<Label> ampRefLabel;
    ScopedPointer<Label> rendererLabel;
    ScopedPointer<ComboBox> rendererAlgorithmBox;
    ScopedPointer<Label> IRFileLabel;
    ScopedPointer<ComboBox> IRFileBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_ED666CC7E31F9094__
