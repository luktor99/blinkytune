//
// Created by luktor99 on 01.01.18.
//

#ifndef BLINKYTUNE_LEDSTRIP_H
#define BLINKYTUNE_LEDSTRIP_H

#include "UDPSender.h"

class LEDStrip {
public:

    LEDStrip(const std::string &ip, int length);

    const int &getLength();

    void update();

    void setR(int n, float r);

    void setG(int n, float g);

    void setB(int n, float b);

    void setRGB(int n, float r, float g, float b);

    static void clamp(float &value);

    void fade(float &value);

    void clear();

private:
    void updateOutputBuffer();

    UDPSender udpSender_;
    const int length_;
    std::unique_ptr<float[]> bufferFloat_;
    std::unique_ptr<uint8_t[]> bufferInt_;
    boost::asio::mutable_buffer outputBuffer_;
};


#endif //BLINKYTUNE_LEDSTRIP_H
