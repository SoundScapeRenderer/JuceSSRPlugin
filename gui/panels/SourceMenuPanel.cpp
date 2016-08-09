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
SourceMenuPanel::SourceMenuPanel (SynthParams &p, SourceComponent *s)
    : PanelBase(p), params(p), sourceComponent(s)
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

    addAndMakeVisible (inputLabel = new Label ("input label",
                                               TRANS("input channel")));
    inputLabel->setFont (Font (13.00f, Font::plain));
    inputLabel->setJustificationType (Justification::centredLeft);
    inputLabel->setEditable (false, false, false);
    inputLabel->setColour (Label::textColourId, Colours::grey);
    inputLabel->setColour (TextEditor::textColourId, Colours::black);
    inputLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (inputBox = new ComboBox ("input box"));
    inputBox->setEditableText (false);
    inputBox->setJustificationType (Justification::centredLeft);
    inputBox->setTextWhenNothingSelected (TRANS("input channel"));
    inputBox->setTextWhenNoChoicesAvailable (String::empty);
    inputBox->addItem (TRANS("left / mono"), 1);
    inputBox->addItem (TRANS("right"), 2);
    inputBox->addListener (this);

    addAndMakeVisible (modelBox = new ComboBox ("model box"));
    modelBox->setEditableText (false);
    modelBox->setJustificationType (Justification::centredLeft);
    modelBox->setTextWhenNothingSelected (TRANS("source model"));
    modelBox->setTextWhenNoChoicesAvailable (String::empty);
    modelBox->addItem (TRANS("point souce"), 1);
    modelBox->addItem (TRANS("plane wave"), 2);
    modelBox->addListener (this);

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
    fixToggle->setToggleState(params.sourcePositionLock.getStep() == eOnOffState::eOn, dontSendNotification);
    fixToggle->setWantsKeyboardFocus(false);
    muteToggle->setToggleState(params.sourceMute.getStep() == eOnOffState::eOn, dontSendNotification);
    muteToggle->setWantsKeyboardFocus(false);

    modelBox->setSelectedItemIndex(static_cast<int>(params.sourceType.getStep()), dontSendNotification);
    inputBox->setSelectedItemIndex(static_cast<int>(params.inputChannel.getStep()), dontSendNotification);
    //[/UserPreSize]

    setSize (300, 400);


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
    inputLabel = nullptr;
    inputBox = nullptr;
    modelBox = nullptr;
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

    positionLabel->setBounds (8, 16, 80, 16);
    distanceLabel->setBounds (8, 40, 80, 16);
    azimuthLabel->setBounds (8, 64, 80, 16);
    fixLabel->setBounds (8, 88, 80, 16);
    volLabel->setBounds (8, 112, 80, 16);
    muteLabel->setBounds (8, 136, 80, 16);
    modelLabel->setBounds (8, 160, 80, 16);
    inputLabel->setBounds (8, 184, 80, 16);
    inputBox->setBounds (96, 184, 144, 16);
    modelBox->setBounds (96, 160, 144, 16);
    muteToggle->setBounds (200, 136, 20, 16);
    fixToggle->setBounds (200, 88, 20, 16);
    volLabel2->setBounds (96, 112, 144, 16);
    azimuthLabel2->setBounds (96, 64, 144, 16);
    distanceLabel2->setBounds (96, 40, 144, 16);
    positionLabel2->setBounds (96, 16, 144, 16);
    //[UserResized] Add your own custom resize handling here..
    fixToggle->setToggleState(params.sourcePositionLock.getStep() == eOnOffState::eOn, dontSendNotification);
    muteToggle->setToggleState(params.sourceMute.getStep() == eOnOffState::eOn, dontSendNotification);

    modelBox->setSelectedItemIndex(static_cast<int>(params.sourceType.getStep()), dontSendNotification);
    inputBox->setSelectedItemIndex(static_cast<int>(params.inputChannel.getStep()), dontSendNotification);
    //[/UserResized]
}

void SourceMenuPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    int selectedId = comboBoxThatHasChanged->getSelectedItemIndex();
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == inputBox)
    {
        //[UserComboBoxCode_inputBox] -- add your combo box handling code here..
        eInputChannel channel;
        selectedId == 0 ? channel = eInputChannel::eLeftChannel : channel = eInputChannel::eRightChannel;
        params.inputChannel.setStep(channel);
        //[/UserComboBoxCode_inputBox]
    }
    else if (comboBoxThatHasChanged == modelBox)
    {
        //[UserComboBoxCode_modelBox] -- add your combo box handling code here..
        eSourceType type;
        selectedId == 0 ? type = eSourceType::ePoint : type = eSourceType::ePlane;
        params.sourceType.setStep(type);
        sourceComponent->refreshBackground(type == eSourceType::ePlane);
        //[/UserComboBoxCode_modelBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void SourceMenuPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    bool isOn = buttonThatWasClicked->getToggleState();
    eOnOffState state;
    isOn ? state = eOnOffState::eOn : state = eOnOffState::eOff;
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == muteToggle)
    {
        //[UserButtonCode_muteToggle] -- add your button handler code here..
        params.sourceMute.setStep(state);
        sourceComponent->refreshSourceNode();
        //[/UserButtonCode_muteToggle]
    }
    else if (buttonThatWasClicked == fixToggle)
    {
        //[UserButtonCode_fixToggle] -- add your button handler code here..
        params.sourcePositionLock.setStep(state);
        sourceComponent->refreshSourceNode();
        //[/UserButtonCode_fixToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SourceMenuPanel::timerCallback()
{
    positionLabel2->setText(String(params.roundNearest(params.sourceX.get())) + " mtrs, " + String(params.roundNearest(params.sourceY.get())) + " mtrs", dontSendNotification);

    float dist = sqrtf(pow(params.referenceX.get() - params.sourceX.get(), 2.0f) + pow(params.referenceY.get() - params.sourceY.get(), 2.0f));
    distanceLabel2->setText(String(params.roundNearest(dist)) + " mtrs", dontSendNotification);

    azimuthLabel2->setText(String(params.roundNearest(params.sourceOrientation.get())) + " degs", dontSendNotification);

    volLabel2->setText(String(params.roundNearest(params.sourceGain.get())) + " dB", dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SourceMenuPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="SynthParams &amp;p, SourceComponent *s"
                 variableInitialisers="PanelBase(p), params(p), sourceComponent(s)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="300" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="position label" id="4fb7b389efd80fef" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="8 16 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="x, y" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="distance label" id="335b9a0960751dc9" memberName="distanceLabel"
         virtualName="" explicitFocusOrder="0" pos="8 40 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="distance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="azimuth label" id="cf62efff78460b63" memberName="azimuthLabel"
         virtualName="" explicitFocusOrder="0" pos="8 64 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="azimuth" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="fix label" id="c5f578c99816c429" memberName="fixLabel"
         virtualName="" explicitFocusOrder="0" pos="8 88 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="fixed position"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="vol label" id="6ae36f4c98da6877" memberName="volLabel"
         virtualName="" explicitFocusOrder="0" pos="8 112 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="volume" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="mute label" id="7adfed4f61cec45c" memberName="muteLabel"
         virtualName="" explicitFocusOrder="0" pos="8 136 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="muted" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="model label" id="c129f4058f99eea0" memberName="modelLabel"
         virtualName="" explicitFocusOrder="0" pos="8 160 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="model" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <LABEL name="input label" id="1764e9ebbbf45408" memberName="inputLabel"
         virtualName="" explicitFocusOrder="0" pos="8 184 80 16" textCol="ff808080"
         edTextCol="ff000000" edBkgCol="0" labelText="input channel" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="13" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="input box" id="976271ca70d23dca" memberName="inputBox"
            virtualName="" explicitFocusOrder="0" pos="96 184 144 16" editable="0"
            layout="33" items="left / mono&#10;right" textWhenNonSelected="input channel"
            textWhenNoItems=""/>
  <COMBOBOX name="model box" id="6589084621656a22" memberName="modelBox"
            virtualName="" explicitFocusOrder="0" pos="96 160 144 16" editable="0"
            layout="33" items="point souce&#10;plane wave" textWhenNonSelected="source model"
            textWhenNoItems=""/>
  <TOGGLEBUTTON name="mute toggle" id="a2a2af1b5eb5e970" memberName="muteToggle"
                virtualName="" explicitFocusOrder="0" pos="200 136 20 16" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="fix toggle" id="85e366cc1aa64435" memberName="fixToggle"
                virtualName="" explicitFocusOrder="0" pos="200 88 20 16" buttonText=""
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="vol label" id="49197c2d125ed02d" memberName="volLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 112 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
  <LABEL name="azimuth label" id="f913124fca9fcf65" memberName="azimuthLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 64 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="azimuth" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
  <LABEL name="distance label" id="716e3f41281fca98" memberName="distanceLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 40 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="distance" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
  <LABEL name="position label" id="79cacb44cd301191" memberName="positionLabel2"
         virtualName="" explicitFocusOrder="0" pos="96 16 144 16" edTextCol="ff000000"
         edBkgCol="0" labelText="x, y" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
