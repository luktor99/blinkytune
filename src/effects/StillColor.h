//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_STILLCOLOR_H
#define BLINKYTUNE_STILLCOLOR_H


#include "../NoSoundEffect.h"

/**
 * Implements the Still Color effect.
 */
class StillColor : public NoSoundEffect {
public:
    /**
     * The constructor.
     */
    StillColor();

    void tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *);

    void populateControls();

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
        float R;
        float G;
        float B;
    };
    
private:
    Params p_;
};


#endif //BLINKYTUNE_STILLCOLOR_H
