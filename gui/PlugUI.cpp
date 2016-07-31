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
#define LEVELMETER 0
//[/MiscUserDefs]

//==============================================================================
PlugUI::PlugUI (SynthParams &p)
    : PanelBase(p), params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimerHz (60);
    //[/Constructor_pre]

    addAndMakeVisible (listenerBackground = new ImageComponent());
    listenerBackground->setName ("listener background");

    addAndMakeVisible (listener = new ImageComponent());
    listener->setName ("listener");

    addAndMakeVisible (gainSlider = new Slider ("gain slider"));
    gainSlider->setRange (-96, 12, 0);
    gainSlider->setSliderStyle (Slider::LinearBar);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->addListener (this);
    gainSlider->setSkewFactor (3);

    addAndMakeVisible (orientationSlider = new Slider ("orientation slider"));
    orientationSlider->setRange (0, 360, 0);
    orientationSlider->setSliderStyle (Slider::RotaryVerticalDrag);
    orientationSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 20);
    orientationSlider->addListener (this);

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

    addAndMakeVisible (source = new SourceComponent (params, SynthParams::sourceColourBlue));
    source->setName ("source");

    addAndMakeVisible (levelMeterLeft = new Slider ("level left"));
    levelMeterLeft->setRange (-0.2, 1, 0);
    levelMeterLeft->setSliderStyle (Slider::LinearVertical);
    levelMeterLeft->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    levelMeterLeft->setColour (Slider::thumbColourId, Colour (0xff60ff60));
    levelMeterLeft->addListener (this);
    levelMeterLeft->setSkewFactor (0.7);

    addAndMakeVisible (levelMeterRight = new Slider ("level right"));
    levelMeterRight->setRange (-0.2, 1, 0);
    levelMeterRight->setSliderStyle (Slider::LinearVertical);
    levelMeterRight->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    levelMeterRight->setColour (Slider::thumbColourId, Colour (0xff60ff60));
    levelMeterRight->addListener (this);
    levelMeterRight->setSkewFactor (0.7);


    //[UserPreSize]
    this->setWantsKeyboardFocus(true);

    // default settings for child components
    orientationSlider->setValue(90.0);
    muteToggle->setToggleState(false, false);
    planeSrcToggle->setToggleState(false, false);
    inputChannelSlider->setValue(0.0);

    gainSlider->setValue(-6.0);
    gainSlider->setColour(Slider::thumbColourId, SynthParams::sourceLevelColour);
    gainSlider->setColour(Slider::textBoxOutlineColourId, SynthParams::sourceColourBlue);
    gainSlider->setAlwaysOnTop(true);

    source->setAlwaysOnTop(true);
    source->registerGainSlider(gainSlider);

#if LEVELMETER 1
    levelMeterLeft->setSliderStyle(Slider::LinearBarVertical);
    levelMeterRight->setSliderStyle(Slider::LinearBarVertical);
#else
    levelMeterLeft->setVisible(false);
    levelMeterRight->setVisible(false);
