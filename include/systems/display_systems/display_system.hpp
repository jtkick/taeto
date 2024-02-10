#ifndef SYSTEMS_DISPLAY_SYSTEMS_DISPLAY_SYSTEM_HPP_
#define SYSTEMS_DISPLAY_SYSTEMS_DISPLAY_SYSTEM_HPP_

#include "frames/display_pixel_frame.hpp"
#include "systems/system.hpp"

namespace taeto
{

class DisplaySystem: public System
{
public:
    DisplaySystem() { };

    ~DisplaySystem() { };

    virtual void display_frame(taeto::DisplayPixelFrame&) = 0;
};

}   // namespace taeto

#endif  // SYSTEMS_DISPLAY_SYSTEMS_DISPLAY_SYSTEM_HPP_
