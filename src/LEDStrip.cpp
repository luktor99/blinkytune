//
// Created by luktor99 on 01.01.18.
//

#include "LEDStrip.h"

namespace {
    const std::string &PORT = "4200";
}

LEDStrip::LEDStrip(const std::string &ip, int length) try : udpSender_(ip, PORT),
                                                            length_(length),
                                                            bufferFloat_(new float[length * 3]),
                                                            bufferInt_(new uint8_t[length * 3]),
                                                            outputBuffer_(bufferInt_.get(), length * 3) {

}
catch (...) {
    throw;
}

void LEDStrip::update() {
    updateOutputBuffer();
    udpSender_.send(outputBuffer_);
}

void LEDStrip::setR(int n, float r) {
    bufferFloat_[n * 3] = r;
}

void LEDStrip::setG(int n, float g) {
    bufferFloat_[n * 3 + 1] = g;
}

void LEDStrip::setB(int n, float b) {
    bufferFloat_[n * 3 + 2] = b;
}

void LEDStrip::setRGB(int n, float r, float g, float b) {
    bufferFloat_[n * 3] = r;
    bufferFloat_[n * 3 + 1] = g;
    bufferFloat_[n * 3 + 2] = b;
}

const int &LEDStrip::getLength() {
    return length_;
}

void LEDStrip::updateOutputBuffer() {
    for (int i = 0; i < length_ * 3; ++i)
        bufferInt_[i] = std::round(bufferFloat_[i]);

}

void LEDStrip::clamp(float &value) {
    if (value >= 255.0f)
        value = 255.0f;
    else if (value <= 0.0f)
        value = 0.0f;
}

void LEDStrip::fade(float &value) {
    for (int i = 0; i < length_ * 3; ++i)
        bufferFloat_[i] *= value;
}