#endif
    //[/UserPreSize]

    setSize (900, 600);


    //[Constructor] You can add your own custom stuff here..
    // load images
    listenerImg = ImageCache::getFromMemory(BinaryData::listener_png, BinaryData::listener_pngSize);
    listenerBackgroundImg = ImageCache::getFromMemory(BinaryData::listener_background_png, BinaryData::listener_background_pngSize);
    listenerShadowImg = ImageCache::getFromMemory(BinaryData::listener_shadow_png, BinaryData::listener_shadow_pngSize);
    ssrLogo = ImageCache::getFromMemory(BinaryData::ssr_logo_large_png, BinaryData::ssr_logo_large_pngSize);

    listener->setImage(listenerImg);
    listener->setTransform(AffineTransform::rotation(degreesToRadians(-90.0f),
        listener->getX() + listener->getWidth() / 2, listener->getY() + listener->getHeight() / 2));
    listener->setWantsKeyboardFocus(true);

    listenerBackground->setImage(listenerShadowImg);
    listenerBackground->setTransform(AffineTransform::rotation(degreesToRadians(-90.0f),
        listenerBackground->getX() + listenerBackground->getWidth() / 2, listenerBackground->getY() + listenerBackground->getHeight() / 2));
    listenerBackground->setWantsKeyboardFocus(true);

    // set new design for some components
    lnf = new CustomLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(lnf);
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    lnf = nullptr;
    //[/Destructor_pre]

    listenerBackground = nullptr;
    listener = nullptr;
    gainSlider = nullptr;
    orientationSlider = nullptr;
    label2 = nullptr;
    muteToggle = nullptr;
    planeSrcToggle = nullptr;
    inputChannelSlider = nullptr;
    label3 = nullptr;
    source = nullptr;
    levelMeterLeft = nullptr;
    levelMeterRight = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlugUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffedede6));

    //[UserPaint] Add your own custom painting code here..
    g.drawImageWithin(ssrLogo, 0 + 15, getHeight() - ssrLogo.getHeight() / 2 - 15, ssrLogo.getWidth() / 2, ssrLogo.getHeight() / 2, RectanglePlacement::centred);
    //[/UserPaint]
}

void PlugUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    listenerBackground->setBounds (391, 242, 128, 128);
    listener->setBounds (400, 250, 100, 100);
    gainSlider->setBounds (416, 192, 75, 16);
    orientationSlider->setBounds (24, 88, 80, 80);
    label2->setBounds (24, 56, 80, 24);
    muteToggle->setBounds (24, 200, 80, 24);
    planeSrcToggle->setBounds (24, 24, 80, 24);
    inputChannelSlider->setBounds (32, 264, 64, 24);
    label3->setBounds (16, 232, 96, 24);
    source->setBounds (408, 96, 90, 90);
    levelMeterLeft->setBounds (824, 150, 24, 300);
    levelMeterRight->setBounds (856, 150, 24, 300);
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
        params.sourceGain.setUI(Param::fromDb(val));
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == orientationSlider)
    {
        //[UserSliderCode_orientationSlider] -- add your slider handling code here..
        params.sourceOrientation.setUI(val);
        //[/UserSliderCode_orientationSlider]
    }
    else if (sliderThatWasMoved == inputChannelSlider)
    {
        //[UserSliderCode_inputChannelSlider] -- add your slider handling code here..
        params.inputChannel.set(val);
        //[/UserSliderCode_inputChannelSlider]
    }
    else if (sliderThatWasMoved == levelMeterLeft)
    {
        //[UserSliderCode_levelMeterLeft] -- add your slider handling code here..
        //[/UserSliderCode_levelMeterLeft]
    }
    else if (sliderThatWasMoved == levelMeterRight)
    {
        //[UserSliderCode_levelMeterRight] -- add your slider handling code here..
        //[/UserSliderCode_levelMeterRight]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PlugUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    bool isOn = buttonThatWasClicked->getToggleState();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == muteToggle)
    {
        //[UserButtonCode_muteToggle] -- add your button handler code here..
        params.sourceMute.setStep(isOn ? eOnOffState::eOn : eOnOffState::eOff);
        //[/UserButtonCode_muteToggle]
    }
    else if (buttonThatWasClicked == planeSrcToggle)
    {
        //[UserButtonCode_planeSrcToggle] -- add your button handler code here..
        params.isSourceTypePlane.setStep(isOn ? eSourceType::ePlane : eSourceType::ePoint);
        //[/UserButtonCode_planeSrcToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::childBoundsChanged(Component *child)
{
    if (child == source)
    {
        int offsetX = source->getX() + (source->getWidth() - gainSlider->getWidth()) / 2;
        int offsetY = source->getY() + source->getHeight() + 5;
        gainSlider->setBounds(offsetX, offsetY, gainSlider->getWidth(), gainSlider->getHeight());
    }
}

void PlugUI::timerCallback()
{
#if LEVELMETER 1
    // get current gui and audio level
    double guiLevelLeft = levelMeterLeft->getValue();
    double guiLevelRight = levelMeterRight->getValue();
    float audioLevelLeft = params.levelLeft.get();
    float audioLevelRight = params.levelRight.get();
    double dropSpeed = 0.00001;

    // refresh level meter values
    if (audioLevelLeft > guiLevelLeft)
    {
            levelMeterLeft->setValue(audioLevelLeft);
    }
    else
    {
        if (guiLevelLeft - dropSpeed> 0.0)
        {
            levelMeterLeft->setValue(jmin(guiLevelLeft - dropSpeed, -1.0), dontSendNotification);
        }
        else
        {
            levelMeterLeft->setValue(0.0, dontSendNotification);
        }
    }

    if (audioLevelRight > guiLevelRight)
    {
        levelMeterRight->setValue(audioLevelRight, dontSendNotification);
    }
    else
    {
        if (guiLevelRight - dropSpeed > 0.0)
        {
            levelMeterRight->setValue(jmin(guiLevelRight - dropSpeed, -1.0), dontSendNotification);
        }
        else
        {
            levelMeterRight->setValue(0.0);
        }
    }
#endif
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlugUI" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p"
                 variableInitialisers="PanelBase(p), params(p)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="900" initialHeight="600">
  <BACKGROUND backgroundColour="ffedede6"/>
  <GENERICCOMPONENT name="listener background" id="28146762f36cc5a3" memberName="listenerBackground"
                    virtualName="ImageComponent" explicitFocusOrder="0" pos="391 242 128 128"
                    class="Component" params=""/>
  <GENERICCOMPONENT name="listener" id="7502391df768a172" memberName="listener" virtualName="ImageComponent"
                    explicitFocusOrder="0" pos="400 250 100 100" class="Component"
                    params=""/>
  <SLIDER name="gain slider" id="69ace909b58289b9" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="416 192 75 16" min="-96"
          max="12" int="0" style="LinearBar" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="orientation slider" id="d65ca37ac19fdb1e" memberName="orientationSlider"
          virtualName="" explicitFocusOrder="0" pos="24 88 80 80" min="0"
          max="360" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fa1442bff5dd15a0" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="24 56 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Orientation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <TOGGLEBUTTON name="mute toggle" id="25e29b2a85486a90" memberName="muteToggle"
                virtualName="" explicitFocusOrder="0" pos="24 200 80 24" buttonText="Mute"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="plane src toggle" id="91e73a52b50b9eeb" memberName="planeSrcToggle"
                virtualName="" explicitFocusOrder="0" pos="24 24 80 24" buttonText="Plane Src"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <SLIDER name="input channel slider" id="56250486a01f94b3" memberName="inputChannelSlider"
          virtualName="" explicitFocusOrder="0" pos="32 264 64 24" min="0"
          max="1" int="1" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="8b1a44246391bae1" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="16 232 96 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Input Channel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <GENERICCOMPONENT name="source" id="7b4082301ad63f28" memberName="source" virtualName="SourceComponent"
                    explicitFocusOrder="0" pos="408 96 90 90" class="Component" params="params, SynthParams::sourceColourBlue"/>
  <SLIDER name="level left" id="13e0962dc81dca1" memberName="levelMeterLeft"
          virtualName="" explicitFocusOrder="0" pos="824 150 24 300" thumbcol="ff60ff60"
          min="-0.20000000000000001" max="1" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="0.69999999999999996"/>
  <SLIDER name="level right" id="a744d1a2c21ea6d8" memberName="levelMeterRight"
          virtualName="" explicitFocusOrder="0" pos="856 150 24 300" thumbcol="ff60ff60"
          min="-0.20000000000000001" max="1" int="0" style="LinearVertical"
          textBoxPos="NoTextBox" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="0.69999999999999996"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
