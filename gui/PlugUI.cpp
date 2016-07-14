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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PlugUI.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlugUI::PlugUI (SynthParams &p)
    : PanelBase(p), params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimerHz (30);
    //[/Constructor_pre]

    addAndMakeVisible (slider = new Slider ("new slider"));
    slider->setRange (0, 1, 0.1);
    slider->setSliderStyle (Slider::RotaryVerticalDrag);
    slider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    slider->addListener (this);

    addAndMakeVisible (xPos = new Slider ("x pos"));
    xPos->setRange (-1, 1, 0.1);
    xPos->setSliderStyle (Slider::LinearHorizontal);
    xPos->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    xPos->addListener (this);

    addAndMakeVisible (yPos = new Slider ("y pos"));
    yPos->setRange (-1, 1, 0.1);
    yPos->setSliderStyle (Slider::LinearVertical);
    yPos->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    yPos->addListener (this);


    //[UserPreSize]
    slider->setValue(0.7);
    xPos->setValue(0.0);
    yPos->setValue(0.0);
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    //lnf = new CustomLookAndFeel();
    //LookAndFeel::setDefaultLookAndFeel(lnf);
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;
    xPos = nullptr;
    yPos = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlugUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlugUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    slider->setBounds (8, 8, 80, 80);
    xPos->setBounds (110, 270, 200, 60);
    yPos->setBounds (180, 50, 60, 200);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlugUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    float val = static_cast<float>(sliderThatWasMoved->getValue());
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider)
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        params.masterVol.set(val);
        //[/UserSliderCode_slider]
    }
    else if (sliderThatWasMoved == xPos)
    {
        //[UserSliderCode_xPos] -- add your slider handling code here..
        params.xPos.set(val);
        //[/UserSliderCode_xPos]
    }
    else if (sliderThatWasMoved == yPos)
    {
        //[UserSliderCode_yPos] -- add your slider handling code here..
        params.yPos.set(val);
        //[/UserSliderCode_yPos]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::timerCallback()
{

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlugUI" componentName=""
                 parentClasses="public PanelBase, public TextEditorListener" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p), params(p)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="new slider" id="69ace909b58289b9" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="8 8 80 80" min="0" max="1" int="0.10000000000000001"
          style="RotaryVerticalDrag" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="x pos" id="9a28c05ae381351" memberName="xPos" virtualName=""
          explicitFocusOrder="0" pos="110 270 200 60" min="-1" max="1"
          int="0.10000000000000001" style="LinearHorizontal" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="y pos" id="4f21307348cde0da" memberName="yPos" virtualName=""
          explicitFocusOrder="0" pos="180 50 60 200" min="-1" max="1" int="0.10000000000000001"
          style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
