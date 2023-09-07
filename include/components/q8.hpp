#ifndef COMPONENTS_Q8_HPP_
#define COMPONENTS_Q8_HPP_

namespace taeto
{

class Q8
{
public:
    Q8();
    ~Q8();

    Q8 operator+(const Q8& q);
    Q8 operator-(const Q8& q);
    Q8 operator*(const Q8& q);
    Q8 operator/(const Q8& q);

    Q8& operator+=(const Q8& q);
    Q8& operator-=(const Q8& q);
    Q8& operator*=(const Q8& q);
    Q8& operator/=(const Q8& q);

    bool operator==(const Q8& q);
    bool operator!=(const Q8& q);
    bool operator>(const Q8& q);
    bool operator<(const Q8& q);
    bool operator>=(const Q8& q);
    bool operator<=(const Q8& q);

    static Q8 from_bits(uint8_t bits);
    static Q8 from_int(int val);
    static Q8 from_float(double val);

private:
    uint8_t saturate(uint16_t x);

    uint8_t val_;
}

}   // namespace taeto
