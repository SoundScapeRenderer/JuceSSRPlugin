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

    addAndMakeVisible (gainSlider = new Slider ("gain slider"));
    gainSlider->setRange (-96, 12, 0);
    gainSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    gainSlider->addListener (this);
    gainSlider->setSkewFactor (2.5);

    addAndMakeVisible (xPos = new Slider ("x pos"));
    xPos->setRange (-2, 2, 0);
    xPos->setSliderStyle (Slider::LinearHorizontal);
    xPos->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    xPos->addListener (this);

    addAndMakeVisible (yPos = new Slider ("y pos"));
    yPos->setRange (-2, 2, 0);
    yPos->setSliderStyle (Slider::LinearVertical);
    yPos->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    yPos->addListener (this);

    addAndMakeVisible (orientationSlider = new Slider ("orientation slider"));
    orientationSlider->setRange (0, 360, 0);
    orientationSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    orientationSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    orientationSlider->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Gain")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("Orientation")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centred);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (muteToggle = new ToggleButton ("mute toggle"));
    muteToggle->setButtonText (TRANS("Mute"));
    muteToggle->addListener (this);

    addAndMakeVisible (planeSrcToggle = new ToggleButton ("plane src toggle"));
    planeSrcToggle->setButtonText (TRANS("Plane Src"));
    planeSrcToggle->addListener (this);

    addAndMakeVisible (inputChannelSlider = new Slider ("input channel slider"));
    inputChannelSlider->setRange (0, 1, 1);
    inputChannelSlider->setSliderStyle (Slider::LinearHorizontal);
    inputChannelSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    inputChannelSlider->addListener (this);

    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Input Channel")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centred);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    xPos->setValue(0.0);
    yPos->setValue(0.0);
    gainSlider->setValue(-6.0);
    orientationSlider->setValue(90.0);
    muteToggle->setToggleState(false, false);
    planeSrcToggle->setToggleState(false, false);

    inputChannelSlider->setValue(0.0);
    //[/UserPreSize]

    setSize (900, 600);


    //[Constructor] You can add your own custom stuff here..
    listenerImg = ImageCache::getFromMemory(BinaryData::listener_png, BinaryData::listener_pngSize);
    listenerBackgroundImg = ImageCache::getFromMemory(BinaryData::listener_background_png, BinaryData::listener_background_pngSize);
    listenerShadowImg = ImageCache::getFromMemory(BinaryData::listener_shadow_png, BinaryData::listener_shadow_pngSize);
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gainSlider = nullptr;
    xPos = nullptr;
    yPos = nullptr;
    orientationSlider = nullptr;
    label = nullptr;
    label2 = nullptr;
    muteToggle = nullptr;
    planeSrcToggle = nullptr;
    inputChannelSlider = nullptr;
    label3 = nullptr;


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

    gainSlider->setBounds (16, 88, 80, 80);
    xPos->setBounds (360, 352, 200, 60);
    yPos->setBounds (432, 144, 60, 200);
    orientationSlider->setBounds (16, 208, 80, 80);
    label->setBounds (16, 56, 80, 24);
    label2->setBounds (16, 176, 80, 24);
    muteToggle->setBounds (16, 320, 80, 24);
    planeSrcToggle->setBounds (16, 16, 80, 24);
    inputChannelSlider->setBounds (24, 384, 64, 24);
    label3->setBounds (8, 352, 96, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlugUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    float val = static_cast<float>(sliderThatWasMoved->getValue());
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        params.gain.set(Param::fromDb(val));
        //[/UserSliderCode_gainSlider]
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
    else if (sliderThatWasMoved == orientationSlider)
    {
        //[UserSliderCode_orientationSlider] -- add your slider handling code here..
        params.orientation.set(val);
        //[/UserSliderCode_orientationSlider]
    }
    else if (sliderThatWasMoved == inputChannelSlider)
    {
        //[UserSliderCode_inputChannelSlider] -- add your slider handling code here..
        params.inputChannel.set(val);
        //[/UserSliderCode_inputChannelSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PlugUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    bool isOn = buttonThatWasClicked->getToggleState();
    eOnOffState state;

    isOn ? state = eOnOffState::eOn : state = eOnOffState::eOff;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == muteToggle)
    {
        //[UserButtonCode_muteToggle] -- add your button handler code here..
        params.isSrcMuted.setStep(state);
        //[/UserButtonCode_muteToggle]
    }
    else if (buttonThatWasClicked == planeSrcToggle)
    {
        //[UserButtonCode_planeSrcToggle] -- add your button handler code here..
        params.isPlaneSrc.setStep(state);
        //[/UserButtonCode_planeSrcToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
                 initialWidth="900" initialHeight="600">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="gain slider" id="69ace909b58289b9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="16 88 80 80" min="-96"
          max="12" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="2.5"/>
  <SLIDER name="x pos" id="9a28c05ae381351" memberName="xPos" virtualName=""
          explicitFocusOrder="0" pos="360 352 200 60" min="-2" max="2"
          int="0" style="LinearHorizontal" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="y pos" id="4f21307348cde0da" memberName="yPos" virtualName=""
          explicitFocusOrder="0" pos="432 144 60 200" min="-2" max="2"
          int="0" style="LinearVertical" textBoxPos="TextBoxBelow" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="orientation slider" id="d65ca37ac19fdb1e" memberName="orientationSlider"
          virtualName="" explicitFocusOrder="0" pos="16 208 80 80" min="0"
          max="360" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="64186e2419f165e2" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 56 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="new label" id="fa1442bff5dd15a0" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 176 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Orientation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="mute toggle" id="25e29b2a85486a90" memberName="muteToggle"
                virtualName="" explicitFocusOrder="0" pos="16 320 80 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="plane src toggle" id="91e73a52b50b9eeb" memberName="planeSrcToggle"
                virtualName="" explicitFocusOrder="0" pos="16 16 80 24" buttonText="Plane Src"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="input channel slider" id="56250486a01f94b3" memberName="inputChannelSlider"
          virtualName="" explicitFocusOrder="0" pos="24 384 64 24" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8b1a44246391bae1" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="8 352 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Channel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
