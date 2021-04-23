#include "Display_System.h"

// For debugging
#include <thread>
#include <chrono>

Display_System::Display_System(shared_ptr<spdlog::logger> l, shared_ptr<Message_Bus> mb)
{
    logger = l;

    message_bus = mb;

    // Open alternate terminal screen
    std::cout << "\e[?1049h";

    // Make cursor not visible
    printf("\e[?25l");

    logger->error("Done setting up display system.");
}

Display_System::~Display_System()
{
    // Go back to original terminal screen
    std::cout << "\e[?1049l";

    // Make cursor visible again
    printf("\e[?25h");
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

        // For debugging
        case KEY_UPDATE:
        {
            logger->info("Received key update message in display system");
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

}

void Display_System::display_frame(shared_ptr<Frame> frame)
{

    shared_ptr<Pixel> current_pixel;

    for (int h = 0; h < frame->get_height(); h++)
    {
        // Move to beginning of line
        printf("%c[%d;%df", 0X1B, h, 0);

        for (int w = 0; w < frame->get_width(); w++)
        {
            // Don't output last character
            if (h == frame->get_height() - 1 &&
                w == frame->get_width() - 1)
                break;

            // Get pixel in question
            current_pixel = frame->get_pixel(h, w);

            // Write background color
            const Color* c = current_pixel->get_background_color();
            printf("\033[48;2;%d;%d;%dm", c->get_red(), c->get_green(), c->get_blue());

            // Write foreground color
            c = current_pixel->get_foreground_color();
            printf("\033[38;2;%d;%d;%dm", c->get_red(), c->get_green(), c->get_blue());

            // Write character
            printf("%c", current_pixel->get_char());
        }

    }

    // Flush output
    fflush(stdout);

}
