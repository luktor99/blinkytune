//
// Created by marcin on 09.12.17.
//

#include "MelFilterBank.h"


MelFilterBank::MelFilterBank(kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> &tFreqValues) :
        freqValues(tFreqValues) {};

float MelFilterBank::hertzToMel(const float &item) const { return 2595.0 * log10(1 + (item / 700.0)); };

float MelFilterBank::melToHertz(const float &item) const { return 700.0 * (10 * (item / 2595.0)) - 700.0; };

std::unique_ptr<std::vector<float>>&& MelFilterBank::compute(const unsigned int &count) const {
    std::unique_ptr<std::vector<float>> melVector = std::make_unique<std::vector<float>>();
    for (const auto &item : freqValues) {
    }

return std::move(melVector);
};