//
// Created by luktor99 on 15.01.18.
//

#include "Rainbow.h"

namespace {
    const Rainbow::Params defaultParams = {
            0.1f,
            1.0f
    };
}

Rainbow::Rainbow() : p_(defaultParams), pos(0.0f) {

}

void Rainbow::tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *) {
    for (int i = 0; i < ledStrip.getLength(); ++i)
        ledStrip.setHSV(i, pos + (i*p_.scale/ledStrip.getLength()*360.0f), 1.0f, 1.0f);

    pos += p_.speed;
}

void Rainbow::populateControls() {
    //TODO
}

void Rainbow::readControls() {
    //TODO
}

Effect *Rainbow::create() {
    return new Rainbow();
}
