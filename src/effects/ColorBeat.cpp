//
// Created by luktor99 on 13.01.18.
//

#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>

#include "ColorBeat.h"

namespace {
    const ColorBeat::Params defaultParams = {
            ColorBeat::M_BASS_MID_TREB,
            true
    };

	const std::vector<std::string> colorMapping = {
		"Bass: red, Mids: green, Treble: blue",
		"Bass: red, Treble: green, Mids: blue",
		"Treble: red, Bass: green, Mids: blue",
		"Treble red, Mids: green, Bass: blue",
		"Mids red, Bass: green, Treble: blue",
		"Mids red, Treble: green, Bass: blue",
	};
}

ColorBeat::ColorBeat() : p_(defaultParams) {

}
void ColorBeat::tick(LEDStrip &ledStrip, const StereoAnalysisBuffer *data) {
	
	std::lock_guard<std::mutex> lock(mutex_);

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
    }
}

void ColorBeat::populateControls(QLayout* layout, QWidget* parent) {
	mixChannelsCheckBox = new QCheckBox(parent);
	mixChannelsCheckBox->setText("Mix channels");
	mixChannelsCheckBox->setChecked(p_.mixChannels);
	mixChannelsCheckBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	QLabel* comboBoxLabel = new QLabel(parent);
	comboBoxLabel->setText("Color mapping");
	colorMappingComboBox = new QComboBox(parent);
	colorMappingComboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	std::for_each(colorMapping.begin(), colorMapping.end(), [this](auto item) {this->colorMappingComboBox->addItem(item.c_str()); });
	layout->addWidget(mixChannelsCheckBox);
	layout->addWidget(comboBoxLabel);
	layout->addWidget(colorMappingComboBox);
}

void ColorBeat::readControls() {
    std::lock_guard<std::mutex> lock(mutex_);

	p_.mode = static_cast<Modes>(colorMappingComboBox->currentIndex());
    p_.mixChannels = mixChannelsCheckBox->isChecked();
}

Effect *ColorBeat::create() {
    return new ColorBeat();
}
