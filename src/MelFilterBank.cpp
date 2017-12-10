//
// Created by marcin on 09.12.17.
//

#include "MelFilterBank.h"


MelFilterBank::MelFilterBank(unsigned int noOfValues, kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> &tFreqValues) :
        MelFilterBank::freqValues(FreqValues), MelFilterBank::noOfValues(noOfValues) {}

float MelFilterBank::hertzToMel(const float &item) const { return 2595.0 * log10(1 + (item / 700.0)); }

float MelFilterBank::melToHertz(const float &item) const { return 700.0 * (10 * (item / 2595.0)) - 700.0; }

std::vector<float> MelFilterBank::compute() {
    for (const auto &item : freqValues) {
        for()
    }
}