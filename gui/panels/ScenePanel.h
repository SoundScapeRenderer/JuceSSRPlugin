/*
  ==============================================================================

    ScenePanel.h
    Created: 24 Aug 2016 10:11:28pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef SCENEPANEL_H_INCLUDED
#define SCENEPANEL_H_INCLUDED

#include "JuceHeader.h"
#include "SynthParams.h"
#include "panels/PanelBase.h"
#include "ListenerComponent.h"
#include "ListenerBackgroundComponent.h"
#include "SourceNodeComponent.h"
#include "SourceBackgroundComponent.h"
#include "VolLevelSlider.h"

//==============================================================================
/**
 * Scene panel of the SSR where source node and listener can be dragged.
 * Scene with all child components within can be dragged and zoomed in/out
 * via scrolling.
 * On double-click the zoom and dragging offset can be reset to default.
 */
class ScenePanel : public PanelBase,
                   public SliderListener,
                   public ButtonListener
{
public:
    ScenePanel(SynthParams &p);
    ~ScenePanel();

    //==============================================================================

    void paint(Graphics& g);
    void resized();
    void childBoundsChanged(Component *child);

    //==============================================================================

    void sliderValueChanged(Slider* sliderThatWasMoved);
    void buttonClicked(Button* buttonThatWasClicked);

    //==============================================================================

    void mouseDown(const MouseEvent& e);
    void mouseDrag(const MouseEvent& e);
    void mouseDoubleClick(const MouseEvent& e);
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel);

    //==============================================================================

private:
    SynthParams &params;
    Image plusImg; //< http://iconmonstr.com/
    Image logoImg;

    const int listenerWidth = 90;
    const int listenerHeight = 90;
    const int sourceSize = 90;
    const int refPointSize = 8;
    Point<float> dragStartOffset = Point<float>(0.0f, 0.0f);

    //==============================================================================

    ScopedPointer<ListenerBackgroundComponent> listenerBackground;
    ScopedPointer<ListenerComponent> listener;
    ScopedPointer<VolLevelSlider> sourceVolSlider;
    ScopedPointer<SourceBackgroundComponent> sourceBackground;
    ScopedPointer<DocumentWindow> sourceMenu;
    ScopedPointer<SourceNodeComponent> sourceNode;
    ScopedPointer<ImageComponent> refPoint;
    ScopedPointer<ImageButton> logoButton;
    ScopedPointer<DocumentWindow> infoWindow;

    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScenePanel)
};


#endif  // SCENEPANEL_H_INCLUDED
