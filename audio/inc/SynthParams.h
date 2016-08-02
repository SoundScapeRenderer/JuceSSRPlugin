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

enum class eInputChannel : int {
    eLeftChannel = 0,
    eRightChannel = 1,
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

    ParamStepped<eInputChannel> inputChannel;
    Param outputLevelLeft;
    Param outputLevelRight;

    Param zoomFactor;
    const int pixelPerMeter = 100;

    juce::Point<int> pos2pix(float meterMiddleX, float meterMiddleY, int sceneWidth, int sceneHeight)
    {
        int x = static_cast<int>(meterMiddleX * pixelPerMeter * zoomFactor.get() + sceneWidth / 2);
        int y = static_cast<int>(-meterMiddleY * pixelPerMeter * zoomFactor.get() + sceneHeight / 2);

        return juce::Point<int>(x, y);
    }

    juce::Point<float> pix2pos(int pixMiddleX, int pixMiddleY, int sceneWidth, int sceneHeight)
    {
        float x = (pixMiddleX - sceneWidth / 2) / (pixelPerMeter * zoomFactor.get());
        float y = (pixMiddleY - sceneHeight / 2) / (pixelPerMeter * zoomFactor.get());
        return juce::Point<float>(x, -y);
    }

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
