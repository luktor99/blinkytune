//
// Created by luktor99 on 29.11.17.
//

#ifndef BLINKYTUNE_AUDIOINTERFACE_H
#define BLINKYTUNE_AUDIOINTERFACE_H

#include <portaudio.h>
#include "AudioDevice.h"
#include <list>

/**
 * Represents the PortAudio interface. This is a singleton class.
 */
class AudioInterface {
public:
    static AudioInterface &getInstance();

    void initialize() const;

    void terminate() const;

    std::list<AudioDevice> getDevicesList() const;

    std::list<AudioDevice> getInputDevicesList() const;

    AudioDevice getDefaultInputDevice() const;

private:
    AudioInterface() = default;

    ~AudioInterface();

    AudioInterface(const AudioInterface &) = delete;

    AudioInterface &operator=(const AudioInterface &) = delete;
};

#endif //BLINKYTUNE_AUDIOINTERFACE_H
