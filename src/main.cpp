
#include <iostream>
#include <thread>
#include <list>
#include <algorithm>

#include "portaudio.h"

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "UDPSender.h"
#include "AudioInterface.h"
#include "AudioInputStream.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <kfr/base.hpp>
#include <kfr/dft.hpp>
#include <kfr/dsp.hpp>
#include <kfr/io.hpp>
#pragma GCC diagnostic pop

const char NUM_LEDS = 60;

#define SAMPLE_RATE         (48000)//(44100)
#define FRAMES_PER_BUFFER   (256)//(64)

std::mutex mtx;

void threadLed(float **inBuffer) {
//    UDPSender client("192.168.1.166", "4200");
    UDPSender client("localhost", "4200");

    std::chrono::system_clock::time_point timeLimit;
    for (int ii = 0;; ++ii) {
        timeLimit = std::chrono::system_clock::now() + std::chrono::milliseconds(30);

        mtx.lock();
        kfr::univector<float, FRAMES_PER_BUFFER> samplesL = kfr::make_univector(inBuffer[0], FRAMES_PER_BUFFER);
        kfr::univector<float, FRAMES_PER_BUFFER> samplesR = kfr::make_univector(inBuffer[1], FRAMES_PER_BUFFER);
        mtx.unlock();

        float volumeL, volumeR;
        volumeL = kfr::rms(samplesL);
        volumeR = kfr::rms(samplesR);

        const auto window = kfr::window_hamming(FRAMES_PER_BUFFER);
        samplesL = samplesL * window;
        samplesR = samplesR * window;

        kfr::univector<kfr::complex<float>, FRAMES_PER_BUFFER / 2 + 1> freqL, freqR;
        //freqL = kfr::realdft(samplesL);
        //freqR = kfr::realdft(samplesR);
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

        char pixel[60 * 3] = {0};

//        for (int i = 0; i < NUM_LEDS * 3; ++i) {
//            if (i % 3 == 2)
//                pixel[i] = 255 * (i / 3.0 / NUM_LEDS < volumeL);
//            else if (i % 3 == 0)
//                pixel[i] = 255 * (i / 3.0 / NUM_LEDS >= (1.0 - volumeR));
//        }

        for (int i = 0; i < NUM_LEDS * 3; ++i) {
            if (i % 3 == 2) {
                int value = 255 * ((spectrumL[i / 3 * 2] + spectrumL[i / 3 * 2 + 1]) / 2.0 > 0.002);
                if (value > 255)
                    value = 255;
                pixel[i] = value;
            }
        }

        const boost::asio::mutable_buffer buffer(pixel, 3 * NUM_LEDS);
        client.send(buffer);
        ii += 1;

        std::this_thread::sleep_until(timeLimit);
    }
}

int main(void) {
    // Initialize PortAudio
    AudioInterface::getInstance().initialize();

    // Display all input devices
    for (auto dev : AudioInterface::getInstance().getInputDevicesList())
        std::cout << "[" << dev.getID() << "] " << dev.getName() << std::endl;

    // Select the input device
    AudioDevice device = AudioInterface::getInstance().getDefaultInputDevice();
    std::cout << "Selected: [" << device.getID() << "] " << device.getName() << std::endl;

    // Create an input stream
    AudioInputStream stream(device, SAMPLE_RATE, FRAMES_PER_BUFFER);

    // Allocate a buffer for samples (TODO: create a class for the samples)
    float inBuffer1[FRAMES_PER_BUFFER] = {0};
    float inBuffer2[FRAMES_PER_BUFFER] = {0};
    float *inBuffer[2] = {inBuffer1, inBuffer2};

    // Start the LED effect thread
    std::thread t(threadLed, inBuffer);

    // Keep collecting new samples
    for (;;) {
    //for (int i=0; i < (SAMPLE_RATE/FRAMES_PER_BUFFER)*5; ++i) {

        float inBuffer1_[FRAMES_PER_BUFFER] = {0};
        float inBuffer2_[FRAMES_PER_BUFFER] = {0};
        float *inBuffer_[2] = {inBuffer1_, inBuffer2_};
        stream.readSamples(&inBuffer_);
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::copy(inBuffer_[0], inBuffer_[0] + FRAMES_PER_BUFFER, inBuffer[0]);
            std::copy(inBuffer_[1], inBuffer_[1] + FRAMES_PER_BUFFER, inBuffer[1]);
        }
    }

    exit(EXIT_SUCCESS);
}