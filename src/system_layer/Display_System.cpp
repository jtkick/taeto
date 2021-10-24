#include "Display_System.h"

// For debugging
#include <thread>
#include <chrono>

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

Display_System::Display_System(shared_ptr<spdlog::logger> l, shared_ptr<Message_Bus> mb)
{
    logger = l;

    message_bus = mb;

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

    logger->error("Done setting up display system.");
}

Display_System::~Display_System()
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

void Display_System::handle_message(shared_ptr<Message> message)
{
    // Handle message types this system cares about
    switch (message->get_id())
    {
        case DISPLAY_FRAME:
        {
            logger->info("Display frame message received.");

            shared_ptr<Display_Frame_Message> dfm = dynamic_pointer_cast<Display_Frame_Message>(message);

            display_frame(dfm->get_frame());
        }
        break;
    }

}

void Display_System::display_frame(shared_ptr<Frame> frame)
{
    // Outputting each piece individually causes buffering issues that makes the game flicker
    // To avoid this, we're going to add everything we want to print to a string, then
    // output it all at once.
    // If you are skeptical that this will work better like I was, just know it works well.
    // It's even faster than what I was doing before
    std::string output_buffer = "";

    Pixel current_pixel;

    for (int h = 0; h < frame->get_height(); h++)
    {
        for (int w = 0; w < frame->get_width(); w++)
        {
            // Move to current column and row
            output_buffer += "\033[" + std::to_string(h+1) + ";" + std::to_string(w+1) + "H";

            // Don't output last character
            if (h == frame->get_height() - 1 &&
                w == frame->get_width() - 1)
                break;

            // Get pixel in question
            current_pixel = frame->get_pixel(h, w);

            // Add background color
            const Color* c = current_pixel.get_background_color();
            output_buffer += "\033[48;2;" + std::to_string((int)(c->get_red())) + ";" +
                                            std::to_string((int)(c->get_green())) + ";" +
                                            std::to_string((int)(c->get_blue())) + "m";

            // Add foreground color
            c = current_pixel.get_foreground_color();
            output_buffer += "\033[38;2;" + std::to_string((int)(c->get_red())) + ";" +
                                            std::to_string((int)(c->get_green())) + ";" +
                                            std::to_string((int)(c->get_blue())) + "m";

            // Add actual character
            output_buffer += current_pixel.get_char();
        }
    }

    // Print frame and flush output
    std::cout << output_buffer << std::flush;

}
