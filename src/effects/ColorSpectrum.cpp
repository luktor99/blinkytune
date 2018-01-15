//
// Created by luktor99 on 15.01.18.
//

#include "ColorSpectrum.h"

namespace {
    const ColorSpectrum::Params defaultParams = {
            0.0f
    };
}

ColorSpectrum::ColorSpectrum() : p_(defaultParams) {

}

void ColorSpectrum::tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *data) {
    for (int i = 0; i < ledStrip.getLength(); ++i) {
        auto &specL = data->spectrumL_[i * (SPECTRUM_BARS) / ledStrip.getLength()];
        auto &specR = data->spectrumR_[i * (SPECTRUM_BARS) / ledStrip.getLength()];
        float value = (specL + specR) / 2.0f;
        ledStrip.setHSV(i, p_.hue, 1.0f, value);
    }
}

void ColorSpectrum::populateControls() {
    //TODO
}

void ColorSpectrum::readControls() {
    //TODO
}

Effect *ColorSpectrum::create() {
    return new ColorSpectrum();
}
