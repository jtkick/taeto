#ifndef PRE_LIGHTING_PASS_FRAME_H
#define PRE_LIGHTING_PASS_FRAME_H

#include "frame.h"
#include "Pixel.h"

#include <vector>

// This is a Pixel with additional information to hold onto that is needed for
// rendering the lighting after the Pixel has been rendered.
struct PreLightingPassPixel
{
    Pixel pixel = Pixel();
    long long int z_pos = 0;
    long long int y_pos = 0;
    long long int x_pos = 0;
    unsigned long long int light_tags = 0;

    // void operator = (const PreLightingPassPixel &p);
};

// void PreLightingPassPixel::operator = (const PreLightingPassPixel &p)
// {
//     pixel = p.pixel;
//     z_pos = p.z_pos;
//     y_pos = p.y_pos;
//     x_pos = p.x_pos;
//     light_tags = p.light_tags;
// };


class PreLightingPassFrame : public NewFrame
{
    private:

        // Values that frame is made up of
        std::vector<std::vector<std::vector<PreLightingPassPixel>>> values;

    public:

        // Constructors
        PreLightingPassFrame();

        PreLightingPassFrame(unsigned long int, unsigned long int, int);

        // Destructor
        ~PreLightingPassFrame();

        std::vector<PreLightingPassPixel>& at(long int y, long int x);

        // Export to string
        std::string serialize();
};

#endif
