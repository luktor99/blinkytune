//
// Created by luktor99 on 10.12.17.
//

#include <iostream>
#include "SpectrumAnalyzer.h"
#include "UDPSender.h"
#include "Filter.h"
#include "LEDStrip.h"

SpectrumAnalyzer::SpectrumAnalyzer(FIFOQueue<StereoSpectrumBuffer> &inputFIFO,
                                   FIFOQueue<StereoAnalysisBuffer> &outputFIFO) : inputFIFO_(inputFIFO),
                                                                                  outputFIFO_(outputFIFO) {

}

void SpectrumAnalyzer::mainLoop() {
    static LEDStrip ledStrip("192.168.0.100", 60);
    static int cnt = 0;
    static boost::circular_buffer<std::shared_ptr<StereoSpectrumBuffer>> spectrumHistory(N_HISTORY);
    static std::vector<Filter> gainsL(SPECTRUM_BARS, Filter(0.99, 0.001)), gainsR(SPECTRUM_BARS, Filter(0.99, 0.001));
    static std::vector<Filter> melFiltersL(SPECTRUM_BARS, Filter(0.99, 0.3)), melFiltersR(SPECTRUM_BARS,
                                                                                          Filter(0.99, 0.3));

    // Acquire new spectrum and samples data
    std::shared_ptr<StereoSpectrumBuffer> data;
    try {
        data = std::move(inputFIFO_.pop());
    }
    catch (FIFOQueue<StereoSpectrumBuffer>::TimeoutException &) {
        return;
    }

    // Calculate the average spectrum levels
    std::vector<float> spectrumAverageL(SPECTRUM_BARS, 0.0f), spectrumAverageR(SPECTRUM_BARS, 0.0f);
    for (int i = 0; i < SPECTRUM_BARS; ++i) {
        std::for_each(spectrumHistory.begin(), spectrumHistory.end(), [&i, &spectrumAverageL, &spectrumAverageR](
                std::shared_ptr<StereoSpectrumBuffer> &s) {
            spectrumAverageL[i] += s->spectrumL_[i];
            spectrumAverageR[i] += s->spectrumR_[i];
        });
        spectrumAverageL[i] /= (float) N_HISTORY;
        spectrumAverageR[i] /= (float) N_HISTORY;
    }

    // Calculate the average volume levels
    float volumeAverageL = 0.0f, volumeAverageR = 0.0f;
    std::for_each(spectrumHistory.begin(), spectrumHistory.end(), [&volumeAverageL, &volumeAverageR](
            std::shared_ptr<StereoSpectrumBuffer> &s) {
        std::for_each(s->samples_->samplesL.cbegin(), s->samples_->samplesL.cend(),
                      [&volumeAverageL](const float &sampleL) {
                          volumeAverageL += sampleL * sampleL;
                      });
        std::for_each(s->samples_->samplesR.cbegin(), s->samples_->samplesR.cend(),
                      [&volumeAverageR](const float &sampleR) {
                          volumeAverageR += sampleR * sampleR;
                      });
    });
    volumeAverageL /= (float) N_HISTORY;
    volumeAverageR /= (float) N_HISTORY;

    // Calculate the momentary volume levels
    float volumeL = 0.0f, volumeR = 0.0f;
    std::for_each(data->samples_->samplesL.cbegin(), data->samples_->samplesL.cend(), [&volumeL](const float &sampleL) {
        volumeL += sampleL * sampleL;
    });
    std::for_each(data->samples_->samplesR.cbegin(), data->samples_->samplesR.cend(), [&volumeR](const float &sampleR) {
        volumeR += sampleR * sampleR;
    });

    float spectrumAverage = 0.0f;
    for (auto &a : spectrumAverageL)
        spectrumAverage += a;
    spectrumAverage /= (float) SPECTRUM_BARS;

    // Find max values in the spectrum
    auto maxL = std::max_element(data->spectrumL_.begin(), data->spectrumL_.end());
    auto maxR = std::max_element(data->spectrumR_.begin(), data->spectrumR_.end());

    // Update spectrum gains
    std::transform(data->spectrumL_.begin(), data->spectrumL_.end(), gainsL.begin(), [&maxL](auto const &s) { return s + 0.05f**maxL; });
    std::transform(data->spectrumR_.begin(), data->spectrumR_.end(), gainsR.begin(), [](auto const &s) { return s; });

    // Scale the spectrum
    std::vector<float> spectrumFilteredL, spectrumFilteredR;
    std::transform(data->spectrumL_.begin(), data->spectrumL_.end(), gainsL.begin(),
                   std::back_inserter(spectrumFilteredL),
                   [](const auto &s, const auto &g) { return s / g.get(); });
    std::transform(data->spectrumR_.begin(), data->spectrumR_.end(), gainsR.begin(),
                   std::back_inserter(spectrumFilteredR),
                   [](const auto &s, const auto &g) { return s / g.get(); });

    // Update the smoothed spectrum
    std::transform(spectrumFilteredL.begin(), spectrumFilteredL.end(), melFiltersL.begin(),
                   [](auto const &s) { return s; });
    std::transform(spectrumFilteredR.begin(), spectrumFilteredR.end(), melFiltersR.begin(),
                   [](auto const &s) { return s; });
    // Get the smoothed spectrum
    std::transform(melFiltersL.begin(), melFiltersL.end(), spectrumFilteredL.begin(),
                   [](const auto &f) { return f.get(); });
    std::transform(melFiltersR.begin(), melFiltersR.end(), spectrumFilteredR.begin(),
                   [](const auto &f) { return f.get(); });

    // Store the momentary spectrum in the history
    spectrumHistory.push_back(data);

    // Calculate bass, mid and treble values
    auto const iter03L = spectrumFilteredL.cbegin();
    auto const iter13L = iter03L + SPECTRUM_BARS / 3;
    auto const iter23L = iter13L + SPECTRUM_BARS / 3;
    auto const iter33L = spectrumFilteredL.cend();
    auto const iter03R = spectrumFilteredR.cbegin();
    auto const iter13R = iter03R + SPECTRUM_BARS / 3;
    auto const iter23R = iter13R + SPECTRUM_BARS / 3;
    auto const iter33R = spectrumFilteredR.cend();
    float bassL = std::accumulate(iter03L, iter13L, 0.0f) / (SPECTRUM_BARS / 3);
    float midL = std::accumulate(iter13L, iter23L, 0.0f) / (SPECTRUM_BARS / 3);
    float trebleL = std::accumulate(iter23L, iter33L, 0.0f) / (SPECTRUM_BARS / 3);
    float bassR = std::accumulate(iter03R, iter13R, 0.0f) / (SPECTRUM_BARS / 3);
    float midR = std::accumulate(iter13R, iter23R, 0.0f) / (SPECTRUM_BARS / 3);
    float trebleR = std::accumulate(iter23R, iter33R, 0.0f) / (SPECTRUM_BARS / 3);

    // Generate a simple effect
    for (int i = 0; i < ledStrip.getLength(); ++i) {
//        auto &spec = spectrumFilteredL[i * (SPECTRUM_BARS) / ledStrip.getLength()];
//        float value = 255.0f * (spec);

//        float value = 255.0f * (data->spectrumL_[i * (SPECTRUM_BARS) / ledStrip.getLength()]);
//        LEDStrip::clamp(value);
//        ledStrip.setRGB(i, 0.0f, value, 0.0f);

        ledStrip.setRGB(i, 255.0f*bassL, 255.0f*midL, 255.0f*trebleL); // a test effect
    }

    // Display the spectrum every 0.02s
    if (cnt++ >= SAMPLE_RATE / FRAMES_PER_BUFFER * 0.02f) {
        ledStrip.update();
    }
}
