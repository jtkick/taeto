#include <memory>

#include <glm/glm.hpp>

#include "taeto/objects/lights/spotlight.hpp"
#include "taeto/objects/sprites/rectangle.hpp"
#include "taeto/engine.hpp"
#include "taeto/components/render_pixel.hpp"

int main()
{
    taeto::debug_mode(true);

    // Load backdrop
    std::shared_ptr<taeto::Rectangle> backdrop = 
        std::make_shared<taeto::Rectangle>(
            glm::uvec2(200, 64),
            taeto::RenderPixel(' ', glm::vec4(),
                glm::vec4(1.0, 1.0, 1.0, 1.0), false));
    backdrop->position({-100, -32, -25});
    backdrop->respect_light_sources(true);
    taeto::load_object(backdrop);
    
    // Load spotlights
    std::shared_ptr<taeto::Spotlight> red_light = 
        std::make_shared<taeto::Spotlight>(glm::dvec3(1.0, 0.0, 0.0), 0.8, 30);
    red_light->position({0, -7, 0});
    taeto::load_object(red_light);
    std::shared_ptr<taeto::Spotlight> green_light = 
        std::make_shared<taeto::Spotlight>(glm::dvec3(0.0, 1.0, 0.0), 0.8, 30);
    green_light->position({-21, 5, 0});
    taeto::load_object(green_light);
    std::shared_ptr<taeto::Spotlight> blue_light = 
        std::make_shared<taeto::Spotlight>(glm::dvec3(0.0, 0.0, 1.0), 0.8, 30);
    blue_light->position({21, 5, 0});
    taeto::load_object(blue_light);
    taeto::run();
}