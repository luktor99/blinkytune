//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_EFFECT_H
#define BLINKYTUNE_EFFECT_H


#include <mutex>
#include "StereoAnalysisBuffer.h"
#include "LEDStrip.h"

class Effect {
public:
    virtual void tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *data = nullptr) = 0;

    virtual void populateControls() = 0;

    virtual void readControls() = 0;

protected:
    std::mutex mutex_;
};


#endif //BLINKYTUNE_EFFECT_H
