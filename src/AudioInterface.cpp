//
// Created by luktor99 on 29.11.17.
//

#include <stdexcept>
#include "AudioInterface.h"

AudioInterface &AudioInterface::getInstance() {
    static AudioInterface instance;
    return instance;
}

std::list<AudioDevice> AudioInterface::getDevicesList() const {
    std::list<AudioDevice> devices;

    for (int i = 0; i < Pa_GetDeviceCount(); ++i)
        devices.push_back(AudioDevice(i));

    return devices;
}

std::list<AudioDevice> AudioInterface::getInputDevicesList() const {
    std::list<AudioDevice> devices;

    for (int i = 0; i < Pa_GetDeviceCount(); ++i)
        if (Pa_GetDeviceInfo(i)->maxInputChannels > 0)
            devices.push_back(AudioDevice(i));

    return devices;
}

AudioDevice AudioInterface::getDefaultInputDevice() const {
    return AudioDevice();
}

void AudioInterface::initialize() const {
    if (Pa_Initialize() != paNoError)
        throw std::runtime_error("Audio interface could not be initialized.");
}

void AudioInterface::terminate() const {
    if (Pa_Terminate() != paNoError)
        throw std::runtime_error("Could not terminate the PortAudio interface.");
}

AudioInterface::~AudioInterface() {
    // Terminate the PortAudio interface
    terminate();
}