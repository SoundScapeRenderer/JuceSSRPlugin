#include "SynthParams.h"

namespace {
    static const char *OnOffStateNames[] = {
        "Disabled", "Enabled", nullptr
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
    : positionIndex(0)
    , xPos("x pos", "xPos", "xPos", "m", -20.0f, 20.0f, 0.0f)
    , yPos("y pos", "yPos", "yPos", "m", -20.0f, 20.0f, 2.0f)
    , orientation("orientation", "orientation", "orientation", "", 0.0f, 360.0f, 90.0f)
    , gain("gain", "gain", "gain", "", 0.0f, 1.0f, 0.8f)
    , isSrcMuted("isSrcMuted", "isSrcMuted", "isSrcMuted", eOnOffState::eOff, OnOffStateNames)
    , isPlaneSrc("isPlaneSrc", "isPlaneSrc", "isPlaneSrc", eOnOffState::eOff, OnOffStateNames)
    , inputChannel("input channel", "inputChannel", "inputChannel", "", 0.0f, 1.0f, 0.0f)
    , levelLeft("level left", "levelLeft", "levelLeft", "", -1.0f, 1.0f, 0.0f)
    , levelRight("level right", "levelright", "levelRight", "", -1.0f, 1.0f, 0.0f)
{
    positionInfo[0].resetToDefault();
    positionInfo[1].resetToDefault();
}

SynthParams::~SynthParams() {
}

int SynthParams::getAudioIndex()
{
    return positionIndex.load();
}

int SynthParams::getGUIIndex()
{
    return (positionIndex.load() + 1) % 2;
}
