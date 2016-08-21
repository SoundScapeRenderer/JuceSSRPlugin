#include "SynthParams.h"

namespace {
    static const char *OnOffStateNames[] = {
        "Disabled", "Enabled", nullptr
    };

    static const char *SourceTypeNames[] = {
        "Point Source", "Plane Source", nullptr
    };

    static const char *InputChannelNames[] = {
        "Left Channel", "Right Channel", nullptr
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
    , sourceVol("source vol", "sourceVol", "sourceVol", "db", -96.0f, 12.0f, -6.0f)
    , sourceLevel("sourceLevel", "sourceLevel", "sourceLevel", "", -1.0f, 1.0f, 0.0f)
    , sourceMute("source muted", "sourceMute", "sourceMute", eOnOffState::eOff, OnOffStateNames)
    , sourceType("source type", "sourceType", "sourceType", eSourceType::ePoint, SourceTypeNames)
    , sourcePositionLock("source position lock", "sourcePositionLock", "sourcePositionLock", eOnOffState::eOff, OnOffStateNames)

    , referenceX("reference x", "referenceX", "referenceX", "m", -50.0f, 50.0f, 0.0f)
    , referenceY("reference y", "referenceY", "referenceY", "m", -50.0f, 50.0f, 0.0f)
    , referenceOrientation("reference orientation", "referenceOrientation", "referenceOrientation", "degs", 0.0f, 360.0f, 90.0f)
    , amplitudeReferenceDistance("amplitude reference distance", "amplitudeReferenceDistance", "amplitudeReferenceDistance", "m", 0.0f, 50.0f, 3.0f)

    , inputChannel("input channel", "inputChannel", "inputChannel", eInputChannel::eLeftChannel, InputChannelNames)
    , outputLevelLeft("output level left", "outputLevelLeft", "outputLevelLeft", "", -1.0f, 1.0f, 0.0f)
    , outputLevelRight("outputlevel right", "outputLevelRight", "outputLevelRight", "", -1.0f, 1.0f, 0.0f)

    , zoomFactor("zoom factor", "zoomFactor", "zoomFactor", "%", 25.0f, 200.0f, 100.0f)
    , pixelPerMeter(125)
    , sceneOffsetX("scene offset x", "sceneOffsetX", "sceneOffsetX", "px", -2500.0f, 2500.0f, 0.0f)
    , sceneOffsetY("scene offset y", "sceneOffsetY", "sceneOffsetY", "px", -2500.0f, 2500.0f, 125.0f)
{
}

SynthParams::~SynthParams()
{
}

//==============================================================================

juce::Point<int> SynthParams::pos2pix(float meterCenterX, float meterCenterY, int screenWidth, int screenHeight)
{
    int x = static_cast<int>(meterCenterX * pixelPerMeter * zoomFactor.get() / 100.0f + (screenWidth / 2 + sceneOffsetX.get()));
    int y = static_cast<int>(-meterCenterY * pixelPerMeter * zoomFactor.get() / 100.0f + (screenHeight / 2 + sceneOffsetY.get()));

    return juce::Point<int>(x, y);
}

juce::Point<float> SynthParams::pix2pos(int pixCenterX, int pixCenterY, int screenWidth, int screenHeight)
{
    float x = (pixCenterX - (screenWidth / 2 + sceneOffsetX.get())) / (pixelPerMeter * zoomFactor.get() / 100.0f);
    float y = (pixCenterY - (screenHeight / 2 + sceneOffsetY.get())) / (pixelPerMeter * zoomFactor.get() / 100.0f);

    return juce::Point<float>(x, -y);
}

float SynthParams::roundNearest(float val)
{
    return roundf(val * 100) / 100;
}
