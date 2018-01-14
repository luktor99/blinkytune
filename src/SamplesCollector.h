//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_SAMPLESCOLLECTOR_H
#define BLINKYTUNE_SAMPLESCOLLECTOR_H


#include "Worker.h"
#include "AudioInputStream.h"
#include "Settings.h"
#include "StereoSamplesBuffer.h"
#include "FIFOQueue.h"

/**
 * Represents a worker thread that collects samples from an input audio stream.
 */
class SamplesCollector : public Worker {
public:
    /**
     * The constructor.
     * @param stream The input audio stream samples will be read from.
     * @param outputFIFO The FIFO queue samples will be outputted to.
     */
    SamplesCollector(AudioInputStream &stream, FIFOQueue<StereoSamplesBuffer> &outputFIFO);

private:
    /**
     * The main loop of the thread.
     */
    void mainLoop();

    AudioInputStream &stream_; /*!< A reference to the input audio stream. */
    FIFOQueue<StereoSamplesBuffer> &outputFIFO_; /*!< A reference to the output FIFO queue. */
};


#endif //BLINKYTUNE_SAMPLESCOLLECTOR_H
