//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MELFILTERBANK_H
#define BLINKYTUNE_MELFILTERBANK_H

#undef min
#undef max
#include <kfr/base/univector.hpp>


#include <memory>
#include "DSPParameters.h"


class MelFilterBank {

public:

    explicit MelFilterBank(const unsigned int &nOut);

    static float melToHertz(const float &freqInMel);

    static float hertzToMel(const float &freqInHertz);

    std::vector<float>
    compute(kfr::univector<float, SPECTRUM_LENGTH> &freqValues, const unsigned int &sampleRate, float lowerFreq = 40.0, float upperFreq = 32000) const;

private:

    unsigned int nOutputValues;

    std::size_t getLowerIndex(const float &lowerBandFrequency, const unsigned int &sampleRate) const;

    std::size_t getUpperIndex(const float &upperBandFrequency, const unsigned int &sampleRate) const;

};


#endif //BLINKYTUNE_MELFILTERBANK_H
