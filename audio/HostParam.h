#pragma once

#include "JuceHeader.h"

#include "Param.h"

/**
 * Parameter class for communication between host and plugin. This mainly implements JUCE's
 * AudioProcessorParameter functions and maps them onto our Param.h class.
 * If necessary, go there for further documentation.
 */
template<typename _par>
class HostParam : public AudioProcessorParameter, public Param::Listener
{
public:
    HostParam(_par &p) : param(p)
    {
        param.addListener(this);
    }

    ~HostParam()
    {
        /* Problem in the destruction sequence:
         * The Param instances belong to PluginParams, a superclass of PluginAudioProcessor
         * The HostParam instances are held in a pointer array that is a private member of
         * the Juce class AudioProcessor, which is also a superclass of PluginAudioProcessor.
         *
         * This means that when the destructor of AudioProcessor is called, the Param instances
         * are already gone. We must therefore not access param at HostParam destruction time.
         *
         * A better solution would be clearing AudioProcessor::managedParameters within the
         * PluginAudioProcessor destructor. This is currently not possible because
         * managedParameters is private.
         */
         //param.removeListener(this);
    }

    //==============================================================================

    /**
     * Called by the host to get the value of this parameter.
     * For further description, see AudioProcessorParameter.
     */
    float getValue() const override
    {
        return engineToHost(param.getUI());
    }

    /**
     * Called by the host to set the value of this parameter.
     * For further description, see AudioProcessorParameter.
     */
    void setValue(float newValue) override
    {
        jassert(newValue >= 0.0f && newValue <= 1.0f);
        param.set(hostToEngine(newValue), true);
    }
    
    /**
     * Called by the host to get the default value of this parameter.
     * For further description, see AudioProcessorParameter.
     */
    virtual float getDefaultValue() const override
    {
        return engineToHost(param.getDefault());
    }

    //==============================================================================

    /**
     * Called by the host to get the name of this parameter
     * to display on the host's UI.
     * For further description, see AudioProcessorParameter.
     */
    virtual String getName(int maximumStringLength) const override
    {
        return param.getHostTag().substring(0, maximumStringLength);
    }

    /**
     * Called by the host to get the value unit of this parameter.
     * For further description, see AudioProcessorParameter.
     */
    virtual String getLabel() const override
    {
        return param.getUnit();
    }

    /**
     * Called by the host to get the number of intervall steps of this parameter.
     * For further description, see AudioProcessorParameter.
     */
    virtual int getNumSteps() const override
    {
        return param.getNumSteps();
    }

    /// \todo implement this to fix automation value input bug?
    /**
     * Called by the host to parse the displayed value text.
     * For further description, see AudioProcessorParameter.
     */
    virtual float getValueForText(const String& text) const override
    {
        return text.getFloatValue();
    }

    /**
     * Called by the host to get the text of this parameter's value.
     * For further description, see AudioProcessorParameter.
     */
    virtual String getText(float value, int maximumStringLength) const override
    {
        return param.getUIString(hostToEngine(value)).substring(0, maximumStringLength);
    }

    /**
     * Notify host of parameter value changes on the plugin UI calling setValueNotifyingHost().
     * For further description, see setValueNotifyingHost() in AudioProcessorParameter.
     */
    virtual void paramUIChanged() override
    {
        // this will (unnecessarily) call setValue
        setValueNotifyingHost(engineToHost(param.getUI()));
    }

    //==============================================================================

protected:

    /**
     * Convert engine/plugin parameter values so that host can use it.
     * Host expects values between 0.0f and 1.0f.
     * For further description, see getValue() in AudioProcessorParameter.
     */
    virtual float engineToHost(float engineVal) const
    {
        jassert(engineVal >= param.getMin() && engineVal <= param.getMax());
        return (engineVal - param.getMin()) / (param.getMax() - param.getMin());
    }

    /**
     * Convert host parameter values so that engine/plugin can use it.
     * Host will pass values between 0.0f and 1.0f to the engine/plugin.
     * For further description, see setValue() in AudioProcessorParameter.
     */
    virtual float hostToEngine(float hostVal) const
    {
        jassert(hostVal >= 0.f && hostVal <= 1.f);
        if (param.getNumSteps() == 0)
        {
            // for basic float parameter
            return (param.getMin() + hostVal*(param.getMax() - param.getMin()));
        }
        else
        {
            // for step parameter
            return trunc(hostVal*static_cast<float>(param.getNumSteps() - 1) + .5f);
        }
    }

    _par &param;
};

//==============================================================================

/**
 * Derived from HostParams, only difference is an additional skew factor for displaying values in the host
 * using logarithmic scaling.
 * Skew must not be 1.0f and _par is not allowed to be ParamStepped. Useful for decibel values.
 */
template<typename _par>
class HostParamLog : public HostParam<_par>
{
public:
    HostParamLog(_par &p, float midPoint) : HostParam<_par>(p)
    {
        skew = log(0.5f) / log((midPoint - p.getMin()) / (p.getMax() - p.getMin()));
        jassert(skew > 1.f || skew < 1.f);
        jassert(p.getNumSteps() == 0);
    }

    //==============================================================================

protected:
    float skew;

    /**
     * Convert engine/plugin parameter values so that host can use it.
     * Host expects values between 0.0f and 1.0f.
     * Uses an additional skew factor for logarithmic scaling.
     * For further description, see getValue() in AudioProcessorParameter.
     */
    float engineToHost(float engineVal) const override
    {
        jassert(engineVal >= HostParam<_par>::param.getMin() && engineVal <= HostParam<_par>::param.getMax());
        float proportion = HostParam<_par>::engineToHost(engineVal);
        // copied from juce::Slider::valueToProportionOfLength
        return pow(proportion, skew);
    }

    /**
     * Convert host parameter values so that engine/plugin can use it.
     * Host will pass values between 0.0f and 1.0f to the engine/plugin.
     * Uses an additional skew factor for logarithmic scaling.
     * For further description, see setValue() in AudioProcessorParameter.
     */
    float hostToEngine(float hostVal) const override
    {
        jassert(hostVal >= 0.f && hostVal <= 1.f);
        // copied from juce::Slider::proportionOfLengthToValue
        if (hostVal > 0.f)
        {
            hostVal = exp(log(hostVal) / skew);
        }
        return HostParam<_par>::hostToEngine(hostVal);
    }
};