//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_COLORBEAT_H
#define BLINKYTUNE_COLORBEAT_H


#include "../StereoAnalysisBuffer.h"
#include "../SoundEffect.h"

class ColorBeat : public SoundEffect {
public:
    ColorBeat();

    void tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *data);

    enum Modes {
        M_BASS_MID_TREB = 0, M_BASS_TREB_MID, M_TREB_BASS_MID, M_TREB_MID_BASS, M_MID_BASS_TREB, M_MID_TREB_BASS
    };

    struct Params {
        Modes mode;
        bool mixChannels;
    };

    void populateControls();

    void readControls();

    static Effect *create();

private:
    Params p_;
};

#endif //BLINKYTUNE_COLORBEAT_H
