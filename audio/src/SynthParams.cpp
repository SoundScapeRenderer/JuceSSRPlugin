#include "SynthParams.h"

SynthParams::SynthParams()
    : positionIndex(0)
    , masterVol("master vol", "masterVol", "masterVol", "", 0.0f, 1.0f, 0.7f)
    , xPos("x pos", "xPos", "xPos", "m", -2.0f, 2.0f, 0.0f)
    , yPos("y pos", "yPos", "yPos", "m", -2.0f, 2.0f, 0.0f)
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
