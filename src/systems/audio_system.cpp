#include "audio_system.h"

namespace taeto
{

AudioSystem::AudioSystem()
{

}

AudioSystem::AudioSystem(std::shared_ptr<spdlog::logger> l)
{
    logger = l;
}

AudioSystem::~AudioSystem()
{

}

}   // namespace taeto
