#include "tools.hpp"

#include <chrono>

#include <glm/glm.hpp>

namespace taeto
{

std::chrono::milliseconds ms_since_epoch()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
}

double smoothstep(double x, double edge0, double edge1)
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

// Used for mixing colors with transparency
glm::vec4 mix_colors(glm::vec4 dest_color, glm::vec4 src_color)
{
    float alpha = src_color.a > 1.0f ? 1.0f : src_color.a;
    alpha = alpha < 0.0f ? 0.0f : alpha;

    glm::vec4 ret;
    ret.r = src_color.r * alpha + dest_color.r * (1.0f - alpha);
    ret.g = src_color.g * alpha + dest_color.g * (1.0f - alpha);
    ret.b = src_color.b * alpha + dest_color.b * (1.0f - alpha);
    ret.a = alpha;
    return ret;
}

int modulo(int a, int b)
{
    int result = a % b;
    if (result < 0)
        result += b;
    return result;
}

}   // namespace taeto
