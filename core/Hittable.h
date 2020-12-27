#ifndef HITTABLE_H
#define HITTABLE_H

#include "Common.h"
#include "Ray.h"
#include "Vec2.h"

class Material;

struct HitRecord 
{
public:
    Point3 point;
    double t;
    Vec3 normal;
    bool front_face;
    TexCoord tex_coords;
    std::shared_ptr<Material> material;

    inline void SetFaceNormal(const Ray &ray, const Vec3 &outward_normal)
    {
        front_face = Dot(ray.GetDirection(), outward_normal) < 0;
        if(!front_face) normal = -outward_normal;
        else normal = outward_normal;
    }

    HitRecord& operator=(const HitRecord &hr)
    { 
        point = hr.point;
        t = hr.t;
        normal = hr.normal;
        front_face = hr.front_face;
        material = hr.material;
        tex_coords = hr.tex_coords;
        return *this;
    }
};

class Hittable 
{
public:
    virtual bool Hit(const Ray &ray, const double &min_t, const double &max_t) = 0;
    virtual HitRecord GetHit() const { return hit; };
protected:
    HitRecord hit;
};

#endif