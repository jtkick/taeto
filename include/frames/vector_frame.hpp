#ifndef FRAMES_VECTOR_FRAME_HPP_
#define FRAMES_VECTOR_FRAME_HPP_

#include "components/color.hpp"
#include "frames/frame.hpp"
#include "frames/uchar_frame.hpp"

namespace taeto
{

// Forward includes
class UCharFrame;

class VectorFrame : public Frame<taeto::Vector>
{
public:
    VectorFrame();

    VectorFrame(
        unsigned long int h,
        unsigned long int w,
        taeto::Vector v = {0, 0, 0});

    VectorFrame(std::string path);

    ~VectorFrame() { };

    taeto::UCharFrame x();

    void x(taeto::UCharFrame&);

    taeto::UCharFrame y();

    void y(taeto::UCharFrame&);

    taeto::UCharFrame z();

    void z(taeto::UCharFrame&);
};

}   // namespace taeto

#endif  // FRAMES_VECTOR_FRAME_HPP_
