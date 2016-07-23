#include "SynthParams.h"

namespace {
    static const char *OnOffStateNames[] = {
        "Disabled", "Enabled", nullptr
    };
}

SynthParams::SynthParams()
    : positionIndex(0)
    , xPos("x pos", "xPos", "xPos", "m", -2.0f, 2.0f, 0.0f)
    , yPos("y pos", "yPos", "yPos", "m", -2.0f, 2.0f, 0.0f)
    , orientation("orientation", "orientation", "orientation", "", 0.0f, 360.0f, 90.0f)
    , gain("gain", "gain", "gain", "", 0.0f, 1.0f, 0.8f)
    , isSrcMuted("isSrcMuted", "isSrcMuted", "isSrcMuted", eOnOffState::eOff, OnOffStateNames)
    , isPlaneSrc("isPlaneSrc", "isPlaneSrc", "isPlaneSrc", eOnOffState::eOff, OnOffStateNames)
    , inputChannel("input channel", "inputChannel", "inputChannel", "", 0.0f, 1.0f, 0.0f)
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
