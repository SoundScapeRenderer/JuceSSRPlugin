
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"
#include "SynthParams.h"
#include "ListenerComponent.h"
#include "SourceNodeComponent.h"

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

    void registerListener(ListenerComponent *l, Param *posX, Param *posY, Param *ori, int screenWidth, int screenHeight, const tHookFn hook = tHookFn())
    {
        l->setScreenSize(screenWidth, screenHeight);

        listenerReg[l] = { posX, posY, ori };
        if (hook) 
        {
            postUpdateHook[l] = hook;
            hook();
        }
    }

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
            }

            auto itHook = postUpdateHook.find(l2p.first);
            if (itHook != postUpdateHook.end()) 
            {
                itHook->second();
            }
        }
    }

    //=======================================================================================================================================

    void registerSource(SourceNodeComponent *s, Param *posX, Param *posY, Param *vol, int screenWidth, int screenHeight, const tHookFn hook = tHookFn())
    {
        s->setAlwaysOnTop(true);
        s->setScreenSize(screenWidth, screenHeight);
        s->setNodeColour(SynthParams::sourceColourBlue);

        s->getVolSlider()->setValue(static_cast<double>(vol->get()), dontSendNotification);

        sourceReg[s] = { posX, posY , vol };
        if (hook)
        {
            postUpdateHook[s] = hook;
            hook();
        }
    }

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

    void updateSourceVolLevel()
    {
        for (auto s2p : sourceReg)
        {
            s2p.first->getVolSlider()->refreshVolLevel(s2p.first->getVolLevel());
        }
    }

    //=======================================================================================================================================

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

        updateSourceVolLevel();
    }

    SynthParams &params;
    std::map<Component*, tHookFn> postUpdateHook;
    std::map<ListenerComponent*, std::array<Param*, 3>> listenerReg;
    std::map<SourceNodeComponent*, std::array<Param*, 3>> sourceReg;
    std::map<Button*, ParamStepped<eOnOffState>*> buttonReg;
};
