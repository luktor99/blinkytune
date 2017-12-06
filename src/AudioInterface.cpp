//
// Created by luktor99 on 29.11.17.
//

#include <stdexcept>
#include "AudioInterface.h"

/**
 * Retrieve a instance of singleton class AudioInterface.
 * @return AudioInterface singleton object.
 */
AudioInterface &AudioInterface::getInstance() {
    static AudioInterface instance;
    return instance;
}

/**
 * Retrieve a list of audio devices present in the system.
 * @return std::list of AudioDevice objects.
 */
std::list<AudioDevice> AudioInterface::getDevicesList() const {
    std::list<AudioDevice> devices;

    for (int i = 0; i < Pa_GetDeviceCount(); ++i)
        devices.push_back(AudioDevice(i));

    return devices;
}

/**
 * Retrieve a list of audio devices present in the system.
 * @return std::list of AudioDevice objects.
 */
std::list<AudioDevice> AudioInterface::getInputDevicesList() const {
    std::list<AudioDevice> devices;

    for (int i = 0; i < Pa_GetDeviceCount(); ++i)
        if (Pa_GetDeviceInfo(i)->maxInputChannels > 0)
            devices.push_back(AudioDevice(i));

    return devices;
}

/**
 * Retrieve the default audio input device.
 * @return AudioDevice object representing the default input device.
 */
AudioDevice AudioInterface::getDefaultInputDevice() const {
    return AudioDevice();
}

/**
 * Initialize the PortAudio interface.
 */
void AudioInterface::initialize() const {
    if (Pa_Initialize() != paNoError)
        throw std::runtime_error("Audio interface could not be initialized.");
}

/**
 * Terminate the PortAudio interface.
 */
void AudioInterface::terminate() const {
    if (Pa_Terminate() != paNoError)
        throw std::runtime_error("Could not terminate the PortAudio interface.");
}

/**
 * Destructor of AudioInterface class.
 */
AudioInterface::~AudioInterface() {
    // Terminate the PortAudio interface
    terminate();
}
