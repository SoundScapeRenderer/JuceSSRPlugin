#include "SynthParams.h"

namespace {
    static const char *OnOffStateNames[] = {
        "Disabled", "Enabled", nullptr
    };

    static const char *SourceTypeNames[] = {
        "Point Source", "Plane Source", nullptr
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
    : sourceX("source x", "sourceX", "sourceX", "m", -5.0f, 5.0f, 0.0f)
    , sourceY("source y", "sourceY", "sourceY", "m", -5.0f, 5.0f, 2.0f)
    , sourceOrientation("source orientation", "sourceOrientation", "sourceOrientation", "deg", 0.0f, 360.0f, 90.0f)
    , sourceGain("source gain", "sourceGain", "sourceGain", "", 0.0f, 1.0f, 0.8f)
    , sourceLevel("level left", "levelLeft", "levelLeft", "", -1.0f, 1.0f, 0.0f)
    , sourceMute("source muted", "sourceMute", "sourceMute", eOnOffState::eOff, OnOffStateNames)
    , isSourceTypePlane("is source type plae", "isSourceTypePlane", "isSourceTypePlane", eSourceType::ePoint, SourceTypeNames)

    , referenceX("reference x", "referenceX", "referenceX", "m", -5.0f, 5.0f, 0.0f)
    , referenceY("reference y", "referenceY", "referenceY", "m", -5.0f, 5.0f, 0.0f)
    , referenceOrientation("reference orientation", "referenceOrientation", "referenceOrientation", "deg", 0.0f, 360.0f, 90.0f)
    , amplitudeReferenceDistance("amplitude reference distance", "amplitudeReferenceDistance", "amplitudeReferenceDistance", "m", 0.0f, 5.0f, 3.0f)

    , inputChannel("input channel", "inputChannel", "inputChannel", "", 0.0f, 1.0f, 0.0f)
    , outputLevelLeft("output level left", "outputLevelLeft", "outputLevelLeft", "", -1.0f, 1.0f, 0.0f)
    , outputLevelRight("outputlevel right", "outputLevelRight", "outputLevelRight", "", -1.0f, 1.0f, 0.0f)
{

}

SynthParams::~SynthParams() 
{

}
