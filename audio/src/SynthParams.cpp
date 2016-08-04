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

SynthParams::SynthParams()
    : sourceX("source x", "sourceX", "sourceX", "m", -50.0f, 50.0f, 0.0f)
    , sourceY("source y", "sourceY", "sourceY", "m", -50.0f, 50.0f, 2.0f)
    , sourceOrientation("source orientation", "sourceOrientation", "sourceOrientation", "degs", -180.0f, 180.0f, 0.0f)
    , sourceGain("source gain", "sourceGain", "sourceGain", "db", -96.0f, 12.0f, -6.0f)
    , sourceLevel("sourceLevel", "sourceLevel", "sourceLevel", "", -1.0f, 1.0f, 0.0f)
    , sourceMute("source muted", "sourceMute", "sourceMute", eOnOffState::eOff, OnOffStateNames)
    , sourceType("source type", "sourceType", "sourceType", eSourceType::ePoint, SourceTypeNames)

    , referenceX("reference x", "referenceX", "referenceX", "m", -50.0f, 50.0f, 0.0f)
    , referenceY("reference y", "referenceY", "referenceY", "m", -50.0f, 50.0f, 0.0f)
    , referenceOrientation("reference orientation", "referenceOrientation", "referenceOrientation", "degs", 0.0f, 360.0f, 90.0f)
    , amplitudeReferenceDistance("amplitude reference distance", "amplitudeReferenceDistance", "amplitudeReferenceDistance", "m", 0.0f, 50.0f, 3.0f)

    , inputChannel("input channel", "inputChannel", "inputChannel", eInputChannel::eLeftChannel, InputChannelNames)
    , outputLevelLeft("output level left", "outputLevelLeft", "outputLevelLeft", "", -1.0f, 1.0f, 0.0f)
    , outputLevelRight("outputlevel right", "outputLevelRight", "outputLevelRight", "", -1.0f, 1.0f, 0.0f)

    , zoomFactor("zoom factor", "zoomFactor", "zoomFactor", "", 0.3f, 1.5f, 1.0f)
{
}

SynthParams::~SynthParams() 
{
}
