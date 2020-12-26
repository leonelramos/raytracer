#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <time.h>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double DegreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

inline double Clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double Random() 
{
    return (Clamp(rand() - 1, 0, RAND_MAX - 1))/(RAND_MAX); 
}

inline double RandomRange(const double &min, const double &max)
{
    return min + Random() * (max - min);
}

#endif