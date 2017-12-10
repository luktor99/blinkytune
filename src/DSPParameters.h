//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_DSPPARAMETERS_H
#define BLINKYTUNE_DSPPARAMETERS_H

#include <cstddef>

const unsigned int SAMPLE_RATE = 48000; // The audio sampling rate
const std::size_t FRAMES_PER_BUFFER = 256; // The number of samples collected at once from the audio device (FFT length)
const std::size_t SPECTRUM_LENGTH = FRAMES_PER_BUFFER / 2 + 1; // The number of samples in the generated spectrum
const std::size_t SPECTRUM_BARS = 8; // The number of generated spectrum bars
const std::size_t FIFO_SIZE = 20; // The length of FIFO queues connecting the DSP workers

#endif //BLINKYTUNE_DSPPARAMETERS_H
