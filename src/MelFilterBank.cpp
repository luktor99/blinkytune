//
// Created by marcin on 12.12.17.
//

#include "MelFilterBank.h"

MelFilterBank::MelFilterBank(const unsigned int &nOut) : nOutputValues(nOut) {};

float MelFilterBank::melToHertz(const float &freqInMel) { return 700.0 * (pow(10.0, (freqInMel / 2595.0))) - 700.0; }

float MelFilterBank::hertzToMel(const float &freqInHertz) { return 2595.0 * log10(1 + (freqInHertz / 700.0)); }

std::vector<float>
MelFilterBank::compute(kfr::univector<float, SPECTRUM_LENGTH> &freqValues, const unsigned int &sampleRate,
                       float lowerFreq, float upperFreq) const {
    float melMin = hertzToMel(lowerFreq);

    float deltaMel = fabs(hertzToMel(static_cast<float>(upperFreq)) - melMin) / (nOutputValues + 1.0);

    std::vector<float> melValues(nOutputValues, 0);
    float lowerBand, centerBand, upperBand, melValue, aCoeff, tValue;
    for (size_t i = 0; i < nOutputValues; ++i) {
        lowerBand = melToHertz(melMin);
        centerBand = melToHertz(melMin + deltaMel);
        upperBand = melToHertz(melMin + 2 * deltaMel);
        melValue = 0.0;
        aCoeff = 1.0 / (centerBand - lowerBand);

        for (size_t j = getLowerIndex(lowerBand, sampleRate); j < getUpperIndex(centerBand, sampleRate); ++j) {
            tValue = aCoeff * j - aCoeff * lowerBand;
            melValue += tValue * freqValues[j];
        }

        aCoeff = -1.0 / (upperBand - centerBand);
        for (size_t j = getLowerIndex(centerBand, sampleRate); j < getUpperIndex(upperBand, sampleRate); ++j) {
            tValue = aCoeff * j + 1.0 - aCoeff * upperBand;
            melValue += tValue * freqValues[j];
        }
        melMin += deltaMel;
        melValues[i] = melValue;
    }
    return melValues;
}

std::size_t MelFilterBank::getLowerIndex(const float &lowerBandFrequency, const unsigned int &sampleRate) const {
    size_t lowerValue = static_cast<size_t>(lowerBandFrequency / (sampleRate / 2) * (SPECTRUM_LENGTH - 1));
    return lowerValue;
}

std::size_t MelFilterBank::getUpperIndex(const float &upperBandFrequency, const unsigned int &sampleRate) const {
    size_t upperValue = static_cast<size_t>(upperBandFrequency / (sampleRate / 2) * (SPECTRUM_LENGTH - 1));
    return upperValue > SPECTRUM_LENGTH - 1 ? SPECTRUM_LENGTH - 1 : upperValue;
}