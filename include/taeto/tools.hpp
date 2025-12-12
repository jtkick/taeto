#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <chrono>

#include <glm/glm.hpp>

namespace taeto
{
    
/**
 * Returns number of milliseconds since UNIX epoch.
 *
 * @returns Number of milliseconds since UNIX epoch.
 */
std::chrono::milliseconds ms_since_epoch();

/**
 * Calculates smoothstep value.
 */
double smoothstep(double x, double edge0 = 0.0f, double edge1 = 1.0f);


glm::vec4 mix_colors(glm::vec4 dest_color, glm::vec4 src_color);

int modulo(int a, int b);

class Timer
{
public:
    Timer() : time_(ms_since_epoch().count()) { };

    ~Timer() { };

    unsigned int reset();

    unsigned int time();

private:
    unsigned int time_;
};

}   // namespace taeto

#endif  // TOOLS_HPP_
