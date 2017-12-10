//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_SPECTRUMANALYZER_H
#define BLINKYTUNE_SPECTRUMANALYZER_H


#include "Worker.h"
#include "DSPParameters.h"
#include "StereoSpectrumBuffer.h"
#include "FIFOQueue.h"
#include "StereoAnalysisBuffer.h"

class SpectrumAnalyzer : public Worker {
public:
    SpectrumAnalyzer(FIFOQueue<StereoSpectrumBuffer> &inputFIFO, FIFOQueue<StereoAnalysisBuffer> &outputFIFO);
private:

    void mainLoop();

    FIFOQueue<StereoSpectrumBuffer> &inputFIFO_;
    FIFOQueue<StereoAnalysisBuffer> &outputFIFO_;
};


#endif //BLINKYTUNE_SPECTRUMANALYZER_H
