//
// Created by luktor99 on 02.12.17.
//

#ifndef BLINKYTUNE_AUDIOINPUTSTREAM_H
#define BLINKYTUNE_AUDIOINPUTSTREAM_H

#include <portaudio.h>
#include <exception>
#include "AudioStream.h"
#include "AudioDevice.h"

class AudioInputStream : public AudioStream {
public:
    AudioInputStream(const AudioDevice &inputDevice, unsigned int sampleRate,
                     unsigned long framesPerBuffer);
};

#endif //BLINKYTUNE_AUDIOINPUTSTREAM_H
