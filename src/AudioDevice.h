//
// Created by luktor99 on 02.12.17.
//

#ifndef BLINKYTUNE_AUDIODEVICE_H
#define BLINKYTUNE_AUDIODEVICE_H

#include "portaudio.h"

class AudioDevice {
public:
    AudioDevice(PaDeviceIndex deviceIndex);

    AudioDevice();

    const char *getName() const;

    int getInputChannels() const;

    int getID() const;

private:
    PaDeviceIndex deviceIndex_;
    PaDeviceInfo deviceInfo_;

    friend class AudioStream;

    friend class AudioInputStream;
};


#endif //BLINKYTUNE_AUDIODEVICE_H
