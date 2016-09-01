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
    // load images from binaries
    plusImg = ImageCache::getFromMemory(BinaryData::plus_icon_png, BinaryData::plus_icon_pngSize);
    logoImg = ImageCache::getFromMemory(BinaryData::ssr_logo_png, BinaryData::ssr_logo_pngSize);

    // create all necessary child components
    addAndMakeVisible(logoButton = new ImageButton("logoButton"));
    logoButton->setButtonText(String::empty);
    logoButton->addListener(this);
    logoButton->setImages(false, true, true,
                          logoImg, 1.0f, Colours::transparentWhite,
                          logoImg, 1.0f, Colours::transparentWhite,
                          logoImg, 1.0f, Colours::transparentWhite);

    addAndMakeVisible(infoWindow = new DocumentWindow("info window", Colours::white, DocumentWindow::closeButton));
    infoWindow->setName("info window");
    infoWindow->setTitleBarHeight(0);
    infoWindow->setDraggable(false);
    infoWindow->setVisible(false);
    infoWindow->setAlwaysOnTop(true);
    infoWindow->setContentOwned(new InfoPanel(), true);

    addAndMakeVisible(listenerBackground = new ListenerBackgroundComponent());
    listenerBackground->setName("listener background");

    addAndMakeVisible(listener = new ListenerComponent(params, listenerBackground));
    listener->setName("listener");

    addAndMakeVisible(sourceVolSlider = new VolLevelSlider("source vol slider"));
    sourceVolSlider->setRange(-96, 12, 0);
    sourceVolSlider->setSliderStyle(Slider::LinearBar);
    sourceVolSlider->setTextBoxStyle(Slider::NoTextBox, false, 80, 20);
    sourceVolSlider->addListener(this);
    sourceVolSlider->setSkewFactor(3);
    sourceVolSlider->setColour(Slider::backgroundColourId, SynthParams::sourceLevelColour);
    sourceVolSlider->setColour(Slider::textBoxOutlineColourId, SynthParams::sourceColourBlue);

    addAndMakeVisible(sourceBackground = new SourceBackgroundComponent());
    sourceBackground->setName("source background");

    addAndMakeVisible(sourceMenu = new DocumentWindow("source menu", Colours::white, DocumentWindow::closeButton));
    sourceMenu->setName("source menu");
    sourceMenu->setTitleBarHeight(0);
    sourceMenu->setDraggable(false);
    sourceMenu->setVisible(false);

    addAndMakeVisible(sourceNode = new SourceNodeComponent(params, sourceVolSlider, sourceBackground, sourceMenu));
    sourceNode->setName("source node");
    sourceNode->setNodeColour(SynthParams::sourceColourBlue);

    // NOTE: must be called after both sourceNode and sourceMenu has been created!
    sourceMenu->setContentOwned(new SourceMenuPanel(params, sourceNode), true);

    addAndMakeVisible(refPoint = new ImageComponent());
    refPoint->setName("reference point");
    refPoint->setInterceptsMouseClicks(false, false);
    refPoint->setImage(plusImg);

    setSize(920, 590);
    
    // reset scene drag offset to default
    params.sceneOffsetX.setUI(params.sceneOffsetX.getDefaultUI());
    params.sceneOffsetY.setUI(params.sceneOffsetY.getDefaultUI());

    // register listener and source for host changes etc.
    registerListener(listener, &params.referenceX, &params.referenceY, &params.referenceOrientation, getWidth(), getHeight());
    registerSource(sourceNode, &params.sourceX, &params.sourceY, &params.sourceVol, &params.sourceLevel, getWidth(), getHeight());
}

