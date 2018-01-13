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

class EffectsController {
public:
    EffectsController();

    void connect(const std::string &ip, int length);

    Effect *getEffect() const;

    void setAudioDevice(const AudioDevice &device);

    void setFPS(const float &fps);

    void setEffect(const std::string &effectName);

    void stop();

private:
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
