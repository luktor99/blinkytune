//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_EFFECTSFACTORY_H
#define BLINKYTUNE_EFFECTSFACTORY_H


#include "Effect.h"

/**
 * This class is a singleton factory of effects objects. It uses the factory design pattern.
 */
class EffectsFactory {
public:
    /**
     * Retrieve an instance of singleton class EffectsFactory.
     * @return EffectsFactory singleton object.
     */
    static EffectsFactory &getInstance();

    /**
     * Create a new instance of the effect of the given name.
     * @param effectName The name of the desired effect.
     * @return A pointer to the newly created instance of the Effect class.
     */
    Effect *createEffect(const std::string &effectName);

    /**
     * Get a vector containing names of available sound-reactive effects.
     * @return std::vector containing names (std::strings) of the effects.
     */
    const std::vector<std::string> &getSoundEffects() const;

    /**
     * Get a vector containing names of available not sound-reactive effects.
     * @return std::vector containing names (std::strings) of the effects.
     */
    const std::vector<std::string> &getNoSoundEffects() const;

private:
    /**
     * The constructor.
     */
    EffectsFactory();

    /**
     * The destructor.
     */
    ~EffectsFactory() = default;

    EffectsFactory(const EffectsFactory &) = delete;

    EffectsFactory &operator=(const EffectsFactory &) = delete;

    /**
     * Register an effect in the factory.
     * @param effectName The name of the effect to be registered.
     * @param createFun A pointer to the create member function of the effect.
     */
    void registerEffect(const std::string &effectName, Effect *(*createFun)(void));

    /**
     * Register a sound-reactive effect in the factory.
     * @param effectName The name of the effect to be registered.
     * @param createFun A pointer to the create member function of the effect.
     */
    void registerSoundEffect(const std::string &effectName, Effect *(*createFun)(void));

    /**
     * Register a not sound-reactive effect in the factory.
     * @param effectName The name of the effect to be registered.
     * @param createFun A pointer to the create member function of the effect.
     */
    void registerNoSoundEffect(const std::string &effectName, Effect *(*createFun)(void));

    std::map<const std::string, Effect *(*)(void)> effectsMap_; /*!< A map storing the registered effects */
    std::vector<std::string> soundEffects_, noSoundEffects_; /*!< Vectors storing the names of effects of each type */
};


#endif //BLINKYTUNE_EFFECTSFACTORY_H
