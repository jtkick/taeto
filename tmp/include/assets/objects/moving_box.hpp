#ifndef ASSETS_OBJECTS_MOVING_BOX_H_
#define ASSETS_OBJECTS_MOVING_BOX_H_

#include <memory>

#include "components/render_pixel.hpp"
#include "object/i_physical_object.hpp"
#include "object/i_renderable.hpp"
#include "object/object.hpp"

namespace taeto
{

class MovingBox: public Object, public IRenderable, public IPhysicalObject
{
public:
    MovingBox();

    bool on_collision(std::shared_ptr<taeto::Object>) override;

    void set_color(taeto::Color);

    unsigned long int height() override;

    unsigned long int width() override;

    taeto::RenderPixel& pixel_at(unsigned long int, unsigned long int);

private:
    taeto::RenderPixelFrame current_frame_;
};

}   // namespace taeto

#endif  // ASSETS_OBJECTS_MOVING_BOX_H_
