//
// Created by luktor99 on 13.01.18.
//

#include <QLabel>

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
	QLabel* rLabel = new QLabel(parent);
	rLabel->setText("Red color slider");
	rSlider = new QSlider(Qt::Horizontal, parent);
	rSlider->setRange(0, 255);
	rSlider->setSingleStep(1);
	rSlider->setValue(static_cast<int>(defaultParams.R));
	rSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

	QLabel* gLabel = new QLabel(parent);
	gLabel->setText("Green color slider");
	gSlider = new QSlider(Qt::Horizontal, parent);
	gSlider->setRange(0, 255);
	gSlider->setSingleStep(1);
	gSlider->setValue(static_cast<int>(defaultParams.G));
	gSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

	QLabel* bLabel = new QLabel(parent);
	bLabel->setText("Blue color slider");
	bSlider = new QSlider(Qt::Horizontal, parent);
	bSlider->setRange(0, 255);
	bSlider->setSingleStep(1);
	bSlider->setValue(static_cast<int>(defaultParams.B));
	bSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

	layout->addWidget(rLabel);
	layout->addWidget(rSlider);
	layout->addWidget(gLabel);
	layout->addWidget(gSlider);
	layout->addWidget(bLabel);
	layout->addWidget(bSlider);

}

void StillColor::readControls() {
    std::lock_guard<std::mutex> lock(mutex_);

	p_.R = static_cast<float>(rSlider->value());
    p_.G = static_cast<float>(gSlider->value());
    p_.B = static_cast<float>(bSlider->value());
}

Effect *StillColor::create() {
    return new StillColor();
}

