//
// Created by luktor99 on 10.12.17.
//

#include <iostream>
#include "SpectrumAnalyzer.h"

SpectrumAnalyzer::SpectrumAnalyzer(FIFOQueue<StereoSpectrumBuffer> &inputFIFO,
                                   FIFOQueue<StereoAnalysisBuffer> &outputFIFO) : inputFIFO_(inputFIFO),
                                                                                  outputFIFO_(outputFIFO) {

}

void SpectrumAnalyzer::mainLoop() {
    static int cnt = 0;

    // Acquire new spectrum spectrum
    std::unique_ptr<StereoSpectrumBuffer> spectrum;
    try {
        spectrum = std::move(inputFIFO_.pop());
    }
    catch (FIFOQueue<StereoSpectrumBuffer>::TimeoutException &) {
        return;
    }

    // Display the spectrum every 0.5s
    if (cnt++ >= SAMPLE_RATE / FRAMES_PER_BUFFER / 2) {
        for (const auto &v: spectrum->spectrumL_)
            std::cout << v << " ";
        std::cout << std::endl;
        cnt = 0;
    }
}
