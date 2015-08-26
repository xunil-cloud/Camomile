/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PdGui.h"
#include "PdMessenger.h"

#include <set>
#include <memory>

using namespace std;
using namespace pd;

class CamomileAudioProcessor  : public AudioProcessor, public Instance
{
public:
    class Listener;
private:
    Patch           m_patch;
    set<Listener*>  m_listeners;
    mutable mutex   m_mutex;
    
public:
    CamomileAudioProcessor();
    ~CamomileAudioProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock(AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override {return true;};

    const String getName() const override {return String(JucePlugin_Name);};

    int getNumParameters() override;
    float getParameter (int index) override;
    void setParameter (int index, float newValue) override;

    const String getParameterName (int index) override;
    const String getParameterText (int index) override;

    const String getInputChannelName(int index) const override {return String(index + 1);}
    const String getOutputChannelName(int index) const override {return String(index + 1);}
    bool isInputChannelStereoPair(int index) const override {return false;}
    bool isOutputChannelStereoPair(int index) const override {return false;}

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool silenceInProducesSilenceOut() const override {return false;}
    double getTailLengthSeconds() const override {return 0.0;}

    int getNumPrograms() override {return 1;}
    int getCurrentProgram() override {return 0;}
    void setCurrentProgram(int index) override {}
    const String getProgramName(int index) override {return String();}
    void changeProgramName(int index, const String& newName) override {}

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    void loadPatch(const juce::File& file);
    inline const Patch getPatch() const noexcept {return m_patch;}
    inline Patch getPatch() noexcept {return m_patch;}
    
    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    inline void lock() const noexcept {m_mutex.lock();}
    inline void unlock() const noexcept {m_mutex.unlock();}
    
    class Listener
    {
    public:
        inline constexpr Listener() {}
        inline virtual ~Listener() {}
        virtual void patchChanged() = 0;
    };

private:
    
    vector<Listener*> getListeners() const noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessor)
};

class CamoParameter : public AudioProcessorParameter
{
private:
    t_eparameter* m_parameter;
    
public:
    
    float getValue() const override {
        float f;
        m_parameter->p_getter(m_parameter->p_owner, &f);
        return f / (m_parameter->p_max - m_parameter->p_min) + m_parameter->p_min;
    };
    
    void setValue(float newValue) override {
        m_parameter->p_setter(m_parameter->p_owner, newValue / (m_parameter->p_max - m_parameter->p_min) + m_parameter->p_min);
    }

};


#endif  // PLUGINPROCESSOR_H_INCLUDED
