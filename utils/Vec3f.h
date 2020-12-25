#ifndef VEC3_F_H
#define VEC3_F_H

#include <cmath>
#include <ostream>

#include "Common.h"

class Vec3f
{
public:
    Vec3f(): x(0), y(0), z(0) {}
    Vec3f(float s): x(s), y(s), z(s){}
    Vec3f(float x, float y, float z): x(x), y(y), z(z) {}
    Vec3f operator - () const { return Vec3f(-x, -y, -z); }
    Vec3f& operator += (const Vec3f &v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vec3f& operator += (const float &s) { x += s, y += s, z += s; return *this; }
    Vec3f& operator -= (const Vec3f &v) { x -= v.x, y -= v.y, z -= v.z; return *this; }
    Vec3f& operator -= (const float &s) { x -= s, y -= s, z -= s; return *this; }
    Vec3f& operator *= (const Vec3f &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vec3f& operator *= (const float &s) { x *= s, y *= s, z *= s; return *this; }
    Vec3f& operator /= (const Vec3f &v) { x /= v.x, y /= v.y, z /= v.z; return *this; }
    Vec3f& operator /= (const float &s) { x /= s, y /= s, z /= s; return *this; }
    Vec3f& operator = (const Vec3f &v) { x = v.x, y = v.y, z = v.z; return *this; }

    inline float Length() const { return std::sqrt(Length2()); } 
    inline float Length2() const { return x * x + y * y + z * z; }

public:
    float x, y, z;
    float &r = x;
    float &g = y;
    float &b = z;
};

inline std::ostream& operator<<(std::ostream &out, const Vec3f &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3f operator+(const Vec3f &v0, const Vec3f &v1) {
    return Vec3f(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

inline Vec3f operator-(const Vec3f &v0, const Vec3f &v1) {
    return Vec3f(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

inline Vec3f operator*(const Vec3f &v0, const Vec3f &v1) {
    return Vec3f(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}

inline Vec3f operator*(float t, const Vec3f &v) {
    return Vec3f(t*v.x, t*v.y, t*v.z);
}

inline Vec3f operator*(const Vec3f &v, float t) {
    return t * v;
}

inline Vec3f operator/(Vec3f v, float t) {
    return (1/t) * v;
}

inline float Magnitude2(const Vec3f &v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline float Magnitude(const Vec3f &v)
{
    float mag2 = Magnitude2(v);
    return std::sqrt(mag2);
}

inline float Distance2(const Vec3f &v0, const Vec3f &v1)
{
    return std::pow(v1.x - v0.x, 2) + std::pow(v1.y - v0.y, 2) + std::pow(v1.z - v0.z, 2);
}

inline float Distance(const Vec3f &v0, const Vec3f &v1)
{
    return std::sqrt(Distance2(v0, v1));
}

inline Vec3f Normalized(const Vec3f &v)
{
    float mag = Magnitude(v);
    if(mag > 0) return v / mag;
    return v;
}

inline float Dot(const Vec3f &v0, const Vec3f &v1)
{
    return v1.x * v0.x + v1.y * v0.y + v1.z * v0.z;
}

inline Vec3f Cross(const Vec3f &v0, const Vec3f &v1)
{
    return Vec3f(
        v0.y * v1.z - v0.z * v1.y,
        v0.z * v1.x - v0.x * v1.z,
        v0.x * v1.y - v0.y * v1.x
    );
}

inline Vec3f Lerp(const Vec3f &v0, const Vec3f &v1, float t)
{
    return (1-t) * v0 + t * v1;
}

inline Vec3f RandVec3()
{
    return Vec3f(
        Random(),
        Random(),
        Random()
    );
}

using RGB = Vec3f;
using Point3f = Vec3f;

#endif