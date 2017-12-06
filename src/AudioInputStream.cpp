//
// Created by luktor99 on 02.12.17.
//

#include "AudioInputStream.h"
#include <stdexcept>

AudioInputStream::AudioInputStream(const AudioDevice &inputDevice, unsigned int sampleRate,
                                   unsigned long framesPerBuffer) : AudioStream(inputDevice, sampleRate,
                                                                                framesPerBuffer) {
    streamParams_.suggestedLatency = Pa_GetDeviceInfo(inputDevice.deviceIndex_)->defaultLowInputLatency;

    // Open the stream
    if (Pa_OpenStream(
            &stream_,
            &streamParams_,
            nullptr, // input-only stream
            static_cast<double>(sampleRate),
            framesPerBuffer,
            0, // no special flags
            nullptr, // no callback
            nullptr // no user data
    ) != paNoError)
        throw std::runtime_error("Could not open the audio stream.");

    // Start the stream to allow collection of samples
    start();
}
