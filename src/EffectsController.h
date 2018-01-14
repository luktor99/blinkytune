//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_EFFECTSCONTROLLER_H
#define BLINKYTUNE_EFFECTSCONTROLLER_H


#include "Effect.h"
#include "AudioDevice.h"
#include "EffectsRenderer.h"
#include "SpectrumGenerator.h"
#include "SamplesCollector.h"
#include "SpectrumAnalyzer.h"
#include "TickGenerator.h"

/**
 * Represents a facade for the whole audio processing and effect generation system. This is the main component of the
 * program that controls the whole life cycle of all processing threads and keeps the connection to the LED strip. This
 * class uses the singleton and facade design pattern.
 */
class EffectsController {
public:
    /**
    * Retrieve a instance of singleton class EffectsController.
    * @return EffectsController singleton object.
    */
    static EffectsController &getInstance();

    void connect(const std::string &ip, int length);

    Effect *getEffect() const;

    void setAudioDevice(const AudioDevice &device);

    void setFPS(const float &fps);

    void setEffect(const std::string &effectName);

    void stop();

private:
    /**
     * The constructor.
     */
    EffectsController();

    /**
     * The destructor.
     */
    ~EffectsController() = default;

    EffectsController(const EffectsController &) = delete;

    EffectsController &operator=(const EffectsController &) = delete;

    void startSoundPipeline();

    void startNoSoundPipeline();

    void stopSoundPipeline();

    void stopNoSoundPipeline();

    void setActiveEffect(Effect *effect);

    enum activePipelineType {
        PIPELINE_NONE = 0, PIPELINE_SOUND, PIPELINE_NOSOUND
    };
    activePipelineType activePipeline;

    std::unique_ptr<LEDStrip> ledStrip_;
    std::unique_ptr<EffectsRenderer> effectsRenderer_;
    std::unique_ptr<Effect> effect_;
    std::unique_ptr<SamplesCollector> samplesCollector_;
    std::unique_ptr<SpectrumGenerator> spectrumGenerator_;
    std::unique_ptr<SpectrumAnalyzer> spectrumAnalyzer_;
    std::unique_ptr<TickGenerator> tickGenerator_;
    AudioDevice audioDevice_;
    std::unique_ptr<AudioInputStream> audioStream_;
    FIFOQueue<StereoSamplesBuffer> samplesFIFO_;
    FIFOQueue<StereoSpectrumBuffer> spectrumFIFO_;
    FIFOQueue<StereoAnalysisBuffer> analysisFIFO_;
    float refreshRate_;
};


#endif //BLINKYTUNE_EFFECTSCONTROLLER_H
