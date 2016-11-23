
#pragma once

#include <map>
#include <functional>

#include "JuceHeader.h"
#include "PluginParams.h"
#include "components/ListenerComponent.h"
#include "components/SourceNodeComponent.h"

/**
 * Parent class for all panel components that make use of the dirtyFlag of PluginParams (e.g. for automation).
 * Use this to synchronize backend changes on the UI.
 * The child components in these panels have to be registered with their corresponding parameter.
 * 
 * The main idea of this class comes from the open-source synthesizer "Synister" (see http://the-synister.github.io/).
 */
class PanelBase : public Component, protected Timer
{
public:

    PanelBase(PluginParams &p) : params(p)
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
     * Register reference listener component with corresponding parameters that needs to be checked.
     * @param l listener component
     * @param posX x position of reference listener
     * @param posY y position of reference listener
     * @param ori reference listener orientation
     * @param hookPos callback function that should correctly reposition reference listener component
     * @param hookOri callback function that should correctly rotate reference listener component
     */
    void registerListener(ListenerComponent *l, Param *posX, Param *posY, Param *ori, const tHookFn hookPos = tHookFn(), const tHookFn hookOri = tHookFn())
    {
        l->updateListenerOrientation(ori->getUI() + params.refOrientationOffset);

        listenerReg[l] = { posX, posY, ori };
        if (hookPos || hookOri)
        {
            postUpdateHook[l] = { hookPos, hookOri };
            hookPos();
            hookOri();
        }
    }

    /**
     * Check whether registered parameters of listener have been changed and synchronize its
     * position and orientation on UI.
     * Registered callback functions are called whenever listener's position or orientation is dirty.
     */
    void updateDirtyListener()
    {
        for (auto l2p : listenerReg)
        {
            auto itHook = postUpdateHook.find(l2p.first);

            // position
            for (int i = 0; i < 2; ++i)
            {
                if (l2p.second[i]->isUIDirty())
                {
                    if (itHook != postUpdateHook.end())
                    {
                        itHook->second[0]();
                    }
                }
            }

            // orientation
            if (l2p.second[2]->isUIDirty())
            {
                l2p.first->updateListenerOrientation(l2p.second[2]->getUI() + params.refOrientationOffset);
                if (itHook != postUpdateHook.end())
                {
                    itHook->second[1]();
                }
            }
        }
    }

    //==============================================================================

    /**
     * Register source component with corresponding position parameters that needs to be checked.
     * @param s source component
     * @param posX x position of source
     * @param posY y position of source
     * @param hook callback function that should correctly reposition source node component
     */
    void registerSource(SourceNodeComponent *s, Param *posX, Param *posY, const tHookFn hook = tHookFn())
    {
        sourceReg[s] = { posX, posY };
        if (hook)
        {
            postUpdateHook[s] = { hook };
            hook();
        }
    }

    /**
     * Check whether registered position parameters of sources have changed and synchronize its position on UI.
     * Registered callback function is called whenever source position is dirty.
     */
    void updateDirtySources()
    {
        for (auto s2p : sourceReg)
        {
            // position
            for (int i = 0; i < 2; ++i)
            {
                if (s2p.second[i]->isUIDirty())
                {
                    auto itHook = postUpdateHook.find(s2p.first);
                    if (itHook != postUpdateHook.end())
                    {
                        itHook->second[0]();
                    }
                }
            }
        }
    }

    //==============================================================================

    /**
     * Register slider component with corresponding parameter that needs to be checked.
     * @param s slider to handle changes and synchronize UI if parameter is dirty
     * @param p parameter to register
     * @param hook callback function
     */
    void registerSlider(Slider *s, Param* p, const tHookFn hook = tHookFn())
    {
        s->setValue(p->getUI(), dontSendNotification);
        s->setTextValueSuffix(p->getUnit());

        sliderReg[s] = { p };
        if (hook)
        {
            postUpdateHook[s] = { hook };
            hook();
        }
    }

    /**
     * Handle slider that was moved and set registered parameter.
     * @sliderThatWasMoved slider in the UI that was moved
     * @return true if slider is registered and could be handled
     */
    bool handleSlider(Slider* sliderThatWasMoved)
    {
        auto it = sliderReg.find(sliderThatWasMoved);
        if (it != sliderReg.end()) 
        {
            float val = static_cast<float>(sliderThatWasMoved->getValue());
            it->second->setUI(val);

            auto itHook = postUpdateHook.find(it->first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second[0]();
            }
            return true;
        }
        return false;
    }

    /**
     * Check whether registered parameters of sliders have changed and synchronize its set value on UI.
     */
    void updateDirtySliders()
    {
        for (auto s2p : sliderReg)
        {
            if (s2p.second->isUIDirty())
            {
                s2p.first->setValue(s2p.second->getUI(), dontSendNotification);

                auto itHook = postUpdateHook.find(s2p.first);
                if (itHook != postUpdateHook.end())
                {
                    itHook->second[0]();
                }
            }
        }
    }

    //==============================================================================

