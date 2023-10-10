#ifndef SYSTEMS_AUDIO_SYSTEM_H_
#define SYSTEMS_AUDIO_SYSTEM_H_

#include <cstdlib>

#include <SFML/Audio.hpp>
#include <thread>

#include "systems/system.hpp"

namespace taeto
{

class AudioSystem: public System
{
public:
    AudioSystem() { };

    ~AudioSystem() { };

    void play();

private:
    std::shared_ptr<sf::Music> music_ptr;
};

}   // namespace taeto

#endif  // SYSTEMS_AUDIO_SYSTEM_H_
