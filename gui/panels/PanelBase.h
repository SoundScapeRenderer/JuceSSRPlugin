
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"
#include "SynthParams.h"

class PanelBase : public Component, protected Timer
{
public:

    PanelBase(SynthParams &p)
        : params(p)
    {
        startTimerHz(60);
    }

    ~PanelBase() {
        stopTimer();
    }

protected:
    typedef std::function<void()> tHookFn;

    //=======================================================================================================================================

    virtual void timerCallback() override
    {

    }

    SynthParams &params;
};
