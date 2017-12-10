//
// Created by luktor99 on 10.12.17.
//

#include "SamplesCollector.h"

SamplesCollector::SamplesCollector(AudioInputStream &stream,
                                   FIFOQueue<StereoSamplesBuffer<FRAMES_PER_BUFFER>> &outputFIFO) : stream_(stream),
                                                                                                    outputFIFO_(
                                                                                                            outputFIFO) {
}

void SamplesCollector::mainLoop() {
    static float samplesBufferL[FRAMES_PER_BUFFER] = {0};
    static float samplesBufferR[FRAMES_PER_BUFFER] = {0};
    static float *samplesBuffer[2] = {samplesBufferL, samplesBufferR};

    stream_.readSamples(&samplesBuffer);

    outputFIFO_.push(new StereoSamplesBuffer<FRAMES_PER_BUFFER>(samplesBufferL, samplesBufferR));
}