    /**
     * Register button component with corresponding parameter that needs to be checked.
     * Use this to display and synchronize its button state on UI correctly.
     * @param b button to handle clicks and synchronize UI if parameter is dirty
     * @param state parameter to register
     * @param hook callback function
     */
    void registerButton(Button *b, ParamStepped<eOnOffState> *state, const tHookFn hook = tHookFn())
    {
        b->setWantsKeyboardFocus(false);
        b->setToggleState(state->getStep() == eOnOffState::eOn, dontSendNotification);

        buttonReg[b] = { state };
        if (hook)
        {
            postUpdateHook[b] = { hook };
            hook();
        }
    }

    /**
     * Handle button that was clicked and set registered parameter.
     * @buttonThatWasClicked button in the UI that was clicked
     * @return true if button is registered and could be handled
     */
    bool handleButton(Button* buttonThatWasClicked)
    {
        auto it = buttonReg.find(buttonThatWasClicked);
        if (it != buttonReg.end())
        {
            bool isOn = buttonThatWasClicked->getToggleState();
            eOnOffState state;
            isOn ? state = eOnOffState::eOn : state = eOnOffState::eOff;
            it->second->setUI(static_cast<float>(state));

            auto itHook = postUpdateHook.find(it->first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second[0]();
            }
            return true;
        }
        return false;
    }

    /**
     * Check whether registered parameters of buttons have changed and synchronize its button state on UI.
     */
    void updateDirtyButtons()
    {
        for (auto b2p : buttonReg)
        {
            if (b2p.second->isUIDirty())
            {
                b2p.first->setToggleState(b2p.second->getStep() == eOnOffState::eOn, dontSendNotification);

                auto itHook = postUpdateHook.find(b2p.first);
                if (itHook != postUpdateHook.end())
                {
                    itHook->second[0]();
                }
            }
        }
    }

    //==============================================================================

    /**
     * Register comboBox with corresponding ParamStepped<E> that needs to be checked.
     * Use this to display and synchronize selected items of comboBox on UI correctly.
     * @param c comboBox to handle and synchronize UI if ParamStepped<E> is dirty
     * @param stepParam ParamStepped<E> to register
     * @param hook callback function
     */
    template <typename E>
    void registerComboBox(ComboBox *c, ParamStepped<E> *stepParam, const tHookFn hook = tHookFn())
    {        
        // fill combo box items
        for (int i = 0; i < static_cast<int>(E::nSteps); ++i)
        {
            c->addItem(stepParam->getUIString(i), i + 1);
        }
        c->setSelectedItemIndex(static_cast<int>(stepParam->getStep()), dontSendNotification);

        comboBoxReg[c] = { stepParam };
        if (hook)
        {
            postUpdateHook[c] = { hook };
            hook();
        }
    }

    /**
     * Handle comboBox that has changed and set registered ParamStepped<E>.
     * @comboBoxThatHasChanged box in the UI that has changed
     * @return true if comboBox is registered and could be handled
     */
    template <typename E>
    bool handleComboBox(ComboBox* comboBoxThatHasChanged)
    {
        auto it = comboBoxReg.find(comboBoxThatHasChanged);
        if (it != comboBoxReg.end())
        {
            int selectedId = comboBoxThatHasChanged->getSelectedItemIndex();
            static_cast<ParamStepped<E>*>(it->second)->setUI(static_cast<float>(selectedId));

            auto itHook = postUpdateHook.find(it->first);
            if (itHook != postUpdateHook.end())
            {
                itHook->second[0]();
            }
            return true;
        }
        return false;
    }

    /**
     * Check whether registered parameters of comboBoxes have changed and synchronize its selected item on UI.
     */
    void updateDirtyComboBoxes()
    {
        for (auto c2p : comboBoxReg)
        {
            if (c2p.second->isUIDirty())
            {
                // dummy cast so we can use getStep(), works with any ParamStepped<E>
                int index = static_cast<int>(static_cast<ParamStepped<eOnOffState>*>(c2p.second)->getStep());

                c2p.first->setSelectedItemIndex(index, dontSendNotification);

                auto itHook = postUpdateHook.find(c2p.first);
                if (itHook != postUpdateHook.end())
                {
                    itHook->second[0]();
                }
            }
        }
    }

    //==============================================================================

    virtual void timerCallback() override
    {
        updateDirtyListener();
        updateDirtySources();

        updateDirtySliders();
        updateDirtyButtons();
        updateDirtyComboBoxes();
    }

    PluginParams &params;

private:
    std::map<Component*, std::array<tHookFn, 2>> postUpdateHook;
    std::map<ListenerComponent*, std::array<Param*, 3>> listenerReg;
    std::map<SourceNodeComponent*, std::array<Param*, 2>> sourceReg;
    std::map<Slider*, Param*> sliderReg;
    std::map<Button*, ParamStepped<eOnOffState>*> buttonReg;
    std::map<ComboBox*, Param*> comboBoxReg; // comboBox for all types of ParamStepped<E>
};
