#pragma once

#include "JuceHeader.h"

#include <atomic>
#include <array>

/**
 * Base parameter class for float values. Uses a dirty flag to handle synchronization of the UI
 * and listener callbacks that can be used to notify host of changes.
 * Needs some atomic member to prevent state inconsistencies.
 *
 * Most of the code in this class comes from the open-source synthesizer "Synister" (see http://the-synister.github.io/).
 */
class Param
{
public:
    Param(const String &name, const String &serializationTag, const String &hostTag, const String &unit
          , float minval, float maxval, float defaultval, int numSteps = 0)
        : val_(defaultval)
        , min_(minval)
        , max_(maxval)
        , default_(defaultval)
        , name_(name)
        , serializationTag_(serializationTag)
        , hostTag_(hostTag)
        , unit_(unit)
        , lock_(false)
        , numSteps_(numSteps)
    {
        jassert(minval <= defaultval);
        jassert(defaultval <= maxval);
    }
    virtual ~Param() {}

    //==============================================================================

    /// setter and getter for prefix
    void setPrefix(const String &s) { prefix_ = s; }
    const String& getPrefix() { return prefix_; }

    /// string getter for name, host tag, serialization tag and unit
    const String& getName() const { return name_; }
    String getSerializationTag() const { return prefix_.isEmpty() ? serializationTag_ : prefix_ + " " + serializationTag_; }
    String getHostTag() const { return prefix_.isEmpty() ? hostTag_ : prefix_ + " " + hostTag_; }
    const String& getUnit() const { return unit_; }

    //==============================================================================

    /**
     * Set value lock to prevent value changes.
     * @param b if true then lock param value
     */
    void setValueLock(bool b)
    {
        lock_.store(b);
    }

    bool isValueLockEnabled() { lock_.load(); }

    /**
     * Set param value if lock is disabled.
     * Limits new value between minimum an maximum.
     */
    void set(float f) { if (!lock_.load()) { val_.store(jmin(jmax(min_, f), max_)); } }

    /**
     * Set param value and dirtyFlag if lock is disabled.
     * Limits new value between minimum an maximum.
     * Use this if values were changed by the host or
     * somewhere else and UI needs synchronization handling.
     * @param f new value
     * @param setDirty exchange dirtyFlag to true or false
     */
    void set(float f, bool setDirty)
    {
        if (!lock_.load())
        {
            val_.store(jmin(jmax(min_, f), max_));
            uiDirty.exchange(setDirty);
        }
    }

    /// further getter for useful param values
    float get() const { return val_.load(); }
    float getMin() const { return min_; }
    float getMax() const { return max_; }
    float getDefault() const { return default_; }

    /**
     * Set param value (virtual) and notify registered listener of changes.
     * @param f new float value, bounds are checked
     * @param notifyHost if true then call listener callback
     */
    virtual void setUI(float f, bool notifyHost = true)
    {
        set(f);
        if (notifyHost) { listener.call(&Listener::paramUIChanged); }
    }

    /**
     * Use this to set param values from host. This sets a new value via setUI
     * and sets the dirty flag to true for further handling on the UI.
     */
    void setHost(float f)
    {
        setUI(f, false);
        uiDirty.exchange(true);
    }

    /// virtual getter for values and strings
    virtual float getUI() const { return get(); }
    virtual float getDefaultUI() const { return getDefault(); }
    virtual String getUIString() const { return getUIString(get()); }
    virtual String getUIString(float v) const { return String(v, 3); }

    /**
     * Check whether this param's UI is dirty. Set dirty flag to false, after checking.
     * NOTE: get and reset semantics -> this will break if one value is represented twice on the ui
     * @return true if dirty flag is set
     */
    bool isUIDirty()
    {
        return uiDirty.exchange(false);
    }

    //==============================================================================

    /**
     * Listener class to be used to register value changes of a parameter.
     * Use this to notify host of parameter changes of the plugin, see HostParam.h.
     */
    class Listener
    {
    public:
        virtual ~Listener() {}
        /// @brief only to be called if the param has been changed in the UI
        virtual void paramUIChanged() {}
    };

    void addListener(Listener *newListener) { listener.add(newListener); }
    void removeListener(Listener *aListener) { listener.remove(aListener); }

