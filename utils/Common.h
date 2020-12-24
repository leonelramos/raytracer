#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

#include "Ray.h"
#include "Vec3f.h"

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;

inline float DegreesToRadians(float degrees) {
    return degrees * pi / 180.0f;
}

inline float Clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline float Random() { return (Clamp(rand() - 1, 0, RAND_MAX - 1))/(RAND_MAX); }

inline float RandomRange(const float &min, const float &max)
{
    return min + Random() * (max - min);
}

#endif