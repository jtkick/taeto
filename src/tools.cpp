#include "tools.hpp"

#include <chrono>

namespace taeto
{

std::chrono::milliseconds ms_since_epoch()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
}

double smoothstep(double x, double edge0 = 0.0f, double edge1 = 1.0f)
{
    auto clamp = [](float x, float ll = 0.0f, float ul = 1.0f)
    {
        if (x < ll) return ll;
        if (x > ul) return ul;
        return x;
    };

    x = clamp((x - edge0) / (edge1 - edge0));
    return x * x * (3.0f - 2.0f * x);
}


}   // namespace taeto