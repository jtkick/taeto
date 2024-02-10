#include "object/sprite.hpp"

#include "components/render_pixel.hpp"
#include "object/object.hpp"
#include "tools.hpp"

#include <chrono>
#include <memory>
#include <stdexcept>

namespace taeto
{

const taeto::RenderPixel& Sprite::get_pixel_at(glm::uvec2)
{
    throw std::runtime_error("'get_pixel_at()' not defined for this sprite.");
}

uint Sprite::height()
{
    return shape_.y;
}

void Sprite::visible(const bool& v)
{
    visible_ = v;
}

bool Sprite::visible()
{
    return visible_;
}

uint Sprite::width()
{
    return shape_.x;
}

bool Sprite::collides()
{
    return false;
}

bool Sprite::detect_collisions()
{
    return detect_collisions_;
}

bool Sprite::get_collision_at(glm::uvec2)
{
    return false;
}

bool Sprite::on_collision(std::shared_ptr<taeto::Sprite>)
{
    return false;
}

int Sprite::frame_timer(int frame_rate, bool refresh)
{
    // Get number of milliseconds per frame
    int frame_time = 1000 / frame_rate;

    // Get difference in time between now and last time timer was called
    std::chrono::milliseconds time_diff = ms_since_epoch() - prev_timer_time_;

    // Get number of frames that have passed
    int num_frames = time_diff.count() / frame_time;

    // Update timer for these new frames
    if (refresh)
        prev_timer_time_ += std::chrono::milliseconds(frame_time * num_frames);

    // Return number of frames that have passed
    return num_frames;
}

void Sprite::mass(double mass)
{
    mass_ = mass;
}

double Sprite::mass()
{
    return mass_;
}

void Sprite::speed(const glm::vec3& speed)
{
    speed_ = speed;
}

glm::vec3& Sprite::speed()
{
    return speed_;
}

void Sprite::force(const glm::vec3& force)
{
    force_ = force;
}

glm::vec3& Sprite::force()
{
    return force_;
}

void Sprite::animate()
{

}

bool Sprite::respect_light_sources()
{
    return false;
}

}   // namespace taeto
