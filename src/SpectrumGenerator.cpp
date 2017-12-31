//
// Created by luktor99 on 10.12.17.
//
#include "MelFilterBank.h"
#include "SpectrumGenerator.h"

#include <kfr/dft.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>
#include <iostream>

SpectrumGenerator::SpectrumGenerator(FIFOQueue<StereoSamplesBuffer> &inputFIFO,
                                     FIFOQueue<StereoSpectrumBuffer> &outputFIFO) : inputFIFO_(
        inputFIFO), outputFIFO_(outputFIFO) {

}

void SpectrumGenerator::mainLoop() {
    // Acquire new samples
    std::unique_ptr<StereoSamplesBuffer> samples;

    try {
        samples = std::move(inputFIFO_.pop());
    }
    catch (FIFOQueue<StereoSamplesBuffer>::TimeoutException &) {
        return;
    }

    //auto t1 = std::chrono::system_clock::now();

    kfr::univector<float, FRAMES_PER_BUFFER> &samplesL = samples->getSamplesL();
    kfr::univector<float, FRAMES_PER_BUFFER> &samplesR = samples->getSamplesR();

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
    kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> spectrumRawL = kfr::cabs(freqL);
    kfr::univector<float, FRAMES_PER_BUFFER / 2 + 1> spectrumRawR = kfr::cabs(freqR);

    // Apply the mel filter bank to the output
    MelFilterBank melFilter(SPECTRUM_BARS);
	std::vector<float> spectrumR = melFilter.compute(spectrumRawR, SAMPLE_RATE);
	std::vector<float> spectrumL = melFilter.compute(spectrumRawL, SAMPLE_RATE);

    // Pass the data to the next thread
    outputFIFO_.push(new StereoSpectrumBuffer(spectrumL, spectrumR, std::move(samples)));

    /*std::cout
            << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t1).count()
            << std::endl;*/
}
