//
// Created by luktor99 on 03.01.18.
//

#include "EffectsRenderer.h"

EffectsRenderer::EffectsRenderer(FIFOQueue<StereoAnalysisBuffer> &inputFIFO, LEDStrip &ledStrip) : inputFIFO_(
        inputFIFO), ledStrip_(ledStrip), activeEffect_(nullptr), effectType_(EFFECT_SOUND) {
}

EffectsRenderer::~EffectsRenderer() {
    try {
        ledStrip_.clear();
        ledStrip_.update();
    }catch(...){
        throw LEDStrip::DisconnectedException();
    }
}

void EffectsRenderer::mainLoop() {
    static int cnt = 0;

    // Acquire new data
    std::unique_ptr<StereoAnalysisBuffer> data;
    try {
        data = std::move(inputFIFO_.pop());
    }
    catch (FIFOQueue<StereoAnalysisBuffer>::TimeoutException &) {
        return;
    }

    // Generate the effect
    if (activeEffect_ != nullptr)
        activeEffect_->tick(ledStrip_, data.get());
    else
        ledStrip_.clear();

    try {
        // Refresh the LED strip if a new frame is expected
        if (effectType_ == EFFECT_SOUND) {
            if (cnt++ >= SAMPLE_RATE / FRAMES_PER_BUFFER * refreshRate_) {
                ledStrip_.update();
                cnt = 0;
            }
        } else {
            if (cnt++ >= TICK_RATE * refreshRate_) {
                ledStrip_.update();
                cnt = 0;
            }
        }
    }
    catch (LEDStrip::DisconnectedException &) {
        // LED strip disconnected

        // TODO: send information to the main thread and handle the situation in GUI
        // TODO: call EffectsController::getInstance().disconnect() in the main thread!!!
    }
}

void EffectsRenderer::setEffectSound(Effect *effect) {
    effectType_ = EFFECT_SOUND;
    activeEffect_ = effect;
}

void EffectsRenderer::setEffectNoSound(Effect *effect) {
    effectType_ = EFFECT_NOSOUND;
    activeEffect_ = effect;
}

void EffectsRenderer::setRefreshRate(const float &refreshRate) {
    refreshRate_ = refreshRate;
}
