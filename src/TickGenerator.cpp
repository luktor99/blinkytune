//
// Created by luktor99 on 13.01.18.
//

#include "TickGenerator.h"

TickGenerator::TickGenerator(FIFOQueue<StereoAnalysisBuffer> &outputFIFO) : outputFIFO_(outputFIFO) {

}

void TickGenerator::mainLoop() {
    std::chrono::system_clock::time_point timeLimit;
    timeLimit = std::chrono::system_clock::now() + std::chrono::milliseconds((int64_t) 1e3 / TICK_RATE);

    outputFIFO_.push(new StereoAnalysisBuffer);

    std::this_thread::sleep_until(timeLimit);
}
