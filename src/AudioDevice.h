//
// Created by luktor99 on 02.12.17.
//

#ifndef BLINKYTUNE_AUDIODEVICE_H
#define BLINKYTUNE_AUDIODEVICE_H

#include "portaudio.h"

class AudioDevice {
public:
    /*
     * The constructor. Creates an AudioDevice object representing the default input device.
     */
    AudioDevice();

    /**
     * The constructor. Creates an AudioDevice object representing a device with the given index.
     * @param deviceIndex The index of the device.
     */
    AudioDevice(int deviceIndex);

    /**
     * Get the name of the audio device.
     * @return Audio device's name.
     */
    const char *getName() const;

    /**
     * Get the max number of input channels supported by the device.
     * @return Max number of input channels supported by the device.
     */
    int getInputChannels() const;

    /**
     * Get the index (ID) of the audio device.
     * @return Index (ID) of the audio device.
     */
    int getID() const;

private:
    PaDeviceIndex deviceIndex_; /*!< The index of the represented audio device. */
    PaDeviceInfo deviceInfo_; /*!< A structure containing information about the device. */

    friend class AudioStream;

    friend class AudioInputStream;
};


#endif //BLINKYTUNE_AUDIODEVICE_H
