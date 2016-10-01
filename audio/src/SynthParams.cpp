#include "SynthParams.h"

namespace {
    static const char *OnOffStateNames[] = {
        "disabled", "enabled", nullptr
    };

    static const char *SourceTypeNames[] = {
        "point source", "plane source", nullptr
    };

    static const char *InputChannelNames[] = {
        "left channel", "right channel", nullptr
    };
}

const Colour SynthParams::sourceColourBrown(163, 95, 35);
const Colour SynthParams::sourceColourBlue(43, 174, 247);
const Colour SynthParams::sourceColourGreen(75, 135, 35);
const Colour SynthParams::sourceColourViolet(97, 31, 160);
const Colour SynthParams::sourceColourRed(173, 54, 35);
const Colour SynthParams::sceneBackgroundColour(237, 237, 230);
const Colour SynthParams::sourceLevelColour(58, 239, 58);

//==============================================================================

SynthParams::SynthParams()
    : sourceX("source x", "sourceX", "sourceX", "m", -50.0f, 50.0f, 0.0f)
    , sourceY("source y", "sourceY", "sourceY", "m", -50.0f, 50.0f, 2.0f)
    , sourceOrientation("source orientation", "sourceOrientation", "sourceOrientation", "degs", -180.0f, 180.0f, 0.0f)
    , sourceVol("source vol", "sourceVol", "sourceVol", "dB", -96.0f, 12.0f, -6.0f)
    , sourceLevel("sourceLevel", "sourceLevel", "sourceLevel", "dB", -96.0f, 12.0f, -96.0f)
    , sourceMute("source muted", "sourceMute", "sourceMute", eOnOffState::eOff, OnOffStateNames)
    , sourceType("source type", "sourceType", "sourceType", eSourceType::ePoint, SourceTypeNames)
    , sourcePositionLock("source position lock", "sourcePositionLock", "sourcePositionLock", eOnOffState::eOff, OnOffStateNames)

    , referenceX("reference x", "referenceX", "referenceX", "m", -50.0f, 50.0f, 0.0f)
    , referenceY("reference y", "referenceY", "referenceY", "m", -50.0f, 50.0f, 0.0f)
    , referenceOrientation("reference orientation", "referenceOrientation", "referenceOrientation", "degs", -180.0f, 180.0f, 0.0f)
    , refOrientationOffset(90.0f)
    , amplitudeReferenceDistance("amplitude reference distance", "amplitudeReferenceDistance", "amplitudeReferenceDistance", "m", 0.0f, 50.0f, 3.0f)

    , outputLevelLeft("output level left", "outputLevelLeft", "outputLevelLeft", "dB", -96.0f, 12.0f, -96.0f)
    , outputLevelRight("outputlevel right", "outputLevelRight", "outputLevelRight", "dB", -96.0f, 12.0f, -96.0f)

    , currentZoom("current zoom", "currentZoom", "currentZoom", "%", 25.0f, 200.0f, 100.0f)
    , pixelPerMeter(125)
    , sceneOffsetX("scene offset x", "sceneOffsetX", "sceneOffsetX", "m", -35.7f, 35.7f, 0.0f)
    , sceneOffsetY("scene offset y", "sceneOffsetY", "sceneOffsetY", "m", -41.0f, 41.0f, 1.00f)

    , serializeParams{ &sourceX, &sourceY, &sourceOrientation, &sourceVol, &sourceMute, &sourceType, &sourcePositionLock,
                       &referenceX, &referenceY, &referenceOrientation, &amplitudeReferenceDistance,
                       &currentZoom, &sceneOffsetX, &sceneOffsetY }

    , positionIndex(0)
{
    positionInfo[0].resetToDefault();
    positionInfo[1].resetToDefault();
}

SynthParams::~SynthParams()
{
}

//==============================================================================

juce::Point<int> SynthParams::pos2pix(float meterCenterX, float meterCenterY, int sceneWidth, int sceneHeight)
{
    int x = static_cast<int>(meterCenterX * getScaledPixelPerMeter() + (sceneWidth / 2 + sceneOffsetX.get() * getScaledPixelPerMeter()));
    int y = static_cast<int>(-meterCenterY * getScaledPixelPerMeter() + (sceneHeight / 2 + sceneOffsetY.get() * getScaledPixelPerMeter()));

    return juce::Point<int>(x, y);
}

