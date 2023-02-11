#ifndef COMPONENTS_OBJECT_OBJECT_H_
#define COMPONENTS_OBJECT_I_SPRITE_H_

namespace taeto
{

class ISprite
{
    // Renderable sprite dimensions
    unsigned int height_;
    unsigned int width_;

    // Renderable settings
    bool respect_light_sources_;
    bool use_normal_mapping_;
}

}   // namespace taeto

#endif COMPONENTS_OBJECT_I_SPRITE_H_
