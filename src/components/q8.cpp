#include "components/q8.hpp"

Q8::Q8()
{
    val_ = 0;
}

Q8::~Q8()
{

}

Q8 Q8::operator+(const Q8& q)
{

}

Q8 Q8::operator-(const Q8& q)
{

}

Q8 Q8::operator*(const Q8& q)
{

}

Q8 Q8::operator/(const Q8& q)
{

}



static Q8 Q8::from_bits(uint8_t bits)
{
    Q8 q(0);
    q.val = bits;
    return q;
}

uint8_t Q8::saturate(uint16_t x)
{
    if (x > 0xFF)
        return 0xFF;
    else if (x < 0x00)
        return 0x00;
    else
        return (uint8_t)x;
}
