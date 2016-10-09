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

#include "PanelBase.h"
#include "components/VolLevelSlider.h"

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
    ScenePanel(PluginParams &p);
    ~ScenePanel();

    //==============================================================================

    void paint(Graphics& g);
    void resized();

    //==============================================================================

    void sliderValueChanged(Slider* sliderThatWasMoved);
    void buttonClicked(Button* buttonThatWasClicked);

    //==============================================================================

    /**
     * On left-click, prepare for dragging components.
     * On right-click, open/cloase source menu.
     */
    void mouseDown(const MouseEvent& e);

    /**
     * Handle dragging routine and make sure background components etc. follow sourceNode or refListener.
     * Right-click drag to rotate refListener.
     */
    void mouseDrag(const MouseEvent& e);

    /**
     * Double click on scene to reset zoom and drag offset.
     * Double click on scene while holding CTRL will jump to listener.
     * Double click on scene while holding ALT will jump to source.
     * Resets zoom factor to default.
     */
    void mouseDoubleClick(const MouseEvent& e);
    
    /**
     * Zoom on ScenePanel via scrolling on mouse wheel.
     */
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel);

    //==============================================================================

private:
    PluginParams &params;
    Point<float> dragStartPosition = Point<float>(0.0f, 0.0f);

    const int refListenerSize = 85; //!< default reference listener size
    const int sourceNodeSize = 85; //!< default source node size
    const int centerPointSize = 8; //!< default center point size
    const int pixelPerMeter = 125; //!< pixel per meter scene scale parameter where 125px = 1m

    //==============================================================================

    /**
     * Reposition refListener and make sure listenerBackground follows it.
     * After repositioning call updateSourcePlaneWave().
     */
    void repositionRefListener();

    /**
     * Reposition sourceNode and make sure sourceVolSlider, sourceBackground
     * and sourceMenu follow it.
     * After repositioning call updateSourcePlaneWave().
     */
    void repositionSource();

    /**
     * Updates sourceOrientation/angle from which the source is seen by the reference listener
     * and/or updates the plane wave direction of sourceBackground towards refListener.
     * @param updateOrientation if true then update source orientation parameter
     * @param updatePlaneWave if true then updates and repaint plane wave angle
     */
    void updateSourceOrientationAndPlaneWave(bool updateOrientation, bool updatePlaneWave);

    /**
     * Converts a meter position into a pixel coordinate of a scene with given width and height.
     * Reference point is the center of that scene, where 1m is equivalent to set pixelPerMeter.
     * Reference point can be moved by setting the sceneOffsetX and sceneOffsetY parameter of PluginParams.
     * Scaling can be used by setting the zoomFactor parameter of PluginParams.
     * @param meterCenterX centerX position in meter of an object in the scene UI
     * @param meterCenterY centerY position in meter of an object in the scene UI
     * @param sceneWidth width of the scene UI in pixel
     * @param sceneHeight height of the scene UI in pixel
     * @return coordinate point in pixel with inverse y axis
     */
    Point<int> pos2pix(float meterCenterX, float meterCenterY, int sceneWidth, int sceneHeight);

    /**
     * Pixel per meter value that takes the current zoom scale factor into account.
     * Needed for some meter to pixel conversion.
     * scaledPixelPerMeter = pixelPerMeter * currentZoom / 100.0f.
     */
    float getScaledPixelPerMeter();

    //==============================================================================

    void timerCallback() override;

    //==============================================================================

    ScopedPointer<ListenerBackgroundComponent> listenerBackground;
    ScopedPointer<ListenerComponent> refListener;
    ScopedPointer<VolLevelSlider> sourceVolSlider;
    ScopedPointer<SourceBackgroundComponent> sourceBackground;
    ScopedPointer<SourceNodeComponent> sourceNode;
    ScopedPointer<ResizableWindow> sourceMenu;
    ScopedPointer<ImageComponent> sceneCenter;
    ScopedPointer<ImageButton> logoButton;
    ScopedPointer<ResizableWindow> infoWindow;

    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScenePanel)
};


#endif  // SCENEPANEL_H_INCLUDED
