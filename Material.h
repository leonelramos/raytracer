#ifndef MATERIAL_H
#define MATERIAL_H

#include "Common.h"
#include "Ray.h"
#include "Hittable.h"

class Material
{
public:
    virtual bool Scatter(const Ray &ray, HitRecord &hit) = 0;
    virtual Ray GetScatteredRay() const { return scattered_ray; }
    virtual RGB GetAttenuation() const { return attenuation; }
protected:
    Ray scattered_ray = Ray(Vec3(0), Vec3(0));
    RGB attenuation;
};

#endif