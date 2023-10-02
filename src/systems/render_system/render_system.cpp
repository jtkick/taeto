#include "systems/render_system/render_system.hpp"

#include "spdlog/spdlog.h"

namespace taeto
{

RenderSystem::RenderSystem()
{

}

RenderSystem::RenderSystem(std::shared_ptr<spdlog::logger> l)
{
    logger_ = l;

    render_distance_ = 1000000000;
}

RenderSystem::~RenderSystem()
{

}

}   // namespace taeto
