#ifndef COMPONENTS_OBJECT_I_LIGHT_H_
#define COMPONENTS_OBJECT_I_LIGHT_H_

namespace taeto
{

class ILight
{
public:
    virtual taeto::Color light_color(
        unsigned long int, unsigned long int, unsigned long int);

    virtual taeto::Vector light_vector(
        unsigned long int, unsigned long int, unsigned long int);
};

}   // namespace taeto

#endif  // COMPONENTS_OBJECT_I_LIGHT_H_
