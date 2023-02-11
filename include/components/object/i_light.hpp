#ifndef COMPONENTS_OBJECT_I_LIGHT_H_
#define COMPONENTS_OBJECT_I_LIGHT_H_

namespace taeto
{

class ILight
{
public:
    virtual taeto::Vector get_vector(long int, long int, long int);

    virtual taeto::Color get_color(long int, long int, long int);
}

}   // namespace taeto

#endif  // COMPONENTS_OBJECT_I_LIGHT_H_
