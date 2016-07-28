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

    // original ssr colour codes
    static const Colour sourceColourBrown;
    static const Colour sourceColourBlue;
    static const Colour sourceColourGreen;
    static const Colour sourceColourViolet;
    static const Colour sourceColourRed;
    static const Colour sceneBackgroundColour;
    static const Colour sourceLevelColour;

protected:
private:
};
