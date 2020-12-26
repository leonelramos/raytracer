#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <ostream>

#include "Common.h"

class Vec3
{
public:
    Vec3()
        : x(0), y(0), z(0) {}
    Vec3(double s)
        : x(s), y(s), z(s) {}
    Vec3(double x, double y, double z)
        : x(x), y(y), z(z) {}

    Vec3 operator - () const { return Vec3(-x, -y, -z); }
    Vec3& operator += (const Vec3 &v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vec3& operator += (const double &s) { x += s, y += s, z += s; return *this; }
    Vec3& operator -= (const Vec3 &v) { x -= v.x, y -= v.y, z -= v.z; return *this; }
    Vec3& operator -= (const double &s) { x -= s, y -= s, z -= s; return *this; }
    Vec3& operator *= (const Vec3 &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vec3& operator *= (const double &s) { x *= s, y *= s, z *= s; return *this; }
    Vec3& operator /= (const Vec3 &v) { x /= v.x, y /= v.y, z /= v.z; return *this; }
    Vec3& operator /= (const double &s) { x /= s, y /= s, z /= s; return *this; }
    Vec3& operator = (const Vec3 &v) { x = v.x, y = v.y, z = v.z; return *this; }

    inline double Length() const { return std::sqrt(Length2()); } 
    inline double Length2() const { return x * x + y * y + z * z; }

public:
    double x, y, z;
    double &r = x;
    double &g = y;
    double &b = z;
};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3 &v0, const Vec3 &v1) {
    return Vec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

inline Vec3 operator-(const Vec3 &v0, const Vec3 &v1) {
    return Vec3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

inline Vec3 operator*(const Vec3 &v0, const Vec3 &v1) {
    return Vec3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.x, t*v.y, t*v.z);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}

inline bool operator==(const Vec3 &v1, const Vec3 &v2)
{
    return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}

inline double Magnitude2(const Vec3 &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline double Magnitude(const Vec3 &v)
{
    double mag2 = Magnitude2(v);
    return std::sqrt(mag2);
}

inline double Distance2(const Vec3 &v0, const Vec3 &v1)
{
    return std::pow(v1.x - v0.x, 2) + std::pow(v1.y - v0.y, 2) + std::pow(v1.z - v0.z, 2);
}

inline double Distance(const Vec3 &v0, const Vec3 &v1)
{
    return std::sqrt(Distance2(v0, v1));
}

inline Vec3 Normalized(const Vec3 &v)
{
    double mag = Magnitude(v);
    if(mag > 0) return v / mag;
    return v;
}

inline double Dot(const Vec3 &v0, const Vec3 &v1)
{
    return v1.x * v0.x + v1.y * v0.y + v1.z * v0.z;
}

inline Vec3 Cross(const Vec3 &v0, const Vec3 &v1)
{
    return Vec3(
        v0.y * v1.z - v0.z * v1.y,
        v0.z * v1.x - v0.x * v1.z,
        v0.x * v1.y - v0.y * v1.x
    );
}

inline Vec3 Lerp(const Vec3 &v0, const Vec3 &v1, double t)
{
    return (1-t) * v0 + t * v1;
}

inline Vec3 RandVec3()
{
    return Vec3(
        RandomRange(-1, 1),
        RandomRange(-1, 1),
        RandomRange(-1, 1)
    );
}

inline Vec3 RandVec3InUnitSphere()
{
    while(true)
    {
        double kill_probability = 0;
        Vec3 candidate = RandVec3();
        double score = Random();
        if(candidate.Length2() > 1 || score < kill_probability) continue;
        else return candidate;
    }
}

inline Vec3 RandUnitVec3()
{
    return Normalized(RandVec3InUnitSphere());
}

inline bool NearZero(const Vec3 &v)
{
    const auto tolerance = 1e-8;
    return fabs(v.x) < tolerance && fabs(v.y) < tolerance && fabs(v.z) < tolerance;
}

inline Vec3 Reflect(const Vec3 &incident, const Vec3 &normal)
{
    return incident - 2*Dot(incident, normal)*normal;
}

inline Vec3 Refract(const Vec3 &incident, const Vec3 &normal, double refraction_ratio)
{
    auto cos_incidence = fmin(Dot(-incident, normal), 1.0);
    Vec3 refracted_rejection = refraction_ratio * (incident + (cos_incidence * normal));
    Vec3 refracted_projection = -sqrt(fabs(1.0 - refracted_rejection.Length2())) * normal;
    return refracted_projection + refracted_rejection;
}

inline Vec3 RandomInUnitDisk()
{
    while(true)
    {
        Vec3 candidate(RandomRange(-1, 1), RandomRange(-1, 1), 0);
        if(candidate.Length2() > 1) continue;
        return candidate;
    }
}

using RGB = Vec3;
using Point3 = Vec3;

#endif