#ifndef COMPONENTS_OBJECT_I_LIGHT_HPP_
#define COMPONENTS_OBJECT_I_LIGHT_HPP_

namespace taeto
{

class ILight
{
public:
    virtual taeto::Color light_color(uint64_t, uint64_t, uint64_t) = 0;

    virtual taeto::Vector light_vector(uint64_t, uint64_t, uint64_t) = 0;
};

}   // namespace taeto

#endif  // COMPONENTS_OBJECT_I_LIGHT_HPP_
