#ifndef COMPONENTS_FRAME_H_
#define COMPONENTS_FRAME_H_

#include "components/pixel.h"

#include <array>
#include <string>
#include <vector>

namespace taeto
{

class Frame
{
    private:

        // Frame dimensions
        unsigned long int width;
        unsigned long int height;

        // Pixels that frame is made up of
        // No longer vector of vectors of Pixels, now shared_ptr to pixels
        std::vector<std::vector<Pixel>> pixels;

        // Setup vector
        void init_pixels();

    public:

        Frame();

        Frame(unsigned long int, unsigned long int);

        Frame(std::vector<std::vector<Pixel>>);

        // Destructor
        ~Frame();

        // Getters and setters
        Pixel& get_pixel(long int, long int);

        long unsigned int get_width();

        long unsigned int get_height();

        void set_pixel(long int, long int, Pixel);

        void set_width(unsigned long int);

        void set_height(unsigned long int);

        // Set just the characters of single pixel in frame
        void set_char(unsigned long int, unsigned long int, char);

        // Set just the characters of all pixels in frame
        void set_chars(std::vector<std::string>);

        // Set just the foreground colors of all pixels in frame
        void set_foreground_colors(std::vector<std::vector<Color>>);

        // Set just the foreground color of single pixel in frame
        void set_foreground_color(unsigned long int, unsigned long int, Color);

        // Set just the background colors of all pixels in frame
        void set_background_colors(std::vector<std::vector<Color>>);

        // Set just the background color of single pixel in frame
        void set_background_color(unsigned long int, unsigned long int, Color);

        // Set just the bold parameter of all pixels in frame
        void set_bolds(std::vector<std::vector<bool>>);

        // Set just the bold parameter of single pixel in frame
        void set_bold(unsigned long int, unsigned long int, bool);

        // Set just the normal vector parameter of all pixels in frame
        void set_normals(std::vector<std::vector<Vector>>); // I'm going to kill myself

        // Set just the normal vector parameter of single pixel in frame
        void set_normal(unsigned long int, unsigned long int, Vector);

        // Helper methods

        // Write string to given location in frame
        void add_string(long int, long int, std::string);

        // Export to string
        std::string serialize();

        // Maps frame onto this frame wherever current frame has the given character
        void map(Frame f, char c);
};

}   // namespace taeto

#endif  // COMPONENTS_FRAME_H_
