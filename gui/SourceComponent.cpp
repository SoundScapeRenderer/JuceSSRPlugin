/*
  ==============================================================================

    SourceComponent.cpp
    Created: 9 Aug 2016 1:31:22pm
    Author:  Nutty

  ==============================================================================
*/

#include "JuceHeader.h"

#include "SourceComponent.h"
#include "panels/SourceMenuPanel.h"

//==============================================================================
SourceComponent::SourceComponent(SynthParams &p, int sourceNodeSize, Colour c)
    : params(p)
    , nodeSize(sourceNodeSize)
    , nodeColour(c)
{
    // default settings
    setAlwaysOnTop(true);
    setInterceptsMouseClicks(false, true);

    // create child components
    addAndMakeVisible (levelSlider = new VolLevelSlider ("gain slider"));
    levelSlider->addListener (this);
    
    addAndMakeVisible (sourceBackground = new SourceBackgroundComponent(nodeColour));
    sourceBackground->setName ("source background");

    addAndMakeVisible(sourceMenu = new DocumentWindow("source menu", Colours::white, DocumentWindow::closeButton));
    sourceMenu->setName("source menu");
    sourceMenu->setTitleBarHeight(0);
    sourceMenu->setVisible(false);
    sourceMenu->setDraggable(false);
    sourceMenu->setContentOwned(new SourceMenuPanel(params, this), true);

    addAndMakeVisible (sourceNode = new SourceNodeComponent (params, sourceMenu, nodeColour));
    sourceNode->setName ("source node");
}

SourceComponent::~SourceComponent()
{
    levelSlider = nullptr;
    sourceBackground = nullptr;
    sourceMenu = nullptr;
    sourceNode = nullptr;
}

//==============================================================================


void SourceComponent::paint (Graphics& g)
{
    float centerPointSize = 3.5f * params.zoomFactor.get() / 100.0f;

    Path centerPoint;
    centerPoint.startNewSubPath(getWidth() / 2.0f - centerPointSize, getHeight() / 2.0f);
    centerPoint.lineTo(getWidth() / 2.0f + centerPointSize, getHeight() / 2.0f);
    centerPoint.startNewSubPath(getWidth() / 2.0f, getHeight() / 2.0f - centerPointSize);
    centerPoint.lineTo(getWidth() / 2.0f, getHeight() / 2.0f + centerPointSize);

    g.setColour(Colours::grey);
    g.strokePath(centerPoint, PathStrokeType(jmin(1.0f, 2.5f * params.zoomFactor.get() / 100.0f)));
}

void SourceComponent::resized()
{
    sourceMenu->setSize(250, 225);

    int scaledSize = static_cast<int>(nodeSize * params.zoomFactor.get() / 100.0f);
    juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    sourceNode->setBounds(pixPosSource.x - scaledSize / 2, pixPosSource.y - scaledSize / 2, scaledSize, scaledSize);

    levelSlider->setValue(params.sourceGain.get());
}

//==============================================================================


void SourceComponent::childBoundsChanged(Component *child)
{
    if (child == sourceNode)
    {
        int scaledSize = static_cast<int>(nodeSize * params.zoomFactor.get() / 100.0f);

        // sourceMenu, levelSlider and sourceBackground should always follow source node
        int offsetX = sourceNode->getX() + scaledSize + 25;
        int offsetY = sourceNode->getY() + scaledSize / 2;
        sourceMenu->setBounds(offsetX, offsetY, sourceMenu->getWidth(), sourceMenu->getHeight());

        levelSlider->setSize(scaledSize * 3 / 4, scaledSize / 3);
        offsetX = sourceNode->getX() + (scaledSize - levelSlider->getWidth()) / 2;
        offsetY = sourceNode->getY() + static_cast<int>(scaledSize * 1.1625f);
        levelSlider->setBounds(offsetX, offsetY, levelSlider->getWidth(), levelSlider->getHeight());

        offsetX = sourceNode->getX() - scaledSize / 2;
        offsetY = sourceNode->getY() - scaledSize / 2;
        sourceBackground->setBounds(offsetX, offsetY, scaledSize * 2, scaledSize * 2);
        sourceBackground->setBackgroundProperties(scaledSize * 0.5f);

        // refresh plane wave of source background
        juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
        juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
        float angle = pixPosRef.getAngleToPoint(pixPosSource);
        refreshBackground(radiansToDegrees(angle), params.sourceType.getStep() == eSourceType::ePlane);
    }
}

void SourceComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    if (sliderThatWasMoved == levelSlider)
    {
        params.sourceGain.setUI(static_cast<float>(sliderThatWasMoved->getValue()));
    }
}

//==============================================================================

void SourceComponent::refreshSourceNode()
{
    sourceNode->repaint();
}

void SourceComponent::refreshBackground(bool isPlaneWave)
{
    sourceBackground->refreshBackground(isPlaneWave);
}

void SourceComponent::refreshBackground(float angle, bool isPlaneWave)
{
    sourceBackground->refreshBackground(angle, isPlaneWave);
}

void SourceComponent::refreshGainLevel(float level)
{
    levelSlider->refreshVolLevel(level);
}

//==============================================================================
