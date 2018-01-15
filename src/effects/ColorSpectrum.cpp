//
// Created by luktor99 on 15.01.18.
//

#include <QLabel>

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

 void ColorSpectrum::populateControls(QLayout* layout, QWidget* parent) {
	 QLabel* hueLabel = new QLabel(parent);
	 hueLabel->setText("Hue slider");
	 hueSlider = new QSlider(Qt::Horizontal, parent);
	 hueSlider->setRange(0, 360);
	 hueSlider->setSingleStep(1);
	 hueSlider->setValue(static_cast<int>(defaultParams.hue));
	 hueSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	 layout->addWidget(hueLabel);
	 layout->addWidget(hueSlider);
}

void ColorSpectrum::readControls() {
	std::lock_guard<std::mutex> lock(mutex_);

	p_.hue = static_cast<float>(hueSlider->value());
}

Effect *ColorSpectrum::create() {
    return new ColorSpectrum();
}
