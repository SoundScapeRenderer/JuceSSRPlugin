/*
  ==============================================================================

    ScenePanel.cpp
    Created: 24 Aug 2016 10:11:28pm
    Author:  Nutty

  ==============================================================================
*/

#include "JuceHeader.h"
#include "ScenePanel.h"
#include "panels/SourceMenuPanel.h"
#include "panels/InfoPanel.h"

//==============================================================================
ScenePanel::ScenePanel(PluginParams &p)
    : PanelBase(p), params(p)
{
    // create clickable button and info window
    addAndMakeVisible(logoButton = new ImageButton("logoButton"));
    logoButton->setButtonText(String::empty);
    logoButton->addListener(this);
    logoButton->setImages(false, true, true,
                          ImageCache::getFromMemory(BinaryData::ssr_logo_png, BinaryData::ssr_logo_pngSize), 1.0f, Colours::transparentWhite,
                          ImageCache::getFromMemory(BinaryData::ssr_logo_png, BinaryData::ssr_logo_pngSize), 1.0f, Colours::transparentWhite,
                          ImageCache::getFromMemory(BinaryData::ssr_logo_png, BinaryData::ssr_logo_pngSize), 1.0f, Colours::transparentWhite);

    addChildComponent(infoWindow = new ResizableWindow("info window", Colours::white, false));
    infoWindow->setAlwaysOnTop(true);
    infoWindow->setContentOwned(new InfoPanel(params), true);

    // create listener components
    addAndMakeVisible(listenerBackground = new ListenerBackgroundComponent());
    listenerBackground->setName("listener background");

    addAndMakeVisible(refListener = new ListenerComponent(listenerBackground));
    refListener->setName("listener");
    refListener->addMouseListener(this, false);

    // create source components
    addAndMakeVisible(sourceVolSlider = new VolLevelSlider("source vol slider"));
    sourceVolSlider->setRange(-96, 12, 0.01);
    sourceVolSlider->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    sourceVolSlider->addListener(this);
    sourceVolSlider->setSkewFactor(3.0);
    sourceVolSlider->setColour(Slider::backgroundColourId, PluginParams::sourceLevelColour);
    sourceVolSlider->setColour(Slider::textBoxOutlineColourId, PluginParams::sourceColourBlue);
    sourceVolSlider->setDefaultSliderValue(params.sourceVol.getDefaultUI());
    sourceVolSlider->addMouseListener(this, false);

    addAndMakeVisible(sourceBackground = new SourceBackgroundComponent());
    sourceBackground->setName("source background");

    addAndMakeVisible(sourceNode = new SourceNodeComponent(sourceBackground));
    sourceNode->setName("source node");
    sourceNode->setNodeColour(PluginParams::sourceColourBlue);
    sourceNode->addMouseListener(this, false);

    addChildComponent(sourceMenu = new ResizableWindow("source menu", Colours::white, false));
    sourceMenu->setContentOwned(new SourceMenuPanel(params, sourceNode), true);

    // create component for scene center point
    addAndMakeVisible(sceneCenter = new ImageComponent());
    sceneCenter->setName("scene center point");
    sceneCenter->setInterceptsMouseClicks(false, false);
    sceneCenter->setImage(ImageCache::getFromMemory(BinaryData::plus_icon_png, BinaryData::plus_icon_pngSize)); //< http://iconmonstr.com/

    // set size of scene component
    setSize(920, 590);

    // register listener and source, must be called after size of scene has been set
    registerListener(refListener, &params.referenceX, &params.referenceY, &params.referenceOrientation,
        std::bind(&ScenePanel::repositionRefListener, this), std::bind(&ScenePanel::rotateRefListener, this));
    registerSource(sourceNode, &params.sourceX, &params.sourceY, std::bind(&ScenePanel::repositionSource, this));
    registerSlider(sourceVolSlider, &params.sourceVol);
}

ScenePanel::~ScenePanel()
{
    listenerBackground = nullptr;
    refListener = nullptr;
    sourceVolSlider = nullptr;
    sourceBackground = nullptr;
    sourceMenu = nullptr;
    sourceNode = nullptr;
    sceneCenter = nullptr;
    logoButton = nullptr;
    infoWindow = nullptr;
}

//==============================================================================

void ScenePanel::paint(Graphics& g)
{
    g.fillAll(PluginParams::sceneBackgroundColour);
}

