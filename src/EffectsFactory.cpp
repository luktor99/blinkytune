//
// Created by luktor99 on 13.01.18.
//

#include "EffectsFactory.h"
#include "effects/StillColor.h"
#include "effects/ColorBeat.h"
#include "effects/Rainbow.h"

EffectsFactory::EffectsFactory() {
    // NoSound effects
    registerNoSoundEffect("Still Color", &StillColor::create);
    registerNoSoundEffect("Rainbow", &Rainbow::create);

    // Sound effects
    registerSoundEffect("Color Beat", &ColorBeat::create);
}

EffectsFactory &EffectsFactory::getInstance() {
    static EffectsFactory instance;
    return instance;
}

void EffectsFactory::registerEffect(const std::string &effectName, Effect *(*createFun)(void)) {
    effectsMap_[effectName] = createFun;
}

void EffectsFactory::registerSoundEffect(const std::string &effectName, Effect *(*createFun)(void)) {
    soundEffects_.push_back(effectName);
    registerEffect(effectName, createFun);
}

void EffectsFactory::registerNoSoundEffect(const std::string &effectName, Effect *(*createFun)(void)) {
    noSoundEffects_.push_back(effectName);
    registerEffect(effectName, createFun);
}

Effect *EffectsFactory::createEffect(const std::string &effectName) {
    auto it = effectsMap_.find(effectName);
    if (it != effectsMap_.end())
        return it->second();

    return nullptr;
}

const std::vector<std::string> &EffectsFactory::getSoundEffects() const {
    return soundEffects_;
}

const std::vector<std::string> &EffectsFactory::getNoSoundEffects() const {
    return noSoundEffects_;
}


