
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"
#include "SynthParams.h"
#include "ListenerComponent.h"
#include "OutputLevelComponent.h"
#include "SourceNodeComponent.h"

/**
 * Parent class for all components that make use of the dirtyFlag of SynthParams (e.g. for automation).
 * The child components in these have to be registered with their corresponding Param.
 */
class PanelBase : public Component, protected Timer
{
public:

    PanelBase(SynthParams &p)
        : params(p)
    {
        startTimerHz(60);
    }

    ~PanelBase()
    {
        stopTimer();
    }

protected:
    typedef std::function<void()> tHookFn;

    //==============================================================================

    /**
     * Register reference listener component with affiliated parameters that needs to be checked.
     * @param posX x position of reference listener
     * @param posY y position of reference listener
     * @param ori reference listener orientation 
     * @param sceneWidth width of the scene component in px
     * @param sceneHeight height of the scene component in px
     * @param hook callback function
     */
    void registerListener(ListenerComponent *l, Param *posX, Param *posY, Param *ori,
        int sceneWidth, int sceneHeight, const tHookFn hook = tHookFn())
    {
        l->setSceneSize(sceneWidth, sceneHeight);
        l->updateBackgroundAngle(ori->getDefaultUI());

        listenerReg[l] = { posX, posY, ori };
        if (hook) 
        {
            postUpdateHook[l] = hook;
            hook();
        }
    }

    /**
     * Check whether registered Params of listener have been changed and handle these correctly.
     */
    void updateDirtyListener()
    {
        for (auto l2p : listenerReg)
        {
            //position
            for (int i = 0; i < 2; ++i)
            {
                if (l2p.second[i]->isUIDirty())
                {
                    l2p.first->relocate();
                }
            }

            // orientation
            if (l2p.second[2]->isUIDirty())
            {
                l2p.first->repaint();
                l2p.first->updateBackgroundAngle(l2p.second[2]->getUI());
            }

            auto itHook = postUpdateHook.find(l2p.first);
            if (itHook != postUpdateHook.end()) 
            {
                itHook->second();
            }
        }
    }

    //==============================================================================

    /**
     * Register source component with affiliated parameters that needs to be checked.
     * @param posX x position of source
     * @param posY y position of source
     * @param vol source input volume
     * @param level real time input level of the source
     * @param lock indicator solely for whether source is allowed to be moved
     * @param sceneWidth width of the scene component in px
     * @param sceneHeight height of the scene component in px
     * @param hook callback function
     */
    void registerSource(SourceNodeComponent *s, Param *posX, Param *posY, Param *vol, Param *level,
        int sceneWidth, int sceneHeight, const tHookFn hook = tHookFn())
    {
        s->setSceneSize(sceneWidth, sceneHeight);

        s->getVolSlider()->setValue(static_cast<double>(vol->getDefaultUI()), dontSendNotification);
        s->getVolSlider()->refreshVolLevel(level->getDefaultUI());

        sourceReg[s] = { posX, posY , vol, level };
        if (hook)
        {
            postUpdateHook[s] = hook;
            hook();
        }
    }

    /**
     * Check whether registered Params of source have been changed and handle these correctly.
     */
    void updateDirtySource()
    {
        for (auto s2p : sourceReg)
        {
            // position
            for (int i = 0; i < 2; ++i)
            {
                if (s2p.second[i]->isUIDirty())
                {
                    s2p.first->relocate();
                }
            }

            // volume
            if (s2p.second[2]->isUIDirty())
            {
                s2p.first->getVolSlider()->setValue(s2p.second[2]->getUI(), dontSendNotification);
            }

            // level
            if (s2p.second[3]->isUIDirty())
            {
                s2p.first->getVolSlider()->refreshVolLevel(s2p.second[3]->getUI());
            }

            auto itHook = postUpdateHook.find(s2p.first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second();
            }
        }
    }

    //==============================================================================

