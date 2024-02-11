#include "systems/render_system/ray_cast_render_system.hpp"

#include <memory>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "spdlog/spdlog.h"

// #include "components/position.hpp"
#include "components/display_pixel.hpp"
#include "components/render_pixel.hpp"
#include "frames/frame.hpp"
#include "frames/display_pixel_frame.hpp"
#include "tools.hpp"

namespace taeto
{

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


    ////////////////////////////////////////////////////////////////
    ////                         RENDER                         ////
    ////////////////////////////////////////////////////////////////

    // Create frames needed for rendering
    // I'm not making a class for these, I'm tired of always changing it
    // taeto::Frame<int8_t> char_buffer(h, w);
    // taeto::Frame<glm::vec4> fg_color_buffer(h, w);
    // taeto::Frame<glm::vec4> bg_colors_buffer(h, w);
    // taeto::Frame<bool> bold_buffer(h, w);
    // taeto::Frame<bool> italic_buffer(h, w);
    // taeto::Frame<bool> underline_buffer(h, w);
    // taeto::Frame<bool> strikethrough_buffer(h, w);

    double half_frame_height = (double)h / 2;
    double half_frame_width = (double)w / 2;

    // Loop over each pixel in frame
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            taeto::RenderPixel current_pixel = taeto::RenderPixel();

            // Render each sprite at a time
            for (std::weak_ptr<taeto::Sprite> current_sprite_weak_ptr : sprites)
            {
                // Get pointer if not dead
                std::shared_ptr<taeto::Sprite> current_sprite;
                if (!(current_sprite = current_sprite_weak_ptr.lock()))
                    continue;

                // TEMP
                // Clear rendered pixel
                rendered_frame.at(glm::uvec2(x, y)).clear();

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
                double abs_y = (((y - half_frame_height) * z_diff) / camera.focal_length()) + (int64_t)camera.position().y;
                double abs_x = (((x - half_frame_width) * z_diff) / camera.focal_length()) + (int64_t)camera.position().x;

                // Map to relative to sprite origin
                double rel_y = abs_y - (int64_t)current_sprite->position().y;
                double rel_x = abs_x - (int64_t)current_sprite->position().x;

                // If pixel doesn't overlap with sprite, move on to next pixel
                if ( rel_x < 0 || rel_x >= current_sprite->width() ||
                     rel_y < 0 || rel_y >= current_sprite->height())
                     continue;

                // LMAO
                double distance_to_camera = 10.0;

                // Get pixel of interest
                current_pixel =
                    current_sprite->get_pixel_at(glm::uvec2(rel_x, rel_y));

                // Now that we have a pixel from the sprite, we know that it's
                // visible, so let it know that
                current_sprite->visible(true);

                // Determine if pixel should be drawn
                // If the foreground alpha channel is anything but 0, it will be
                // drawn
                if (!current_pixel.render)
                    continue;

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
                        const glm::vec3 &pixel_normal = current_pixel.normal;
                        const glm::vec3 light_vector =
                            light->vector(glm::dvec3(abs_x, abs_y, abs_z));

                        // TODO: PUT THIS IN A VECTOR OPERATOR METHOD
                        // Get vector components
                        double x1 = pixel_normal.x;
                        double y1 = pixel_normal.y;
                        double z1 = pixel_normal.z;
                        double x2 = light_vector.x;
                        double y2 = light_vector.y;
                        double z2 = light_vector.z;

                        // Calculate angle between the two
                        // float angle = acos((x1 * x2 + y1 * y2 + z1 * z2) /
                        //                    (sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2)) *
                        //                     sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2))));
                        double dot = x1*x2 + y1*y2 + z1*z2;
                        double len_sq1 = x1*x1 + y1*y1 + z1*z1;
                        double len_sq2 = x2*x2 + y2*y2 + z2*z2;
                        double angle = acos(dot / sqrt(len_sq1 * len_sq2));

                        // Scale from 0 to pi, to between 0 and 255
                        // unsigned char brightness = 255 - (unsigned char)(angle * 81.1690378636);

                        // Scale from 0 to pi, to between 0 and 1 and compute smoothstep
                        double brightness = taeto::smoothstep(1.0 - (angle / 3.1415927));

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

                // Add pixel to stack for combining into rendered pixel
                // pixel_stack.push_back({current_pixel, distance_to_camera});

                rendered_frame.at(glm::uvec2(x, y)) = current_pixel;
				// rendered_frame.at(y, x).background_color = taeto::Color(current_pixel.normal.x()+127, current_pixel.normal.y()+127, current_pixel.normal.z()+127);

                // If this sprite's pixel is fully opaque, we're done rendering this pixel
                if (current_pixel.bg_color.w == 255)
                    continue;
            }
            continue;
            // // Add skybox pixel to stack
            // // TODO: SKYBOXES
            // // taeto::Pixel skybox_pixel = taeto::Pixel(' ', taeto::Color(255, 255, 255, 255), taeto::Color(0, 0, 0, 255), false);
            // // pixel_stack.push_back(skybox_pixel);
            //
            //
            //
            // if (pixel_stack.size() == 0)
            // {
            //     rendered_frame.at(glm::uvec2(x, y)).clear();
            //     continue;
            // }
            //
            //
            //
            // // I SAY "FUCK IT"
            //
            // // Pixel is officially finished rendering, write to final frame
            // rendered_frame.at(glm::uvec2(x, y)) = std::get<0>(pixel_stack.at(0));
            // continue;
            //
            //
            //
            //
            //
            // // Now that we have all the rendered pixels, combine them together
            // taeto::DisplayPixel rendered_pixel =
            //     std::get<0>(pixel_stack.at(pixel_stack.size() - 1));
            // for (int i = pixel_stack.size() - 2; i >= 0; --i)
            // {
            //     // Get new background color
            //     taeto::Color bg = rendered_pixel.background_color &
            //         std::get<0>(pixel_stack.at(i)).background_color;
            //     rendered_pixel = std::get<0>(pixel_stack.at(i));
            //     rendered_pixel.background_color = bg;
            // }
            //
            // // Pixel is officially finished rendering, write to final frame
            // rendered_frame.at(y, x) = rendered_pixel;
        }
    }

    ////////////////////////////////////////////////////////////////
    ////                    POST-PROCESSING                     ////
    ////////////////////////////////////////////////////////////////
}

}   // namespace taeto
