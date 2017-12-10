//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_STEREOSPECTRUMBUFFER_H
#define BLINKYTUNE_STEREOSPECTRUMBUFFER_H

#include <cstddef>
#include <array>

template<std::size_t N>
class StereoSpectrumBuffer {
public:
    StereoSpectrumBuffer(const std::array<float, N> &spectrumL, const std::array<float, N> &spectrumR) : spectrumL_(
            spectrumL), spectrumR_(spectrumR) {}

    StereoSpectrumBuffer(std::array<float, N> &&spectrumL, std::array<float, N> &&spectrumR) : spectrumL_(
            std::move(spectrumL)), spectrumR_(std::move(spectrumR)) {}

private:
    std::array<float, N> spectrumL_, spectrumR_;
};


#endif //BLINKYTUNE_STEREOSPECTRUMBUFFER_H
