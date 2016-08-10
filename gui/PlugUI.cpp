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
    startTimerHz (60);
    //[/Constructor_pre]

    addAndMakeVisible (zoomLabel = new Label ("zoom label",
                                              TRANS("zoom")));
    zoomLabel->setFont (Font (22.00f, Font::plain));
    zoomLabel->setJustificationType (Justification::centred);
    zoomLabel->setEditable (false, false, false);
    zoomLabel->setColour (TextEditor::textColourId, Colours::black);
    zoomLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (levelMeterRight = new Slider ("level right"));
    levelMeterRight->setRange (0, 1, 0);
    levelMeterRight->setSliderStyle (Slider::LinearVertical);
    levelMeterRight->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    levelMeterRight->setColour (Slider::thumbColourId, Colour (0xff60ff60));
    levelMeterRight->addListener (this);

    addAndMakeVisible (levelMeterLeft = new Slider ("level left"));
    levelMeterLeft->setRange (0, 1, 0);
    levelMeterLeft->setSliderStyle (Slider::LinearVertical);
    levelMeterLeft->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    levelMeterLeft->setColour (Slider::thumbColourId, Colour (0xff60ff60));
    levelMeterLeft->addListener (this);

    addAndMakeVisible (debugText = new Label ("debug",
                                              String::empty));
    debugText->setFont (Font (15.00f, Font::plain));
    debugText->setJustificationType (Justification::topLeft);
    debugText->setEditable (false, false, false);
    debugText->setColour (TextEditor::textColourId, Colours::black);
    debugText->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sourceComponent = new SourceComponent (params, 90, SynthParams::sourceColourBlue));
    sourceComponent->setName ("source component");

    addAndMakeVisible (zoomSlider = new ZoomSlider());
    zoomSlider->setName ("zoom slider");

    addAndMakeVisible (listener = new ListenerComponent (params));
    listener->setName ("listener");

    drawable1 = Drawable::createFromImageData (BinaryData::ssr_logo_png, BinaryData::ssr_logo_pngSize);

    //[UserPreSize]
    zoomSlider->addListener(this);
    zoomSlider->setValue(100.0);
    zoomSlider->setTextValueSuffix(params.zoomFactor.getUnit());

    /// \todo create actual output gain level component
    levelMeterLeft->setSliderStyle(Slider::LinearBarVertical);
    levelMeterLeft->setInterceptsMouseClicks(false, false);
    levelMeterRight->setSliderStyle(Slider::LinearBarVertical);
    levelMeterRight->setInterceptsMouseClicks(false, false);
    debugText->setInterceptsMouseClicks(false, false);
    //[/UserPreSize]

    setSize (900, 600);


    //[Constructor] You can add your own custom stuff here..
    lnf = new CustomLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(lnf);
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    lnf = nullptr;
    //[/Destructor_pre]

    zoomLabel = nullptr;
    levelMeterRight = nullptr;
    levelMeterLeft = nullptr;
    debugText = nullptr;
    sourceComponent = nullptr;
    zoomSlider = nullptr;
    listener = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlugUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffedede6));

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (13, 530, 64, 64),
                               RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlugUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    zoomLabel->setBounds (812, 540, 80, 24);
    levelMeterRight->setBounds (856, 150, 24, 300);
    levelMeterLeft->setBounds (824, 150, 24, 300);
    debugText->setBounds (648, 8, 250, 584);
    sourceComponent->setBounds (0, 0, 900, 600);
    zoomSlider->setBounds (812, 568, 80, 24);
    listener->setBounds (400, 250, 100, 100);
    //[UserResized] Add your own custom resize handling here..
    juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());

    int listenerW = static_cast<int>(listener->getWidth() * params.zoomFactor.get() / 100.0f);
    int listenerH = static_cast<int>(listener->getHeight() * params.zoomFactor.get() / 100.0f);
    listener->setBounds(pixPosRef.x - listenerW / 2, pixPosRef.y - listenerH / 2, listenerW, listenerH);

    sourceComponent->resized();
    //[/UserResized]
}

void PlugUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    float val = static_cast<float>(sliderThatWasMoved->getValue());
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == levelMeterRight)
    {
        //[UserSliderCode_levelMeterRight] -- add your slider handling code here..
        //[/UserSliderCode_levelMeterRight]
    }
    else if (sliderThatWasMoved == levelMeterLeft)
    {
        //[UserSliderCode_levelMeterLeft] -- add your slider handling code here..
        //[/UserSliderCode_levelMeterLeft]
    }

    //[UsersliderValueChanged_Post]
    else if (sliderThatWasMoved == zoomSlider)
    {
        params.zoomFactor.setUI(val);
        resized();
    }
    //[/UsersliderValueChanged_Post]
}

void PlugUI::mouseDoubleClick (const MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
    ignoreUnused(e);
    zoomSlider->setValue(100.0);
    //[/UserCode_mouseDoubleClick]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::childBoundsChanged(Component *child)
{

    if (child == listener)
    {
        // refresh plane wave of source background
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
        juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
        float angle = pixPosRef.getAngleToPoint(pixPosSource);
        sourceComponent->refreshBackground(radiansToDegrees(angle), params.sourceType.getStep() == eSourceType::ePlane);
    }
}

void PlugUI::timerCallback()
{
    sourceComponent->refreshGainLevel(params.sourceLevel.get());

    levelMeterLeft->setValue(params.outputLevelLeft.get(), dontSendNotification);
    levelMeterRight->setValue(params.outputLevelRight.get(), dontSendNotification);

#if 1
    debugText->setText(
        "SourceX = " + String(params.sourceX.get()) +
        "\nSourceY = " + String(params.sourceY.get()) +
        "\nSourceOri = " + String(params.sourceOrientation.get()) +
        "\nSourceGain = " + String(params.sourceGain.get()) +
        "\nSourceLevel = " + String(params.sourceLevel.get()) +
        "\nSourceMute = " + String(params.sourceMute.getUIString()) +
        "\nSourceType = " + String(params.sourceType.getUIString()) +

        "\n\nRefX = " + String(params.referenceX.get()) +
        "\nRefY = " + String(params.referenceY.get()) +
        "\nRefOri = " + String(params.referenceOrientation.get()) +
        "\nAmpliRefDist = " + String(params.amplitudeReferenceDistance.get()) +

        "\n\nInputChannel = " + String(params.inputChannel.getUIString()) +
        "\nOutputLevelLeft = " + String(params.outputLevelLeft.get()) +
        "\nOutputLevelRight = " + String(params.outputLevelRight.get()) +

        "\n\nZoomfactor = " + String(params.zoomFactor.get())
        , dontSendNotification);
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
  <METHODS>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffedede6">
    <IMAGE pos="13 530 64 64" resource="BinaryData::ssr_logo_png" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <LABEL name="zoom label" id="425995adac828d4e" memberName="zoomLabel"
         virtualName="" explicitFocusOrder="0" pos="812 540 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="zoom" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="22"
         bold="0" italic="0" justification="36"/>
  <SLIDER name="level right" id="a744d1a2c21ea6d8" memberName="levelMeterRight"
          virtualName="" explicitFocusOrder="0" pos="856 150 24 300" thumbcol="ff60ff60"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="level left" id="13e0962dc81dca1" memberName="levelMeterLeft"
          virtualName="" explicitFocusOrder="0" pos="824 150 24 300" thumbcol="ff60ff60"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="debug" id="3b44d9ef5ee9c1a" memberName="debugText" virtualName=""
         explicitFocusOrder="0" pos="648 8 250 584" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="9"/>
  <GENERICCOMPONENT name="source component" id="3a94749bbf0b0aa6" memberName="sourceComponent"
                    virtualName="" explicitFocusOrder="0" pos="0 0 900 600" class="SourceComponent"
                    params="params, 90, SynthParams::sourceColourBlue"/>
  <GENERICCOMPONENT name="zoom slider" id="e94c3a78f0b8bd9a" memberName="zoomSlider"
                    virtualName="" explicitFocusOrder="0" pos="812 568 80 24" class="ZoomSlider"
                    params=""/>
  <GENERICCOMPONENT name="listener" id="a34b6db6e6ed2361" memberName="listener" virtualName="ListenerComponent"
                    explicitFocusOrder="0" pos="400 250 100 100" class="Component"
                    params="params"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
