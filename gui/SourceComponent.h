/*
  ==============================================================================

    SourceContainer.h
    Created: 9 Aug 2016 1:31:22pm
    Author:  Smoky

  ==============================================================================
*/

#ifndef SOURCECOMPONENT_H_INCLUDED
#define SOURCECOMPONENT_H_INCLUDED

#include "JuceHeader.h"

#include "SynthParams.h"
#include "GainLevelSlider.h"
#include "SourceBackgroundComponent.h"
#include "SourceNodeComponent.h"

//==============================================================================
/*
*/
class SourceComponent    : public Component,
                           public SliderListener
{
public:
    SourceComponent(SynthParams &p);
    ~SourceComponent();

    void paint (Graphics&g);
    void resized();
    
    void childBoundsChanged(Component *c);
    void sliderValueChanged(Slider *s);

    void refreshBackground(float angle, bool isPlaneWave);

private:
    SynthParams &params;
    
    ScopedPointer<GainLevelSlider> gainSlider;
    ScopedPointer<SourceBackgroundComponent> sourceBackground;
    ScopedPointer<DocumentWindow> sourceMenu;
    ScopedPointer<SourceNodeComponent> source;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceComponent)
};


#endif  // SOURCECOMPONENT_H_INCLUDED
