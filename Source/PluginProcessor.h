#pragma once
#include <JuceHeader.h>
#include <array>
#include <vector>
#include <algorithm>
#include "PitchDetector.h"
#include "ScaleQuantizer.h"

class WIR3DProcessor : public juce::AudioProcessor
{
public:
    WIR3DProcessor();
    ~WIR3DProcessor() override = default;

    void prepareToPlay(double, int) override;
    void releaseResources() override;
    bool isBusesLayoutSupported(const BusesLayout&) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int) override;
    const juce::String getProgramName(int) override;
    void changeProgramName(int, const juce::String&) override;

    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;

    void loadPreset(int index);
    void saveUserPreset(int slotIndex, const juce::String& name);
    juce::StringArray getPresetNames() const;

    juce::AudioProcessorValueTreeState params;

private:
    static juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    static juce::NormalisableRange<float> frequencyRange(float min, float max, float interval = 0.1f);
    void updatePitchRange(int rangeIndex);
    void cacheParameterPointers();

    double sampleRate = 44100.0;

    // Zero-Lookup Direct Atomic Parameter Caches for real-time thread
    std::atomic<float>* bendParam = nullptr;
    std::atomic<float>* tuneParam = nullptr;
    std::atomic<float>* speedParam = nullptr;
    std::atomic<float>* harmoParam = nullptr;
    std::atomic<float>* smileParam = nullptr;
    std::atomic<float>* repeatParam = nullptr;
    std::atomic<float>* rptMixParam = nullptr;
    std::atomic<float>* filterParam = nullptr;
    std::atomic<float>* rootParam = nullptr;
    std::atomic<float>* scaleParam = nullptr;
    std::atomic<float>* rangeParam = nullptr;
    std::atomic<float>* inputGainParam = nullptr;
    std::atomic<float>* outputGainParam = nullptr;

    // Advanced Pitch Detector & Quantizer
    PitchDetector pitchDetector;
    int currentRangeIndex = 0;
    int lockedTargetMidi = -1;
    float smoothedTargetMidi = -1.0f;
    float smoothedInputMidi = -1.0f;
    int pitchHoldSamples = 0;
    float currentPitchRatio = 1.0f;
    float smoothRatio = 1.0f;

    // Mono input buffer for pitch analysis
    std::vector<float> monoAnalysisBuffer;

    // Pitch shifter primary delay lines
    std::vector<float> delay[2];
    int writePos = 0;
    float phase = 0.0f;
    float grainDepth = 1500.0f;

    // Dimension Stereo Harmonizer (+7 semitones with micro-detune and quadrature LFO)
    float harmoPhaseL = 0.0f;
    float harmoPhaseR = 0.0f;
    float harmoLfoPhase = 0.0f;
    float tapeDriftPhase = 0.0f;

    // Ping-Pong delay lines
    std::vector<float> pingPongL;
    std::vector<float> pingPongR;
    int pingPongPosL = 0;
    int pingPongPosR = 0;
    float pingPongFilterL = 0.0f;
    float pingPongFilterR = 0.0f;

    // Beat Repeat buffer
    std::vector<float> repeatBuf[2];
    int repeatWritePos = 0;
    int repeatReadPos = 0;
    int currentSliceLength = 2048;
    float repeatFilterState[2] = {0.0f, 0.0f};

    // Smile & Filter states
    std::array<float, 2> hpState = {0.0f, 0.0f};
    std::array<float, 2> echoState = {0.0f, 0.0f};
    std::vector<std::vector<float>> smileEcho;
    int smileEchoPos = 0;

    // Master Filter (Bipolar LP / HP)
    std::array<float, 2> masterFiltState1 = {0.0f, 0.0f};
    std::array<float, 2> masterFiltState2 = {0.0f, 0.0f};

    // Smooth Parameter Ramping to eliminate clicks
    juce::LinearSmoothedValue<float> smoothedWet;
    juce::LinearSmoothedValue<float> smoothedHarmo;
    juce::LinearSmoothedValue<float> smoothedRptMix;
    juce::LinearSmoothedValue<float> smoothedSmile;
    juce::LinearSmoothedValue<float> smoothedInputGain;
    juce::LinearSmoothedValue<float> smoothedOutputGain;

    // Presets
    struct PresetData {
        juce::String name;
        float bend = 0.0f;
        float tune = 75.0f;
        float speed = 85.0f;
        float harmo = 35.0f;
        float smile = 20.0f;
        int repeat = 2;
        float rptMix = 0.0f;
        float filter = 0.0f;
        int root = 0;
        int scale = 2;
        int range = 0;
        float inGain = 0.0f;
        float outGain = 0.0f;

        PresetData() = default;
        PresetData(juce::String n, float b, float t, float s, float h, float sm,
                   int rep, float rMix, float f, int rt, int sc, int rg, float inG = 0.0f, float outG = 0.0f)
            : name(std::move(n)), bend(b), tune(t), speed(s), harmo(h), smile(sm),
              repeat(rep), rptMix(rMix), filter(f), root(rt), scale(sc), range(rg),
              inGain(inG), outGain(outG) {}
    };

    std::vector<PresetData> presets;
    int currentPreset = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WIR3DProcessor)
};
