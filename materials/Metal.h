#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material
{
public:
    Metal() 
        : albedo(RGB(.5, .5, .5)), 
        reflection_fuzz(0) {}
    Metal(const RGB &albedo, const double &reflection_fuzz) 
        : albedo(albedo), 
        reflection_fuzz(reflection_fuzz) {}
    virtual bool Scatter(const Ray &ray, HitRecord &hit)
    {
        Vec3 reflect_direction = Reflect(Normalized(ray.GetDirection()), hit.normal);
        scattered_ray = Ray(hit.point, reflect_direction + reflection_fuzz * RandVec3InUnitSphere());
        attenuation = albedo;
        return Dot(hit.normal, reflect_direction) > 0;   
    }
private:
    RGB albedo;
    double reflection_fuzz;
};

#endif