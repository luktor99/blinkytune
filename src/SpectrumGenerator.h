//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_SPECTRUMGENERATOR_H
#define BLINKYTUNE_SPECTRUMGENERATOR_H


#include "Worker.h"
#include "Settings.h"
#include "StereoSamplesBuffer.h"
#include "StereoSpectrumBuffer.h"
#include "FIFOQueue.h"

/**
 * Represents a worker thread that generates and filters spectrum of the incoming audio.
 */
class SpectrumGenerator : public Worker {
public:
    /**
     * The constructor.
     * @param inputFIFO The FIFO queue audio samples are read from.
     * @param outputFIFO The FIFO queue spectrum data is outputted to.
     */
    SpectrumGenerator(FIFOQueue<StereoSamplesBuffer> &inputFIFO,
                      FIFOQueue<StereoSpectrumBuffer> &outputFIFO);

private:
    /**
    * The main loop of the thread.
    */
    void mainLoop();

    FIFOQueue<StereoSamplesBuffer> &inputFIFO_; /*!< A reference to the input FIFO queue. */
    FIFOQueue<StereoSpectrumBuffer> &outputFIFO_; /*!< A referene to the output FIFO queue. */
};


#endif //BLINKYTUNE_SPECTRUMGENERATOR_H
