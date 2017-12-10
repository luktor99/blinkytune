//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MELFILTERBANK_H
#define BLINKYTUNE_MELFILTERBANK_H

#include <kfr/base/univector.hpp>
#include <memory>

#define FRAMES_PER_BUFFER 48000


class MelFilterBank {

public:

    MelFilterBank(kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> &tFreqValues);

    float melToHertz(const float &item) const;

    float hertzToMel(const float &item) const;

    std::unique_ptr<std::vector<float>> &&compute(const unsigned int &count) const;


private:

    const kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> &freqValues;

};


#endif //BLINKYTUNE_MELFILTERBANK_H
