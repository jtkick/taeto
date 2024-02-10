#ifndef SYSTEMS_DISPLAY_SYSTEMS_STDOUT_DISPLAY_SYSTEM_STDOUT_DISPLAY_SYSTEM_HPP_
#define SYSTEMS_DISPLAY_SYSTEMS_STDOUT_DISPLAY_SYSTEM_STDOUT_DISPLAY_SYSTEM_HPP_

#include <memory>

#include <glm/glm.hpp>

#include "frames/display_pixel_frame.hpp"
#include "systems/display_systems/display_system.hpp"

// Typical pixel
const std::string BLANK_PIXEL_STRING =
// char_offset ------------------------------------------------------------
// fg_blue_offset -----------------------------------------------------   |
// fg_green_offset ------------------------------------------------   |   |
// fg_red_offset ----------------------------------------------   |   |   |
// bg_blue_offset -------------------------------             |   |   |   |
// bg_green_offset --------------------------   |             |   |   |   |
// bg_red_offset ------------------------   |   |             |   |   |   |
// x_loc_offset ----------              |   |   |             |   |   |   |
// y_loc_offset -----    |              |   |   |             |   |   |   |
//                  V    V              V   V   V             V   V   V   V
              "\033[0000;0000H\033[48;2;000;000;000m\033[38;2;000;000;000m ";
const unsigned int Y_LOC_OFFSET = 2;
const unsigned int X_LOC_OFFSET = 7;
const unsigned int BG_RED_OFFSET = 19;
const unsigned int BG_GREEN_OFFSET = 23;
const unsigned int BG_BLUE_OFFSET = 27;
const unsigned int FG_RED_OFFSET = 38;
const unsigned int FG_GREEN_OFFSET = 42;
const unsigned int FG_BLUE_OFFSET = 46;
const unsigned int CHAR_OFFSET = 50;
const unsigned int TOTAL_PIXEL_STRING_LENGTH = 51;

namespace taeto
{

class StdoutDisplaySystem: public DisplaySystem
{
public:
    StdoutDisplaySystem();

    ~StdoutDisplaySystem();

    // Write entire frame to stdout
    void display_frame(taeto::DisplayPixelFrame&);
    void display_frame_old(taeto::DisplayPixelFrame&);

private:
    // Resize output buffer
    void resize(int, int);

    std::string color_to_string(float);

    // The output buffer that will output on every frame to stdout
    std::string output_buffer;
    unsigned int height;
    unsigned int width;
};

}   // namespace taeto

#endif  // SYSTEMS_DISPLAY_SYSTEMS_STDOUT_DISPLAY_SYSTEM_STDOUT_DISPLAY_SYSTEM_HPP_
