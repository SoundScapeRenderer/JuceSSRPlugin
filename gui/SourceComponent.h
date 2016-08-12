/*
  ==============================================================================

    SourceContainer.h
    Created: 9 Aug 2016 1:31:22pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef SOURCECOMPONENT_H_INCLUDED
#define SOURCECOMPONENT_H_INCLUDED

#include "JuceHeader.h"

#include "SynthParams.h"
#include "VolLevelSlider.h"
#include "SourceBackgroundComponent.h"
#include "SourceNodeComponent.h"

//==============================================================================
/*
*/
class SourceComponent    : public Component,
                           public SliderListener
{
public:
    SourceComponent(SynthParams &p, int sourceNodeSize, Colour c);
    ~SourceComponent();

    void paint (Graphics&g);
    void resized();
    
    void childBoundsChanged(Component *c);
    void sliderValueChanged(Slider *s);

    void setScreenSize(int width, int height);
    void relocateSourceNode();
    void repaintSourceNode();

    void repaintPlaneWave(bool isPlaneWave);
    void repaintPlaneWave(float angle, bool isPlaneWave);

    void setVol(float volume);
    void refreshVolLevel(float level);

private:
    SynthParams &params;
    int nodeSize;
    Colour nodeColour;

    ScopedPointer<VolLevelSlider> levelSlider;
    ScopedPointer<SourceBackgroundComponent> sourceBackground;
    ScopedPointer<DocumentWindow> sourceMenu;
    ScopedPointer<SourceNodeComponent> sourceNode;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceComponent)
};


#endif  // SOURCECOMPONENT_H_INCLUDED
