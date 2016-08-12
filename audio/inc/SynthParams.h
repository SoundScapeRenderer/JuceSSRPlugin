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

    // source parameter
    Param sourceX;
    Param sourceY;
    Param sourceOrientation;
    Param sourceVol;
    Param sourceLevel;
    ParamStepped<eOnOffState> sourceMute;
    ParamStepped<eSourceType> sourceType;
    ParamStepped<eOnOffState> sourcePositionLock;

    // reference listener parameter
    Param referenceX;
    Param referenceY;
    Param referenceOrientation;
    Param amplitudeReferenceDistance;

    // routing and output level parameter
    ParamStepped<eInputChannel> inputChannel;
    Param outputLevelLeft;
    Param outputLevelRight;

    // GUI scaling parameter
    Param zoomFactor;
    const int pixelPerMeter;

    //==============================================================================

    // original SSR colour codes
    static const Colour sourceColourBrown;
    static const Colour sourceColourBlue;
    static const Colour sourceColourGreen;
    static const Colour sourceColourViolet;
    static const Colour sourceColourRed;
    static const Colour sceneBackgroundColour;
    static const Colour sourceLevelColour;

    //==============================================================================

    /**
        Converts a meter position into a pixel coordinate of a scene with given width and height.
        Reference point is the center of that scene, where 1m is equivalent to 100px.
        Scaling can be used by setting the zoomFactor variable of SynthParams.
    
        @param meterCenterX centerX position in meter of an object in the scene GUI
        @param meterCenterY centerY position in meter of an object in the scene GUI
        @param screenWidth width of the scene GUI in pixel
        @param screenHeight height of the scene GUI in pixel
        @return coordinate point in pixel with inverse y
     */
    juce::Point<int> pos2pix(float meterCenterX, float meterCenterY, int screenWidth, int screenHeight);

    /**
        Converts a pixel coordinate of a scene with given width and height into a meter position.
        Reference point is the center of that scene, where 1m is equivalent to 100px.
        Scaling can be used by setting the zoomFactor variable of SynthParams.

        @param pixCenterX centerX pixel of an object in the scene GUI
        @param pixCenterY centerY pixel of an object in the scene GUI
        @param screenWidth width of the scene GUI in pixel
        @param screenHeight height of the scene GUI in pixel
        @return position point in meter with inverse y
    */
    juce::Point<float> pix2pos(int pixCenterX, int pixCenterY, int screenWidth, int screenHeight);

    /**
        Round float value to not more than 2 numbers after comma.
    */
    float roundNearest(float val);

    //==============================================================================

private:
};
