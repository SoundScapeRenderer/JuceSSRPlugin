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

/**
 * This class contains all parameters of the plugin as well as 
 * functions for serialization in a custom XML format.
 */
class PluginParams {
public:
    PluginParams();
    ~PluginParams();

    //==============================================================================

    /// source related parameters
    Param sourceX; //!< source x position in range [-50.0f ... 50.0f]m
    Param sourceY; //!< source y position (inverted y axis) in range [-50.0f ... 50.0f]m
    Param sourceOrientation; //!< source orientation in range [-180.0f ... 180.0f]degs
    Param sourceVol; //!< source vol in range [-96.0f ... 12.0f]dB
    Param sourceLevel; //!< source input level in range [-96.0f ... 12.0f]dB
    ParamStepped<eOnOffState> sourceMute; //!< source muted {eOff, eOn}
    ParamStepped<eSourceType> sourceType; //!< source type {ePoint, ePlane}
    ParamStepped<eOnOffState> sourcePositionLock; //!< source position locked {eOff, eOn}
    Param amplitudeReferenceDistance; //!< SSR's amplitude reference distance in range [0.5f ... 50.0f]m

    /// reference listener related parameters
    Param referenceX; //!< reference listener x position in range [-50.0f ... 50.0f]m
    Param referenceY; //!< reference listener y position (inverted y axis)  in range [-50.0f ... 50.0f]m
    Param referenceOrientation; //!< reference listener orientation in range [-180.0f ... 180.0f]degs
    const float refOrientationOffset; //!< offset due to reference listener image's default orientation

    /// output level related parameters
    Param outputLevelLeft; //!< left output level in range [-96.0f ... 12.0f]dB
    Param outputLevelRight; //!< right output level in range [-96.0f ... 12.0f]dB

    /// GUI scaling and dragging related parameters
    Param currentZoom; //!< current scene zoom in range [25.0f ... 200.0f]%
    Param sceneOffsetX; //!< scene offset x for dragging in range [-50.0f ... 50.0f]m
    Param sceneOffsetY; //!< scene offset y for dragging (inverted y axis)  in range [-50.0f ... 50.0f]m

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
