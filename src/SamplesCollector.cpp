//
// Created by luktor99 on 10.12.17.
//

#include "SamplesCollector.h"
#include <iostream>

SamplesCollector::SamplesCollector(AudioInputStream &stream,
                                   FIFOQueue<StereoSamplesBuffer> &outputFIFO) : stream_(stream),
                                                                                                    outputFIFO_(
                                                                                                            outputFIFO) {
}

void SamplesCollector::mainLoop() {
    static float samplesBufferL[FRAMES_PER_BUFFER] = {0};
    static float samplesBufferR[FRAMES_PER_BUFFER] = {0};
    static float *samplesBuffer[2] = {samplesBufferL, samplesBufferR};

    try {
        stream_.readSamples(&samplesBuffer);
    }catch(const std::runtime_error& error){
        //Debugging info
        std::cout << "SamplesCollector: Can't read samples from stream" << std::endl;
    }

    outputFIFO_.push(new StereoSamplesBuffer(samplesBufferL, samplesBufferR));
}
