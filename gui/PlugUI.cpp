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
#include "panels/SourceMenuPanel.h"
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

    addAndMakeVisible (debugText = new Label ("debug",
                                              String::empty));
    debugText->setFont (Font (15.00f, Font::plain));
    debugText->setJustificationType (Justification::topLeft);
    debugText->setEditable (false, false, false);
    debugText->setColour (TextEditor::textColourId, Colours::black);
    debugText->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (listener = new ListenerComponent (params));
    listener->setName ("listener");

    addAndMakeVisible (gainSlider = new GainLevelSlider ("gain slider"));
    gainSlider->setRange (-96, 12, 0);
    gainSlider->setSliderStyle (Slider::LinearBar);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->addListener (this);
    gainSlider->setSkewFactor (3);

    addAndMakeVisible (sourceBackground = new SourceBackgroundComponent());
    sourceBackground->setName ("source background");

    addAndMakeVisible (sourceMenu = new DocumentWindow ("source menu", Colours::white, DocumentWindow::closeButton));
    sourceMenu->setName ("source menu");

    addAndMakeVisible (source = new SourceComponent (params));
    source->setName ("source");

    drawable1 = Drawable::createFromImageData (BinaryData::ssr_logo_png, BinaryData::ssr_logo_pngSize);

    //[UserPreSize]
    sourceMenu->setTitleBarHeight(0);
    sourceMenu->setContentOwned(new SourceMenuPanel(params, source), true);
    sourceMenu->setVisible(false);
    sourceMenu->setAlwaysOnTop(true);
    sourceMenu->setDraggable(false);

    /// \todo restructuring component relationsships
    source->registerGainLevelSlider(gainSlider);
    source->registerBackground(sourceBackground);
    source->registerMenu(sourceMenu);

    /// \todo create actual output gain level component
    levelMeterLeft->setSliderStyle(Slider::LinearBarVertical);
    levelMeterRight->setSliderStyle(Slider::LinearBarVertical);
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

    debugText = nullptr;
    levelMeterRight = nullptr;
    levelMeterLeft = nullptr;
    listener = nullptr;
    gainSlider = nullptr;
    sourceBackground = nullptr;
    sourceMenu = nullptr;
    source = nullptr;
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

    debugText->setBounds (648, 8, 250, 584);
    levelMeterRight->setBounds (856, 150, 24, 300);
    levelMeterLeft->setBounds (824, 150, 24, 300);
    listener->setBounds (400, 250, 100, 100);
    gainSlider->setBounds (413, 191, 75, 28);
    sourceBackground->setBounds (350, 40, 200, 200);
    sourceMenu->setBounds (505, 95, 250, 225);
    source->setBounds (400, 90, 100, 100);
    //[UserResized] Add your own custom resize handling here..
    // draw components at their position
    juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    source->setBounds(pixPosSource.x - source->getWidth() / 2, pixPosSource.y - source->getHeight() / 2, source->getWidth(), source->getHeight());

    juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
    listener->setBounds(pixPosRef.x - listener->getWidth() / 2, pixPosRef.y - listener->getHeight() / 2, listener->getWidth(), listener->getHeight());

    gainSlider->setValue(params.sourceGain.get());
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
    else if (sliderThatWasMoved == gainSlider)
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
        params.sourceGain.setUI(val);
        //[/UserSliderCode_gainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::childBoundsChanged(Component *child)
{
    int offsetX;
    int offsetY;
    if (child == source || child == listener)
    {
        if (child = source)
        {
            // gainSlider, sourceMenu and sourceBackground should always follow source node
            offsetX = source->getX() + (source->getWidth() - gainSlider->getWidth()) / 2;
            offsetY = source->getY() + source->getHeight() + 5;
            gainSlider->setBounds(offsetX, offsetY, gainSlider->getWidth(), gainSlider->getHeight());

            offsetX = source->getX() + source->getWidth() + 25;
            offsetY = source->getY() + source->getHeight() / 2;
            sourceMenu->setBounds(offsetX, offsetY, sourceMenu->getWidth(), sourceMenu->getHeight());

            offsetX = source->getX() - source->getWidth() / 2;
            offsetY = source->getY() - source->getHeight() / 2;
            sourceBackground->setBounds(offsetX, offsetY, source->getWidth() * 2, source->getHeight() * 2);
            sourceBackground->setShadowRadius(source->getWidth() * 0.5f);
        }

        // refresh plane wave of source background
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
        juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
        float angle = pixPosRef.getAngleToPoint(pixPosSource);
        source->refreshBackground(radiansToDegrees(angle), params.sourceType.getStep() == eSourceType::ePlane);
    }
}

void PlugUI::timerCallback()
{
    source->refreshGainLevel(params.sourceLevel.get());

    levelMeterLeft->setValue(params.outputLevelLeft.get(), dontSendNotification);
    levelMeterRight->setValue(params.outputLevelRight.get(), dontSendNotification);

#if 0
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
  <BACKGROUND backgroundColour="ffedede6">
    <IMAGE pos="13 530 64 64" resource="BinaryData::ssr_logo_png" opacity="1"
           mode="1"/>
  </BACKGROUND>
  <LABEL name="debug" id="3b44d9ef5ee9c1a" memberName="debugText" virtualName=""
         explicitFocusOrder="0" pos="648 8 250 584" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="9"/>
  <SLIDER name="level right" id="a744d1a2c21ea6d8" memberName="levelMeterRight"
          virtualName="" explicitFocusOrder="0" pos="856 150 24 300" thumbcol="ff60ff60"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="level left" id="13e0962dc81dca1" memberName="levelMeterLeft"
          virtualName="" explicitFocusOrder="0" pos="824 150 24 300" thumbcol="ff60ff60"
          min="0" max="1" int="0" style="LinearVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GENERICCOMPONENT name="listener" id="a34b6db6e6ed2361" memberName="listener" virtualName="ListenerComponent"
                    explicitFocusOrder="0" pos="400 250 100 100" class="Component"
                    params="params"/>
  <SLIDER name="gain slider" id="69ace909b58289b9" memberName="gainSlider"
          virtualName="GainLevelSlider" explicitFocusOrder="0" pos="413 191 75 28"
          min="-96" max="12" int="0" style="LinearBar" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="3"/>
  <GENERICCOMPONENT name="source background" id="5a992e1246372c92" memberName="sourceBackground"
                    virtualName="SourceBackgroundComponent" explicitFocusOrder="0"
                    pos="350 40 200 200" class="Component" params=""/>
  <GENERICCOMPONENT name="source menu" id="83eb0626dd657a1f" memberName="sourceMenu"
                    virtualName="" explicitFocusOrder="0" pos="505 95 250 225" class="DocumentWindow"
                    params="&quot;source menu&quot;, Colours::white, DocumentWindow::closeButton"/>
  <GENERICCOMPONENT name="source" id="7b4082301ad63f28" memberName="source" virtualName="SourceComponent"
                    explicitFocusOrder="0" pos="400 90 100 100" class="Component"
                    params="params"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
