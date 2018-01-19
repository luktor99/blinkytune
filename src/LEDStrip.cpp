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
    try {
        udpSender_.send(outputBuffer_);
    }
    catch (...) {
        // LED strip connection broke
        // throw DisconnectedException(); can't be used in every occasion
    }
}

void LEDStrip::setRGB(int n, float r, float g, float b) {
    clamp(r);
    clamp(g);
    clamp(b);
    bufferFloat_[n * 3] = r;
    bufferFloat_[n * 3 + 1] = g;
    bufferFloat_[n * 3 + 2] = b;
}

void LEDStrip::setHSV(int n, float h, float s, float v) {
    // Make sure values are in the correct ranges
    if (s < 0.0f)
        s = 0.0f;
    else if (s > 1.0f)
        s = 1.0f;
    if (v < 0.0f)
        v = 0.0f;
    else if (v > 1.0f)
        v = 1.0f;
    h = std::fmod(h, 360.0f);

    if (v == 0.0f)
        setRGB(n, 0.0f, 0.0f, 0.0f);
    else {
        h /= 60.0f;
        int sector = static_cast<int>(h);
        float f = h - static_cast<float>(sector);
        float p = v * (1 - s);
        float q = v * (1 - (s * f));
        float t = v * (1 - (s * (1 - f)));

        if (sector == 0)
            setRGB(n, v * 255.0f, t * 255.0f, p * 255.0f);
        else if (sector == 1)
            setRGB(n, q * 255.0f, v * 255.0f, p * 255.0f);
        else if (sector == 2)
            setRGB(n, p * 255.0f, v * 255.0f, t * 255.0f);
        else if (sector == 3)
            setRGB(n, p * 255.0f, q * 255.0f, v * 255.0f);
        else if (sector == 4)
            setRGB(n, t * 255.0f, p * 255.0f, v * 255.0f);
        else if (sector == 5)
            setRGB(n, v * 255.0f, p * 255.0f, q * 255.0f);
    }

//    float red, grn, blu;
//    float i, f, p, q, t;
//
//    if(v==0) {
//        red = 0;
//        grn = 0;
//        blu = 0;
//    } else {
//        h/=60;
//        i = floor(h);
//        f = h-i;
//        p = v*(1-s);
//        q = v*(1-(s*f));
//        t = v*(1-(s*(1-f)));
//        if (i==0) {red=v; grn=t; blu=p;}
//        else if (i==1) {red=q; grn=v; blu=p;}
//        else if (i==2) {red=p; grn=v; blu=t;}
//        else if (i==3) {red=p; grn=q; blu=v;}
//        else if (i==4) {red=t; grn=p; blu=v;}
//        else if (i==5) {red=v; grn=p; blu=q;}
//    }
//
//    setRGB(n, red*255.0f, grn*255.0f, blu*255.0f);
}

const int &LEDStrip::getLength() {
    return length_;
}

void LEDStrip::updateOutputBuffer() {
    for (int i = 0; i < length_ * 3; ++i)
        bufferInt_[i] = static_cast<uint8_t>(std::round(bufferFloat_[i]));

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

void LEDStrip::clear() {
    for (int i = 0; i < length_ * 3; ++i)
        bufferFloat_[i] = 0.0f;
}

