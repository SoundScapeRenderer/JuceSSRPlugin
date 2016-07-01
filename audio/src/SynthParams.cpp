#include "SynthParams.h"

SynthParams::SynthParams()
    : positionIndex(0)
    , masterVol("master vol", "masterVol", "masterVol", "", 0.0f, 1.0f, 0.7f)
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
