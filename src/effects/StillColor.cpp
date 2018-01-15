//
// Created by luktor99 on 13.01.18.
//

#include "StillColor.h"

namespace {
    const StillColor::Params defaultParams{
            255.0f,
            120.0f,
            0.0f
    };
}

StillColor::StillColor() : p_(defaultParams) {

}

void StillColor::tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *) {
    std::lock_guard<std::mutex> lock(mutex_);
    for (int i = 0; i < ledStrip.getLength(); ++i)
        ledStrip.setRGB(i, p_.R, p_.G, p_.B);
}

void StillColor::populateControls(QLayout* layout, QWidget* parent) {
    // TODO...
}

void StillColor::readControls() {
    std::lock_guard<std::mutex> lock(mutex_);
    // TODO...

    p_.R = rand() % 256;
    p_.G = rand() % 256;
    p_.B = rand() % 256;
}

Effect *StillColor::create() {
    return new StillColor();
}

