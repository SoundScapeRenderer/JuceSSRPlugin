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
}

void SourceComponent::resized()
{
    sourceMenu->setSize(250, 225);
    sourceNode->setSize(nodeSize, nodeSize);

    juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    sourceNode->setBounds(pixPosSource.x - nodeSize / 2, pixPosSource.y - nodeSize / 2, nodeSize, nodeSize);

    levelSlider->setValue(params.sourceGain.get());
}

//==============================================================================


void SourceComponent::childBoundsChanged(Component *child)
{
    if (child == sourceNode)
    {
        // sourceMenu, levelSlider and sourceBackground should always follow source node
        int offsetX = sourceNode->getX() + nodeSize + 25;
        int offsetY = sourceNode->getY() + nodeSize / 2;
        sourceMenu->setBounds(offsetX, offsetY, sourceMenu->getWidth(), sourceMenu->getHeight());

        levelSlider->setSize(nodeSize * 3 / 4, nodeSize / 3);
        offsetX = sourceNode->getX() + (nodeSize - levelSlider->getWidth()) / 2;
        offsetY = sourceNode->getY() + static_cast<int>(nodeSize * 1.1f);
        levelSlider->setBounds(offsetX, offsetY, levelSlider->getWidth(), levelSlider->getHeight());

        offsetX = sourceNode->getX() - nodeSize / 2;
        offsetY = sourceNode->getY() - nodeSize / 2;
        sourceBackground->setBounds(offsetX, offsetY, nodeSize * 2, nodeSize * 2);
        sourceBackground->setBackgroundProperties(nodeSize * 0.5f);

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