    /**
     * Register output level component with affiliated parameter that needs to be checked.
     * @param o OutputLevelComponent to register
     * @param l left channel level parameter to register and handle if dirty
     * @param r right channel level parameter to register and handle if dirty
     * @param hook callback function
     */
    void registerOutputLevel(OutputLevelComponent *o, Param* l, Param* r, const tHookFn hook = tHookFn())
    {
        o->setLeveLColour(SynthParams::sourceLevelColour);
        o->setSkewFactor(3.0f);
        o->refreshOutputLevel(l->getDefaultUI(), r->getDefaultUI());

        outputLevelReg[o] = { l, r };
        if (hook)
        {
            postUpdateHook[o] = hook;
            hook();
        }
    }

    /**
    * Check whether registered parameters of OutputLevelComponent have changed and handle these correctly.
    */
    void updateDirtyOutputLevel()
    {
        for (auto o2p : outputLevelReg)
        {
            if (o2p.second[0]->isUIDirty() || o2p.second[1]->isUIDirty())
            {
                o2p.first->refreshOutputLevel(o2p.second[0]->getUI(), o2p.second[1]->getUI());
            }

            auto itHook = postUpdateHook.find(o2p.first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second();
            }
        }
    }

    //==============================================================================

    /**
     * Register slider component with affiliated parameter that needs to be checked.
     * @param s slider to register
     * @param p parameter to register and handle if dirty
     * @param hook callback function
     */
    void registerSlider(Slider *s, Param* p, const tHookFn hook = tHookFn())
    {
        s->setValue(p->getDefaultUI());
        s->setTextValueSuffix(p->getUnit());

        sliderReg[s] = { p };
        if (hook)
        {
            postUpdateHook[s] = hook;
            hook();
        }
    }

    /**
     * Check whether registered parameters of slider have changed and handle these correctly.
     */
    void updateDirtySlider()
    {
        for (auto s2p : sliderReg)
        {
            if (s2p.second->isUIDirty())
            {
                s2p.first->setValue(s2p.second->getUI(), sendNotificationAsync);
            }

            auto itHook = postUpdateHook.find(s2p.first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second();
            }
        }
    }

    //==============================================================================

    /**
     * Register button component with affiliated parameter that needs to be checked.
     * @param b button to register
     * @param state ParamStepped to register and handle if dirty
     * @param hook callback function
     */
    void registerButton(Button *b, ParamStepped<eOnOffState> *state, const tHookFn hook = tHookFn())
    {
        b->setWantsKeyboardFocus(false);
        b->setToggleState(state->getStep() == eOnOffState::eOn, dontSendNotification);

        buttonReg[b] = { state };
        if (hook)
        {
            postUpdateHook[b] = hook;
            hook();
        }
    }

    /**
     * Check whether registered parameters of buttons have changed and handle these correctly.
     */
    void updateDirtyButton()
    {
        for (auto b2p : buttonReg)
        {
            if (b2p.second->isUIDirty())
            {
                b2p.first->setToggleState(b2p.second->getStep() == eOnOffState::eOn, sendNotificationAsync);
            }

            auto itHook = postUpdateHook.find(b2p.first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second();
            }
        }
    }

    //==============================================================================

    virtual void timerCallback() override
    {
        updateDirtyListener();
        updateDirtySource();
        updateDirtyOutputLevel();

        updateDirtySlider();
        updateDirtyButton();
    }

    SynthParams &params;
    std::map<Component*, tHookFn> postUpdateHook;
    std::map<ListenerComponent*, std::array<Param*, 3>> listenerReg;
    std::map<SourceNodeComponent*, std::array<Param*, 5>> sourceReg;
    std::map<OutputLevelComponent*, std::array<Param*, 2>> outputLevelReg;
    std::map<Slider*, Param*> sliderReg;
    std::map<Button*, ParamStepped<eOnOffState>*> buttonReg;
};
