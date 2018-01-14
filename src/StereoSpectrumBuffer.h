//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_STEREOSPECTRUMBUFFER_H
#define BLINKYTUNE_STEREOSPECTRUMBUFFER_H

#include <cstddef>
#include <vector>
#include "Settings.h"
#include "StereoSamplesBuffer.h"

/**
 * Represents a buffer that contains left and right channel spectrum data.
 */
class StereoSpectrumBuffer {
public:
    StereoSpectrumBuffer(const std::vector<float> &spectrumL, const std::vector<float> &spectrumR, std::unique_ptr<StereoSamplesBuffer> &&samples) : spectrumL_(spectrumL), spectrumR_(spectrumR), samples_(std::move(samples)) {}

    StereoSpectrumBuffer(std::vector<float> &&spectrumL, std::vector<float> &&spectrumR, std::unique_ptr<StereoSamplesBuffer> &&samples) : spectrumL_(std::move(spectrumL)), spectrumR_(std::move(spectrumR)), samples_(std::move(samples)) {}

    std::vector<float> spectrumL_, spectrumR_;
    std::unique_ptr<StereoSamplesBuffer> samples_;
};


#endif //BLINKYTUNE_STEREOSPECTRUMBUFFER_H
