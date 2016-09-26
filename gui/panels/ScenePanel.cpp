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
ScenePanel::ScenePanel(SynthParams &p)
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
    infoWindow->setContentOwned(new InfoPanel(), true);

    // create listener components
    addAndMakeVisible(listenerBackground = new ListenerBackgroundComponent());
    listenerBackground->setName("listener background");

    addAndMakeVisible(refListener = new ListenerComponent(params, listenerBackground));
    refListener->setName("listener");

    // create source components
    addAndMakeVisible(sourceVolSlider = new VolLevelSlider("source vol slider"));
    sourceVolSlider->setRange(-96, 12, 0.01);
    sourceVolSlider->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    sourceVolSlider->addListener(this);
    sourceVolSlider->setSkewFactor(3);
    sourceVolSlider->setColour(Slider::backgroundColourId, SynthParams::sourceLevelColour);
    sourceVolSlider->setColour(Slider::textBoxOutlineColourId, SynthParams::sourceColourBlue);

    addAndMakeVisible(sourceBackground = new SourceBackgroundComponent());
    sourceBackground->setName("source background");

    addChildComponent(sourceMenu = new ResizableWindow("source menu", Colours::white, false));

    addAndMakeVisible(sourceNode = new SourceNodeComponent(params, sourceVolSlider, sourceBackground, sourceMenu));
    sourceNode->setName("source node");
    sourceNode->setNodeColour(SynthParams::sourceColourBlue);

    // NOTE: must be called after both sourceNode and sourceMenu has been created!
    sourceMenu->setContentOwned(new SourceMenuPanel(params, sourceNode), true);

    // create component for scene center point
    addAndMakeVisible(sceneCenter = new ImageComponent());
    sceneCenter->setName("scene center point");
    sceneCenter->setInterceptsMouseClicks(false, false);
    sceneCenter->setImage(ImageCache::getFromMemory(BinaryData::plus_icon_png, BinaryData::plus_icon_pngSize)); //< http://iconmonstr.com/
    
    // reset scene drag offset to default
    params.sceneOffsetX.setUI(params.sceneOffsetX.getDefaultUI());
    params.sceneOffsetY.setUI(params.sceneOffsetY.getDefaultUI());

    // set size of scene component
    setSize(920, 590);

    // register listener and source, must be called after size of scene has been set
    registerListener(refListener, &params.referenceX, &params.referenceY, &params.referenceOrientation, getWidth(), getHeight());
    registerSource(sourceNode, &params.sourceX, &params.sourceY, &params.sourceVol, &params.sourceLevel, getWidth(), getHeight());
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
    g.fillAll(SynthParams::sceneBackgroundColour);
}

void ScenePanel::resized()
{
    logoButton->setBounds(20, 510, 70, 70);
    infoWindow->setBounds(20, 20, 280, 490);

    /// \todo initial size and scaling into own classes? relocate into panelbase?
    // set source and listener position according to their position parameters and scene drag offset
    int listenerSizeScaled = static_cast<int>(refListenerSize * params.zoomFactor.get() / 100.0f);
    refListener->setSize(listenerSizeScaled, listenerSizeScaled);
    refListener->relocate();

    int sourceSizeScaled = static_cast<int>(sourceNodeSize * params.zoomFactor.get() / 100.0f);
    sourceNode->setSize(sourceSizeScaled, sourceSizeScaled);
    sourceNode->relocate();

    // set refPoint position from scene center plus scene drag offset
    int refPointSizeScaled = static_cast<int>(centerPointSize * jmax(63.0f, params.zoomFactor.get()) / 100.0f);
    int paddingL = static_cast<int>(getWidth() / 2 - refPointSizeScaled / 2 + params.sceneOffsetX.get());
    int paddingT = static_cast<int>(getHeight() / 2 - refPointSizeScaled / 2 + params.sceneOffsetY.get());
    sceneCenter->setBounds(paddingL, paddingT, refPointSizeScaled, refPointSizeScaled);
}

void ScenePanel::childBoundsChanged(Component *child)
{
    if (child == refListener || child == sourceNode)
    {
        int paddingL, paddingT;
        if (child == sourceNode)
        {
            int sourceSizeScaled = static_cast<int>(sourceNode->getWidth());

            // make sure sourceMenu, sourceVolSlider and sourceBackground always follow sourceNode
            paddingL = sourceNode->getX() + sourceSizeScaled + 25;
            paddingT = sourceNode->getY();
            sourceMenu->setBounds(paddingL, paddingT, 250, 225);

            sourceVolSlider->setSize(sourceSizeScaled * 3 / 4, sourceSizeScaled / 3);
            paddingL = sourceNode->getX() + (sourceSizeScaled - sourceVolSlider->getWidth()) / 2;
            paddingT = sourceNode->getY() + static_cast<int>(sourceSizeScaled * 1.1625f);
            sourceVolSlider->setTopLeftPosition(paddingL, paddingT);

            // sourceBackground must be double the size of source
            paddingL = sourceNode->getX() - sourceSizeScaled / 2;
            paddingT = sourceNode->getY() - sourceSizeScaled / 2;
            sourceBackground->setBounds(paddingL, paddingT, sourceSizeScaled * 2, sourceSizeScaled * 2);
        }
        else if (child == refListener)
        {
            /// \todo too much zoom leads to host ui stuttering, scene resized() too much cpu?
            /// \todo especially this part here
            // make sure listenerBackground follows listener
            // listenerBackground must be double the size of source
            paddingL = refListener->getX() - refListener->getWidth() / 2;
            paddingT = refListener->getY() - refListener->getHeight() / 2;
            listenerBackground->setBounds(paddingL, paddingT, refListener->getWidth() * 2, refListener->getHeight() * 2);
        }

        // refresh plane wave of source background so that always points at reference listener
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
        juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
        float angle = pixPosRef.getAngleToPoint(pixPosSource);
        sourceBackground->setPlaneWaveAngle(radiansToDegrees(angle));
    }
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
    }
}

//==============================================================================

void ScenePanel::mouseDown(const MouseEvent& e)
{
    ignoreUnused(e);
    dragStartOffset = Point<float>(params.sceneOffsetX.get(), params.sceneOffsetY.get());
}

void ScenePanel::mouseDrag(const MouseEvent& e)
{
    float deltaX = e.getDistanceFromDragStartX() / 1.0f;
    float deltaY = e.getDistanceFromDragStartY() / 1.0f;
    params.sceneOffsetX.setUI(dragStartOffset.x + deltaX);
    params.sceneOffsetY.setUI(dragStartOffset.y + deltaY);
    resized();
}

void ScenePanel::mouseDoubleClick(const MouseEvent& e)
{
    ignoreUnused(e);
    params.sceneOffsetX.setUI(params.sceneOffsetX.getDefaultUI());
    params.sceneOffsetY.setUI(params.sceneOffsetY.getDefaultUI());
    params.zoomFactor.set(params.zoomFactor.getDefaultUI(), true);
}

void ScenePanel::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel)
{
    ignoreUnused(e);
    float delta = wheel.deltaY;
    float currZoom = params.zoomFactor.getUI();
    float newZoom = jmin(jmax(params.zoomFactor.getMin(), currZoom + 15.0f * delta), params.zoomFactor.getMax());
    params.zoomFactor.set(newZoom, true);
}
