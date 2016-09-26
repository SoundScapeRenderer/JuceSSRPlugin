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
#include "panels/PanelBase.h"

//==============================================================================
/**
 * Scene panel of the SSR where source node and listener can be dragged.
 * Scene with all child components within can be dragged and zoomed in/out
 * via scrolling. On double-click the zoom and dragging offset can be reset to default.
 * Designed according to SSR's scene.
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

    /**
     * If source or reference listener has been moved or resized then make sure
     * affilliated components such as background etc. follow them.
     * Further redraw plane wave directed at reference listener if necessary. 
     */
    void childBoundsChanged(Component *child);

    //==============================================================================

    void sliderValueChanged(Slider* sliderThatWasMoved);
    void buttonClicked(Button* buttonThatWasClicked);

    //==============================================================================

    /// drag scene
    void mouseDown(const MouseEvent& e);
    void mouseDrag(const MouseEvent& e);

    /// reset dragging offset and zoom
    void mouseDoubleClick(const MouseEvent& e);
    
    /// zoom in and out by scrolling
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel);

    //==============================================================================

private:
    SynthParams &params;

    const int refListenerSize = 90;
    const int sourceNodeSize = 90;
    const int centerPointSize = 8;
    Point<float> dragStartOffset = Point<float>(0.0f, 0.0f);

    //==============================================================================

    ScopedPointer<ListenerBackgroundComponent> listenerBackground;
    ScopedPointer<ListenerComponent> refListener;
    ScopedPointer<VolLevelSlider> sourceVolSlider;
    ScopedPointer<SourceBackgroundComponent> sourceBackground;
    ScopedPointer<ResizableWindow> sourceMenu;
    ScopedPointer<SourceNodeComponent> sourceNode;
    ScopedPointer<ImageComponent> sceneCenter;
    ScopedPointer<ImageButton> logoButton;
    ScopedPointer<ResizableWindow> infoWindow;

    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScenePanel)
};


#endif  // SCENEPANEL_H_INCLUDED
