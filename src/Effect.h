//@ref
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_EFFECT_H
#define BLINKYTUNE_EFFECT_H


#include <mutex>
#include "StereoAnalysisBuffer.h"
#include "LEDStrip.h"
#include <QLayout>
#include <QWidget>

/**
 * Represents a light effect. This is an abstract class - the base of the class hierarchy.
 */
class Effect {
public:
    /**
     * Perform a single update of the LED strip's output buffer using (or not) the analysis data.
     * @param ledStrip A reference to the active LED strip.
     * @param data A pointer to the analysis data buffer.
     */
    virtual void tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *data = nullptr) = 0;

    /**
     * Populate the GUI with effect parameters' controls.
     */
    virtual void  populateControls(QLayout* layout, QWidget* parent) = 0;

    /**
     * Apply the parameters set in the GUI to the effect.
     */
    virtual void readControls() = 0;

protected:
    std::mutex mutex_; /*!< A mutex allowing concurrent read/write access to the effect's parameters */
};


#endif //BLINKYTUNE_EFFECT_H
