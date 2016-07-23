#pragma once

#include "JuceHeader.h"
#include "Param.h"
#include <vector>
#include <array>

enum class eOnOffState : int {
    eOff = 0,
    eOn = 1,
    nSteps = 2
};

class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    // ssr params
    Param xPos;
    Param yPos;
    Param orientation;
    Param gain;
    ParamStepped<eOnOffState> isSrcMuted;
    ParamStepped<eOnOffState> isPlaneSrc;

    Param inputChannel;

    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;
    std::atomic<int> positionIndex;

    int getGUIIndex();
    int getAudioIndex();

protected:
private:
};
