#pragma once

#include "JuceHeader.h"
#include "Param.h"

enum class eOnOffState : int {
    eOff = 0,
    eOn = 1,
    nSteps = 2
};

enum class eSourceType : int {
    ePoint = 0,
    ePlane = 1,
    nSteps = 2
};

class SynthParams {
public:
    SynthParams();
    ~SynthParams();

    // source params
    Param sourceX;
    Param sourceY;
    Param sourceOrientation;
    Param sourceGain;
    Param sourceLevel;
    ParamStepped<eOnOffState> sourceMute;
    ParamStepped<eSourceType> isSourceTypePlane;
    /// \todo positionlock for source and reference?

    // reference listener params
    Param referenceX;
    Param referenceY;
    Param referenceOrientation;
    Param amplitudeReferenceDistance;

    Param inputChannel;
    Param outputLevelLeft;
    Param outputLevelRight;

    // original ssr colour codes
    static const Colour sourceColourBrown;
    static const Colour sourceColourBlue;
    static const Colour sourceColourGreen;
    static const Colour sourceColourViolet;
    static const Colour sourceColourRed;
    static const Colour sceneBackgroundColour;
    static const Colour sourceLevelColour;

private:
};
