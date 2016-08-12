
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"

#include "SynthParams.h"
#include "ListenerComponent.h"
#include "SourceComponent.h"

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
            for (int i = 0; i < 2; ++i)
            {
                if (l2p.second[i]->isUIDirty())
                {
                    l2p.first->relocate();
                }
            }

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

    void registerSource(SourceComponent *s, Param *posX, Param *posY, Param *volLevel, int screenWidth, int screenHeight, const tHookFn hook = tHookFn())
    {
        s->setAlwaysOnTop(true);
        s->setInterceptsMouseClicks(false, true);
        s->setScreenSize(screenWidth, screenHeight);

        sourceReg[s] = { posX, posY, volLevel };
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
            for (int i = 0; i < 2; ++i)
            {
                if (s2p.second[i]->isUIDirty())
                {
                    s2p.first->relocateSourceNode();
                }
            }

            if (s2p.second[2]->isUIDirty())
            {
                s2p.first->setVol(s2p.second[2]->getUI());
            }

            auto itHook = postUpdateHook.find(s2p.first);
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
    }

    SynthParams &params;
    std::map<Component*, tHookFn> postUpdateHook;
    std::map<ListenerComponent*, std::array<Param*, 3>> listenerReg;
    std::map<SourceComponent*, std::array<Param*, 3>> sourceReg;
};
