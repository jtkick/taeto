#include "assets/objects/box.hpp"

#include "components/color.hpp"
#include "components/render_pixel_frame.hpp"
#include "components/vector.hpp"

namespace taeto
{

Box::Box(unsigned int height, unsigned width, taeto::Color color)
{
    // Set default position to center on the origin
    position_  = Position(0, -(height_/2), -(width_/2));

    taeto::RenderPixel p = taeto::RenderPixel(' ', {}, color_, false);
    taeto::Frame f = taeto::RenderPixelFrame(height_, width_, p);

    // Set color and normals
    if (height_ > 2 && width_ > 4)
        for (int i = 0; i < height_; ++i)
            for (int j = 0; j < width_; ++i)
            {
                // Top-left
                if (i == 0 && j < 2)
                    f.at(i, j).normal = taeto::Vector(-90, -90, 90);
                // Top-center
                if (i == 0 && j > 1 && j < width_ - 2)
                    f.at(i, j).normal = taeto::Vector(0, -90, 90);
                // Top-right
                if (i == 0 && j > width_ - 3)
                    f.at(i, j).normal = taeto::Vector(90, -90, 90);
                // Center-left
                if (i > 0 && i < height_ - 1 && j < 2)
                    f.at(i, j).normal = taeto::Vector(-90, 0, 90);
                // Center
                if (i > 0 && i < height_ - 1 && j > 1 && j < width_ -2)
                    f.at(i, j).normal = taeto::Vector(0, 0, 120);
                // Center-right
                if (i > 0 && i < height_ - 1 && j > width_ - 3)
                    f.at(i, j).normal = taeto::Vector(90, 0, 90);
                // Bottom-left
                if (i > height_ - 2 && j < 2)
                    f.at(i, j).normal = taeto::Vector(-90, 90, 90);
                // Bottom-center
                if (i > height_ - 2 && j > 1 && j < width_ - 2)
                    f.at(i, j).normal = taeto::Vector(0, 90, 90);
                // Bottom-right
                if (i > height_ - 2 && j > width_ - 3)
                    f.at(i, j).normal = taeto::Vector(90, 90, 90);
            }
}

const taeto::RenderPixel& get_pixel_at(uint64_t y, uint64_t x)
{
    return f.at(y, x);
}

}   // namespace taeto
