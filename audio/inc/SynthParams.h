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

    //==============================================================================

    /// source parameter
    Param sourceX; //!< source x position in range [-50.0f ... 50.0f]m
    Param sourceY; //!< source y position in range [-50.0f ... 50.0f]m
    Param sourceOrientation; //!< source orientation in range [-180.0f ... 180.0f]degs
    Param sourceVol; //!< source vol in range [-96.0f ... 12.0f]dB
    Param sourceLevel; //!< source level in range [-96.0f ... 12.0f]dB
    ParamStepped<eOnOffState> sourceMute; //!< source muted {eOff, eOn}
    ParamStepped<eSourceType> sourceType; //!< source type {ePoint, ePlane}
    ParamStepped<eOnOffState> sourcePositionLock; //!< source position locked {eOff, eOn}

    /// reference listener parameter
    Param referenceX; //!< reference listener x position in range [-50.0f ... 50.0f]m
    Param referenceY; //!< reference listener y position in range [-50.0f ... 50.0f]m
    Param referenceOrientation; //!< reference listener orientation in range [0.0f ... 360.0f]degs
    Param amplitudeReferenceDistance; //!< SSR's amplitude reference distance in range [0.0f ... 50.0f]m

    /// routing and output level parameter
    ParamStepped<eInputChannel> inputChannel; //!< host track input channel {eLeftChannel/mono, eRightChannel}
    Param outputLevelLeft; //!< left output level in range [-96.0f ... 12.0f]dB
    Param outputLevelRight; //!< right output level in range [-96.0f ... 12.0f]dB

    /// GUI scaling and dragging parameter
    Param zoomFactor; //!< scene zoom factor in range [25.0f ... 200.0f]%
    const int pixelPerMeter; //!< pixel per meter scene scale parameter 125px = 1m
    Param sceneOffsetX; //!< scene offset x for dragging in range [-2500.0f ... 2500.0f]px
    Param sceneOffsetY; //!< scene offset y for dragging in range [-2500.0f ... 2500.0f]px

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
     * Round float value to not more than 2 numbers after comma.
     */
    float roundNearest(float val);

    //==============================================================================

    std::vector<Param*> serializeParams; //!< vector of params to be serialized
    String patchName = "";
    bool patchNameDirty = false;
    const String appName = ProjectInfo::projectName;
    const String appVersion = ProjectInfo::versionString; //!< application version to be written into the xml

    /**
     * Store host state by creating XML file to serialize parameters by using writeXMLPatchTree().
     * @param destData host data
     */
    void writeXMLPatchHost(MemoryBlock& destData);

    /**
     * Create XML file to serialize parameters by using writeXMLPatchTree().
     */
    void writeXMLPatchStandalone();

    /**
     * Restore host state by converting binary data into a XML file and set serialized parameters by using fillValues().
     * @param data binary data to return to XML
     * @param sizeInBytes data size
     */
    void readXMLPatchHost(const void * data, int sizeInBytes);

    /**
     * Read XML file to set serialized parameters by using fillValues().
     */
    void readXMLPatchStandalone();

    //==============================================================================

private:

    /**
     * Adds an element to the XML tree.
     * @param patch XML pstch to work on
     * @param name parameter name
     * @param value  value of parameter to be added
     */
    void addElement(XmlElement* patch, String name, float value);

    /**
     * Write the XML patch tree for parameters to be serialized.
     * @param patch XML patch to work on
     */
    void writeXMLPatchTree(XmlElement * patch);

    /**
     * Set the parameters if they exist in the XML patch.
     * @param patch XML patch to work on
     * @param paramName name to check whether parameter exist in XML patch
     * @param param parameter to set
     */
    void fillValueIfExists(XmlElement * patch, String paramName, Param& param);

    /**
     * Iterate over parameters and set the values in the xml by using fillValueIfExists().
     * @param patch XML patch to work on
     */
    void fillValues(XmlElement * patch);
};
