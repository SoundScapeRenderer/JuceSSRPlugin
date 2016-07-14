#pragma once

#include "JuceHeader.h"
#include "Param.h"
#include <vector>
#include <array>

class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    Param masterVol;
    Param xPos;
    Param yPos;

    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;

    std::atomic<int> positionIndex;

    int getGUIIndex();
    int getAudioIndex();

protected:
private:
};
