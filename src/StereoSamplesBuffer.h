//
// Created by luktor99 on 09.12.17.
//

#ifndef BLINKYTUNE_STEREOSAMPLESBUFFER_H
#define BLINKYTUNE_STEREOSAMPLESBUFFER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <kfr/base.hpp>

#pragma GCC diagnostic pop

template<std::size_t N>
class StereoSamplesBuffer {
public:
    StereoSamplesBuffer() = default;

    StereoSamplesBuffer(const float *samplesL, const float *samplesR) : samplesL(kfr::make_univector(samplesL, N)),
                                                                        samplesR(kfr::make_univector(samplesR, N)) {};

    kfr::univector<float, N> &getSamplesL() {
        return samplesL;
    }

    kfr::univector<float, N> &getSamplesR() {
        return samplesR;
    }

private:
    kfr::univector<float, N> samplesL, samplesR;
};


#endif //BLINKYTUNE_STEREOSAMPLESBUFFER_H
