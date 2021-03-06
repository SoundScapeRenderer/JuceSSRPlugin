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

#include "SourceMenuPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SourceMenuPanel::SourceMenuPanel (PluginParams &p, SourceNodeComponent *s)
    : PanelBase(p), sourceNode(s)
{
    //[Constructor_pre] You can add your own custom stuff here..
    startTimerHz (60);
    //[/Constructor_pre]

    addAndMakeVisible (positionLabel = new Label ("position label",
                                                  TRANS("x, y")));
    positionLabel->setFont (Font (13.00f, Font::plain));
    positionLabel->setJustificationType (Justification::centredLeft);
    positionLabel->setEditable (false, false, false);
    positionLabel->setColour (Label::textColourId, Colours::grey);
    positionLabel->setColour (TextEditor::textColourId, Colours::black);
    positionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (distanceLabel = new Label ("distance label",
                                                  TRANS("distance")));
    distanceLabel->setFont (Font (13.00f, Font::plain));
    distanceLabel->setJustificationType (Justification::centredLeft);
    distanceLabel->setEditable (false, false, false);
    distanceLabel->setColour (Label::textColourId, Colours::grey);
    distanceLabel->setColour (TextEditor::textColourId, Colours::black);
    distanceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (azimuthLabel = new Label ("azimuth label",
                                                 TRANS("azimuth")));
    azimuthLabel->setFont (Font (13.00f, Font::plain));
    azimuthLabel->setJustificationType (Justification::centredLeft);
    azimuthLabel->setEditable (false, false, false);
    azimuthLabel->setColour (Label::textColourId, Colours::grey);
    azimuthLabel->setColour (TextEditor::textColourId, Colours::black);
    azimuthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (fixLabel = new Label ("fix label",
                                             TRANS("fixed position")));
    fixLabel->setFont (Font (13.00f, Font::plain));
    fixLabel->setJustificationType (Justification::centredLeft);
    fixLabel->setEditable (false, false, false);
    fixLabel->setColour (Label::textColourId, Colours::grey);
    fixLabel->setColour (TextEditor::textColourId, Colours::black);
    fixLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (volLabel = new Label ("vol label",
                                             TRANS("volume")));
    volLabel->setFont (Font (13.00f, Font::plain));
    volLabel->setJustificationType (Justification::centredLeft);
    volLabel->setEditable (false, false, false);
    volLabel->setColour (Label::textColourId, Colours::grey);
    volLabel->setColour (TextEditor::textColourId, Colours::black);
    volLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (muteLabel = new Label ("mute label",
                                              TRANS("muted")));
    muteLabel->setFont (Font (13.00f, Font::plain));
    muteLabel->setJustificationType (Justification::centredLeft);
    muteLabel->setEditable (false, false, false);
    muteLabel->setColour (Label::textColourId, Colours::grey);
    muteLabel->setColour (TextEditor::textColourId, Colours::black);
    muteLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (modelLabel = new Label ("model label",
                                               TRANS("model")));
    modelLabel->setFont (Font (13.00f, Font::plain));
    modelLabel->setJustificationType (Justification::centredLeft);
    modelLabel->setEditable (false, false, false);
    modelLabel->setColour (Label::textColourId, Colours::grey);
    modelLabel->setColour (TextEditor::textColourId, Colours::black);
    modelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (sourceModelBox = new ComboBox ("source model box"));
    sourceModelBox->setEditableText (false);
    sourceModelBox->setJustificationType (Justification::centredLeft);
    sourceModelBox->setTextWhenNothingSelected (TRANS("source model"));
    sourceModelBox->setTextWhenNoChoicesAvailable (String::empty);
    sourceModelBox->addListener (this);

    addAndMakeVisible (muteToggle = new ToggleButton ("mute toggle"));
    muteToggle->setButtonText (String::empty);
    muteToggle->addListener (this);

    addAndMakeVisible (fixToggle = new ToggleButton ("fix toggle"));
    fixToggle->setButtonText (String::empty);
    fixToggle->addListener (this);

    addAndMakeVisible (volLabel2 = new Label ("vol label",
                                              TRANS("volume")));
    volLabel2->setFont (Font (13.00f, Font::plain));
    volLabel2->setJustificationType (Justification::centredRight);
    volLabel2->setEditable (false, false, false);
    volLabel2->setColour (TextEditor::textColourId, Colours::black);
    volLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (azimuthLabel2 = new Label ("azimuth label",
                                                  TRANS("azimuth")));
    azimuthLabel2->setFont (Font (13.00f, Font::plain));
    azimuthLabel2->setJustificationType (Justification::centredRight);
    azimuthLabel2->setEditable (false, false, false);
    azimuthLabel2->setColour (TextEditor::textColourId, Colours::black);
    azimuthLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (distanceLabel2 = new Label ("distance label",
                                                   TRANS("distance")));
    distanceLabel2->setFont (Font (13.00f, Font::plain));
    distanceLabel2->setJustificationType (Justification::centredRight);
    distanceLabel2->setEditable (false, false, false);
    distanceLabel2->setColour (TextEditor::textColourId, Colours::black);
    distanceLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (positionLabel2 = new Label ("position label",
                                                   TRANS("x, y")));
    positionLabel2->setFont (Font (13.00f, Font::plain));
    positionLabel2->setJustificationType (Justification::centredRight);
    positionLabel2->setEditable (false, false, false);
    positionLabel2->setColour (TextEditor::textColourId, Colours::black);
    positionLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    registerButton(muteToggle, &params.sourceMute, std::bind(&SourceMenuPanel::sourceMutedStateChanged, this));
    registerButton(fixToggle, &params.sourcePositionLock, std::bind(&SourceMenuPanel::sourceFixedPositionStateChanged, this));

    registerComboBox<eSourceType>(sourceModelBox, &params.sourceType, std::bind(&SourceMenuPanel::updatePlaneWaveVisibility, this));
    //[/UserPreSize]

    setSize (250, 225);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SourceMenuPanel::~SourceMenuPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    positionLabel = nullptr;
    distanceLabel = nullptr;
    azimuthLabel = nullptr;
    fixLabel = nullptr;
    volLabel = nullptr;
    muteLabel = nullptr;
    modelLabel = nullptr;
    sourceModelBox = nullptr;
    muteToggle = nullptr;
    fixToggle = nullptr;
    volLabel2 = nullptr;
    azimuthLabel2 = nullptr;
    distanceLabel2 = nullptr;
    positionLabel2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SourceMenuPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SourceMenuPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    positionLabel->setBounds (8, 17, 80, 16);
    distanceLabel->setBounds (8, 46, 80, 16);
    azimuthLabel->setBounds (8, 75, 80, 16);
    fixLabel->setBounds (8, 104, 80, 16);
    volLabel->setBounds (8, 133, 80, 16);
    muteLabel->setBounds (8, 162, 80, 16);
    modelLabel->setBounds (8, 191, 80, 16);
    sourceModelBox->setBounds (96, 191, 144, 16);
    muteToggle->setBounds (200, 162, 20, 16);
    fixToggle->setBounds (200, 104, 20, 16);
    volLabel2->setBounds (96, 133, 144, 16);
    azimuthLabel2->setBounds (96, 75, 144, 16);
    distanceLabel2->setBounds (96, 46, 144, 16);
    positionLabel2->setBounds (96, 17, 144, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SourceMenuPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    handleComboBox<eSourceType>(comboBoxThatHasChanged);
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == sourceModelBox)
    {
        //[UserComboBoxCode_sourceModelBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_sourceModelBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void SourceMenuPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    handleButton(buttonThatWasClicked);
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == muteToggle)
    {
        //[UserButtonCode_muteToggle] -- add your button handler code here..
        //[/UserButtonCode_muteToggle]
    }
    else if (buttonThatWasClicked == fixToggle)
    {
        //[UserButtonCode_fixToggle] -- add your button handler code here..
        //[/UserButtonCode_fixToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SourceMenuPanel::sourceMutedStateChanged()
{
    sourceNode->setSourceMute(params.sourceMute.getStep() == eOnOffState::eOn);
}

void SourceMenuPanel::sourceFixedPositionStateChanged()
{
    // lock source's X and Y position parameter
    params.sourceX.setValueLock(params.sourcePositionLock.getStep() == eOnOffState::eOn);
    params.sourceY.setValueLock(params.sourcePositionLock.getStep() == eOnOffState::eOn);

    sourceNode->setSourcePositionFixed(params.sourcePositionLock.getStep() == eOnOffState::eOn);
}

void SourceMenuPanel::updatePlaneWaveVisibility()
{
    sourceNode->setPlaneWaveVisible(params.sourceType.getStep() == eSourceType::ePlane);
}

void SourceMenuPanel::timerCallback()
{
    PanelBase::timerCallback();

    // update source information to display
    positionLabel2->setText(String(params.sourceX.get(), 2) + " mtrs, " + String(params.sourceY.get(), 2) + " mtrs", dontSendNotification);

    float dist = sqrtf(pow(params.referenceX.get() - params.sourceX.get(), 2.0f) + pow(params.referenceY.get() - params.sourceY.get(), 2.0f));
    distanceLabel2->setText(String(dist, 2) + " mtrs", dontSendNotification);

    azimuthLabel2->setText(String(params.sourceOrientation.get(), 2) + " degs", dontSendNotification);

    volLabel2->setText(String(params.sourceVol.get(), 2) + " dB", dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SourceMenuPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="PluginParams &amp;p, SourceNodeComponent *s"
                 variableInitialisers="PanelBase(p), sourceNode(s)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="250" initialHeight="225">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="position label" id="4fb7b389efd80fef" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="8 17 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="x, y" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="distance label" id="335b9a0960751dc9" memberName="distanceLabel"
         virtualName="" explicitFocusOrder="0" pos="8 46 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="distance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="azimuth label" id="cf62efff78460b63" memberName="azimuthLabel"
         virtualName="" explicitFocusOrder="0" pos="8 75 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="azimuth" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="fix label" id="c5f578c99816c429" memberName="fixLabel"
         virtualName="" explicitFocusOrder="0" pos="8 104 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="fixed position"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="vol label" id="6ae36f4c98da6877" memberName="volLabel"
         virtualName="" explicitFocusOrder="0" pos="8 133 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="volume" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="mute label" id="7adfed4f61cec45c" memberName="muteLabel"
         virtualName="" explicitFocusOrder="0" pos="8 162 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="muted" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="model label" id="c129f4058f99eea0" memberName="modelLabel"
         virtualName="" explicitFocusOrder="0" pos="8 191 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="model" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="source model box" id="6589084621656a22" memberName="sourceModelBox"
            virtualName="" explicitFocusOrder="0" pos="96 191 144 16" editable="0"
            layout="33" items="" textWhenNonSelected="source model" textWhenNoItems=""/>
  <TOGGLEBUTTON name="mute toggle" id="a2a2af1b5eb5e970" memberName="muteToggle"
                virtualName="" explicitFocusOrder="0" pos="200 162 20 16" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="fix toggle" id="85e366cc1aa64435" memberName="fixToggle"
                virtualName="" explicitFocusOrder="0" pos="200 104 20 16" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="vol label" id="49197c2d125ed02d" memberName="volLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 133 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
  <LABEL name="azimuth label" id="f913124fca9fcf65" memberName="azimuthLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 75 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="azimuth" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
  <LABEL name="distance label" id="716e3f41281fca98" memberName="distanceLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 46 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="distance" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
  <LABEL name="position label" id="79cacb44cd301191" memberName="positionLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 17 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="x, y" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
