//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MELFILTERBANK_H
#define BLINKYTUNE_MELFILTERBANK_H

#include <kfr/base/univector.hpp>
#include <memory>


template<size_t N_IN, unsigned int N_OUT>
class MelFilterBank {

public:

    MelFilterBank(kfr::univector<float, N_IN> &tFreqValues, const unsigned int &tSampleRate) :
            freqValues(tFreqValues), sampleRate(tSampleRate) {};

    static float melToHertz(const float &freqInMel) const { return 2595.0 * log10(1 + (freqInMel / 700.0)); };

    static float hertzToMel(const float &freqInHertz) const {
        return 700.0 * (pow(10.0, (freqInHertz / 2595.0))) - 700.0;
    };

    std::size_t getLowerIndex(const float &lowerBandFrequency) const {
        size_t lowerValue = static_cast<size_t>(lowerBandFrequency / (sampleRate / 2) * freqValues.size());
        return lowerValue > (sampleRate / 2) ? (sampleRate / 2 + 1) : lowerValue;
    }

    std::size_t getUpperIndex(const float &upperBandFrequency) const {
        size_t upperValue = static_cast<size_t>(upperBandFrequency / (sampleRate / 2) * freqValues.size());
        return upperValue > sampleRate / 2 ? sampleRate / 2 : upperValue;
    }

    std::unique_ptr<std::vector<float>> compute(const size_t &nMelBands, const float &freqMin,
                                                const float &freqMax, const unsigned int &countFreqBands) const {
        float melMin = hertzToMel(freqMin);

        float deltaMel = abs(hertzToMel(freqMax) - melMin) / (nMelBands + 1.0);

        std::unique_ptr<std::vector<float>> melValues = std::make_unique<std::vector<float>>();

        for (size_t i = 0; i < nMelBands; ++i) {
            float lowerBand = melToHertz(melMin);
            float centerBand = melToHertz(melMin + deltaMel);
            float upperBand = melToHertz(melMin + 2 * deltaMel);
            float melValue = 0.0;

            for (size_t j = getLowerIndex(lowerBand); j < getUpperIndex(upperBand); ++j) {
                float aCoeff = (freqValues[getUpperIndex(upperBand)] - freqValues[getLowerIndex(lowerBand)]) /
                          (lowerBand - upperBand);
                float tValue = aCoeff*j+ freqValues[getLowerIndex(lowerBand)] - aCoeff*lowerBand;
                melValue += tValue;
            }
            melMin += deltaMel;
            melValues->push_back(melValue);
        }
        return std::move(melValues);
    }

private:

    unsigned int sampleRate = 0;
    const kfr::univector<float, N_IN> &freqValues;

};


#endif //BLINKYTUNE_MELFILTERBANK_H
