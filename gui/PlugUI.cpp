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
    //[/Constructor_pre]

    addAndMakeVisible (scene = new ScenePanel (params));
    scene->setName ("scene");

    addAndMakeVisible (debugText = new Label ("debug",
                                              String::empty));
    debugText->setFont (Font (15.00f, Font::plain));
    debugText->setJustificationType (Justification::topLeft);
    debugText->setEditable (false, false, false);
    debugText->setColour (TextEditor::textColourId, Colours::black);
    debugText->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (outputLevel = new OutputLevelComponent());
    outputLevel->setName ("output level");

    addAndMakeVisible (zoomSlider = new ZoomSlider ("zoom slider"));
    zoomSlider->setRange (25, 200, 1);
    zoomSlider->setSliderStyle (Slider::LinearHorizontal);
    zoomSlider->setTextBoxStyle (Slider::TextBoxBelow, false, 80, 24);
    zoomSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x00000000));
    zoomSlider->addListener (this);

    addAndMakeVisible (loadButton = new TextButton ("load button"));
    loadButton->setButtonText (TRANS("load"));
    loadButton->addListener (this);

    addAndMakeVisible (saveButton = new TextButton ("save button"));
    saveButton->setButtonText (TRANS("save"));
    saveButton->addListener (this);


    //[UserPreSize]
    outputLevel->setLeveLColour(SynthParams::sourceLevelColour);
    outputLevel->setSkewFactor(3.0f);

    // register zoomSlider and reset zoomFactor to 100%
    registerSlider(zoomSlider, &params.zoomFactor, std::bind(&PlugUI::resizeScenePanel, this));
    zoomSlider->setValue(params.zoomFactor.getDefaultUI());

    // create some custom component designs to use as default
    lnf = new CustomLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(lnf);

    debugText->setInterceptsMouseClicks(false, false);
    //[/UserPreSize]

    setSize (950, 650);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PlugUI::~PlugUI()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    lnf = nullptr;
    //[/Destructor_pre]

    scene = nullptr;
    debugText = nullptr;
    outputLevel = nullptr;
    zoomSlider = nullptr;
    loadButton = nullptr;
    saveButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlugUI::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xfff9f9f9));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlugUI::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    scene->setBounds (15, 12, 920, 590);
    debugText->setBounds (685, 15, 255, 625);
    outputLevel->setBounds (570, 613, 150, 24);
    zoomSlider->setBounds (812, 613, 80, 24);
    loadButton->setBounds (190, 613, 80, 24);
    saveButton->setBounds (110, 613, 80, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlugUI::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == zoomSlider)
    {
        //[UserSliderCode_zoomSlider] -- add your slider handling code here..
        //[/UserSliderCode_zoomSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PlugUI::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loadButton)
    {
        //[UserButtonCode_loadButton] -- add your button handler code here..
        params.readXMLPatchStandalone();
        //[/UserButtonCode_loadButton]
    }
    else if (buttonThatWasClicked == saveButton)
    {
        //[UserButtonCode_saveButton] -- add your button handler code here..
        params.writeXMLPatchStandalone();
        //[/UserButtonCode_saveButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlugUI::resizeScenePanel()
{
    scene->resized();
}

void PlugUI::timerCallback()
{
    PanelBase::timerCallback();
    outputLevel->refreshOutputLevel(params.outputLevelLeft.getUI(), params.outputLevelRight.getUI());

#if 0
    debugText->setText(
        "SourceX = " + String(params.sourceX.get())
        + "\nSourceY = " + String(params.sourceY.get())
        + "\nSourceOri = " + String(params.sourceOrientation.get())
        + "\nsourceVol = " + String(params.sourceVol.get())
        + "\nSourceLevel = " + String(params.sourceLevel.get())
        + "\nSourceMute = " + String(params.sourceMute.getUIString())
        + "\nSourceType = " + String(params.sourceType.getUIString())
        + "\nPositionLock = " + String(params.sourcePositionLock.getUIString())

        + "\n\nRefX = " + String(params.referenceX.get())
        + "\nRefY = " + String(params.referenceY.get())
        + "\nRefOri = " + String(params.referenceOrientation.get())
        + "\nAmpliRefDist = " + String(params.amplitudeReferenceDistance.get())

        + "\n\nInputChannel = " + String(params.inputChannel.getUIString())
        + "\nOutputLevelLeft = " + String(params.outputLevelLeft.get())
        + "\nOutputLevelRight = " + String(params.outputLevelRight.get())

        + "\n\nZoomfactor = " + String(params.zoomFactor.get())
        + "\nSceneOffsetX = " + String(params.sceneOffsetX.get())
        + "\nSceneOffsetY = " + String(params.sceneOffsetY.get())
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
                 initialWidth="950" initialHeight="650">
  <BACKGROUND backgroundColour="fff9f9f9"/>
  <GENERICCOMPONENT name="scene" id="31a3828dbcedcc3f" memberName="scene" virtualName=""
                    explicitFocusOrder="0" pos="15 12 920 590" class="ScenePanel"
                    params="params"/>
  <LABEL name="debug" id="3b44d9ef5ee9c1a" memberName="debugText" virtualName=""
         explicitFocusOrder="0" pos="685 15 255 625" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="9"/>
  <GENERICCOMPONENT name="output level" id="18d306cbb6aed73e" memberName="outputLevel"
                    virtualName="" explicitFocusOrder="0" pos="570 613 150 24" class="OutputLevelComponent"
                    params=""/>
  <SLIDER name="zoom slider" id="c8e0b018d0c69bbf" memberName="zoomSlider"
          virtualName="ZoomSlider" explicitFocusOrder="0" pos="812 613 80 24"
          textboxoutline="0" min="25" max="200" int="1" style="LinearHorizontal"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="24" skewFactor="1"/>
  <TEXTBUTTON name="load button" id="7a6f9aa471624d92" memberName="loadButton"
              virtualName="" explicitFocusOrder="0" pos="190 613 80 24" buttonText="load"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="save button" id="b25b544b7310227e" memberName="saveButton"
              virtualName="" explicitFocusOrder="0" pos="110 613 80 24" buttonText="save"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
