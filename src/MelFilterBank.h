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

    MelFilterBank(kfr::univector<float, N_IN> &tFreqValues,const unsigned int tSampleRate) :
            freqValues(tFreqValues), sampleRate(tSampleRate) {};

    static float melToHertz(const float &freqInMel) { return 700.0 * (pow(10.0, (freqInMel / 2595.0))) - 700.0; }

    static float hertzToMel(const float &freqInHertz) { return 2595.0 * log10(1 + (freqInHertz / 700.0)); }

   std::array<float, N_OUT> compute() const {
        float melMin = hertzToMel(0);

        float deltaMel = abs(hertzToMel(static_cast<float>(sampleRate)) - melMin) / (N_OUT + 1.0);

        std::array<float, N_OUT> melValues;

        for (size_t i = 0; i < N_OUT; ++i) {
            float lowerBand = melToHertz(melMin);
            float centerBand = melToHertz(melMin + deltaMel);
            float upperBand = melToHertz(melMin + 2 * deltaMel);
            float melValue = 0.0;
            float aCoeff = 1.0/(centerBand - lowerBand);
            float tValue;

            for (size_t j = getLowerIndex(lowerBand); j < getUpperIndex(centerBand); ++j) {
                tValue = aCoeff * j - aCoeff * lowerBand;
                melValue += tValue * freqValues[j];
            }

            aCoeff = -1.0/(upperBand - centerBand);
            for (size_t j = getLowerIndex(centerBand); j < getUpperIndex(upperBand); ++j) {
                tValue = aCoeff * j + 1.0 - aCoeff * upperBand;
                melValue += tValue * freqValues[j];
            }
            melMin += deltaMel;
            melValues[i] = melValue;
        }
        return melValues;
    }

private:
    const kfr::univector<float, N_IN> &freqValues;
    const unsigned int sampleRate = 0;

    std::size_t getLowerIndex(const float &lowerBandFrequency) const {
        size_t lowerValue = static_cast<size_t>(lowerBandFrequency / (sampleRate / 2) * freqValues.size());
        return lowerValue < 0 ? 0 : lowerValue;
    }

    std::size_t getUpperIndex(const float &upperBandFrequency) const {
        size_t upperValue = static_cast<size_t>(upperBandFrequency / (sampleRate / 2) * freqValues.size());
        return upperValue > sampleRate / 2 ? sampleRate / 2 : upperValue;
    }

};


#endif //BLINKYTUNE_MELFILTERBANK_H
