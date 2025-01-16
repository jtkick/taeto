#include <chrono>
#include <math.h>
#include <memory>

#include <glm/glm.hpp>

#include "taeto/engine.hpp"
#include "taeto/tools.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/objects/lights/directional_light.hpp"
#include "taeto/objects/lights/point_light.hpp"
#include "taeto/objects/sprites/circle.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/scenes/scene.hpp"

int const TWO_PI = 6.283;

class NormalMappingTest : public taeto::Scene
{
public:
    NormalMappingTest()
    {
        distance_ = 60;
        speed_ = 0.075;
        current_degree_ = 0.0;
        last_animate_ = taeto::ms_since_epoch();
        stopwatch_ = std::chrono::milliseconds(0);
        s_ = std::make_shared<taeto::Circle>(51, taeto::RenderPixel(' ', glm::vec4(), glm::vec4(1.0, 1.0, 1.0, 1.0), false),true);
        s_->position({-((double)s_->width()/2), -((double)s_->height()/2), -10});
        s_->respect_light_sources(true);
        pl_ = std::make_shared<taeto::PointLight>(glm::vec3(1.0, 1.0, 1.0), 0.9999);
        pl_->position({10, 0, 0});
        dl_ = std::make_shared<taeto::DirectionalLight>(glm::vec3(0.05, 0.05, 0.05), glm::vec3(0.0, 0.0, -1.0));
    };

    ~NormalMappingTest() { };

    void animate()
    {
        stopwatch_ += taeto::ms_since_epoch() - last_animate_;
        last_animate_ = taeto::ms_since_epoch();
        while (stopwatch_ > std::chrono::milliseconds(30))
        {
            stopwatch_ -= std::chrono::milliseconds(30);
            current_degree_ += speed_;
            if (current_degree_ > 1000.0)
                current_degree_ = 0.0;
        }

        // Move light in a circle about the box
        double x = distance_ * cos(current_degree_);
        double y = distance_ * sin(current_degree_);
        pl_->position({x, y, 50});
    };

    void load()
    {
        taeto::load_sprite(s_);
        taeto::load_light(pl_);
        taeto::load_light(dl_);
    };

private:
    int distance_ = 50;

    float speed_ = 5.0;

    float current_degree_ = 0.0;

    std::chrono::milliseconds last_animate_;
    std::chrono::milliseconds stopwatch_;

    // Assets
    std::shared_ptr<taeto::Circle> s_;
    std::shared_ptr<taeto::PointLight> pl_;
    std::shared_ptr<taeto::DirectionalLight> dl_;
};

int main()
{
    taeto::set_debug_mode(true);
    taeto::load_scene(std::make_shared<NormalMappingTest>());
    taeto::run();
}