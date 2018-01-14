//
// Created by luktor99 on 01.01.18.
//

#ifndef BLINKYTUNE_LEDSTRIP_H
#define BLINKYTUNE_LEDSTRIP_H

#include "UDPSender.h"

/**
 * Represents the LED strip as a buffered network device communicating through UDP. The color data is buffered in a
 * floating point buffer, which provides smooth transitions between colors.
 */
class LEDStrip {
public:

    /**
     * The constructor.
     * @param ip The IP address of the LED strip device.
     * @param length The number of LEDs in the strip.
     */
    LEDStrip(const std::string &ip, int length);

    /**
     * Retrieve the number of LEDs in the strip.
     * @return Number of LEDs in the strip.
     */
    const int &getLength();

    /**
     * Send the output buffer to the LED strip (refresh it).
     */
    void update();

    /**
     * Set single pixel's color in the output buffer.
     * @param n The index of the pixel.
     * @param r Red color component (0..255 range)
     * @param g Green color component (0..255 range)
     * @param b Blue color component (0..255 range)
     */
    void setRGB(int n, float r, float g, float b);

    /**
     * Clamp the value if it exceeds the 0..255 range.
     * @param value The variable to be processed.
     */
    static void clamp(float &value);

    /**
     * Multiply all color components of all pixels by a given factor.
     * @param value The multiplier.
     */
    void fade(float &value);

    /**
     * Set all pixels in the output buffer to black color.
     */
    void clear();

private:
    /**
     * Update the integer output buffer using values from the floating point output buffer.
     */
    void updateOutputBuffer();

    UDPSender udpSender_; /*!< An instance of UDPSender class that manages the UDP connection. */
    const int length_; /*!< The number of LEDs in the strip. */
    std::unique_ptr<float[]> bufferFloat_; /*!< An unique_ptr to the floating point output buffer. */
    std::unique_ptr<uint8_t[]> bufferInt_; /*!< An unique_ptr to the integer output buffer. */
    boost::asio::mutable_buffer outputBuffer_; /*!< Raw buffer that is passed directly to the LED strip. */
};

#endif //BLINKYTUNE_LEDSTRIP_H
