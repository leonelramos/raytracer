#ifndef MATERIAL_H
#define MATERIAL_H

#include "Common.h"
#include "Ray.h"
#include "Hittable.h"
#include "Texture.h"

class Material
{
public:
    virtual bool Scatter(const Ray &ray, HitRecord &hit) = 0;
    virtual Ray GetScatteredRay() const { return scattered_ray; }
    virtual RGB GetAttenuation() const { return attenuation; }
    virtual bool UsingTexture() { return using_texture; }

    virtual double GetTextureIntensity(const double u, const double v) const
    {
        return texture->SampleTexture(u, v);
    }
    virtual RGB GetTextureColor(const double u, const double v) const 
    { 
        double t = GetTextureIntensity(u, v);
        return Mix(primary_color, secondary_color, t); 
    }
    
protected:
    Ray scattered_ray = Ray(Vec3(0), Vec3(0));
    RGB attenuation;
    RGB primary_color;
    RGB secondary_color;
    bool using_texture = false;
    std::shared_ptr<Texture> texture;
};

#endif