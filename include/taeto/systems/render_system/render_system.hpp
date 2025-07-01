#ifndef SYSTEMS_RENDER_SYSTEM_HPP_
#define SYSTEMS_RENDER_SYSTEM_HPP_

#include <chrono>
#include <deque>
#include <memory>
#include <tuple>
#include <vector>

#include "spdlog/spdlog.h"

#include "taeto/objects/camera.hpp"
#include "taeto/components/display_pixel.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/objects/lights/light.hpp"
#include "taeto/objects/sprites/sprite.hpp"
#include "taeto/systems/system.hpp"
#include "taeto/tools.hpp"

namespace taeto
{

/**
 * This struct contains all of the relevant settings for a render system.
 */
struct RenderSettings {
    // How far away from the camera a pixel can be before it's not rendered
    double render_distance;

    // Whether or not to consider light sources for lighting pixels
    bool dynamic_lighting = true;

    // Whether or not to use consider pixel normals for lighting calculations
    bool normal_mapping = true;

    // Curve that relates light source angle to the normal of the pixel
    std::function<double(double)> diffusion_curve;

    // Bloom strength, 0.0 for no bloom computing
    double bloom;

    // Whether or not to use high-dynamic range
    bool hdr;

    // Default values constructor
    RenderSettings() {
        render_distance = 10000000.0;
        dynamic_lighting = true;
        normal_mapping = true;
        diffusion_curve = [](double brightness){
            return smoothstep(brightness, 0.45, 1.0);
        };
        bloom = 1.0;
        hdr = true;
    }
};

class RenderSystem : public System
{
public:
    RenderSystem(RenderSettings& settings) : settings_(settings) { };

    ~RenderSystem() { };

    /**
     * Render a PixelFrame with all known objects in the engine. Uses a
     * ray-casting type method and deferred lighting.
     *
     * @param[in,out] rendered_frame Frame to write rendered pixels to.
     * @param[in] camera Camera used to render the frame.
     * @param[in] sprites List of sprites that should be rendered in the frame.
     * @param[in] lights List of lights that should be used to light the scene.
     */
    virtual void render_frame(
        taeto::DisplayPixelFrame&,
        taeto::Camera&,
        std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
        std::vector<std::weak_ptr<taeto::Light>>& lights
    );

    /**
     * @brief Returns the settings struct for the render system.
     *
     * @return RenderSettings& A reference to the settings currently being
     * used.
     */
    RenderSettings& settings() { return settings_; };

protected:
    RenderSettings& settings_;
};

}   // namespace taeto

#endif  // SYSTEMS_RENDER_SYSTEM_HPP_
