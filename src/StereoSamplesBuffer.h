//
// Created by luktor99 on 09.12.17.
//

#ifndef BLINKYTUNE_STEREOSAMPLESBUFFER_H
#define BLINKYTUNE_STEREOSAMPLESBUFFER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <kfr/base.hpp>
#include "DSPParameters.h"

#pragma GCC diagnostic pop

class StereoSamplesBuffer {
public:
    StereoSamplesBuffer() = default;

    StereoSamplesBuffer(const float *samplesL, const float *samplesR) : samplesL(kfr::make_univector(samplesL, FRAMES_PER_BUFFER)),
                                                                        samplesR(kfr::make_univector(samplesR, FRAMES_PER_BUFFER)) {};

    kfr::univector<float, FRAMES_PER_BUFFER> &getSamplesL() {
        return samplesL;
    }

    kfr::univector<float, FRAMES_PER_BUFFER> &getSamplesR() {
        return samplesR;
    }

    kfr::univector<float, FRAMES_PER_BUFFER> samplesL, samplesR;
};


#endif //BLINKYTUNE_STEREOSAMPLESBUFFER_H
