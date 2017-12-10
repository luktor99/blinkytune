//
// Created by luktor99 on 10.12.17.
//
#include "MelFilterBank.h"
#include "SpectrumGenerator.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <kfr/dft.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>
#include <iostream>

#pragma GCC diagnostic pop

SpectrumGenerator::SpectrumGenerator(FIFOQueue<StereoSamplesBuffer<FRAMES_PER_BUFFER>> &inputFIFO,
                                     FIFOQueue<StereoSpectrumBuffer<FRAMES_PER_BUFFER>> &outputFIFO) : inputFIFO_(
        inputFIFO), outputFIFO_(outputFIFO_) {

}

void SpectrumGenerator::mainLoop() {
    // Acquire new samples
    std::unique_ptr<StereoSamplesBuffer<FRAMES_PER_BUFFER>> samples;

    try {
        samples = std::move(inputFIFO_.pop());
    }
    catch (FIFOQueue<StereoSamplesBuffer<FRAMES_PER_BUFFER>>
           ::TimeoutException &) {
        return;
    }

    //auto t1 = std::chrono::system_clock::now();

    kfr::univector<float, FRAMES_PER_BUFFER> &samplesL = samples->getSamplesL();
    kfr::univector<float, FRAMES_PER_BUFFER> &samplesR = samples->getSamplesR();

//    float volumeL, volumeR;
//    volumeL = kfr::rms(samplesL);
//    volumeR = kfr::rms(samplesR);

    const auto window = kfr::window_hamming(FRAMES_PER_BUFFER);
    samplesL = samplesL * window;
    samplesR = samplesR * window;

    kfr::univector<kfr::complex<float>, FRAMES_PER_BUFFER / 2 + 1> freqL, freqR;
    const kfr::dft_plan_real<float> dft(FRAMES_PER_BUFFER);   // initialize plan
    kfr::univector<kfr::u8> temp(dft.temp_size);       // allocate work buffer
    dft.execute(freqL, samplesL, temp);        // do the actual transform
    dft.execute(freqR, samplesR, temp);        // do the actual transform

    // Scale outputs
    freqL = freqL / FRAMES_PER_BUFFER;
    freqR = freqR / FRAMES_PER_BUFFER;

    // Get spectrum
    kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> spectrumL = kfr::cabs(freqL);
    kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> spectrumR = kfr::cabs(freqR);

    std::array<float,8> melSpectrumL = MelFilterBank<FRAMES_PER_BUFFER/2+1, 8>(spectrumL, SAMPLE_RATE).compute();
    /*std::cout
            << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t1).count()
            << std::endl;*/
}
