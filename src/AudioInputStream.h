//
// Created by luktor99 on 02.12.17.
//

#ifndef BLINKYTUNE_AUDIOINPUTSTREAM_H
#define BLINKYTUNE_AUDIOINPUTSTREAM_H

#include "portaudio.h"
#include <exception>
#include "AudioStream.h"
#include "AudioDevice.h"

/**
 * Represents an input audio stream.
 */
class AudioInputStream : public AudioStream {
public:
    /**
     * The constructor. Creates and opens an input audio stream.
     * @param inputDevice The input audio device
     * @param sampleRate  Audio sampling rate
     * @param framesPerBuffer The number of samples per single buffer
     */
    AudioInputStream(const AudioDevice &inputDevice, unsigned int sampleRate,
                     unsigned long framesPerBuffer);
};

#endif //BLINKYTUNE_AUDIOINPUTSTREAM_H
