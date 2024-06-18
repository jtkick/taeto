#include "assets/sprites/roflcopter.hpp"

#include <glm/glm.hpp>

#include "components/render_pixel.hpp"

namespace taeto
{

Roflcopter::Roflcopter(glm::uvec2 s, taeto::RenderPixel p)
{
    std::vector<std::string> string_vector = {
        R"(ROFL:ROFL:LOL:FORL:ROFL )",
        R"(           ^            )",
        R"(  L   /-------------    )",
        R"( LOL===           []\   )",
        R"(  L     \            \  )",
        R"(         \___________ ] )",
        R"(           I        I   )"
    };


    shape_ = s;
    pixel_ = p;
}

taeto::RenderPixel Roflcopter::get_pixel_at(glm::uvec2 pos)
{
    return pixel_;
}

}   // namespace taeto
