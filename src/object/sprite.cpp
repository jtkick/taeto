#include "object/sprite.hpp"

#include "components/render_pixel.hpp"
#include "object/object.hpp"

#include <chrono>
#include <memory>

namespace taeto
{

// Bro, just give me time since epoch
std::chrono::milliseconds ms_since_epoch()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
}

const taeto::RenderPixel& Sprite::get_pixel_at(uint64_t, uint64_t)
{
    return taeto::RenderPixel();
}

uint64_t Sprite::height()
{
    return height_;
}

char Sprite::plane_orientation()
{
    return 'Z';
}

void Sprite::visible(const bool& v)
{
    visible_ = v;
}

bool Sprite::visible()
{
    return visible_;
}

uint64_t Sprite::width()
{
    return width_;
}

bool Sprite::collides()
{
    return false;
}

bool Sprite::detect_collisions()
{
    return detect_collisions_;
}

bool Sprite::get_collision_at(uint64_t, uint64_t)
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


void Sprite::set_speed(const taeto::Speed& speed)
{
    speed_ = speed;
}

void Sprite::apply_speed(const taeto::Speed& speed)
{
    speed_.z += speed.z;
    speed_.y += speed.y;
    speed_.x += speed.x;
}

taeto::Speed Sprite::speed()
{
    return speed_;
}

void Sprite::set_force(const taeto::Force& force)
{
    force_ = force;
}

void Sprite::apply_force(const taeto::Force& force)
{
    force_.z += force.z;
    force_.y += force.y;
    force_.x += force.x;
}

taeto::Force Sprite::force()
{
    return force_;
}

void Sprite::animate()
{

}

}   // namespace taeto
