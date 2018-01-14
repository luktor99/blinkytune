#include <iostream>
#include <QApplication>
#include <QSplashScreen>

#include "MainWindow.h"
//#include "CollapseWidget.h"


#include "AudioInterface.h"

#include "FIFOQueue.h"
#include "StereoSamplesBuffer.h"
#include "SamplesCollector.h"
#include "EffectsRenderer.h"
#include "EffectsController.h"
#include "EffectsFactory.h"


int main(int argc, char **argv) {
    // Supress warnings:
    (void) argc;
    (void) argv;
    // Initialize PortAudio
    AudioInterface::getInstance().initialize();

    // Display all input devices
    for (auto dev : AudioInterface::getInstance().getInputDevicesList())
        std::cout << "[" << dev.getID() << "] " << dev.getName() << std::endl;

    // Select the input device
    AudioDevice device = AudioInterface::getInstance().getDefaultInputDevice();
    std::cout << "Selected: [" << device.getID() << "] " << device.getName() << std::endl;

    // List the available effects
    std::cout << "Registered sound effects:" << std::endl;
    auto s = EffectsFactory::getInstance().getSoundEffects();
    std::for_each(s.cbegin(), s.cend(), [](const auto &name) { std::cout << "\t" << name << std::endl; });
    std::cout << "Registered no sound effects:" << std::endl;
    auto ns = EffectsFactory::getInstance().getNoSoundEffects();
    std::for_each(ns.cbegin(), ns.cend(), [](const auto &name) { std::cout << "\t" << name << std::endl; });

    // Start the effects controller
    auto &effectsController = EffectsController::getInstance();
    effectsController.connect("192.168.1.166", 60);
    effectsController.setAudioDevice(device);

    effectsController.setEffect("Color Beat");
//    effectsController.setEffect("Still Color");

    // Just a test for now...
    getchar();
    effectsController.getEffect()->readControls();

    // Wait for a key press...
    getchar();

    effectsController.stop();

    exit(EXIT_SUCCESS);
}