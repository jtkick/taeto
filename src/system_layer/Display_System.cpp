#include "Display_System.h"

Display_System::Display_System()
{
    // Open alternate terminal screen
    std::cout << "\e[?1049h";
}

Display_System::Display_System(shared_ptr<spdlog::logger> l)
{
    logger = l;

    // Open alternate terminal screen
    std::cout << "\e[?1049h";
}

Display_System::~Display_System()
{
    // Go back to original terminal screen
    std::cout << "\e[?1049l";
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

    logger->error("Frame height: " + std::to_string(frame->get_height()));
    logger->error("Frame width: " + std::to_string(frame->get_width()));

    unique_ptr<Pixel> current_pixel;

    for (int h = 0; h < frame->get_height(); h++)
    {
        // Move to beginning of line
        printf("%c[%d;%df", 0X1B, h, 0);

        for (int w = 0; w < frame->get_width(); w++)
        {
            //logger->error("Current pixel in frame: (" + std::to_string(h) + ", " + std::to_string(w) + ")");
            //logger->flush();

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
