#ifndef DISPLAY_SYSTEM_H
#define DISPLAY_SYSTEM_H

#include "Display_Frame_Message.h"
#include "Frame.h"
#include "Message_Bus.h"
#include "System.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <signal.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <termios.h>

using namespace std;
/*
struct output_pixel
{
    // Location on terminal output
    char location_escape_sequence[2] = "\033[";
    char location_col[4] = "0000";
    char location_div = ";";
    char location_row[4] = "0000";
    char location_close = "H";

    // Background color
    char bg_color_escape_sequence[7] = "\033[48;2;";
    char bg_color_red[3] = "000";
    char bg_color_div0 = ";";
    char bg_color_green[3] = "000";
    char bg_color_div1 = ";";
    char bg_color_blue[3] = "000";
    char bg_color_close = "m";

    // Foreground color
    char fg_color_escape_sequence[7] = "\033[38;2;";
    char fg_color_red[3] = "000";
    char fg_color_div0 = ";";
    char fg_color_div1 = ";";
    char fg_color_green[3] = "000";
    char fg_color_blue[3] = "000";
    char fg_color_close = "m";

    // Pixel character
    char character = " ";
};*/

// Typical pixel
// char_offset -------------------------------------------------------------------------------------
// fg_blue_offset ------------------------------------------------------------------------------   |
// fg_green_offset -------------------------------------------------------------------------   |   |
// fg_red_offset -----------------------------------------------------------------------   |   |   |
// bg_blue_offset --------------------------------------------------------             |   |   |   |
// bg_green_offset ---------------------------------------------------   |             |   |   |   |
// bg_red_offset -------------------------------------------------   |   |             |   |   |   |
// x_loc_offset -----------------------------------              |   |   |             |   |   |   |
// y_loc_offset ------------------------------    |              |   |   |             |   |   |   |
//                                           V    V              V   V   V             V   V   V   V
const std::string BLANK_PIXEL_STRING = "\033[0000;0000H\033[48;2;000;000;000m\033[38;2;000;000;000m ";
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

class Display_System: public System
{
    // Engine-wide logger
    shared_ptr<spdlog::logger> logger;

    // Message bus for posting messages
    shared_ptr<Message_Bus> message_bus;

    // The output buffer that will output on every frame to stdout
    std::string output_buffer;
    unsigned int height;
    unsigned int width;

    int display_loop;

    public:

        Display_System(shared_ptr<spdlog::logger>, shared_ptr<Message_Bus>);

        ~Display_System(void);

        // Read message from engine-wide message bus
        void handle_message(shared_ptr<Message>);

    private:

        // Write entire frame to stdout
        void display_frame(shared_ptr<Frame>);
        void display_frame_old(shared_ptr<Frame>);

        // Resize output buffer
        void resize(int, int);
};

#endif
