#include "systems/render_system/ray_cast_render_system.hpp"

#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "frames/display_pixel_frame.h"
// #include "components/position.hpp"

namespace taeto
{

void RayCastRenderSystem::render_frame(
    taeto::DisplayPixelFrame &rendered_frame,
    taeto::Camera &camera,
    std::vector<std::weak_ptr<taeto::Object>>& sprites,
    std::vector<std::weak_ptr<taeto::Object>>& lights)
{
    // Get height and width for quick reference
    int h = rendered_frame.height();
    int w = rendered_frame.width();

    double half_frame_height = (double)h / 2;
    double half_frame_width = (double)w / 2;

    // Loop over each 'pixel' in frame
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            // Vector for rendered pixels before they're combined into a single
            // displayed pixel
            static std::vector<std::tuple<taeto::RenderPixel, double>> pixel_stack =
                std::vector<std::tuple<taeto::RenderPixel, double>>();
            pixel_stack.clear();

            // TODO: MAKE SURE SPRITE AND LIGHT POINTERS AREN'T DEAD

            // Render each sprite at a time
            for (std::weak_ptr<Object> current_object_weak_ptr : sprites)
            {
                // Get pointer if not dead
                std::shared_ptr<taeto::Object> current_sprite;
                if (!(current_sprite = current_sprite_weak_ptr.lock()))
                    continue;

                // Set visible to false until we get a pixel from the object
                current_sprite->visible(false);

                // Get distance between sprite and camera
                double z_diff = camera.get_z_pixel_position() -
                                current_sprite->get_z_pixel_position();

                // Make sure sprite is at least in front of the camera and
                // within rendering distance
                // Also handle case where z-diff is 0 to prevent divide by zero error
                // if (z_diff <= 0 || z_diff > render_distance_)
                //     continue;

                // Get sprite pixel of interest depending on orientation plane
                // We're going to be very literal to keep things straight
                char plane_orientation =
                    current_sprite->get_plane_orientation();
                int dp_y = y - half_frame_height;
                int dp_x = x - half_frame_width;
                double sprite_z = 0.0;
                double sprite_y = 0.0;
                double sprite_x = 0.0;
                if (plane_orientation == 'Z')
                {
                    double z_diff = camera.get_z_pixel_position() -
                        current_sprite->get_z_pixel_position();
                    double sprite_y =
                        (((dp_y * z_diff) /
                          camera.get_focal_length()) +
                         camera.get_y_pixel_position()) -
                        current_sprite->get_y_pixel_position();
                    double sprite_x =
                        (((dp_x * z_diff) /
                          camera.get_focal_length()) +
                         camera.get_x_pixel_position()) -
                        current_sprite->get_x_pixel_position();
                }
                else if (plane_orientation == 'Y')
                {
                    double y_diff = camera.get_y_pixel_position() -
                        current_sprite->get_y_pixel_position();
                    double sprite_y =
                        (((dp_y * y_diff) /
                          camera.get_focal_length()) +
                         camera.get_z_pixel_position()) -
                        current_sprite->get_z_pixel_position();
                    double sprite_x =
                        (((dp_x * y_diff) /
                          camera.get_focal_length()) +
                         camera.get_x_pixel_position()) -
                        current_sprite->get_z_pixel_position();
                }

                // Map frame position to sprite plane position
                double abs_z = current_sprite->get_z_pixel_position();
                double abs_y = (((y - half_frame_height) * z_diff) / camera.get_focal_length()) + camera.get_y_pixel_position();
                double abs_x = (((x - half_frame_width) * z_diff) / camera.get_focal_length()) + camera.get_x_pixel_position();

                // Get distance to camera
                double distance_to_camera =
                    std::sqrt(abs_z * abs_z + abs_y * abs_y + abs_x * abs_x);

                // Map to relative to sprite origin
                double rel_y = abs_y - current_sprite->get_y_pixel_position();
                double rel_x = abs_x - current_sprite->get_x_pixel_position();

                // If pixel doesn't overlap with sprite, move on to next pixel
                if (sprite_x < 0 || sprite_x >= current_sprite->width() ||
                    sprite_y < 0 || sprite_y >= current_sprite->height())
                     continue;

                // Get pixel of interest
                taeto::Pixel current_pixel =
                    current_sprite->get_pixel_at(sprite_y, sprite_x);

                // Now that we have a pixel from the sprite, we know that it's
                // visible, so let it know that
                current_sprite->visible(true);

                // Determine if pixel should be drawn
                // If the foreground alpha channel is anything but 0, it will be drawn
                if (current_pixel.foreground_color.alpha == 0)
                    continue;

                // Compute lighting for this pixel
                taeto::Color received_light(0, 0, 0);
                for (std::weak_ptr<Object> light_weak_ptr : lights)
                {
                    // Get pointer if not dead
                    std::shared_ptr<taeto::Object> light;
                    if (!(light = light_weak_ptr.lock()))
                        continue;

                    // Light color at this pixel location
                    taeto::Color light_color = light->get_light_color(abs_x, abs_y, abs_z);

                    // Get light vector and pixel normal
                    const taeto::Vector &pixel_normal = current_pixel.normal;
                    const taeto::Vector light_vector = light->get_light_vector(abs_x, abs_y, abs_z);

                    // TODO: PUT THIS IN A VECTOR OPERATOR METHOD
                    // Get vector components
                    char x1 = pixel_normal.x();
                    char y1 = pixel_normal.y();
                    char z1 = pixel_normal.z();
                    char x2 = light_vector.x();
                    char y2 = light_vector.y();
                    char z2 = light_vector.z();

                    // Calculate angle between the two
                    float angle = acos((x1 * x2 + y1 * y2 + z1 * z2) /
                                       (sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2)) *
                                        sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2))));

                    // Scale from 0 to pi, to between 0 and 255
                    unsigned char brightness = 255 - (unsigned char)(angle * 81.1690378636);

                    // Adjust light brightness accordingly
                    light_color.set_brightness(brightness);

                    // Add light to accumulated pixel light
                    received_light += light_color;
                }

                // Apply light to pixel
                current_pixel.foreground_color = current_pixel.foreground_color * received_light;
                current_pixel.background_color = current_pixel.background_color * received_light;

                // Add pixel to stack for combining into rendered pixel
                pixel_stack.push_back({current_pixel, distance_to_camera});

                // If this sprite's pixel is fully opaque, we're done rendering this pixel
                if (current_pixel.background_color.alpha == 255)
                    break;
            }

            // Add skybox pixel to stack
            // TODO: SKYBOXES
            // taeto::Pixel skybox_pixel = taeto::Pixel(' ', taeto::Color(255, 255, 255, 255), taeto::Color(0, 0, 0, 255), false);
            // pixel_stack.push_back(skybox_pixel);

            if (pixel_stack.size() == 0)
            {
                rendered_frame.get_pixel_at(y, x).clear();
                continue;
            }



            // I SAY "FUCK IT"

            // Pixel is officially finished rendering, write to final frame
            rendered_frame.get_pixel_at(y, x) = std::get<0>(pixel_stack.at(0));
            continue;





            // Now that we have all the rendered pixels, combine them together
            taeto::Pixel rendered_pixel =
                std::get<0>(pixel_stack.at(pixel_stack.size() - 1));
            for (int i = pixel_stack.size() - 2; i >= 0; --i)
            {
                // Get new background color
                taeto::Color bg = rendered_pixel.background_color &
                    std::get<0>(pixel_stack.at(i)).background_color;
                rendered_pixel = std::get<0>(pixel_stack.at(i));
                rendered_pixel.background_color = bg;
            }

            // Pixel is officially finished rendering, write to final frame
            rendered_frame.get_pixel_at(y, x) = rendered_pixel;
        }
    }
}

}   // namespace taeto
