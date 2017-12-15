//
// Created by luktor99 on 02.12.17.
//

#ifndef BLINKYTUNE_AUDIOSTREAM_H
#define BLINKYTUNE_AUDIOSTREAM_H

#include "portaudio.h"
#include "AudioDevice.h"

class AudioStream {
public:
    void readSamples(void *buffer) const;

protected:
    AudioStream(const AudioDevice &inputDevice, unsigned int sampleRate, unsigned int framesPerBuffer);

    ~AudioStream();

    void start() const;

    void close() const;

    PaStream *stream_;
    PaStreamParameters streamParams_;
    unsigned int sampleRate_;
    unsigned int framesPerBuffer_;
};


#endif //BLINKYTUNE_AUDIOSTREAM_H
