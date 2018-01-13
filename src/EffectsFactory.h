//
// Created by luktor99 on 13.01.18.
//

#ifndef BLINKYTUNE_EFFECTSFACTORY_H
#define BLINKYTUNE_EFFECTSFACTORY_H


#include "Effect.h"

class EffectsFactory {
public:
    static EffectsFactory &getInstance();

    Effect *createEffect(const std::string &effectName);

    const std::vector<std::string> &getSoundEffects() const;

    const std::vector<std::string> &getNoSoundEffects() const;

private:
    EffectsFactory();

    ~EffectsFactory() = default;

    EffectsFactory(const EffectsFactory &) = delete;

    EffectsFactory &operator=(const EffectsFactory &) = delete;

    void registerEffect(const std::string &effectName, Effect *(*createFun)(void));

    void registerSoundEffect(const std::string &effectName, Effect *(*createFun)(void));

    void registerNoSoundEffect(const std::string &effectName, Effect *(*createFun)(void));

    std::map<const std::string, Effect *(*)(void)> effectsMap_;

    std::vector<std::string> soundEffects_, noSoundEffects_;
};


#endif //BLINKYTUNE_EFFECTSFACTORY_H
