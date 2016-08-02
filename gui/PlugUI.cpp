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
#define DEBUG_PARAMS 0
//[/MiscUserDefs]

//==============================================================================
PlugUI::PlugUI (SynthParams &p)
    : PanelBase(p), params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimerHz (60);
    //[/Constructor_pre]

    addAndMakeVisible (gainSlider = new GainLevelSlider ("gain slider"));
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

    addAndMakeVisible (source = new SourceComponent (params));
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

    addAndMakeVisible (listener = new ListenerComponent (params));
    listener->setName ("listener");

    addAndMakeVisible (debugText = new Label ("debug",
                                              TRANS("Debug:")));
    debugText->setFont (Font (15.00f, Font::plain));
    debugText->setJustificationType (Justification::topLeft);
    debugText->setEditable (false, false, false);
    debugText->setColour (TextEditor::textColourId, Colours::black);
    debugText->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    // default settings for child components
    orientationSlider->setValue(90.0);
    gainSlider->setValue(-6.0);

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
    ssrLogo = ImageCache::getFromMemory(BinaryData::ssr_logo_large_png, BinaryData::ssr_logo_large_pngSize);

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

    gainSlider = nullptr;
    orientationSlider = nullptr;
    label2 = nullptr;
    source = nullptr;
    levelMeterLeft = nullptr;
    levelMeterRight = nullptr;
    listener = nullptr;
    debugText = nullptr;


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
    g.drawImageWithin(ssrLogo, 0 + 15, getHeight() - ssrLogo.getHeight() / 3 - 15, ssrLogo.getWidth() / 3, ssrLogo.getHeight() / 3, RectanglePlacement::centred);
    //[/UserPaint]
}

void PlugUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    gainSlider->setBounds (413, 191, 75, 28);
    orientationSlider->setBounds (16, 48, 80, 80);
    label2->setBounds (16, 16, 80, 24);
    source->setBounds (405, 95, 90, 90);
    levelMeterLeft->setBounds (824, 150, 24, 300);
    levelMeterRight->setBounds (856, 150, 24, 300);
    listener->setBounds (400, 250, 100, 100);
    debugText->setBounds (648, 8, 250, 584);
    //[UserResized] Add your own custom resize handling here..
    // draw components at their position
    juce::Point<int> pixSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    source->setBounds(pixSource.x - source->getWidth() / 2, pixSource.y - source->getHeight() / 2, source->getWidth(), source->getHeight());

    juce::Point<int> pixRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
    listener->setBounds(pixRef.x - listener->getWidth() / 2, pixRef.y - listener->getHeight() / 2, listener->getWidth(), listener->getHeight());
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
        params.sourceGain.setUI(val);
        //[/UserSliderCode_gainSlider]
    }
    else if (sliderThatWasMoved == orientationSlider)
    {
        //[UserSliderCode_orientationSlider] -- add your slider handling code here..
        params.sourceOrientation.setUI(val);
        //[/UserSliderCode_orientationSlider]
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::childBoundsChanged(Component *child)
{
    // gainSlider should always follow source node
    if (child == source)
    {
        int offsetX = source->getX() + (source->getWidth() - gainSlider->getWidth()) / 2;
        int offsetY = source->getY() + source->getHeight() + 5;
        gainSlider->setBounds(offsetX, offsetY, gainSlider->getWidth(), gainSlider->getHeight());
    }
}

void PlugUI::timerCallback()
{
    gainSlider->setGainLevel(params.sourceLevel.get());

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

#if DEBUG_PARAMS 1
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

        "\n\nZoomfactor = " + String(params.zoomFactor.get()) +
        "\nDistX = " + String(params.sourceX.get() - params.referenceX.get()) +
        "\nDistY = " + String(params.sourceY.get() - params.referenceY.get())
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
  <BACKGROUND backgroundColour="ffedede6"/>
  <SLIDER name="gain slider" id="69ace909b58289b9" memberName="gainSlider"
          virtualName="GainLevelSlider" explicitFocusOrder="0" pos="413 191 75 28"
          min="-96" max="12" int="0" style="LinearBar" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="3"/>
  <SLIDER name="orientation slider" id="d65ca37ac19fdb1e" memberName="orientationSlider"
          virtualName="" explicitFocusOrder="0" pos="16 48 80 80" min="0"
          max="360" int="0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="fa1442bff5dd15a0" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="16 16 80 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Orientation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <GENERICCOMPONENT name="source" id="7b4082301ad63f28" memberName="source" virtualName="SourceComponent"
                    explicitFocusOrder="0" pos="405 95 90 90" class="Component" params="params"/>
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
  <GENERICCOMPONENT name="listener" id="a34b6db6e6ed2361" memberName="listener" virtualName="ListenerComponent"
                    explicitFocusOrder="0" pos="400 250 100 100" class="Component"
                    params="params"/>
  <LABEL name="debug" id="3b44d9ef5ee9c1a" memberName="debugText" virtualName=""
         explicitFocusOrder="0" pos="648 8 250 584" edTextCol="ff000000"
         edBkgCol="0" labelText="Debug:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
