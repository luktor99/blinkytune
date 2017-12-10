//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MELFILTERBANK_H
#define BLINKYTUNE_MELFILTERBANK_H

#include "kfr/base"

#define FRAMES_PER_BUFFER 48000


class MelFilterBank {

public:

    MelFilterBank(unsigned int noOfVals, kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> &tFreqValues = nullptr);

    float melToHertz(const float& item) const;

    float hertzToMel(const float& item) const;

    std::vector<float> compute();


private:

    kfr::univector<float, FRAMES_PER_BUFFER/2+1> * freqValues;

    unsigned int noOfValues;

    std::vector<float> values;
};


#endif //BLINKYTUNE_MELFILTERBANK_H
