#include "systems/render_system.hpp"

#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "components/frame.h"
#include "components/position.hpp"

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
