//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_STEREOANALYSISBUFFER_H
#define BLINKYTUNE_STEREOANALYSISBUFFER_H

#include "StereoSpectrumBuffer.h"

/**
 * Represents a buffer that contains left and right channel spectrum analysis output.
 */
class StereoAnalysisBuffer {
public:
    StereoAnalysisBuffer() {};

    StereoAnalysisBuffer(float &bassL, float &bassR, float &midL, float &midR, float &trebleL, float &trebleR,
                         float &volumeL, float &volumeR, std::vector<float> &spectrumL,
                         std::vector<float> &spectrumR) : bassL_(bassL), bassR_(bassR), midL_(midL),
                                                          midR_(midR), trebleL_(trebleL), trebleR_(trebleR),
                                                          volumeL_(volumeL), volumeR_(volumeR),
                                                          spectrumL_(spectrumL), spectrumR_(spectrumR) {}

    StereoAnalysisBuffer(float &bassL, float &bassR, float &midL, float &midR, float &trebleL, float &trebleR,
                         float &volumeL, float &volumeR, std::vector<float> &&spectrumL,
                         std::vector<float> &&spectrumR) : bassL_(bassL), bassR_(bassR), midL_(midL),
                                                          midR_(midR), trebleL_(trebleL), trebleR_(trebleR),
                                                          volumeL_(volumeL), volumeR_(volumeR),
                                                          spectrumL_(spectrumL), spectrumR_(spectrumR) {}
    
    float bassL_, bassR_;
    float midL_, midR_;
    float trebleL_, trebleR_;
    float volumeL_, volumeR_;
    std::vector<float> spectrumL_, spectrumR_;
};


#endif //BLINKYTUNE_STEREOANALYSISBUFFER_H