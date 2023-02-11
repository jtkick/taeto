#ifndef COLOR_FRAME_H
#define COLOR_FRAME_H

#include "Color.h"
#include "frame.h"

#include <algorithm>
#include <array>
#include <vector>
#include "lodepng.h"

using namespace std;

class ColorFrame : NewFrame
{
    private:

        // Frame dimensions
        unsigned int width;
        unsigned int height;

        // Values that frame is made up of
        vector<vector<uint8_t>> values;

    public:

        // Constructors
        ColorFrame();

        ColorFrame(unsigned long int, unsigned long int);

        ColorFrame(std::vector<std::vector<uint8_t>>);

        ColorFrame(std::string);

        // Destructor
        ~ColorFrame();

        uint8_t& at(long int y, long int x);

        unsigned int get_width();

        unsigned int get_height();

        // Helper methods

        // Combine the values of each frame at the given location and return result
        void combine(ColorFrame, unsigned int, unsigned int, bool, bool, bool);

        void print();

        // Export to string
        std::string serialize();

        // Turns frame into a renderable sprite. Mainly for testing
        Sprite to_sprite();
};

#endif
