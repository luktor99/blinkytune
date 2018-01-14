//
// Created by luktor99 on 02.12.17.
//

#include "AudioDevice.h"
#include <stdexcept>

AudioDevice::AudioDevice(PaDeviceIndex deviceIndex) : deviceIndex_(deviceIndex) {
    if (deviceIndex_ == paNoDevice)
        throw std::out_of_range("Audio device not found.");

    deviceInfo_ = *Pa_GetDeviceInfo(deviceIndex_);
}

AudioDevice::AudioDevice() {
   deviceIndex_ = static_cast<PaDeviceIndex>(Pa_GetDefaultInputDevice());

   if (deviceIndex_ == paNoDevice)
	   throw std::out_of_range("Audio device not found.");

   deviceInfo_ = *Pa_GetDeviceInfo(deviceIndex_);
}

const char *AudioDevice::getName() const {
    return deviceInfo_.name;
}

int AudioDevice::getInputChannels() const{
	return deviceInfo_.maxInputChannels;
};

int AudioDevice::getID() const {
    return deviceIndex_;
}
