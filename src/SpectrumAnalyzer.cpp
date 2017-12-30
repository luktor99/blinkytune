//
// Created by luktor99 on 10.12.17.
//

#include <iostream>
#include "SpectrumAnalyzer.h"
#include "UDPSender.h"

const std::size_t NUM_LEDS = 60;

SpectrumAnalyzer::SpectrumAnalyzer(FIFOQueue<StereoSpectrumBuffer> &inputFIFO,
                                   FIFOQueue<StereoAnalysisBuffer> &outputFIFO) : inputFIFO_(inputFIFO),
                                                                                  outputFIFO_(outputFIFO) {

}

void SpectrumAnalyzer::mainLoop() {
    static UDPSender client("192.168.1.166", "4200");
    static float pixels[3 * NUM_LEDS] = {0.0};
    static int cnt = 0;
    static boost::circular_buffer<std::shared_ptr<StereoSpectrumBuffer>> spectrumHistory(N_HISTORY);

    // Acquire new spectrum and smaples data
    std::shared_ptr<StereoSpectrumBuffer> data;
    try {
        data = std::move(inputFIFO_.pop());
    }
    catch (FIFOQueue<StereoSpectrumBuffer>::TimeoutException &) {
        return;
    }

    // Fade all pixels
    for (int i = 0; i < NUM_LEDS * 3; ++i)
        pixels[i] = pixels[i] * 0.86;

    // Update pixels if necessary
/*    for (int i = 0; i < NUM_LEDS * 3; ++i) {
        if (i % 3 == 2) {
            float value = 255.0f * (data->spectrumL_[(i / 3) * (SPECTRUM_BARS - 3) / NUM_LEDS] > 0.2f);
            if (value < 0.0f)
                value = 0.0f;
            if (value > 255.0f)
                value = 255.0f;

            if (value > pixels[i])
                pixels[i] = value;
        }
    }*/

    // Calculate the average spectrum levels
    std::vector<float> spectrumAverageL(SPECTRUM_BARS, 0.0f), spectrumAverageR(SPECTRUM_BARS, 0.0f);
    for (int i = 0; i < SPECTRUM_BARS; ++i) {
        std::for_each(spectrumHistory.begin(), spectrumHistory.end(), [&i, &spectrumAverageL, &spectrumAverageR](
                std::shared_ptr<StereoSpectrumBuffer> &s) {
            spectrumAverageL[i] += s->spectrumL_[i];
            spectrumAverageR[i] += s->spectrumR_[i];
        });
        spectrumAverageL[i] /= (float)N_HISTORY;
        spectrumAverageR[i] /= (float)N_HISTORY;
    }

    // Calculate the average volume levels
    float volumeAverageL = 0.0f, volumeAverageR = 0.0f;
    std::for_each(spectrumHistory.begin(), spectrumHistory.end(), [&volumeAverageL, &volumeAverageR](
            std::shared_ptr<StereoSpectrumBuffer> &s) {
        std::for_each(s->samples_->samplesL.cbegin(), s->samples_->samplesL.cend(), [&volumeAverageL](const float &sampleL) {
            volumeAverageL += sampleL*sampleL;
        });
        std::for_each(s->samples_->samplesR.cbegin(), s->samples_->samplesR.cend(), [&volumeAverageR](const float &sampleR) {
            volumeAverageR += sampleR*sampleR;
        });
    });
    volumeAverageL /= (float)N_HISTORY;
    volumeAverageR /= (float)N_HISTORY;

    // Calculate the momentary volume levels
    float volumeL = 0.0f, volumeR = 0.0f;
    std::for_each(data->samples_->samplesL.cbegin(), data->samples_->samplesL.cend(), [&volumeL](const float &sampleL) {
        volumeL += sampleL*sampleL;
    });
    std::for_each(data->samples_->samplesR.cbegin(), data->samples_->samplesR.cend(), [&volumeR](const float &sampleR) {
        volumeR += sampleR*sampleR;
    });

    // Calculate the variance of the volume levels
    float volumeVarL = 0.0f, volumeVarR = 0.0f;
    std::for_each(spectrumHistory.begin(), spectrumHistory.end(), [&volumeVarL, &volumeAverageL](
            std::shared_ptr<StereoSpectrumBuffer> &s) {
        std::for_each(s->samples_->samplesL.cbegin(), s->samples_->samplesL.cend(), [&volumeVarL, &volumeAverageL](const float &sampleL) {
            volumeVarL += pow(volumeAverageL-sampleL*sampleL, 2.0f);
        });
    });
    volumeVarL /= (float)N_HISTORY;

    float spectrumAverage = 0.0f;
    for(auto &a : spectrumAverageL)
        spectrumAverage += a;
    spectrumAverage /= (float)SPECTRUM_BARS;

    auto maxL = std::max_element(data->spectrumL_.begin(), data->spectrumL_.end()-10);
    auto freqMax = std::distance(data->spectrumL_.begin(), maxL);

    // Store the momentary spectrum in the history
    spectrumHistory.push_back(data);

    // Generate a simple effect
    for (int i = 0; i < NUM_LEDS * 3; ++i) {
        if (i % 3 == 1) {
            //float value = 255.0f * (data->spectrumL_[(i / 3) * (SPECTRUM_BARS - 10) / NUM_LEDS] > 0.3f);
//            float value = 255.0f * (data->spectrumL_[(i / 3) * (SPECTRUM_BARS - 10) / NUM_LEDS] > 2.0*spectrumAverageL[(i / 3) * (SPECTRUM_BARS - 10) / NUM_LEDS]);
//            float value = 255.0f * (data->spectrumL_[(i / 3) * (SPECTRUM_BARS - 10) / NUM_LEDS] > 2.2*spectrumAverage);
            float value = 255.0f * (data->spectrumL_[(i / 3) * (SPECTRUM_BARS - 10) / NUM_LEDS] / *maxL);
            //float value = 255.0f * ((i / 3) * (SPECTRUM_BARS - 10) / NUM_LEDS == freqMax);

            if (value < 0.0f)
                value = 0.0f;
            if (value > 255.0f)
                value = 255.0f;

//            if (value > pixels[i])
                pixels[i] = value;
        }
        if (i % 3 == 4) {
            float value = 255.0f * (volumeL > (-0.0001*volumeVarL + 1.8f)*volumeAverageL);

            if (value < 0.0f)
                value = 0.0f;
            if (value > 255.0f)
                value = 255.0f;

            if (value > pixels[i])
                pixels[i] = value;
        }
    }

    // Display the spectrum every 0.02s
    if (cnt++ >= SAMPLE_RATE / FRAMES_PER_BUFFER * 0.02f) {
        //std::cout << volumeVarL << " " << volumeL << std::endl;
        uint8_t pixels_char[3 * NUM_LEDS];
        for (int i = 0; i < 3 * NUM_LEDS; ++i)
            pixels_char[i] = (uint8_t) pixels[i];
        const boost::asio::mutable_buffer buffer(pixels_char, 3 * NUM_LEDS);
        client.send(buffer);
    }
}
