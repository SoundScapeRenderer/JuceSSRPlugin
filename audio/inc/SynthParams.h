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

    //==============================================================================

    /// source parameter
    Param sourceX; //!< source x position in range [-50.0f ... 50.0f]m
    Param sourceY; //!< source y position in range [-50.0f ... 50.0f]m
    Param sourceOrientation; //!< source orientation in range [-180.0f ... 180.0f]degs
    Param sourceVol; //!< source vol in range [-96.0f ... 12.0f]dB
    Param sourceLevel; //!< source input level in range [-96.0f ... 12.0f]dB
    ParamStepped<eOnOffState> sourceMute; //!< source muted {eOff, eOn}
    ParamStepped<eSourceType> sourceType; //!< source type {ePoint, ePlane}
    ParamStepped<eOnOffState> sourcePositionLock; //!< source position locked {eOff, eOn}

    /// reference listener parameter
    Param referenceX; //!< reference listener x position in range [-50.0f ... 50.0f]m
    Param referenceY; //!< reference listener y position in range [-50.0f ... 50.0f]m
    Param referenceOrientation; //!< reference listener orientation in range [-180.0f ... 180.0f]degs
    const float refOrientationOffset; //!< offset due to reference listener image's default orientation
    Param amplitudeReferenceDistance; //!< SSR's amplitude reference distance in range [0.0f ... 50.0f]m

    /// output level parameter
    Param outputLevelLeft; //!< left output level in range [-96.0f ... 12.0f]dB
    Param outputLevelRight; //!< right output level in range [-96.0f ... 12.0f]dB

    /// GUI scaling and dragging parameter
    Param currentZoom; //!< current scene zoom in range [25.0f ... 200.0f]%
    const int pixelPerMeter; //!< pixel per meter scene scale parameter 125px = 1m
    Param sceneOffsetX; //!< scene offset x for dragging in range [-25.0f ... 25.0f]m
    Param sceneOffsetY; //!< scene offset y for dragging in range [-25.0f ... 25.0f]m

    //==============================================================================

    /// original SSR colour codes
    static const Colour sourceColourBrown;
    static const Colour sourceColourBlue;
    static const Colour sourceColourGreen;
    static const Colour sourceColourViolet;
    static const Colour sourceColourRed;
    static const Colour sceneBackgroundColour;
    static const Colour sourceLevelColour;

    //==============================================================================

    /**
     * Converts a meter position into a pixel coordinate of a scene with given width and height.
     * Reference point is the center of that scene, where 1m is equivalent to 125px.
     * Reference point can be moved by setting the sceneOffsetX and sceneOffsetY parameter of SynthParams.
     * Scaling can be used by setting the zoomFactor parameter of SynthParams.
     * @param meterCenterX centerX position in meter of an object in the scene GUI
     * @param meterCenterY centerY position in meter of an object in the scene GUI
     * @param sceneWidth width of the scene GUI in pixel
     * @param sceneHeight height of the scene GUI in pixel
     * @return coordinate point in pixel with inverse y
     */
    juce::Point<int> pos2pix(float meterCenterX, float meterCenterY, int sceneWidth, int sceneHeight);

    /**
     * Converts a pixel coordinate of a scene with given width and height into a meter position.
     * Reference point is the center of that scene, where 1m is equivalent to 125px.
     * Reference point can be moved by setting the sceneOffsetX and sceneOffsetY parameter of SynthParams.
     * Scaling can be used by setting the zoomFactor parameter of SynthParams.
     * @param pixCenterX centerX pixel of an object in the scene GUI
     * @param pixCenterY centerY pixel of an object in the scene GUI
     * @param sceneWidth width of the scene GUI in pixel
     * @param sceneHeight height of the scene GUI in pixel
     * @return position point in meter with inverse y
     */
    juce::Point<float> pix2pos(int pixCenterX, int pixCenterY, int sceneWidth, int sceneHeight);

    /**
     * Pixel per meter value that takes the current zoom scale factor into account.
     * Needed for some meter to pixel conversion and vice versa.
     * scaledPixelPerMeter = pixelPerMeter * currentZoom / 100.0f.
     */
    float getScaledPixelPerMeter();

    /**
     * Get name of source type.
     * @param index eSourceType index
     * @return name of eSourceType index
     */
    static const char* getSourceTypeNames(int index);

    //==============================================================================

    std::vector<Param*> serializeParams; //!< vector of params to be serialized
    String patchName = "";
    bool patchNameDirty = false;
    const String appName = ProjectInfo::projectName;
    const String appVersion = ProjectInfo::versionString; //!< application version to be written into the xml

    /**
     * Store plugin state in host by creating XML patch and converting it into MemoryBlock to serialize parameters.
     * Will be called in the host.
     * @param destData host data
     */
    void writeXMLPatchHost(MemoryBlock& destData);

    /**
     * Creates XML via file chooser and write XML patch to serialize parameters.
     */
    void writeXMLPatchStandalone();

    /**
     * Restore plugin state in host by converting binary data into a XML patch tree and set serialized parameters.
     * Will be called in the host.
     * @param data binary data to convert into XML patch
     * @param sizeInBytes data size
     */
    void readXMLPatchHost(const void * data, int sizeInBytes);

    /**
     * Read XML patch tree from file via file chooser and set serialized parameters.
     */
    void readXMLPatchStandalone();

    //==============================================================================

    /** 
     * Current position information of audio playhead using double buffering.
     * Call positionInfo[getAudioIndex()] to get the newest info.
     */
    std::array<AudioPlayHead::CurrentPositionInfo, 2> positionInfo;

    std::atomic<int> positionIndex;
    int getAudioIndex();
    int getGUIIndex();

    //==============================================================================

private:

    /**
     * Write the XML patch tree for parameters to be serialized.
     * @param patch XML patch to write to
     */
    void writeXMLPatchTree(XmlElement * patch);

    /**
     * Iterate over parameters and read the values in the XML patch.
     * @param patch XML patch to read from
     */
    void readXMLPatchTree(XmlElement * patch);
};