ScenePanel::~ScenePanel()
{
    listenerBackground = nullptr;
    listener = nullptr;
    sourceVolSlider = nullptr;
    sourceBackground = nullptr;
    sourceMenu = nullptr;
    sourceNode = nullptr;
    refPoint = nullptr;
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
    logoButton->setBounds(20, getHeight() - 78, 70, 70);
    infoWindow->setBounds(55, 40, 280, 470);

    // set source and listener position according to their position parameters and scene drag offset
    int listenerW = static_cast<int>(listenerWidth * params.zoomFactor.get() / 100.0f);
    int listenerH = static_cast<int>(listenerHeight * params.zoomFactor.get() / 100.0f);
    juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
    listener->setBounds(pixPosRef.x - listenerW / 2, pixPosRef.y - listenerH / 2, listenerW, listenerH);

    int sourceNodeSize = static_cast<int>(sourceSize * params.zoomFactor.get() / 100.0f);
    juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    sourceNode->setBounds(pixPosSource.x - sourceNodeSize / 2, pixPosSource.y - sourceNodeSize / 2, sourceNodeSize, sourceNodeSize);

    // set refPoint position from scene center plus scene drag offset
    int refPointSizeScaled = static_cast<int>(refPointSize * jmax(63.0f, params.zoomFactor.get()) / 100.0f);
    int paddingL = static_cast<int>(getWidth() / 2 - refPointSizeScaled / 2 + params.sceneOffsetX.get());
    int paddingT = static_cast<int>(getHeight() / 2 - refPointSizeScaled / 2 + params.sceneOffsetY.get());
    refPoint->setBounds(paddingL, paddingT, refPointSizeScaled, refPointSizeScaled);
}

void ScenePanel::childBoundsChanged(Component *child)
{
    if (child == listener || child == sourceNode)
    {
        int paddingL, paddingT;
        if (child == sourceNode)
        {
            int sourceNodeSize = static_cast<int>(sourceNode->getWidth());

            // make sure sourceMenu, sourceVolSlider and sourceBackground always follow sourceNode
            paddingL = sourceNode->getX() + sourceNodeSize + 25;
            paddingT = sourceNode->getY() + sourceNodeSize / 2;
            sourceMenu->setBounds(paddingL, paddingT, 250, 225);

            sourceVolSlider->setSize(sourceNodeSize * 3 / 4, sourceNodeSize / 3);
            paddingL = sourceNode->getX() + (sourceNodeSize - sourceVolSlider->getWidth()) / 2;
            paddingT = sourceNode->getY() + static_cast<int>(sourceNodeSize * 1.1625f);
            sourceVolSlider->setTopLeftPosition(paddingL, paddingT);

            // sourceBackground must be double the size of source
            paddingL = sourceNode->getX() - sourceNodeSize / 2;
            paddingT = sourceNode->getY() - sourceNodeSize / 2;
            sourceBackground->setBounds(paddingL, paddingT, sourceNodeSize * 2, sourceNodeSize * 2);
        }
        else if (child == listener)
        {
            // make sure listenerBackground follows listener
            // listenerBackground must be double the size of source
            paddingL = listener->getX() - listener->getWidth() / 2;
            paddingT = listener->getY() - listener->getHeight() / 2;
            listenerBackground->setBounds(paddingL, paddingT, listener->getWidth() * 2, listener->getHeight() * 2);
        }

        // refresh plane wave of source background so that always points at reference listener
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
        juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
        float angle = pixPosRef.getAngleToPoint(pixPosSource);
        sourceBackground->updatePlaneWave(radiansToDegrees(angle), params.sourceType.getStep() == eSourceType::ePlane, sourceNode->getNodeColour());
    }
}

//==============================================================================

void ScenePanel::sliderValueChanged(Slider* sliderThatWasMoved)
{
    float val = static_cast<float>(sliderThatWasMoved->getValue());
    if (sliderThatWasMoved == sourceVolSlider)
    {
        params.sourceVol.setUI(val);
    }
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
    resized();
}

void ScenePanel::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel)
{
    ignoreUnused(e);
    float delta = wheel.deltaY;
    float currZoom = params.zoomFactor.getUI();
    float newZoom = jmin(jmax(params.zoomFactor.getMin(), currZoom + 15.0f * delta), params.zoomFactor.getMax());
    params.zoomFactor.set(newZoom, true);
}
