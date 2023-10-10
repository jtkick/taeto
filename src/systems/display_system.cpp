#include "systems/display_system.hpp"

#include <cstdlib>
#include <signal.h>
#include <termios.h>

#include <iostream>
#include <memory>

#include "spdlog/spdlog.h"

#include "components/color.hpp"
#include "components/display_pixel.hpp"
#include "frames/display_pixel_frame.hpp"

void signal_callback_handler(int signum)
{
    // Go back to original terminal screen
    std::cout << "\e[?1049l";

    // Make cursor visible again
    printf("\e[?25h");

    // Turn character echo back on
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &t);

    // Exit
    exit(signum);
}

namespace taeto
{

DisplaySystem::DisplaySystem()
{
    // Open alternate terminal screen
    std::cout << "\e[?1049h";

    // Make cursor not visible
    printf("\e[?25l");

    // Turn off character echo
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &t);

    // Register function to be called when ctrl-c is sent
    signal(SIGINT, signal_callback_handler);

    // Change terminal title
    std::cout << "\033]0;Taeto\007";

    spdlog::debug("Done setting up display system.");
}

DisplaySystem::~DisplaySystem()
{
    // Go back to original terminal screen
    std::cout << "\e[?1049l";

    // Make cursor visible again
    printf("\e[?25h");

    // Turn character echo back on
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &t);
}

void DisplaySystem::display_frame(taeto::DisplayPixelFrame &frame)
{
    // First, resize buffer if wrong size
    if (frame.height() != height || frame.width() != width)
    {
        resize(frame.height(), frame.width());
    }

    for (int h = 0; h < frame.height(); h++)
    {
        for (int w = 0; w < frame.width(); w++)
        {
            // Don't output last character
            if (h == frame.height() - 1 &&
                w == frame.width() - 1)
                break;

            // Get pixel in question
            DisplayPixel& current_pixel = frame.at(h, w);

            // Location of start of this pixel in string
            unsigned int pixel_start = TOTAL_PIXEL_STRING_LENGTH * ((h*width) + w);

            // Get pixel row
            std::string temp = std::to_string(h+1);
            // Pad it with zeros
            temp.insert(temp.begin(), 4 - temp.length(), '0');
            // Add to output string
            output_buffer.replace(pixel_start + Y_LOC_OFFSET, 4, temp);

            // Do same for collumn
            temp = std::to_string(w+1);
            temp.insert(temp.begin(), 4 - temp.length(), '0');
            output_buffer.replace(pixel_start + X_LOC_OFFSET, 4, temp);

            // Get pixel to display
            current_pixel = frame.at(h, w);

            // Get background color
            Color& c = current_pixel.background_color;

            // BG red
            temp = std::to_string((int)(c.red));
            temp.insert(temp.begin(), 3 - temp.length(), '0');
            output_buffer.replace(pixel_start + BG_RED_OFFSET, 3, temp);

            // BG green
            temp = std::to_string((int)(c.green));
            temp.insert(temp.begin(), 3 - temp.length(), '0');
            output_buffer.replace(pixel_start + BG_GREEN_OFFSET, 3, temp);

            // BG blue
            temp = std::to_string((int)(c.blue));
            temp.insert(temp.begin(), 3 - temp.length(), '0');
            output_buffer.replace(pixel_start + BG_BLUE_OFFSET, 3, temp);

            // Get foreground color
            c = current_pixel.foreground_color;

            // FG red
            temp = std::to_string((int)(c.red));
            temp.insert(temp.begin(), 3 - temp.length(), '0');
            output_buffer.replace(pixel_start + FG_RED_OFFSET, 3, temp);

            // FG green
            temp = std::to_string((int)(c.green));
            temp.insert(temp.begin(), 3 - temp.length(), '0');
            output_buffer.replace(pixel_start + FG_GREEN_OFFSET, 3, temp);

            // FG blue
            temp = std::to_string((int)(c.blue));
            temp.insert(temp.begin(), 3 - temp.length(), '0');
            output_buffer.replace(pixel_start + FG_BLUE_OFFSET, 3, temp);

            // Add actual character
            output_buffer.at(pixel_start + CHAR_OFFSET) = current_pixel.c;
        }
    }

    // Print frame and flush output
    std::cout << output_buffer << std::flush;

    // Write frame to file for debugging
    // std::string filename = "/tmp/taeto_frame_" + std::to_string(display_loop++) + ".txt";
    // std::ofstream out(filename);
    // out << output_buffer;
    // out.close();
}



void DisplaySystem::display_frame_old(taeto::DisplayPixelFrame &frame)
{
    output_buffer = "";

    for (int h = 0; h < frame.height(); h++)
    {
        for (int w = 0; w < frame.width(); w++)
        {
            // Move to current column and row
            output_buffer += "\033[" + std::to_string(h+1) + ";" + std::to_string(w+1) + "H";

            // Don't output last character
            if (h == frame.height() - 1 &&
                w == frame.width() - 1)
                break;

            // Get pixel in question
            DisplayPixel& current_pixel = frame.at(h, w);

            // Add background color
            Color& c = current_pixel.background_color;
            output_buffer += "\033[48;2;" + std::to_string((int)(c.red)) + ";" +
                                            std::to_string((int)(c.green)) + ";" +
                                            std::to_string((int)(c.blue)) + "m";

            // Add foreground color
            c = current_pixel.foreground_color;
            output_buffer += "\033[38;2;" + std::to_string((int)(c.red)) + ";" +
                                            std::to_string((int)(c.green)) + ";" +
                                            std::to_string((int)(c.blue)) + "m";

            // Add actual character
            output_buffer += current_pixel.c;
        }
    }

    // Print frame and flush output
    std::cout << output_buffer << std::flush;
}

void DisplaySystem::resize(int h, int w)
{
    // Save dimensions
    height = h;
    width = w;

    // Initialize the output buffer
    output_buffer = "";
    for (int i = 0; i < height*width; i++)
        output_buffer += BLANK_PIXEL_STRING;
}

}   // namespace taeto
