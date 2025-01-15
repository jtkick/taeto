#include "taeto/objects/sprites/roflcopter.hpp"

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

taeto::RenderPixel Roflcopter::get_pixel_at(glm::uvec2 pos)
{
    return pixel_;
}

}   // namespace taeto
