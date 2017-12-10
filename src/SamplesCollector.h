//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_SAMPLESCOLLECTOR_H
#define BLINKYTUNE_SAMPLESCOLLECTOR_H


#include "Worker.h"
#include "AudioInputStream.h"
#include "DSPParameters.h"
#include "StereoSamplesBuffer.h"
#include "FIFOQueue.h"

class SamplesCollector : public Worker {
public:
    SamplesCollector(AudioInputStream &stream, FIFOQueue<StereoSamplesBuffer<FRAMES_PER_BUFFER>> &outputFIFO);

private:

    void mainLoop();

    AudioInputStream &stream_;
    FIFOQueue<StereoSamplesBuffer<FRAMES_PER_BUFFER>> &outputFIFO_;
};


#endif //BLINKYTUNE_SAMPLESCOLLECTOR_H
