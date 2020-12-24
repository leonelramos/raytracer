#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

struct HitRecord 
{
public:
    Point3f point;
    float t;
    Vec3f normal;
    bool front_face;

    inline void SetFaceNormal(const Ray &ray, const Vec3f &outward_normal)
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
        return *this;
    }
};

class Hittable 
{
public:
    virtual bool Hit(const Ray &ray, const float &min_t, const float &max_t) = 0;
    virtual HitRecord GetHit() const { return hit; };
protected:
    HitRecord hit;
};

#endif