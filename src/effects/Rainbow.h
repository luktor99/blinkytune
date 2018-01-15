//
// Created by luktor99 on 15.01.18.
//

#ifndef BLINKYTUNE_RAINBOW_H
#define BLINKYTUNE_RAINBOW_H


#include "../NoSoundEffect.h"

/**
 * Implements the Rainbow effect
 */
class Rainbow : public NoSoundEffect {
public:
    /**
     * The constructor.
     */
    Rainbow();

    void tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *);

    void populateControls(QLayout* layout, QWidget* parent);

    void readControls();

    /**
     * Create a new instance of the effect. This function is used by the EffectsFactory class.
     * @return A pointer to the newly created Effect class object.
     */
    static Effect *create();

    /**
     * The parameters controlling the effect's behaviour.
     */
    struct Params {
        float speed;
        float scale;
    };

private:
    Params p_;
    float pos;
};


#endif //BLINKYTUNE_RAINBOW_H
