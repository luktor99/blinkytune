//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_SPECTRUMGENERATOR_H
#define BLINKYTUNE_SPECTRUMGENERATOR_H


#include "Worker.h"
#include "DSPParameters.h"
#include "StereoSamplesBuffer.h"
#include "StereoSpectrumBuffer.h"
#include "FIFOQueue.h"

class SpectrumGenerator : public Worker {
public:
    SpectrumGenerator(FIFOQueue<StereoSamplesBuffer<FRAMES_PER_BUFFER>> &inputFIFO,
                      FIFOQueue<StereoSpectrumBuffer<FRAMES_PER_BUFFER>> &outputFIFO);

    void mainLoop();

private:
    FIFOQueue<StereoSamplesBuffer<FRAMES_PER_BUFFER>> &inputFIFO_;
    FIFOQueue<StereoSpectrumBuffer<FRAMES_PER_BUFFER>> &outputFIFO_;
};


#endif //BLINKYTUNE_SPECTRUMGENERATOR_H
