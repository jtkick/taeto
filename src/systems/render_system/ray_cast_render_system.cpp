#include "taeto/systems/render_system/ray_cast_render_system.hpp"

#include <memory>
#include <csignal>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include "spdlog/spdlog.h"

// #include "components/position.hpp"
#include "taeto/components/display_pixel.hpp"
#include "taeto/components/render_pixel.hpp"
#include "taeto/frames/frame.hpp"
#include "taeto/frames/display_pixel_frame.hpp"
#include "taeto/shaders/shader.hpp"
#include "taeto/tools.hpp"

namespace taeto
{

// For sorting vector of sprites
bool compare_sprites(std::weak_ptr<taeto::Sprite> weak_sprite1,
                     std::weak_ptr<taeto::Sprite> weak_sprite2)
{
    // Get shared pointers to both sprites
    std::shared_ptr<taeto::Sprite> sprite1;
    std::shared_ptr<taeto::Sprite> sprite2;
    if (!(sprite1 = weak_sprite1.lock()) ||
        !(sprite2 = weak_sprite2.lock()))
        return false;

    // Compare position
    return sprite1->position().z < sprite2->position().z;
}

void RayCastRenderSystem::render_frame(
    taeto::DisplayPixelFrame &rendered_frame,
    taeto::Camera &camera,
    std::vector<std::weak_ptr<taeto::Sprite>>& sprites,
    std::vector<std::weak_ptr<taeto::Light>>& lights)
{
    // Get height and width for quick reference
    int h = rendered_frame.height();
    int w = rendered_frame.width();

    ////////////////////////////////////////////////////////////////
    ////                       PRE-RENDER                       ////
    ////////////////////////////////////////////////////////////////

    // Sort all sprites from closest to farthest
    // Just going to assume std::sort() is smart enough to use insertion sort
    // in this scenario (for now)
    std::sort(sprites.begin(), sprites.end(), compare_sprites);

    ////////////////////////////////////////////////////////////////
    ////                         RENDER                         ////
    ////////////////////////////////////////////////////////////////

    double half_frame_height = (double)h / 2;
    double half_frame_width = (double)w / 2;

    // Loop over each pixel in frame
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // Make sure to start with completely black pixel
            rendered_frame.at(glm::uvec2(x, y)).clear();

            // // Go down sprites until we find one that is completely opaque
            // int pixel_index = sprites.size()-1;
            // while (pixel_index >= 0)
            // {
            //     // Get pointer if not dead
            //     std::shared_ptr<taeto::Sprite> current_sprite;
            //     if (!(current_sprite = current_sprite_weak_ptr.lock()))
            //         continue;
            //
            //     // Stop here if sprite is completely opaque
            //
            //     if (current_sprite->get_pixel_at(glm::uvec2(x, y)))
            // }

            // Render each sprite at a time
            for (std::weak_ptr<taeto::Sprite> current_sprite_weak_ptr : sprites)
            {
                // Get pointer if not dead
                std::shared_ptr<taeto::Sprite> current_sprite;
                if (!(current_sprite = current_sprite_weak_ptr.lock()))
                    continue;

                // Assume it's invisible and update it as such
                current_sprite->visible(false);

                // Get distance between sprite and camera
                double z_diff = (int64_t)camera.position().z -
                                (int64_t)current_sprite->position().z;

                // Make sure sprite is at least in front of the camera and
                // within rendering distance
                // Also handle case where z-diff is 0 to prevent divide by zero error
                if (z_diff <= 0 || z_diff > render_distance_)
                    continue;

                // Map frame position to sprite plane position
                double abs_z = (int64_t)current_sprite->position().z;
                double abs_y = (((y - half_frame_height) * z_diff) /
                    camera.focal_length()) + (int64_t)camera.position().y;
                double abs_x = (((x - half_frame_width) * z_diff) /
                    camera.focal_length()) + (int64_t)camera.position().x;

                // Map to relative to sprite origin
                double rel_y = abs_y - (int64_t)current_sprite->position().y;
                double rel_x = abs_x - (int64_t)current_sprite->position().x;

                // If pixel doesn't overlap with sprite, move on to next pixel
                if ( rel_x < 0 || rel_x >= current_sprite->width() ||
                     rel_y < 0 || rel_y >= current_sprite->height())
                     continue;

                // Get pixel of interest
                taeto::RenderPixel current_pixel =
                    current_sprite->get_pixel_at(glm::uvec2(rel_x, rel_y));

                // Now that we have a pixel from the sprite, we know that it's
                // visible, so let it know that
                current_sprite->visible(true);

                // Determine if pixel should be drawn
                // If the foreground alpha channel is anything but 0, it will be
                // drawn
                if (!current_pixel.render)
                    continue;

                ////////////////////////////////////////////////////////////////
                ////                      LIGHT PIXEL                       ////
                ////////////////////////////////////////////////////////////////

                // Compute lighting for this pixel
                if (current_sprite->respect_light_sources())
                {
                    glm::vec3 received_light(0.0, 0.0, 0.0);
                    for (std::weak_ptr<taeto::Light> light_weak_ptr : lights)
                    {
                        // Get pointer if not dead
                        std::shared_ptr<taeto::Light> light;
                        if (!(light = light_weak_ptr.lock()))
                            continue;

                        // Light color at this pixel location
                        glm::vec3 light_color =
                            light->color(glm::dvec3(abs_x, abs_y, abs_z));

                        // Get light vector and pixel normal
                        const glm::vec3 light_vec = glm::normalize(light->vector(glm::vec3(abs_x, abs_y, abs_z)));
                        const glm::vec3 pixel_vec = glm::normalize(current_pixel.normal);

                        // Compute how much the two vectors align
                        double brightness = (1.0f - glm::dot(light_vec, pixel_vec)) * 0.5f;

                        // Apply smoothstep function to pixel
                        brightness = taeto::smoothstep(brightness, 0.45, 1.0);

                        // Adjust light brightness accordingly
                        light_color *= brightness;

                        // Add light to accumulated pixel light
                        received_light += light_color;
                    }

                    // Apply light to pixel
                    current_pixel.fg_color =
                        current_pixel.fg_color * glm::vec4(received_light, 1.0);
                    current_pixel.bg_color =
                        current_pixel.bg_color * glm::vec4(received_light, 1.0);
                }

                ////////////////////////////////////////////////////////////////
                ////                      SHADE PIXEL                       ////
                ////////////////////////////////////////////////////////////////

                // Gather all values to pass to shader
                glm::uvec2 frame_shape = glm::uvec2(w, h);
                glm::uvec2 pos_in_frame = glm::uvec2(x, y);
                glm::dvec3 pos_in_world = glm::dvec3(abs_x, abs_y, abs_z);
                glm::dvec3 camera_pos = camera.position();

                // Apply shading to pixel
                for (auto shader : current_sprite->shaders())
                    current_pixel = shader->shade(
                        current_pixel, frame_shape, pos_in_frame, pos_in_world,
                        camera_pos);

                ////////////////////////////////////////////////////////////////
                ////                      APPLY PIXEL                       ////
                ////////////////////////////////////////////////////////////////

                // Now combine this pixel with the previous one rendered
                taeto::DisplayPixel& rendered_pixel =
                    rendered_frame.at(glm::uvec2(x, y));

                if (render_normals_)
                {
                    rendered_pixel.c = ' ';
                    glm::vec3 scaled = (current_pixel.normal / glm::vec3(2.0)) + glm::vec3(0.5);
                    rendered_pixel.bg_color = glm::vec4(
                        scaled.r, scaled.g, scaled.b, 1.0
                    );
                }
                else
                {
                    // Default, combine this with previous pixel
                    rendered_pixel.c = current_pixel.c;
                    rendered_pixel.fg_color = mix_colors(
                        rendered_pixel.fg_color,
                        current_pixel.fg_color);
                    rendered_pixel.bg_color = mix_colors(
                        rendered_pixel.bg_color,
                        current_pixel.bg_color);
                    rendered_pixel.bold = current_pixel.bold;
                    rendered_pixel.italic = current_pixel.italic;
                    rendered_pixel.underline = current_pixel.underline;
                    rendered_pixel.strikethrough = current_pixel.strikethrough;
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////
    ////                    POST-PROCESSING                     ////
    ////////////////////////////////////////////////////////////////

    // Add bloom to scene
    if (bloom_)
    {
        // Extract all bright pixels to separate buffer
        std::vector<std::vector<glm::vec3>> bloom_frame;
        bloom_frame.resize(h, std::vector<glm::vec3>(w, glm::vec3(0.0)));
        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                glm::vec3 color = rendered_frame.at(glm::uvec2(x, y)).bg_color;
                if (glm::length(color) > 1.5f)
                    bloom_frame.at(y).at(x) = color;
                else
                    bloom_frame.at(y).at(x) = glm::vec3(0.0f);
            }
        }

        // Generate 2D Gaussian kernel
        int kKernelSize = 30;
        float kSigma = 1.25f;
        std::vector<std::vector<float>> kernel;
        kernel.resize(kKernelSize * 2 + 1,
                      std::vector<float>(kKernelSize * 2 + 1));
        float sum = 0.0f;
        for (int y = -kKernelSize; y <= kKernelSize; ++y)
            for (int x = -kKernelSize; x <= kKernelSize; ++x)
            {
                float weight = exp(-(y * y + x/2 * x/2) / (2 * kSigma * kSigma));
                kernel.at(y + kKernelSize).at(x + kKernelSize) = weight;
                sum += weight;
            }

        // Normalize kernel
        for (auto& row : kernel)
            for (float& weight : row)
                weight /= sum;

        // Apply horizontal convolution
        std::vector<std::vector<glm::vec3>> blurred_horizontal;
        blurred_horizontal.reserve(bloom_frame.size());
        for (const auto& row : bloom_frame)
        {
            std::vector<glm::vec3> result;
            result.reserve(row.size());
            for (std::size_t i = 0; i < row.size(); ++i)
            {
                glm::vec3 convolved_pixel(0.0f);
                for (int j = -kKernelSize; j <= kKernelSize; ++j)
                {
                    int index = std::min(std::max(static_cast<int>(i) + j, 0),
                        static_cast<int>(row.size()) - 1);
                    convolved_pixel += row.at(index) *
                        kernel.at(kKernelSize).at(j + kKernelSize);
                }
                result.push_back(convolved_pixel);
            }
            blurred_horizontal.push_back(result);
        }

        // Apply vertical convolution
        std::vector<std::vector<glm::vec3>> blurred_vertical;
        blurred_vertical.resize(blurred_horizontal.size());
        for (std::size_t i = 0; i < blurred_horizontal.size(); ++i)
        {
            blurred_vertical.at(i).resize(blurred_horizontal.at(i).size());
            for (std::size_t j = 0; j < blurred_horizontal.at(i).size(); ++j)
            {
                glm::vec3 convolved_pixel(0.0f);
                for (int k = -kKernelSize; k <= kKernelSize; ++k)
                {
                    int index = std::min(std::max(static_cast<int>(i) + k, 0),
                        static_cast<int>(blurred_horizontal.size()) - 1);
                    convolved_pixel += blurred_horizontal.at(index).at(j) *
                        kernel.at(kKernelSize + k).at(kKernelSize);
                }
                blurred_vertical.at(i).at(j) = convolved_pixel;
            }
        }

        // Add blurred frame to the rendered frame
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x)
                rendered_frame.at(glm::uvec2(x, y)).bg_color +=
                    glm::vec4(blurred_vertical.at(y).at(x), 0.0f);

    }

    // Run tone mapping if HDR is on
    if (hdr_)
    {
        // Gamma correction value
        const float kGamma = 2.2f;

        for (int y = 0; y < h; ++y)
        {
            for (int x = 0; x < w; ++x)
            {
                // Get pixel
                taeto::DisplayPixel& pixel =
                    rendered_frame.at(glm::uvec2(x, y));

                // Map foreground color
                glm::vec3 color = pixel.fg_color;
                color = color / (color + glm::vec3(1.0));
                pixel.fg_color = glm::vec4(glm::pow(color, glm::vec3(1.0 / kGamma)), pixel.fg_color.w);

                // Map background color
                color = pixel.bg_color;
                color = color / (color + glm::vec3(1.0));
                pixel.bg_color = glm::vec4(glm::pow(color, glm::vec3(1.0 / kGamma)), pixel.bg_color.w);
            }
        }
    }
}

}   // namespace taeto