void ScenePanel::resized()
{
    logoButton->setBounds(20, 510, 70, 70);
    infoWindow->setBounds(20, 20, 300, 500);

    // set source and listener position according to their position parameters and scene drag offset
    int listenerSizeScaled = static_cast<int>(refListenerSize * params.currentZoom.getUI() / 100.0f);
    refListener->setSize(listenerSizeScaled, listenerSizeScaled);
    repositionRefListener();

    int sourceSizeScaled = static_cast<int>(sourceNodeSize * params.currentZoom.getUI() / 100.0f);
    sourceNode->setSize(sourceSizeScaled, sourceSizeScaled);
    repositionSource();

    // set refPoint position from scene center plus scene drag offset
    int refPointSizeScaled = static_cast<int>(centerPointSize * jmax(63.0f, params.currentZoom.getUI()) / 100.0f);
    sceneCenter->setSize(refPointSizeScaled, refPointSizeScaled);

    int pixPosCenterX = static_cast<int>(params.sceneOffsetX.getUI() * getScaledPixelPerMeter() + (getWidth() / 2));
    int pixPosCenterY = static_cast<int>(-params.sceneOffsetY.getUI() * getScaledPixelPerMeter() + (getHeight() / 2));
    sceneCenter->setTopLeftPosition(pixPosCenterX - refPointSizeScaled / 2, pixPosCenterY - refPointSizeScaled / 2);
}

//==============================================================================

void ScenePanel::sliderValueChanged(Slider* sliderThatWasMoved)
{
    handleSlider(sliderThatWasMoved);
}

void ScenePanel::buttonClicked(Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == logoButton)
    {
        /// \todo add content for infopanel
        infoWindow->setVisible(!infoWindow->isVisible());
        sourceMenu->setVisible(false);
    }
}

//==============================================================================

void ScenePanel::mouseDown(const MouseEvent& e)
{
    if (e.mods == ModifierKeys::leftButtonModifier)
    {
        if (e.eventComponent == this)
        {
            // preparing drag scenePanel
            dragStartPosition = Point<float>(params.sceneOffsetX.get(), params.sceneOffsetY.get());
            sourceMenu->setVisible(false);
        }
        else if (e.eventComponent == refListener)
        {
            // preparing drag refListener
            dragStartPosition = Point<float>(params.referenceX.get(), params.referenceY.get());
        }
        else if (e.eventComponent == sourceNode && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            // preparing drag source if position is not fixed
            dragStartPosition = Point<float>(params.sourceX.get(), params.sourceY.get());
        }
    }
    else if (e.mods == ModifierKeys::rightButtonModifier && e.eventComponent == sourceNode)
    {
        // right-click on sourceNode to open/close sourceMenu
        sourceMenu->setVisible(!sourceMenu->isVisible());
    }

    // close infoWindow if it is open
    infoWindow->setVisible(false);
}

void ScenePanel::mouseDrag(const MouseEvent& e)
{
    // left-drag for dragging component
    if (e.mods == ModifierKeys::leftButtonModifier)
    {
        // calculate new positions for dragging
        float deltaX = e.getDistanceFromDragStartX() / getScaledPixelPerMeter();
        float deltaY = e.getDistanceFromDragStartY() / getScaledPixelPerMeter();
        float newPosX = dragStartPosition.x + deltaX;
        float newPosY = dragStartPosition.y - deltaY;

        if (e.eventComponent == this)
        {
            // drag scene
            params.sceneOffsetX.set(newPosX);
            params.sceneOffsetY.set(newPosY);
            resized();
        }
        else if (e.eventComponent == refListener)
        {
            // drag reference listener
            params.referenceX.setUI(newPosX);
            params.referenceY.setUI(newPosY);
            repositionRefListener();
        }
        else if (e.eventComponent == sourceNode && params.sourcePositionLock.getStep() == eOnOffState::eOff)
        {
            // drag source node if position is not fixed
            params.sourceX.setUI(newPosX);
            params.sourceY.setUI(newPosY);
            repositionSource();
        }

    }
    else if (e.mods == ModifierKeys::rightButtonModifier && e.eventComponent == refListener)
    {
        // right-drag on reference listener to rotate reference listener towards mouse position
        float listenerSizeHalf = static_cast<float>(refListener->getWidth() / 2);
        Point<float> listenerCenterPosition = Point<float>(listenerSizeHalf, listenerSizeHalf);
        Point<float> mousePosition = Point<float>(static_cast<float>(e.getPosition().x), static_cast<float>(e.getPosition().y));
        float newAngle = radiansToDegrees(listenerCenterPosition.getAngleToPoint(mousePosition));

        params.referenceOrientation.setUI(-newAngle);
        rotateRefListener();
    }
}

void ScenePanel::mouseDoubleClick(const MouseEvent& e)
{
    if (e.mods.isCtrlDown())
    {
        // focus on refListener
        params.sceneOffsetX.set(-params.referenceX.getUI());
        params.sceneOffsetY.set(-params.referenceY.getUI() + params.sceneOffsetY.getDefaultUI());
    }
    else if (e.mods.isAltDown())
    {
        // focus on source
        params.sceneOffsetX.set(-params.sourceX.getUI());
        params.sceneOffsetY.set(-params.sourceY.getUI() + params.sceneOffsetY.getDefaultUI());
    }
    else
    {
        // focus on scene center point
        params.sceneOffsetX.set(params.sceneOffsetX.getDefaultUI());
        params.sceneOffsetY.set(params.sceneOffsetY.getDefaultUI());
    }

    // reset zoomfactor
    params.currentZoom.set(params.currentZoom.getDefaultUI(), true);
}

