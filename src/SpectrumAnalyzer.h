//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_SPECTRUMANALYZER_H
#define BLINKYTUNE_SPECTRUMANALYZER_H


#include "Worker.h"
#include "Settings.h"
#include "StereoSpectrumBuffer.h"
#include "FIFOQueue.h"
#include "StereoAnalysisBuffer.h"
#include "Filter.h"

/**
 * Represents a worker thread that analyzes the received spectrum and outputs analysis data for effect generation.
 */
class SpectrumAnalyzer : public Worker {
public:
    /**
     * The constructor.
     * @param inputFIFO The FIFO queue spectrum data is read from.
     * @param outputFIFO The FIFO queue analysis data is outputted to.
     */
    SpectrumAnalyzer(FIFOQueue<StereoSpectrumBuffer> &inputFIFO, FIFOQueue<StereoAnalysisBuffer> &outputFIFO);

private:
    /**
     * The main loop of the thread.
     */
    void mainLoop();

    FIFOQueue<StereoSpectrumBuffer> &inputFIFO_; /*!< A reference to the input FIFO queue. */
    FIFOQueue<StereoAnalysisBuffer> &outputFIFO_; /*!< A reference to the output FIFO queue. */
    boost::circular_buffer<std::shared_ptr<StereoSpectrumBuffer>> spectrumHistory_; /*!< Spectrum data history */
    std::vector<Filter> gainsL_, gainsR_; /*!< Exponential filters for spectrum gains */
    std::vector<Filter> melFiltersL_, melFiltersR_; /*!< Exponential filters for mel spectrum output */
};


#endif //BLINKYTUNE_SPECTRUMANALYZER_H
