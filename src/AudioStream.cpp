//
// Created by luktor99 on 02.12.17.
//

#include <stdexcept>
#include "AudioStream.h"

/**
 * Constructor of AudioStream class.
 * @param inputDevice A reference to AudioDevice object representing the audio device the stream will be connected to.
 * @param sampleRate The sampling rate of the stream.
 * @param framesPerBuffer The amount of samples stored in a single buffer.
 */
AudioStream::AudioStream(const AudioDevice &inputDevice, unsigned int sampleRate, unsigned int framesPerBuffer)
        : sampleRate_(sampleRate), framesPerBuffer_(framesPerBuffer) {
    streamParams_.device = inputDevice.deviceIndex_;
    streamParams_.sampleFormat = paFloat32 | paNonInterleaved;
    streamParams_.channelCount = 2; // stereo device
    streamParams_.hostApiSpecificStreamInfo = nullptr;
}

/**
 * Start the audio stream.
 */
void AudioStream::start() const {
    if (Pa_StartStream(stream_) != paNoError)
        throw std::runtime_error("Could not start the audio stream.");
}

/**
 * Close the audio stream.
 */
void AudioStream::close() const {
    if (Pa_CloseStream(stream_) != paNoError)
        throw std::runtime_error("Could not close the audio stream.");
}

/**
 * Read new samples from the audio device.
 * @param buffer A void pointer to the buffer structure
 */
void AudioStream::readSamples(void *buffer) const {
    if (Pa_ReadStream(stream_, buffer, framesPerBuffer_) != paNoError)
        throw std::runtime_error("Could not read samples from the audio stream.");
}

/**
 * Destructor of AudioStream class.
 */
AudioStream::~AudioStream() {
    close();
}
