#ifndef SYSTEMS_RENDER_SYSTEM_FRAMES_COLOR_FRAME_H_
#define SYSTEMS_RENDER_SYSTEM_FRAMES_COLOR_FRAME_H_

#include "components/color.h"
#include "components/sprite.h"
#include "systems/render_system/frame.h"

#include <algorithm>
#include <array>
#include <vector>
#include "lodepng.h"

namespace taeto
{

class ColorFrame : NewFrame
{
public:
    ColorFrame();

    ColorFrame(unsigned long int, unsigned long int);

    ColorFrame(std::vector<std::vector<taeto::Color>>);

    ColorFrame(std::string);

    ~ColorFrame();

    taeto::Color& at(long int y, long int x);

    unsigned int get_width();

    unsigned int get_height();

    // Helper methods

    // Combine the values of each frame at the given location and return result
    void combine(ColorFrame, unsigned int, unsigned int, bool, bool, bool);

    void print();

    // Export to string
    std::string serialize();

    // Turns frame into a renderable sprite. Mainly for testing
    taeto::Sprite to_sprite();

private:
    // Frame dimensions
    unsigned int width;
    unsigned int height;

    // Values that frame is made up of
    std::vector<std::vector<taeto::Color>> values;
};

}   // namespace taeto

#endif  // SYSTEMS_RENDER_SYSTEM_FRAMES_COLOR_FRAME_H_
