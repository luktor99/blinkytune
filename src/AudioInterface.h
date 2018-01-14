//
// Created by luktor99 on 29.11.17.
//

#ifndef BLINKYTUNE_AUDIOINTERFACE_H
#define BLINKYTUNE_AUDIOINTERFACE_H

#include "portaudio.h"
#include "AudioDevice.h"
#include <list>

/**
 * Represents the PortAudio interface. This class uses the singleton design pattern.
 */
class AudioInterface {
public:

    /**
    * Retrieve an instance of singleton class AudioInterface.
    * @return AudioInterface singleton object.
    */
    static AudioInterface &getInstance();

    /**
    * Initialize the PortAudio interface.
    */
    void initialize() const;

    /**
    * Terminate the PortAudio interface.
    */
    void terminate() const;

    /**
    * Retrieve a list of audio devices present in the system.
    * @return std::list of AudioDevice objects.
    */
    std::list<AudioDevice> getDevicesList() const;

    /**
    * Retrieve a list of audio devices present in the system.
    * @return std::list of AudioDevice objects.
    */
    std::list<AudioDevice> getInputDevicesList() const;

    /**
    * Retrieve the default audio input device.
    * @return AudioDevice object representing the default input device.
    */
    AudioDevice getDefaultInputDevice() const;

private:
    /**
    * The constructor.
    */
    AudioInterface() = default;

    /**
    * The destructor.
    */
    ~AudioInterface();

    AudioInterface(const AudioInterface &) = delete;

    AudioInterface &operator=(const AudioInterface &) = delete;
};

#endif //BLINKYTUNE_AUDIOINTERFACE_H
