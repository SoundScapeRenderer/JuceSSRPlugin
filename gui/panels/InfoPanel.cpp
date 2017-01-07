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

#include "InfoPanel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
InfoPanel::InfoPanel (PluginParams &p)
    : params(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (infoLabel = new Label ("infoLabel",
                                              CharPointer_UTF8 ("This is an open-source audio plug-in for spatial hearing\n"
                                              "based on the\n"
                                              "\n"
                                              "\n"
                                              "\n"
                                              "\n"
                                              "It is developed at QULab at the Technische Universit\xc3\xa4t Berlin.")));
    infoLabel->setFont (Font (15.00f, Font::plain));
    infoLabel->setJustificationType (Justification::topLeft);
    infoLabel->setEditable (false, false, false);
    infoLabel->setColour (TextEditor::textColourId, Colours::black);
    infoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (ssrHyperlink = new HyperlinkButton (TRANS("SoundScape Renderer"),
                                                           URL ("http://spatialaudio.net/ssr/")));
    ssrHyperlink->setTooltip (TRANS("http://spatialaudio.net/ssr/"));
    ssrHyperlink->setButtonText (TRANS("SoundScape Renderer"));

    addAndMakeVisible (authorLabel = new Label ("author label",
                                                TRANS("Author: Tran, Nhat Duc\n"
                                                "Email: tran.nhatduc@yahoo.com")));
    authorLabel->setFont (Font (15.00f, Font::plain));
    authorLabel->setJustificationType (Justification::topLeft);
    authorLabel->setEditable (false, false, false);
    authorLabel->setColour (TextEditor::textColourId, Colours::black);
    authorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (versionLabel = new Label ("version label",
                                                 TRANS("Version: 1.0.0")));
    versionLabel->setFont (Font (15.00f, Font::plain));
    versionLabel->setJustificationType (Justification::centredRight);
    versionLabel->setEditable (false, false, false);
    versionLabel->setColour (TextEditor::textColourId, Colours::black);
    versionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    drawable1 = Drawable::createFromImageData (BinaryData::ssr_logo_large_png, BinaryData::ssr_logo_large_pngSize);

    //[UserPreSize]
    versionLabel->setText("Version: " + params.appVersion, dontSendNotification);
    //[/UserPreSize]

    setSize (300, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

InfoPanel::~InfoPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    infoLabel = nullptr;
    ssrHyperlink = nullptr;
    authorLabel = nullptr;
    versionLabel = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void InfoPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (16, 16, 128, 128),
                               RectanglePlacement::centred, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void InfoPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    infoLabel->setBounds (16, 170, 268, 232);
    ssrHyperlink->setBounds (16, 227, 268, 30);
    authorLabel->setBounds (16, 445, 268, 40);
    versionLabel->setBounds (120, 109, 164, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="InfoPanel" componentName=""
                 parentClasses="public Component" constructorParams="PluginParams &amp;p"
                 variableInitialisers="params(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="300"
                 initialHeight="500">
  <BACKGROUND backgroundColour="ffffffff">
    <IMAGE pos="16 16 128 128" resource="BinaryData::ssr_logo_large_png"
           opacity="1" mode="1"/>
  </BACKGROUND>
  <LABEL name="infoLabel" id="78b17336deacfe88" memberName="infoLabel"
         virtualName="" explicitFocusOrder="0" pos="16 170 268 232" edTextCol="ff000000"
         edBkgCol="0" labelText="This is an open-source audio plug-in for spatial hearing&#10;based on the&#10;&#10;&#10;&#10;&#10;It is developed at QULab at the Technische Universit&#228;t Berlin."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="9"/>
  <HYPERLINKBUTTON name="ssr hyperlink" id="2cee26e8706479ea" memberName="ssrHyperlink"
                   virtualName="" explicitFocusOrder="0" pos="16 227 268 30" tooltip="http://spatialaudio.net/ssr/"
                   buttonText="SoundScape Renderer" connectedEdges="0" needsCallback="0"
                   radioGroupId="0" url="http://spatialaudio.net/ssr/"/>
  <LABEL name="author label" id="1de163a2e8abc9e" memberName="authorLabel"
         virtualName="" explicitFocusOrder="0" pos="16 445 268 40" edTextCol="ff000000"
         edBkgCol="0" labelText="Author: Tran, Nhat Duc&#10;Email: tran.nhatduc@yahoo.com"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="9"/>
  <LABEL name="version label" id="4224045a2ad0455c" memberName="versionLabel"
         virtualName="" explicitFocusOrder="0" pos="120 109 164 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Version: 1.0.0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
