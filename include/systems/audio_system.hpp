#ifndef SYSTEMS_AUDIO_SYSTEM_H_
#define SYSTEMS_AUDIO_SYSTEM_H_

#include <cstdlib>

#include <SFML/Audio.hpp>
#include <thread>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "systems/system.hpp"

namespace taeto
{

class AudioSystem: public System
{
public:
    AudioSystem();

    AudioSystem(std::shared_ptr<spdlog::logger>);

    ~AudioSystem();

    void play();

private:
    // Engine-wide logger
    std::shared_ptr<spdlog::logger> logger;

    std::shared_ptr<sf::Music> music_ptr;
};

}   // namespace taeto

#endif  // SYSTEMS_AUDIO_SYSTEM_H_
