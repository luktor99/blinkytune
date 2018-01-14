//
// Created by luktor99 on 10.12.17.
//

#ifndef BLINKYTUNE_SETTINGS_H
#define BLINKYTUNE_SETTINGS_H


#include <cstddef>
#include <chrono>

/**
 * The audio sampling rate.
 */
const unsigned int SAMPLE_RATE = 48000;
/**
 * The tick generator's rate.
 */
const unsigned int TICK_RATE = 1000;
/**
 * The default frames per second setting for the LED strip.
 */
const float DEFAULT_FPS = 30.0f;
/**
 * The number of samples collected at once from the audio device (FFT length).
 */
const std::size_t FRAMES_PER_BUFFER = 1024;
/**
 * The number of samples in the generated spectrum.
 */
const std::size_t SPECTRUM_LENGTH = FRAMES_PER_BUFFER / 2 + 1;
/**
 * The number of generated spectrum bars (should be a multiple of 3).
 */
const std::size_t SPECTRUM_BARS = 21;
/**
 * The length of FIFO queues connecting the DSP workers.
 */
const std::size_t FIFO_SIZE = 20;
/**
 * The number of samples stored for averaging (1 sec).
 */
const unsigned long N_HISTORY = SAMPLE_RATE / FRAMES_PER_BUFFER;
/**
 * The beat detection factor (threshold: BEAT_DETECT_FACTOR*avg).
 */
const float BEAT_DETECT_FACTOR = 1.5;
/**
 * The minimal analyzed frequency (in Hz).
 */
const float CUTOFF_FREQ_LOW = 100;
/**
 * The maximal analyzed frequency (in Hz).
 */
const float CUTOFF_FREQ_HIGH = 12000;
/**
 * The timeout of the FIFO I/O methods.
 */
const auto FIFO_TIMEOUT = std::chrono::milliseconds(100);


#endif //BLINKYTUNE_SETTINGS_H