    //==============================================================================

    /// for derived ParamStepped
    virtual int getNumSteps() const { return numSteps_; }
    virtual bool hasLabels() const { return false; }

    //==============================================================================

    /// decibel conversion functions
    constexpr static float MIN_DB = -96.0f;
    static inline float toDb(float linear) { return linear > 0.0f ? 20.0f * std::log10(linear) : MIN_DB; }
    static inline float fromDb(float db) { return db <= MIN_DB ? 0.0f : std::pow(10.0f, db / 20.0f); }

    //==============================================================================

protected:
    std::atomic<float> val_; //!< current value of param
    float min_; //!< min value of param
    float max_; //!< max value of param
    float default_; //!< default value of param
    String name_; //!< name of param
    String serializationTag_; //!< name of param to be written into patches
    String hostTag_; //!< name of param to be used in host
    String unit_; //!< unit of param value
    std::atomic<bool> lock_; //!< lock for params, if true then param value can not be changed 
    String prefix_; //!< name prefix of param
    int numSteps_; //!< number of steps, used for ParamStepped

    ListenerList<Listener> listener; //!< listener for callbacks notifying host
    std::atomic<bool> uiDirty; //!< dirty flag to check for further handling and synchronization on UI
};

//==============================================================================

/**
 * Derived parameter class from Param with a static number of steps for enums. _enum must be of type int and
 * needs _enum::nSteps as a value which is the number of steps, see PluginParams.h.
 * A label can be set to give each step a concrete name.
 * The step value is an atomic member to prevent state inconsistencies.
 */
template<typename _enum>
class ParamStepped : public Param 
{
public:
    ParamStepped(const String &name, const String &serializationTag, const String &hostTag
                 , _enum defaultval, const char **labels = nullptr)
        : Param(name, serializationTag, hostTag, "", 0.0f, static_cast<float>(_enum::nSteps) - 1.0f
                , static_cast<float>(defaultval), static_cast<int>(_enum::nSteps))
        , step_(defaultval)
        , labelsSet(false)
    {
        // set label strings
        const char **lbl = labels;
        for (size_t u = 0; u < labels_.size() && lbl != nullptr && *lbl != nullptr; ++u, ++lbl)
        {
            labels_[u] = *lbl;
            labelsSet = true;
        }
    }

    //==============================================================================

    /**
     * Set current step value. This also sets parent's float value.
     * @param v new _enum value
     */
    void setStep(_enum v)
    {
        if (!lock_.load())
        {
            step_.store(v);
            set(static_cast<float>(v));
        }
    }

    /**
     * Set step param value and notify registered listener of changes.
     * Limits new value between minimum an maximum.
     * @param f new step value as flaot, bounds are checked
     * @param notifyHost if true then call listener callback
     */
    virtual void setUI(float f, bool notifyHost = true) override
    {
        // check bounds of step value
        if (!lock_.load())
        {
            int ival = static_cast<int>(std::trunc(f + .5f));
            ival = jmin(jmax(0, ival), static_cast<int>(_enum::nSteps) - 1);
            step_.store(static_cast<_enum>(ival));
        }

        Param::setUI(f, notifyHost);
    }

    /**
     * Get current step param enum value.
     */
    _enum getStep() const { return step_.load(); }

    /**
     * Get text label of current set step param value.
     */
    virtual String getUIString() const override { return labels_[static_cast<size_t>(getStep())]; }

    /**
     * Get text label of a specific step param value.
     * @param v specific _enum value to get text label from
     */
    virtual String getUIString(float v) const override
    {
        size_t u = static_cast<size_t>(std::trunc(v + .5f));
        if (u < labels_.size())
        {
            return labels_[u];
        }
        else
        {
            jassert(false);
            return String::formatted("val%u", u);
        }
    }

    /**
     * If step param's text label is set then return true.
     */
    virtual bool hasLabels() const override { return labelsSet; }

    //==============================================================================

protected:
    std::atomic<_enum> step_; //!< current step value
    std::array<String, static_cast<size_t>(_enum::nSteps)> labels_; //!< step value text labels
    bool labelsSet; //!< true if has labels
};
