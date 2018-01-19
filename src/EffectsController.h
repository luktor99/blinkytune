//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_EFFECTSCONTROLLER_H
#define BLINKYTUNE_EFFECTSCONTROLLER_H


#include "Effect.h"
#include "AudioDevice.h"
#include "EffectsRenderer.h"
#include "SpectrumGenerator.h"
#include "SamplesCollector.h"
#include "SpectrumAnalyzer.h"
#include "TickGenerator.h"

/**
 * Represents a facade for the whole audio processing and effect generation system. This is the main component of the
 * program that controls the whole life cycle of all processing threads and keeps the connection to the LED strip. This
 * class uses the singleton and facade design patterns.
 */
class EffectsController {
public:
    /**
    * Retrieve a instance of singleton class EffectsController.
    * @return EffectsController instance.
    */
    static EffectsController &getInstance();

    /**
     * Establish connection with the LED strip.
     * @param ip The IP of the LED strip.
     * @param length The number of LEDs in the strip.
     */
    void connect(const std::string &ip, int length);

    /**
     * Retrieve the object of currently running effect.
     * @return A pointer to the currently active Effect object.
     */
    Effect *getEffect() const;

    /**
     * Set the input audio device.
     * @param device A reference the the desired AudioDevice object.
     */
    void setAudioDevice(const AudioDevice &device);

    /**
     * Set the desired update rate of the LED strip (in frames per seconds).
     * @param fps The number of frames per seconds.
     */
    void setFPS(const float &fps);

    /**
     * Set the active light effect.
     * @param effectName The name of the effect.
     */
    void setEffect(const std::string &effectName);

    /**
     * Stop the effects controler. This function stops all processing threads and disconnects from the LED strip.
     */
    void stop();

    /**
     * Stops the effects controller and disconnects from the LED strip.
     */
    void disconnect();

	/**
	* Check if LED strip is connected.
	* @return True if LED strip connected, otherwise false.
	*/
	bool isConnected() const;

private:
    /**
     * The constructor.
     */
    EffectsController();

    /**
     * The destructor.
     */
    ~EffectsController() = default;

    EffectsController(const EffectsController &) = delete;

    EffectsController &operator=(const EffectsController &) = delete;

    /**
     * Start the processing threads required to render sound effects.
     */
    void startSoundPipeline();

    /**
     * Start the processing threads required to render no sound effects.
     */
    void startNoSoundPipeline();

    /**
    * Stop the processing threads required to render sound effects.
    */
    void stopSoundPipeline();

    /**
    * Stop the processing threads required to render no sound effects.
    */
    void stopNoSoundPipeline();

    /**
     * Set the active effect.
     * @param effect A pointer to the Effect object.
     */
    void setActiveEffect(Effect *effect);

    /**
     * The possible effect processing modes.
     */
    enum activePipelineType {
        PIPELINE_NONE = 0,  /*!< No processing threads are active. */
        PIPELINE_SOUND,     /*!< Processing threads required to render sound effects are active. */
        PIPELINE_NOSOUND    /*!< Processing threads required to render no sound effects are active. */
    };

    activePipelineType activePipeline; /*!< The current effect processing mode. */
    std::unique_ptr<LEDStrip> ledStrip_; /*!< A unique_ptr to the active LEDStrip object. */
    std::unique_ptr<EffectsRenderer> effectsRenderer_; /*!< A unique_ptr to the EffectsRenderer thread. */
    std::unique_ptr<Effect> effect_; /*!< A unique_ptr to the active Effect object. */
    std::unique_ptr<SamplesCollector> samplesCollector_; /*!< A unique_ptr to the SamplesCollector thread. */
    std::unique_ptr<SpectrumGenerator> spectrumGenerator_; /*!< A unique_ptr to the SpectrumGenerator thread. */
    std::unique_ptr<SpectrumAnalyzer> spectrumAnalyzer_; /*!< A unique_ptr to the SpectrumAnalyzer thread. */
    std::unique_ptr<TickGenerator> tickGenerator_; /*!< A unique_ptr to the TickGenerator thread. */
    AudioDevice audioDevice_; /*!< The currently selected AudioDevice object. */
    std::unique_ptr<AudioInputStream> audioStream_; /*!< A unique_ptr to the active AudioInputStream object. */
    FIFOQueue<StereoSamplesBuffer> samplesFIFO_; /*!< A FIFO queue used to pass samples data between threads. */
    FIFOQueue<StereoSpectrumBuffer> spectrumFIFO_; /*!< A FIFO queue used to pass spectrum data between threads. */
    FIFOQueue<StereoAnalysisBuffer> analysisFIFO_; /*!< A FIFO queue used to pass analysis data between threads. */
    float refreshRate_; /*!< The currently selected update rate of the LED strip */
};


#endif //BLINKYTUNE_EFFECTSCONTROLLER_H
