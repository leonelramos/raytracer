#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3f.h"
#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere() : center(Point3f(0,0,0)), radius(1) {}
    Sphere(Point3f center) : center(center), radius(1) {}
    Sphere(Point3f center, float radius) : center(center), radius(radius) {}

    virtual bool Hit(const Ray &ray, const float &min_t, const float &max_t) override;

    Point3f GetCenter() const { return center; }
    float GetRadius() const { return radius; }
private:
    Point3f center;
    float radius;
};

bool Sphere::Hit(const Ray &ray, const float &min_t, const float &max_t)
{
    Point3f orig = ray.GetOrigin();
    Vec3f dir = ray.GetDirection();
    float a  = Dot(dir, dir);
    float half_b = Dot(dir, orig - center);
    float c = Dot(orig - center, orig - center) - radius * radius;

    float discriminant = half_b * half_b - a*c;
    if(discriminant < 0) return false;
    float t0 = (-half_b - sqrt(discriminant))/a;
    float t1 = (-half_b + sqrt(discriminant))/a;
    if(t0 < min_t || t0 > max_t) t0 = t1;
    if(t0 < min_t || t0 > max_t) return false;

    hit = {ray.At(t0), t0};
    Vec3f outward_normal = (hit.point - center)/radius;
    hit.SetFaceNormal(ray, outward_normal);
    return true;
}

#endif