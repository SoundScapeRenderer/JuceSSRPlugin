/*
  ==============================================================================

    SourceComponent.h
    Created: 28 Jul 2016 3:12:40pm
    Author:  Nutty

  ==============================================================================
*/

#ifndef SOURCECOMPONENT_H_INCLUDED
#define SOURCECOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "SynthParams.h"

//==============================================================================
/*
*/
class SourceComponent    : public Component
{
public:
    SourceComponent(SynthParams &p)
        : params(p)
    {
        setAlwaysOnTop(true);
    }

    ~SourceComponent()
    {
    }

    //==============================================================================

    void paint (Graphics& g)
    {
        drawSourceNode(g);

        /// \todo draw angle arrows
        if (params.sourceType.getStep() == eSourceType::ePlane)
        {

        }
    }

    void resized()
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
    }

    //==============================================================================

    void mouseDown (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::leftButtonModifier)
        {
            dragger.startDraggingComponent(this, e);
        }
        else
        {
            // create right-click popup menu and item handling
            if (e.mods == ModifierKeys::rightButtonModifier)
            {
                PopupMenu mainMenu, muteSourceMenu, sourceTypeMenu, inputChannelMenu;

                muteSourceMenu.addItem(1, "mute source OFF", true, params.sourceMute.getStep() == eOnOffState::eOff ? true : false);
                muteSourceMenu.addItem(2, "mute source ON", true, params.sourceMute.getStep() == eOnOffState::eOn ? true : false);
                sourceTypeMenu.addItem(3, "source type POINT", true, params.sourceType.getStep() == eSourceType::ePoint ? true : false);
                sourceTypeMenu.addItem(4, "source type PLANE", true, params.sourceType.getStep() == eSourceType::ePlane ? true : false);
                inputChannelMenu.addItem(5, "input channel LEFT", true, params.inputChannel.getStep() == eInputChannel::eLeftChannel ? true : false);
                inputChannelMenu.addItem(6, "input channel RIGHT", true, params.inputChannel.getStep() == eInputChannel::eRightChannel ? true : false);

                mainMenu.addSubMenu("mute source", muteSourceMenu);
                mainMenu.addSubMenu("source type", sourceTypeMenu);
                mainMenu.addSubMenu("input channel", inputChannelMenu);

                const int selectedItem = mainMenu.show();
                switch (selectedItem)
                {
                case 1:
                    params.sourceMute.setStep(eOnOffState::eOff);
                    break;
                case 2:
                    params.sourceMute.setStep(eOnOffState::eOn);
                    break;
                case 3:
                    params.sourceType.setStep(eSourceType::ePoint);
                    break;
                case 4:
                    params.sourceType.setStep(eSourceType::ePlane);
                    break;
                case 5:
                    params.inputChannel.setStep(eInputChannel::eLeftChannel);
                    break;
                case 6:
                    params.inputChannel.setStep(eInputChannel::eRightChannel);
                    break;
                default:
                    break;
                }
            }
        }
    }
    
    void mouseDrag (const MouseEvent& e)
    {
        if (e.mods == ModifierKeys::leftButtonModifier)
        {
            dragger.dragComponent(this, e, nullptr);

            // parent must be scene UI
            int middleX = getX() + getWidth() / 2;
            int middleY = getY() + getHeight() / 2;
            juce::Point<float> posSource = params.pix2pos(middleX, middleY, getParentWidth(), getParentHeight());
            params.sourceX.setUI(posSource.x);
            params.sourceY.setUI(posSource.y);
        }
    }

    //==============================================================================

private:
    SynthParams &params;
    ComponentDragger dragger;
    const Colour nodeColour = SynthParams::sourceColourBlue;

    const float ringRatio1 = 0.925f, ringRatio2 = 0.875f;

    //==============================================================================

    void drawSourceNode(Graphics &g)
    {
        float w = static_cast<float>(getWidth());
        float h = static_cast<float>(getHeight());
        float paddingL = (getWidth() - w) * 0.5f;
        float paddingT = (getHeight() - h) * 0.5f;

        /// \todo draw shadow
        // draw actual node
        g.setColour(nodeColour);
        g.fillEllipse(paddingL, paddingT, w, h);

        w *= ringRatio1;
        h *= ringRatio1;
        paddingL = (getWidth() - w) * 0.5f;
        paddingT = (getHeight() - h) * 0.5f;
        g.setColour(Colours::white);
        g.fillEllipse(paddingL, paddingT, w, h);

        w *= ringRatio2;
        h *= ringRatio2;
        paddingL = (getWidth() - w) * 0.5f;
        paddingT = (getHeight() - h) * 0.5f;
        g.setColour(nodeColour);
        g.fillEllipse(paddingL, paddingT, w, h);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceComponent)
};


#endif  // SOURCECOMPONENT_H_INCLUDED
