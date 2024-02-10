#ifndef SHADERS_SHADER_H_
#define SHADERS_SHADER_H_

#include "components/render_pixel.hpp"

namespace taeto
{

class Shader
{
public:
    Shader();

    ~Shader();

    virtual void animate();

    virtual taeto::RenderPixel shade();
};

}   // namespace taeto

#endif  // SHADERS_SHADER_H_
