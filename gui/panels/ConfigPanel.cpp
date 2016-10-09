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

#include "ConfigPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConfigPanel::ConfigPanel (PluginParams &p)
    : PanelBase(p), params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (ampRefDistanceSlider = new Slider ("ampRefDistance slider"));
    ampRefDistanceSlider->setRange (0.5, 50, 0.01);
    ampRefDistanceSlider->setSliderStyle (Slider::LinearHorizontal);
    ampRefDistanceSlider->setTextBoxStyle (Slider::TextBoxRight, false, 80, 20);
    ampRefDistanceSlider->addListener (this);

    addAndMakeVisible (ampRefLabel = new Label ("amp ref label",
                                                TRANS("amplitude reference distance:")));
    ampRefLabel->setFont (Font (15.00f, Font::plain));
    ampRefLabel->setJustificationType (Justification::centredLeft);
    ampRefLabel->setEditable (false, false, false);
    ampRefLabel->setColour (TextEditor::textColourId, Colours::black);
    ampRefLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rendererLabel = new Label ("renderer label",
                                                  TRANS("rendering algorithm:")));
    rendererLabel->setFont (Font (15.00f, Font::plain));
    rendererLabel->setJustificationType (Justification::centredLeft);
    rendererLabel->setEditable (false, false, false);
    rendererLabel->setColour (TextEditor::textColourId, Colours::black);
    rendererLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (rendererAlgorithmBox = new ComboBox ("renderer algorithm box"));
    rendererAlgorithmBox->setEditableText (false);
    rendererAlgorithmBox->setJustificationType (Justification::centredLeft);
    rendererAlgorithmBox->setTextWhenNothingSelected (TRANS("rendering algorithm"));
    rendererAlgorithmBox->setTextWhenNoChoicesAvailable (TRANS("select algorithm"));
    rendererAlgorithmBox->addItem (TRANS("binaural synthesis"), 1);
    rendererAlgorithmBox->addListener (this);

    addAndMakeVisible (IRFileLabel = new Label ("IR file label",
                                                TRANS("impulse response file:")));
    IRFileLabel->setFont (Font (15.00f, Font::plain));
    IRFileLabel->setJustificationType (Justification::centredLeft);
    IRFileLabel->setEditable (false, false, false);
    IRFileLabel->setColour (TextEditor::textColourId, Colours::black);
    IRFileLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (IRFileBox = new ComboBox ("IR file box"));
    IRFileBox->setEditableText (false);
    IRFileBox->setJustificationType (Justification::centredLeft);
    IRFileBox->setTextWhenNothingSelected (TRANS("impulse response file"));
    IRFileBox->setTextWhenNoChoicesAvailable (TRANS("select IR file"));
    IRFileBox->addItem (TRANS("hrirs - fabian"), 1);
    IRFileBox->addListener (this);


    //[UserPreSize]
    // for now only binaural synthesis with hrirs_fabian is available
    rendererAlgorithmBox->setSelectedItemIndex(0, dontSendNotification);
    rendererAlgorithmBox->setEnabled(false);
    IRFileBox->setSelectedItemIndex(0, dontSendNotification);
    IRFileBox->setEnabled(false);

    registerSlider(ampRefDistanceSlider, &params.amplitudeReferenceDistance);
    //[/UserPreSize]

    setSize (400, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConfigPanel::~ConfigPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    ampRefDistanceSlider = nullptr;
    ampRefLabel = nullptr;
    rendererLabel = nullptr;
    rendererAlgorithmBox = nullptr;
    IRFileLabel = nullptr;
    IRFileBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConfigPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConfigPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ampRefDistanceSlider->setBounds (16, 163, 368, 24);
    ampRefLabel->setBounds (16, 136, 368, 24);
    rendererLabel->setBounds (16, 32, 144, 24);
    rendererAlgorithmBox->setBounds (176, 36, 208, 16);
    IRFileLabel->setBounds (16, 77, 144, 24);
    IRFileBox->setBounds (176, 81, 208, 16);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConfigPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    handleSlider(sliderThatWasMoved);
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == ampRefDistanceSlider)
    {
        //[UserSliderCode_ampRefDistanceSlider] -- add your slider handling code here..
        //[/UserSliderCode_ampRefDistanceSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void ConfigPanel::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == rendererAlgorithmBox)
    {
        //[UserComboBoxCode_rendererAlgorithmBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_rendererAlgorithmBox]
    }
    else if (comboBoxThatHasChanged == IRFileBox)
    {
        //[UserComboBoxCode_IRFileBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_IRFileBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ConfigPanel" componentName=""
                 parentClasses="public PanelBase" constructorParams="PluginParams &amp;p"
                 variableInitialisers="PanelBase(p), params(p)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="400" initialHeight="500">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="ampRefDistance slider" id="b7d805ed219ae642" memberName="ampRefDistanceSlider"
          virtualName="" explicitFocusOrder="0" pos="16 163 368 24" min="0.5"
          max="50" int="0.010000000000000000208" style="LinearHorizontal"
          textBoxPos="TextBoxRight" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <LABEL name="amp ref label" id="7554da043029f059" memberName="ampRefLabel"
         virtualName="" explicitFocusOrder="0" pos="16 136 368 24" edTextCol="ff000000"
         edBkgCol="0" labelText="amplitude reference distance:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="renderer label" id="fffb10db8d5fcc88" memberName="rendererLabel"
         virtualName="" explicitFocusOrder="0" pos="16 32 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="rendering algorithm:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="renderer algorithm box" id="e038bb6efc51d085" memberName="rendererAlgorithmBox"
            virtualName="" explicitFocusOrder="0" pos="176 36 208 16" editable="0"
            layout="33" items="binaural synthesis" textWhenNonSelected="rendering algorithm"
            textWhenNoItems="select algorithm"/>
  <LABEL name="IR file label" id="61e57b70d01f48f7" memberName="IRFileLabel"
         virtualName="" explicitFocusOrder="0" pos="16 77 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="impulse response file:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="IR file box" id="d91b446018867d2b" memberName="IRFileBox"
            virtualName="" explicitFocusOrder="0" pos="176 81 208 16" editable="0"
            layout="33" items="hrirs - fabian" textWhenNonSelected="impulse response file"
            textWhenNoItems="select IR file"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