void ScenePanel::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel)
{
    // zoom via moving mouse wheel
    if (e.eventComponent == this)
    {
        float delta = wheel.deltaY;
        float currZoom = params.currentZoom.getUI();
        float newZoom = jmin(jmax(params.currentZoom.getMin(), currZoom + 15.0f * delta), params.currentZoom.getMax());
        params.currentZoom.set(newZoom, true);
    }
}

//==============================================================================

void ScenePanel::repositionRefListener()
{
    // reposition reference listener
    int listenerSizeScaled = static_cast<int>(refListener->getWidth());
    Point<int> pixPosRef = pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
    refListener->setTopLeftPosition(pixPosRef.x - listenerSizeScaled / 2, pixPosRef.y - listenerSizeScaled / 2);

    // make sure listenerBackground follows listener
    int paddingL = refListener->getX() - refListener->getWidth() / 2;
    int paddingT = refListener->getY() - refListener->getHeight() / 2;
    listenerBackground->setBounds(paddingL, paddingT, listenerSizeScaled * 2, listenerSizeScaled * 2);

    // update plane wave direction
    updateSourceOrientationAndPlaneWave(true, true);
}

void ScenePanel::rotateRefListener()
{
    refListener->updateListenerOrientation(params.referenceOrientation.getUI() + params.refOrientationOffset);
    updateSourceOrientationAndPlaneWave(true, false);
}

void ScenePanel::repositionSource()
{
    // reposition source node
    int sourceSizeScaled = static_cast<int>(sourceNode->getWidth());
    Point<int> pixPosRef = pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    sourceNode->setTopLeftPosition(pixPosRef.x - sourceSizeScaled / 2, pixPosRef.y - sourceSizeScaled / 2);

    // make sure sourceMenu, sourceVolSlider and sourceBackground always follow sourceNode
    int paddingL = sourceNode->getX() + sourceSizeScaled + 25;
    int paddingT = sourceNode->getY();
    sourceMenu->setBounds(paddingL, paddingT, 250, 225);

    sourceVolSlider->setSize(sourceSizeScaled * 3 / 4, sourceSizeScaled / 3);
    paddingL = sourceNode->getX() + (sourceSizeScaled - sourceVolSlider->getWidth()) / 2;
    paddingT = sourceNode->getY() + static_cast<int>(sourceSizeScaled * 1.1625f);
    sourceVolSlider->setTopLeftPosition(paddingL, paddingT);

    paddingL = sourceNode->getX() - sourceSizeScaled / 2;
    paddingT = sourceNode->getY() - sourceSizeScaled / 2;
    sourceBackground->setBounds(paddingL, paddingT, sourceSizeScaled * 2, sourceSizeScaled * 2);

    // update plane wave direction
    updateSourceOrientationAndPlaneWave(true, true);
}

void ScenePanel::updateSourceOrientationAndPlaneWave(bool updateOrientation, bool updatePlaneWave)
{
    // calculate position angle between source and reference listener
    Point<int> pixPosRef = pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
    Point<int> pixPosSource = pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    float angle = pixPosRef.getAngleToPoint(pixPosSource);

    // calculate angle from which the source is seen by the reference listener in interval ]-180, 180]
    if (updateOrientation)
    {
        float ang = radiansToDegrees(-angle) - params.referenceOrientation.get();
        ang = std::fmod(ang, 360.0f);
        if (ang > 180.0f)
        {
            ang -= 360.0f;
        }
        else if (ang <= -180.0f)
        {
            ang += 360.0f;
        }
        params.sourceOrientation.setUI(ang);
    }

    // update plane wave direction towards reference listener
    if (updatePlaneWave)
    {
        sourceBackground->setPlaneWaveAngle(radiansToDegrees(angle));
    }
}

Point<int> ScenePanel::pos2pix(float meterCenterX, float meterCenterY, int sceneWidth, int sceneHeight)
{
    int x = static_cast<int>(meterCenterX * getScaledPixelPerMeter() + (sceneWidth / 2 + params.sceneOffsetX.getUI() * getScaledPixelPerMeter()));
    int y = static_cast<int>(-meterCenterY * getScaledPixelPerMeter() + (sceneHeight / 2 - params.sceneOffsetY.getUI() * getScaledPixelPerMeter()));

    return Point<int>(x, y);
}

float ScenePanel::getScaledPixelPerMeter()
{
    return pixelPerMeter * params.currentZoom.getUI() / 100.0f;
}

//==============================================================================

void ScenePanel::timerCallback()
{
    PanelBase::timerCallback();

    // update source level
    sourceVolSlider->refreshVolLevel(params.sourceLevel.getUI());
}