juce::Point<float> SynthParams::pix2pos(int pixCenterX, int pixCenterY, int sceneWidth, int sceneHeight)
{
    float x = (pixCenterX - (sceneWidth / 2 + sceneOffsetX.get() * getScaledPixelPerMeter())) / getScaledPixelPerMeter();
    float y = (pixCenterY - (sceneHeight / 2 + sceneOffsetY.get() * getScaledPixelPerMeter())) / getScaledPixelPerMeter();

    return juce::Point<float>(x, -y);
}

float SynthParams::getScaledPixelPerMeter()
{
    return pixelPerMeter * currentZoom.get() / 100.0f;
}

const char* SynthParams::getSourceTypeNames(int index)
{
    return SourceTypeNames[jmin(jmax(0, index), static_cast<int>(eSourceType::nSteps))];
}

//==============================================================================

void SynthParams::writeXMLPatchHost(MemoryBlock& destData)
{
    // create an outer node of the patch
    ScopedPointer<XmlElement> patch = new XmlElement("patch");
    writeXMLPatchTree(patch);
    AudioProcessor::copyXmlToBinary(*patch, destData);
}

void SynthParams::writeXMLPatchStandalone()
{
    // create an outer node of the patch
    ScopedPointer<XmlElement> patch = new XmlElement("patch");
    writeXMLPatchTree(patch);

    // create the output
    FileChooser saveDirChooser("Save current state as patch!",
        File::getSpecialLocation(File::commonDocumentsDirectory).getChildFile(appName), "*.xml");
    if (saveDirChooser.browseForFileToSave(true))
    {
        File saveFile(saveDirChooser.getResult());
        patch->setAttribute("patchname", saveFile.getFileNameWithoutExtension());
        saveFile.create();
        if (!patch->writeToFile(saveFile, "")) // DTD optional, no validation yet
        {
            AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "File not saved!",
                "The file could not be saved to the selected folder!", "Close");
        }
    }
}

void SynthParams::readXMLPatchHost(const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> patch = AudioProcessor::getXmlFromBinary(data, sizeInBytes);
    readXMLPatchTree(patch);
}

void SynthParams::readXMLPatchStandalone()
{
    // read the xml params into the synth params
    FileChooser openFileChooser("Please select the patch you want to read!",
        File::getSpecialLocation(File::commonDocumentsDirectory).getChildFile(appName), "*.xml");

    if (openFileChooser.browseForFileToOpen())
    {
        File openedFile(openFileChooser.getResult());
        ScopedPointer<XmlElement> patch = XmlDocument::parse(openedFile);
        readXMLPatchTree(patch);
    }
}

void SynthParams::writeXMLPatchTree(XmlElement* patch)
{
    // set name and  version of the patch
    patch->setAttribute("version", appVersion);

    // iterate over all parameter to be serialized and insert them into the XML tree
    std::vector<Param*> parameters = serializeParams;
    for (auto &param : parameters)
    {
        float value = param->getUI();
        if (param->serializationTag() != "")
        {
            // add element to xml patch tree
            String prefixedName = (param->prefix() + param->serializationTag()).replace(" ", "");
            XmlElement* node = new XmlElement(prefixedName);
            node->setAttribute("value", value);
            patch->addChildElement(node);
        }
    }
}

void SynthParams::readXMLPatchTree(XmlElement* patch)
{
    // if the versions don't align, inform the user
    if (patch == NULL) { return; }
    if (patch->getTagName() != "patch" || patch->getStringAttribute("version").compare(appVersion) > 0)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "Version Conflict",
            "The file was created by a newer version of the software, some settings may be ignored.",
            "OK");
    }

    std::vector<Param*> parameters = serializeParams;
    patchName = patch->getStringAttribute("patchname");
    patchNameDirty = true;

    // iterate over all params and read the values if they exist in the xml patch
    for (auto &param : parameters)
    {
        if (param->serializationTag() != "")
        {
            // read and set values if exist
            String prefixedName = (param->prefix() + param->serializationTag()).replace(" ", "");
            if (patch->getChildByName(prefixedName) != NULL)
            {
                param->setUI(static_cast<float>(patch->getChildByName(prefixedName)->getDoubleAttribute("value")));
                param->set(param->get(), true);
            }
        }
    }
}

//==============================================================================

int SynthParams::getAudioIndex()
{
    return positionIndex.load();
}

int SynthParams::getGUIIndex()
{
    return (positionIndex.load() + 1) % 2;
}

