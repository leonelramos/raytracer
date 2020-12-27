#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Hittable.h"
#include "Lambertian.h"

class Sphere : public Hittable
{
public:
    Sphere()
        : center(Point3(0,0,0)), radius(1) {}
    Sphere(Point3 center) 
        : center(center), radius(1) {}
    Sphere(Point3 center, double radius) 
        : center(center), radius(radius) {}
    Sphere(Point3 center, std::shared_ptr<Material> material) 
        : center(center), radius(1), material(material) {}
    Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
        : center(center), radius(radius), material(material) {}

    virtual bool Hit(const Ray &ray, const double &min_t, const double &max_t) override;

    Point3 GetCenter() const { return center; }
    double GetRadius() const { return radius; }
private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> material;
};

bool Sphere::Hit(const Ray &ray, const double &min_t, const double &max_t)
{
    Point3 orig = ray.GetOrigin();
    Vec3 dir = ray.GetDirection();
    double a  = Dot(dir, dir);
    double half_b = Dot(dir, orig - center);
    double c = Dot(orig - center, orig - center) - radius * radius;

    double discriminant = half_b * half_b - a*c;
    if(discriminant < 0) return false;
    double t0 = (-half_b - sqrt(discriminant))/a;
    double t1 = (-half_b + sqrt(discriminant))/a;
    if(t0 < min_t || t0 > max_t) t0 = t1;
    if(t0 < min_t || t0 > max_t) return false;

    hit = {ray.At(t0), t0};
    Vec3 outward_normal = (hit.point - center)/radius;
    hit.SetFaceNormal(ray, outward_normal);
    hit.material = material;
    double u = outward_normal.x / 2.0 + 0.5;
    double v = outward_normal.y / 2.0 + 0.5;
    hit.tex_coords = TexCoord(u, v);
    return true;
}

#endif