//
// Created by luktor99 on 13.01.18.
//

#include "EffectsController.h"
#include "NoSoundEffect.h"
#include "EffectsFactory.h"

EffectsController &EffectsController::getInstance() {
    static EffectsController instance;
    return instance;
}

EffectsController::EffectsController() : activePipeline(PIPELINE_NONE), samplesFIFO_(FIFO_SIZE),
                                         spectrumFIFO_(FIFO_SIZE), analysisFIFO_(FIFO_SIZE),
                                         refreshRate_(1.0f / DEFAULT_FPS) {

}

void EffectsController::connect(const std::string &ip, int length) {
    LEDStrip *ledStrip = nullptr;
    try {
        ledStrip = new LEDStrip(ip, length);

        ledStrip_.reset(ledStrip);
    }
    catch (...) {
        throw;
    }
}

void EffectsController::setActiveEffect(Effect *effect) {
    // Check the effect type
    bool isSoundEffect = (dynamic_cast<NoSoundEffect *>(effect) == nullptr);

    // Start the required sound processing pipeline
    if (activePipeline == PIPELINE_NONE) {
        if (isSoundEffect)
            startSoundPipeline();
        else
            startNoSoundPipeline();
    } else if (activePipeline == PIPELINE_NOSOUND) {
        if (isSoundEffect) {
            stopNoSoundPipeline();
            startSoundPipeline();
        }
    } else if (activePipeline == PIPELINE_SOUND) {
        if (!isSoundEffect) {
            stopSoundPipeline();
            startNoSoundPipeline();
        }
    }

    // Store the new effect
    effect_.reset(effect);

    // Update/set the effect
    if (isSoundEffect)
        effectsRenderer_->setEffectSound(effect_.get());
    else
        effectsRenderer_->setEffectNoSound(effect_.get());
}

Effect *EffectsController::getEffect() const {
    return effect_.get();
}

void EffectsController::setAudioDevice(const AudioDevice &device) {
    audioDevice_ = device;

    // Stop SamplesCollector if it's already running
    if (activePipeline == PIPELINE_SOUND) {
        samplesCollector_->stop();
        samplesCollector_->join();
    }

    // Open the new audio stream
	try {
		audioStream_.reset(new AudioInputStream(audioDevice_, SAMPLE_RATE, FRAMES_PER_BUFFER));
	}
	catch(const std::runtime_error& error){
		throw error;
	}
	catch(...){
		throw;
	}

    // Restart SamplesCollector if it's already running (using the new audio device)
    if (activePipeline == PIPELINE_SOUND) {
        samplesCollector_.reset(new SamplesCollector(*audioStream_, samplesFIFO_));
        samplesCollector_->run();
    }
}

void EffectsController::startSoundPipeline() {
    samplesCollector_.reset(new SamplesCollector(*audioStream_, samplesFIFO_));
    spectrumGenerator_.reset(new SpectrumGenerator(samplesFIFO_, spectrumFIFO_));
    spectrumAnalyzer_.reset(new SpectrumAnalyzer(spectrumFIFO_, analysisFIFO_));
    effectsRenderer_.reset(new EffectsRenderer(analysisFIFO_, *ledStrip_));

    effectsRenderer_->setRefreshRate(refreshRate_);

    samplesCollector_->run();
    spectrumGenerator_->run();
    spectrumAnalyzer_->run();
    effectsRenderer_->run();

    // Update the active pipeline type
    activePipeline = PIPELINE_SOUND;
}

void EffectsController::startNoSoundPipeline() {
    tickGenerator_.reset(new TickGenerator(analysisFIFO_));
    effectsRenderer_.reset(new EffectsRenderer(analysisFIFO_, *ledStrip_));

    effectsRenderer_->setRefreshRate(refreshRate_);

    tickGenerator_->run();
    effectsRenderer_->run();

    // Update the active pipeline type
    activePipeline = PIPELINE_NOSOUND;
}

void EffectsController::stopSoundPipeline() {
    samplesCollector_->stop();
    spectrumGenerator_->stop();
    spectrumAnalyzer_->stop();
    effectsRenderer_->stop();

    samplesCollector_->join();
    spectrumGenerator_->join();
    spectrumAnalyzer_->join();
    effectsRenderer_->join();

    samplesCollector_.reset();
    spectrumGenerator_.reset();
    spectrumAnalyzer_.reset();
    effectsRenderer_.reset();

    // Update the active pipeline type
    activePipeline = PIPELINE_NONE;
}

void EffectsController::stopNoSoundPipeline() {
    tickGenerator_->stop();
    effectsRenderer_->stop();

    tickGenerator_->join();
    effectsRenderer_->join();

    tickGenerator_.reset();
    effectsRenderer_.reset();

    // Update the active pipeline type
    activePipeline = PIPELINE_NONE;
}

void EffectsController::stop() {
    // Stop the active pipeline (if any is active)
    if (activePipeline == PIPELINE_NOSOUND)
        stopNoSoundPipeline();
    else if (activePipeline == PIPELINE_SOUND)
        stopSoundPipeline();

    // Clear the LED strip
		ledStrip_->clear();
		ledStrip_->update();
		ledStrip_.reset();
}

void EffectsController::setFPS(const float &fps) {
    refreshRate_ = 1.0f / fps;

    if (activePipeline != PIPELINE_NONE)
        effectsRenderer_->setRefreshRate(refreshRate_);
}

void EffectsController::setEffect(const std::string &effectName) {
    auto newEffect = EffectsFactory::getInstance().createEffect(effectName);
    setActiveEffect(newEffect);
}

bool EffectsController::isConnected() const {
	// Check if LED strip is connected
	return ledStrip_ == nullptr;
}