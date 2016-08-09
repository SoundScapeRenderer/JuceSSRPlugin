/*
  ==============================================================================

    SourceComponent.cpp
    Created: 9 Aug 2016 1:31:22pm
    Author:  Smoky

  ==============================================================================
*/

#include "JuceHeader.h"

#include "SourceComponent.h"
#include "panels/SourceMenuPanel.h"

//==============================================================================
SourceComponent::SourceComponent(SynthParams &p)
    : params(p)
{
    // pass all mouse click events to component behind this
    setInterceptsMouseClicks(false, true);
        
    addAndMakeVisible (gainSlider = new GainLevelSlider ("gain slider"));
    gainSlider->setRange (-96, 12, 0);
    gainSlider->setSliderStyle (Slider::LinearBar);
    gainSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    gainSlider->addListener (this);
    gainSlider->setSkewFactor (3);
    
    addAndMakeVisible (sourceBackground = new SourceBackgroundComponent());
    sourceBackground->setName ("source background");

    addAndMakeVisible(sourceMenu = new DocumentWindow("source menu", Colours::white, DocumentWindow::closeButton));
    sourceMenu->setName("source menu");

    addAndMakeVisible (source = new SourceNodeComponent (params));
    source->setName ("source");

    /// \todo restructuring component relationsships
    source->registerGainLevelSlider(gainSlider);
    source->registerBackground(sourceBackground);
    source->registerMenu(sourceMenu);

    sourceMenu->setTitleBarHeight(0);
    sourceMenu->setContentOwned(new SourceMenuPanel(params, source), true);
    sourceMenu->setVisible(false);
    sourceMenu->setAlwaysOnTop(true);
    sourceMenu->setDraggable(false);
}

SourceComponent::~SourceComponent()
{
    gainSlider = nullptr;
    sourceBackground = nullptr;
    sourceMenu = nullptr;
    source = nullptr;
}

//==============================================================================


void SourceComponent::paint (Graphics& g)
{
}

void SourceComponent::resized()
{
    gainSlider->setBounds (0, 0, 75, 28);
    sourceBackground->setBounds (0, 0, 200, 200);
    sourceMenu->setBounds(0, 0, 250, 225);
    source->setBounds (50, 50, 100, 100);
}

//==============================================================================


void SourceComponent::childBoundsChanged(Component *child)
{
    int offsetX;
    int offsetY;
    if (child == source)
    {
        if (child = source)
        {
            // gainSlider, sourceBackground and  sourceMenu should always follow source node
            offsetX = source->getX() - source->getWidth() / 2;
            offsetY = source->getY() - source->getHeight() / 2;
            sourceBackground->setBounds(offsetX, offsetY, source->getWidth() * 2, source->getHeight() * 2);
            sourceBackground->setShadowRadius(source->getWidth() * 0.5f);

            offsetX = source->getX() + (source->getWidth() - gainSlider->getWidth()) / 2;
            offsetY = source->getY() + source->getHeight() + 5;
            gainSlider->setBounds(offsetX, offsetY, gainSlider->getWidth(), gainSlider->getHeight());

            offsetX = source->getX() + source->getWidth() + 25;
            offsetY = source->getY() + source->getHeight() / 2;
            sourceMenu->setBounds(offsetX, offsetY, sourceMenu->getWidth(), sourceMenu->getHeight());
        }
    }

    // refresh plane wave of source background
    juce::Point<int> pixPosRef = params.pos2pix(params.referenceX.get(), params.referenceY.get(), getWidth(), getHeight());
    juce::Point<int> pixPosSource = params.pos2pix(params.sourceX.get(), params.sourceY.get(), getWidth(), getHeight());
    float angle = pixPosRef.getAngleToPoint(pixPosSource);
    sourceBackground->refreshBackground(radiansToDegrees(angle), params.sourceType.getStep() == eSourceType::ePlane);
}

void SourceComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    float val = static_cast<float>(sliderThatWasMoved->getValue());

    if (sliderThatWasMoved == gainSlider)
    {
        params.sourceGain.setUI(val);
    }
}

//==============================================================================

void SourceComponent::refreshBackground(float angle, bool isPlaneWave)
{
    sourceBackground->refreshBackground(angle, isPlaneWave);
}

//==============================================================================
