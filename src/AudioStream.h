//
// Created by luktor99 on 02.12.17.
//

#ifndef BLINKYTUNE_AUDIOSTREAM_H
#define BLINKYTUNE_AUDIOSTREAM_H

#include "portaudio.h"
#include "AudioDevice.h"

/**
 * Represents an audio stream.
 */
class AudioStream {
public:
    /**
     * Read a single buffer of samples from the attached audio device.
     * @param buffer A pointer to the buffer.
     */
    void readSamples(void *buffer) const;

protected:
    /**
     * The constructor.
     * @param inputDevice The audio device samples will be read from.
     * @param sampleRate The sampling rate.
     * @param framesPerBuffer The number of samples that fit in a single buffer.
     */
    AudioStream(const AudioDevice &inputDevice, unsigned int sampleRate, unsigned int framesPerBuffer);

    /**
     * The destructor.
     */
    ~AudioStream();

    /**
     * Open the audio stream.
     */
    void start() const;

    /**
     * Close the audio stream.
     */
    void close() const;

	PaStream *stream_{nullptr}; /*!< A pointer to the opened stream. */
    PaStreamParameters streamParams_; /*!< A structure containing the stream parameters. */
    unsigned int sampleRate_; /*!< The sampling rate of the stream. */
    unsigned int framesPerBuffer_; /*!< The size of the samples buffer. */
};


#endif //BLINKYTUNE_AUDIOSTREAM_H
