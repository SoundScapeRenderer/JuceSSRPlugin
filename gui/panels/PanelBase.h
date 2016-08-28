
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"
#include "SynthParams.h"
#include "ListenerComponent.h"
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

    //=======================================================================================================================================

    /**
     * Register reference listener component with all its automatable params and sceneWidth and sceneHeight.
     */
    void registerListener(ListenerComponent *l, Param *posX, Param *posY, Param *ori, int sceneWidth, int sceneHeight, const tHookFn hook = tHookFn())
    {
        l->setSceneSize(sceneWidth, sceneHeight);
        l->updateBackgroundAngle(ori->getUI());

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

    //=======================================================================================================================================

    /**
     * Register source component with all its automatable params and sceneWidth and sceneHeight.
     */
    void registerSource(SourceNodeComponent *s, Param *posX, Param *posY, Param *vol, int sceneWidth, int sceneHeight, const tHookFn hook = tHookFn())
    {
        s->setSceneSize(sceneWidth, sceneHeight);
        s->setNodeColour(SynthParams::sourceColourBlue);

        s->getVolSlider()->setValue(static_cast<double>(vol->get()), dontSendNotification);

        sourceReg[s] = { posX, posY , vol };
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

            auto itHook = postUpdateHook.find(s2p.first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second();
            }
        }
    }

    /**
     * Update source volume slider level.
     */
    void updateSourceVolLevel()
    {
        for (auto s2p : sourceReg)
        {
            s2p.first->getVolSlider()->refreshVolLevel(s2p.first->getVolLevel());
        }
    }

    //=======================================================================================================================================

    /**
     * Register button component with corresponding Param that needs to be checked.
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
     * Check whether registered Params of buttons have been changed and handle these correctly.
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

    //=======================================================================================================================================

    virtual void timerCallback() override
    {
        updateDirtyListener();
        updateDirtySource();
        updateDirtyButton();

        // constantly update level
        updateSourceVolLevel();
    }

    SynthParams &params;
    std::map<Component*, tHookFn> postUpdateHook;
    std::map<ListenerComponent*, std::array<Param*, 3>> listenerReg;
    std::map<SourceNodeComponent*, std::array<Param*, 3>> sourceReg;
    std::map<Button*, ParamStepped<eOnOffState>*> buttonReg;
};
