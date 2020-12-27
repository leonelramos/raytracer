#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material
{
public:
    Lambertian() : albedo(RGB(.5, .5, .5)) {}
    Lambertian(const RGB &albedo) : albedo(albedo) {}
    Lambertian(const RGB &albedo, 
        std::shared_ptr<Texture> in_texture,
        RGB in_primary_color,
        RGB in_secondary_color
    ) 
        : albedo(albedo)
        {
            texture = in_texture;
            primary_color = in_primary_color;
            secondary_color = in_secondary_color;
            using_texture = true;
        }
    virtual bool Scatter(const Ray &ray, HitRecord &hit) override;
private:
    RGB albedo;
};

bool Lambertian::Scatter(const Ray &ray, HitRecord &hit)
{
    Vec3 scattered_direction = hit.normal + RandUnitVec3();
    if(NearZero(scattered_direction)) scattered_direction = hit.normal;
    scattered_ray = Ray(hit.point, scattered_direction);
    attenuation = albedo;
    return true;
}

#endif