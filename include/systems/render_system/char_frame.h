#ifndef CHAR_FRAME_H
#define CHAR_FRAME_H

#include "frame.h"

#include <algorithm>
#include <array>
#include <vector>
#include "lodepng.h"

using namespace std;

class CharFrame : NewFrame
{
    private:

        // Frame dimensions
        unsigned int width;
        unsigned int height;

        // Values that frame is made up of
        vector<vector<uint8_t>> values;

    public:

        // Constructors
        CharFrame();

        CharFrame(unsigned long int, unsigned long int);

        CharFrame(std::vector<std::vector<uint8_t>>);

        CharFrame(std::string);

        // Destructor
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
};

#endif
