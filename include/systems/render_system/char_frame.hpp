#ifndef SYSTEMS_RENDER_SYSTEM_FRAMES_CHAR_FRAME_H_
#define SYSTEMS_RENDER_SYSTEM_FRAMES_CHAR_FRAME_H_

#include <algorithm>
#include <array>
#include <vector>

#include "lodepng.h"

#include "systems/render_system/frame.h"

namespace taeto
{

class CharFrame : NewFrame
{
public:
    CharFrame();

    CharFrame(unsigned long int, unsigned long int);

    CharFrame(std::vector<std::vector<uint8_t>>);

    CharFrame(std::string);

    ~CharFrame();

    uint8_t& at(long int y, long int x);

    unsigned int get_width();

    unsigned int get_height();

    // Helper methods

    // Combine the values of each frame at the given location and return result
    void combine(CharFrame, unsigned int, unsigned int, bool, bool, bool);

    void print();

    // Export to string
    std::string serialize();

private:
    // Frame dimensions
    unsigned int width;
    unsigned int height;

    // Values that frame is made up of
    std::vector<std::vector<uint8_t>> values;
};

}   // namespace taeto

#endif  // SYSTEMS_RENDER_SYSTEM_FRAMES_CHAR_FRAME_H_
