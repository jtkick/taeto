#include "Engine.h"

#include "Render_Frame_Message.h"

// For getting window size info in UNIX
#include <sys/ioctl.h>
#include <unistd.h>

// Used for scaling angle from between 0 and pi, to between 0 and 255
#define ANGLE_SCALE (255/3.14159265)

Engine::Engine()
{
    cout << "YoOoOoOoOoOoOoOoO!" << endl;

    logger = spdlog::basic_logger_mt("logger", "logs/log.txt");

    // Make sure logger flushes on all error messages
    logger->flush_on(spdlog::level::err);

    logger->info("testing, attention please");
    logger->error("my leg!");
    logger->critical("go get em!");
    logger->debug("i must kermit sudoku");

    render_system = Render_System(logger);
    display_system = Display_System(logger);

    // Create new frame
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    shared_ptr<Frame> new_frame = make_shared<Frame>(size.ws_row, size.ws_col);

    shared_ptr<Render_Frame_Message> rfm = make_shared<Render_Frame_Message>(new_frame);

    render_system.handle_message(rfm);

    shared_ptr<Display_Frame_Message> dfm = make_shared<Display_Frame_Message>(new_frame);

    display_system.handle_message(dfm);

}

Engine::~Engine()
{
    endwin();
}

void Engine::add_sprite(shared_ptr<Sprite> s)
{
    logger->info("Adding sprite");

    // Create sprite update message
    shared_ptr<Sprite_Update_Message> sum = make_shared<Sprite_Update_Message>(s, true, true);

    render_system.handle_message(sum);

    // Purely for testing purposes, remove0
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    shared_ptr<Frame> new_frame = make_shared<Frame>(size.ws_row, size.ws_col);
    shared_ptr<Render_Frame_Message> rfm = make_shared<Render_Frame_Message>(new_frame);
    render_system.handle_message(rfm);
}

void Engine::display_frame(shared_ptr<Frame> f)
{

    unique_ptr<Pixel> current_pixel;

    for (int h = 0; h < f->get_height(); h++)
    {
        // Move to beginning of line
        printf("%c[%d;%df", 0X1B, h, 0);

        for (int w = 0; w < f->get_width(); w++)
        {
            // Get pixel in question
            current_pixel = f->get_pixel(h, w);

            // Write background color
            //const Color* c = current_pixel->get_background_color();
            //printf("\033[48;2;%d;%d;%dm", c->get_red(), c->get_green(), c->get_blue());

            // Write foreground color
            //c = current_pixel->get_foreground_color();
            //printf("\033[38;2;%d;%d;%dm", c->get_red(), c->get_green(), c->get_blue());

            // Write character
            printf("%c", current_pixel->get_char());
        }

    }

    // Flush output
    fflush(stdout);

}
