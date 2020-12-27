#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vec3.h"

inline double Pattern1(double u, double v);

class Texture
{
public:
    Texture() : using_procedural(true) {}
    Texture(bool using_procedural) 
        : using_procedural(using_procedural) {}
    double SampleTexture(double u, double v)
    {
        return Pattern1(u, v);
    }
private:
    bool using_procedural;
};

inline double Pattern1(double u, double v)
{
    double intensity = fabs(fmodf(sin((cos(u)-cos(v)) * 1000) * 5, 1));
    return intensity;
}

#endif