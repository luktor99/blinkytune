//
// Created by luktor99 on 03.01.18.
//

#ifndef BLINKYTUNE_EFFECTSRENDERER_H
#define BLINKYTUNE_EFFECTSRENDERER_H


#include "Worker.h"
#include "StereoAnalysisBuffer.h"
#include "FIFOQueue.h"
#include "Effect.h"

/**
 * Represents a worker thread that generates light effects and updates the LED strip.
 */
class EffectsRenderer : public Worker {
public:
    /**
     * The constructor.
     * @param inputFIFO The FIFO queue analysis data is read from.
     * @param ledStrip A reference to the active LED strip.
     */
    EffectsRenderer(FIFOQueue<StereoAnalysisBuffer> &inputFIFO, LEDStrip &ledStrip);

    /**
     * The destructor.
     */
    ~EffectsRenderer();

    /**
     * Set the active effect to a given sound-reactive effect.
     * @param effect A pointer to the new effect.
     */
    void setEffectSound(Effect *effect);

    /**
     * Set the active effect to a given not sound-reactive effect.
     * @param effect A pointer to the new effect.
     */
    void setEffectNoSound(Effect *effect);

    /**
     * Update the refresh rate of the LED strip.
     * @param refreshRate The new value of the refreshing rate.
     */
    void setRefreshRate(const float &refreshRate);

private:
    /**
    * The main loop of the thread.
    */
    void mainLoop();

    FIFOQueue<StereoAnalysisBuffer> &inputFIFO_; /*!< A reference to the input FIFO queue. */
    LEDStrip &ledStrip_; /*!< A reference to the LED strip. */
    Effect *activeEffect_; /*!< A pointer to the active Effect class object. */
    /**
     * The possible types of effects.
     */
    enum effectTypes {
        EFFECT_SOUND, /*!< A sound-reactive effect. */
        EFFECT_NOSOUND /*!< A not sound-reactive effect. */
    };
    effectTypes effectType_; /*!< The type of the active effect */
    float refreshRate_; /*!< The current refreshing rate of the LED strip. */
};


#endif //BLINKYTUNE_EFFECTSRENDERER_H
