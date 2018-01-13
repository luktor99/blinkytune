//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_TICKGENERATOR_H
#define BLINKYTUNE_TICKGENERATOR_H


#include "Worker.h"
#include "StereoAnalysisBuffer.h"
#include "FIFOQueue.h"

class TickGenerator : public Worker {
public:
    TickGenerator(FIFOQueue<StereoAnalysisBuffer> &outputFIFO);

private:
    void mainLoop();

    FIFOQueue<StereoAnalysisBuffer> &outputFIFO_;
};


#endif //BLINKYTUNE_TICKGENERATOR_H
