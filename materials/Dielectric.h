#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectric : public Material
{
public:
    Dielectric() 
        : ir(1.0) {}
    Dielectric(const double &index_of_refraction)
        : ir(index_of_refraction) {}

    virtual bool Scatter(const Ray &ray, HitRecord &hit) override;
private:
    static double Reflectance(double cosine, double ref_idx) {
        // Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }

    double ir;
};

bool Dielectric::Scatter(const Ray &ray, HitRecord &hit)
{
    double refraction_ratio = hit.front_face ? (1.0/ir) : ir;
    Vec3 unit_incident = Normalized(ray.GetDirection());

    auto cos_incidence = fmin(Dot(-unit_incident, hit.normal), 1.0);
    auto sin_incidence = sqrt(1.0 - cos_incidence * cos_incidence);

    bool can_refract = refraction_ratio * sin_incidence <= 1.0;
    Vec3 direction;
    if(can_refract && Reflectance(cos_incidence, refraction_ratio) < Random())
        direction = Refract(unit_incident, hit.normal, refraction_ratio);
    else
        direction = Reflect(unit_incident, hit.normal);
    attenuation = RGB(1.0);
    scattered_ray = Ray(hit.point + (direction * 1.e-4), direction);
    return true;
}


#endif