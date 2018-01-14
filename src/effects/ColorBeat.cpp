//
// Created by luktor99 on 13.01.18.
//

#include "ColorBeat.h"

namespace {
    const ColorBeat::Params defaultParams = {
            ColorBeat::M_BASS_MID_TREB,
            true
    };
}

ColorBeat::ColorBeat() : p_(defaultParams) {

}

void ColorBeat::tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *data) {
    std::lock_guard<std::mutex> lock(mutex_);

    // Generate a simple effect
    for (int i = 0; i < ledStrip.getLength(); ++i) {
        if (p_.mixChannels) {
            float bass = (data->bassL_ + data->bassR_) / 2.0f;
            float mid = (data->midL_ + data->midR_) / 2.0f;
            float treble = (data->trebleL_ + data->trebleR_) / 2.0f;

            switch (p_.mode) {
                case M_TREB_BASS_MID:
                    ledStrip.setRGB(i, 255.0f * treble, 255.0f * bass, 255.0f * mid);
                    break;
                case M_TREB_MID_BASS:
                    ledStrip.setRGB(i, 255.0f * treble, 255.0f * mid, 255.0f * bass);
                    break;
                case M_BASS_MID_TREB:
                    ledStrip.setRGB(i, 255.0f * bass, 255.0f * mid, 255.0f * treble);
                    break;
                case M_BASS_TREB_MID:
                    ledStrip.setRGB(i, 255.0f * bass, 255.0f * treble, 255.0f * mid);
                    break;
                case M_MID_BASS_TREB:
                    ledStrip.setRGB(i, 255.0f * mid, 255.0f * bass, 255.0f * treble);
                    break;
                case M_MID_TREB_BASS:
                    ledStrip.setRGB(i, 255.0f * mid, 255.0f * treble, 255.0f * bass);
                    break;
            }
        } else {
            if (i < ledStrip.getLength() / 2) {
                switch (p_.mode) {
                    case M_TREB_BASS_MID:
                        ledStrip.setRGB(i, 255.0f * data->trebleL_, 255.0f * data->bassL_, 255.0f * data->midL_);
                        break;
                    case M_TREB_MID_BASS:
                        ledStrip.setRGB(i, 255.0f * data->trebleL_, 255.0f * data->midL_, 255.0f * data->bassL_);
                        break;
                    case M_BASS_MID_TREB:
                        ledStrip.setRGB(i, 255.0f * data->bassL_, 255.0f * data->midL_, 255.0f * data->trebleL_);
                        break;
                    case M_BASS_TREB_MID:
                        ledStrip.setRGB(i, 255.0f * data->bassL_, 255.0f * data->trebleL_, 255.0f * data->midL_);
                        break;
                    case M_MID_BASS_TREB:
                        ledStrip.setRGB(i, 255.0f * data->midL_, 255.0f * data->bassL_, 255.0f * data->trebleL_);
                        break;
                    case M_MID_TREB_BASS:
                        ledStrip.setRGB(i, 255.0f * data->midL_, 255.0f * data->trebleL_, 255.0f * data->bassL_);
                        break;
                }
            } else {
                switch (p_.mode) {
                    case M_TREB_BASS_MID:
                        ledStrip.setRGB(i, 255.0f * data->trebleR_, 255.0f * data->bassR_, 255.0f * data->midR_);
                        break;
                    case M_TREB_MID_BASS:
                        ledStrip.setRGB(i, 255.0f * data->trebleR_, 255.0f * data->midR_, 255.0f * data->bassR_);
                        break;
                    case M_BASS_MID_TREB:
                        ledStrip.setRGB(i, 255.0f * data->bassR_, 255.0f * data->midR_, 255.0f * data->trebleR_);
                        break;
                    case M_BASS_TREB_MID:
                        ledStrip.setRGB(i, 255.0f * data->bassR_, 255.0f * data->trebleR_, 255.0f * data->midR_);
                        break;
                    case M_MID_BASS_TREB:
                        ledStrip.setRGB(i, 255.0f * data->midR_, 255.0f * data->bassR_, 255.0f * data->trebleR_);
                        break;
                    case M_MID_TREB_BASS:
                        ledStrip.setRGB(i, 255.0f * data->midR_, 255.0f * data->trebleR_, 255.0f * data->bassR_);
                        break;
                }
            }
        }

//        auto &specL = data->spectrumL_[i * (SPECTRUM_BARS) / ledStrip.getLength()];
//        auto &specR = data->spectrumL_[i * (SPECTRUM_BARS) / ledStrip.getLength()];
//        float value = 255.0f * (specL + specR) / 2.0f;
//        LEDStrip::clamp(value);
//        ledStrip.setRGB(i, 0.0f, value, 0.0f);
    }
}

void ColorBeat::populateControls() {
    // TODO...
}

void ColorBeat::readControls() {
    std::lock_guard<std::mutex> lock(mutex_);
    // TODO...

    p_.mode = M_TREB_MID_BASS;
    p_.mixChannels = false;
}

Effect *ColorBeat::create() {
    return new ColorBeat();
}
