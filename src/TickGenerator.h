//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_TICKGENERATOR_H
#define BLINKYTUNE_TICKGENERATOR_H


#include "Worker.h"
#include "StereoAnalysisBuffer.h"
#include "FIFOQueue.h"

/**
 * Represents a worker thread that outputs blank analysis data. It is a time base for no sound effects.
 */
class TickGenerator : public Worker {
public:
    /**
     * The constructor.
     * @param outputFIFO The FIFO queue fake analysis data is outputted to.
     */
    TickGenerator(FIFOQueue<StereoAnalysisBuffer> &outputFIFO);

private:
    /**
     * The main loop of the thread.
     */
    void mainLoop();

    FIFOQueue<StereoAnalysisBuffer> &outputFIFO_; /*!< A reference to the output FIFO queue. */
};


#endif //BLINKYTUNE_TICKGENERATOR_H
