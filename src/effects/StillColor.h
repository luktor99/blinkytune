//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_STILLCOLOR_H
#define BLINKYTUNE_STILLCOLOR_H


#include "../NoSoundEffect.h"

class StillColor : public NoSoundEffect {
public:
    StillColor();

    void tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *);

    struct Params {
        float R;
        float G;
        float B;
    };

    void populateControls();

    void readControls();

    static Effect * create();

private:
    Params p_;
};


#endif //BLINKYTUNE_STILLCOLOR_H
