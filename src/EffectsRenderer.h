//
// Created by luktor99 on 03.01.18.
//

#ifndef BLINKYTUNE_EFFECTSRENDERER_H
#define BLINKYTUNE_EFFECTSRENDERER_H


#include "Worker.h"
#include "StereoAnalysisBuffer.h"
#include "FIFOQueue.h"
#include "Effect.h"

class EffectsRenderer : public Worker {
public:
    EffectsRenderer(FIFOQueue<StereoAnalysisBuffer> &inputFIFO, LEDStrip &ledStrip);

    ~EffectsRenderer();

    void setEffectSound(Effect *effect);

    void setEffectNoSound(Effect *effect);

    void setRefreshRate(const float& refreshRate);

private:
    void mainLoop();

    FIFOQueue<StereoAnalysisBuffer> &inputFIFO_;
    LEDStrip &ledStrip_;
    Effect *activeEffect_;
    enum effectTypes {
        EFFECT_SOUND, EFFECT_NOSOUND
    };
    effectTypes effectType_;
    float refreshRate_;
};


#endif //BLINKYTUNE_EFFECTSRENDERER_H
