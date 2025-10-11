#include "taeto/objects/sprites/roflcopter.hpp"

#include <vector>

#include <glm/glm.hpp>

#include "taeto/components/render_pixel.hpp"

namespace taeto
{

Roflcopter::Roflcopter(glm::uvec2 s, taeto::RenderPixel p)
{
    std::vector<std::string> string_vector = {
        R"(ROFL:ROFL:LOL:ROFL:ROFL)",
        R"(           ^           )",
        R"(  L   /--------        )",
        R"( LOL===      []\       )",
        R"(  L     \       \      )",
        R"(         \_______]     )",
        R"(           I   I       )",
        R"(         ----------/   )"
    };


    shape_ = s;
    pixel_ = p;
}

taeto::RenderPixel Roflcopter::pixel_at(glm::uvec2& pos)
{
    return pixel_;
}

}   // namespace taeto
