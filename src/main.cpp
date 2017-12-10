#include <iostream>

#include "AudioInterface.h"
#include "AudioInputStream.h"
#include "FIFOQueue.h"
#include "StereoSamplesBuffer.h"
#include "StereoSpectrumBuffer.h"
#include "DSPParameters.h"
#include "SamplesCollector.h"
#include "SpectrumGenerator.h"
#include "SpectrumAnalyzer.h"

int main(int argc, char **argv) {
    // Initialize PortAudio
    AudioInterface::getInstance().initialize();

    // Display all input devices
    for (auto dev : AudioInterface::getInstance().getInputDevicesList())
        std::cout << "[" << dev.getID() << "] " << dev.getName() << std::endl;

    // Select the input device
    AudioDevice device = AudioInterface::getInstance().getDefaultInputDevice();
    std::cout << "Selected: [" << device.getID() << "] " << device.getName() << std::endl;

    // Create an input stream
    AudioInputStream stream(device, SAMPLE_RATE, FRAMES_PER_BUFFER);

    // Allocate a FIFO queue for samples
    FIFOQueue<StereoSamplesBuffer> samplesFIFO(FIFO_SIZE);
    FIFOQueue<StereoSpectrumBuffer> spectrumFIFO(FIFO_SIZE);
    FIFOQueue<StereoAnalysisBuffer> analysisFIFO(FIFO_SIZE);

    SamplesCollector samplesCollector(stream, samplesFIFO);
    SpectrumGenerator spectrumGenerator(samplesFIFO, spectrumFIFO);
    SpectrumAnalyzer spectrumAnalyzer(spectrumFIFO, analysisFIFO);

    samplesCollector.run();
    spectrumGenerator.run();
    spectrumAnalyzer.run();

    // Keep collecting new samples
    getchar();

    samplesCollector.stop();
    spectrumGenerator.stop();
    spectrumAnalyzer.stop();

    samplesCollector.join();
    spectrumGenerator.join();
    spectrumAnalyzer.join();

    exit(EXIT_SUCCESS);
}