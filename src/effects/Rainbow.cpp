//
// Created by luktor99 on 15.01.18.
//

#include <QLabel>

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

void Rainbow::populateControls(QLayout* layout, QWidget* parent) {
	QLabel* scaleLabel = new QLabel(parent);
	scaleLabel->setText("Scale slider");
	scaleSlider = new QSlider(Qt::Horizontal, parent);
	scaleSlider->setRange(0, 1000000);
	scaleSlider->setSingleStep(10);
	scaleSlider->setValue(static_cast<int>(defaultParams.scale) * 500000);
	scaleSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	QLabel* speedLabel = new QLabel(parent);
	speedLabel->setText("Speed slider");
	speedSlider = new QSlider(Qt::Horizontal, parent);
	speedSlider->setRange(0, 1000000);
	speedSlider->setSingleStep(10);
	scaleSlider->setValue(static_cast<int>(defaultParams.speed) * 500000);
	speedSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	layout->addWidget(scaleLabel);
	layout->addWidget(scaleSlider);
	layout->addWidget(speedLabel);
	layout->addWidget(speedSlider);
}

void Rainbow::readControls() {
	std::lock_guard<std::mutex> lock(mutex_);

	p_.speed = static_cast<float>(speedSlider->value())/ 500000;
	p_.scale = static_cast<float>(scaleSlider->value()) / 500000  + 0.0001f;
}

Effect *Rainbow::create() {
    return new Rainbow();
}
