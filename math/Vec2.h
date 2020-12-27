#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <ostream>

#include "Common.h"

class Vec2
{
public:
    Vec2()
        : x(0), y(0) {}
    Vec2(double s)
        : x(s), y(s) {}
    Vec2(double x, double y)
        : x(x), y(y) {}

    Vec2 operator - () const { return Vec2(-x, -y); }
    Vec2& operator += (const Vec2 &v) { x += v.x, y += v.y; return *this; }
    Vec2& operator += (const double &s) { x += s, y += s; return *this; }
    Vec2& operator -= (const Vec2 &v) { x -= v.x, y -= v.y; return *this; }
    Vec2& operator -= (const double &s) { x -= s, y -= s; return *this; }
    Vec2& operator *= (const Vec2 &v) { x *= v.x, y *= v.y; return *this; }
    Vec2& operator *= (const double &s) { x *= s, y *= s; return *this; }
    Vec2& operator /= (const Vec2 &v) { x /= v.x, y /= v.y; return *this; }
    Vec2& operator /= (const double &s) { x /= s, y /= s; return *this; }
    Vec2& operator = (const Vec2 &v) { x = v.x, y = v.y; return *this; }

    inline double Length() const { return std::sqrt(Length2()); } 
    inline double Length2() const { return x * x + y * y; }

public:
    double x, y;
    double &u = x;
    double &v = y;
};

inline std::ostream& operator<<(std::ostream &out, const Vec2 &v) {
    return out << v.x << ' ' << v.y;
}

inline Vec2 operator+(const Vec2 &v0, const Vec2 &v1) {
    return Vec2(v0.x + v1.x, v0.y + v1.y);
}

inline Vec2 operator-(const Vec2 &v0, const Vec2 &v1) {
    return Vec2(v0.x - v1.x, v0.y - v1.y);
}

inline Vec2 operator*(const Vec2 &v0, const Vec2 &v1) {
    return Vec2(v0.x * v1.x, v0.y * v1.y);
}

inline Vec2 operator*(double t, const Vec2 &v) {
    return Vec2(t*v.x, t*v.y);
}

inline Vec2 operator*(const Vec2 &v, double t) {
    return t * v;
}

inline Vec2 operator/(Vec2 v, double t) {
    return (1/t) * v;
}

inline bool operator==(const Vec2 &v1, const Vec2 &v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

inline double Magnitude2(const Vec2 &v)
{
    return v.x * v.x + v.y * v.y;
}

inline double Magnitude(const Vec2 &v)
{
    double mag2 = Magnitude2(v);
    return std::sqrt(mag2);
}

inline double Distance2(const Vec2 &v0, const Vec2 &v1)
{
    return std::pow(v1.x - v0.x, 2) + std::pow(v1.y - v0.y, 2);
}

inline double Distance(const Vec2 &v0, const Vec2 &v1)
{
    return std::sqrt(Distance2(v0, v1));
}

inline Vec2 Normalized(const Vec2 &v)
{
    double mag = Magnitude(v);
    if(mag > 0) return v / mag;
    return v;
}

inline double Dot(const Vec2 &v0, const Vec2 &v1)
{
    return v1.x * v0.x + v1.y * v0.y;
}

inline Vec2 Lerp(const Vec2 &v0, const Vec2 &v1, double t)
{
    return (1-t) * v0 + t * v1;
}

inline Vec2 Mix(const Vec2 &v0, const Vec2 &v1, double t)
{
    return Lerp(v0, v1, t);
}

inline Vec2 RandVec2()
{
    return Vec2(
        RandomRange(-1, 1),
        RandomRange(-1, 1)
    );
}

inline Vec2 RandVec2InUnitCircle()
{
    while(true)
    {
        double kill_probability = 0;
        Vec2 candidate = RandVec2();
        double score = Random();
        if(candidate.Length2() > 1 || score < kill_probability) continue;
        else return candidate;
    }
}

inline Vec2 RandUnitVec2()
{
    return Normalized(RandVec2InUnitCircle());
}

inline bool NearZero(const Vec2 &v)
{
    const auto tolerance = 1e-8;
    return fabs(v.x) < tolerance && fabs(v.y) < tolerance;
}

inline Vec2 Reflect(const Vec2 &incident, const Vec2 &normal)
{
    return incident - 2*Dot(incident, normal)*normal;
}

inline Vec2 Refract(const Vec2 &incident, const Vec2 &normal, double refraction_ratio)
{
    auto cos_incidence = fmin(Dot(-incident, normal), 1.0);
    Vec2 refracted_rejection = refraction_ratio * (incident + (cos_incidence * normal));
    Vec2 refracted_projection = -sqrt(fabs(1.0 - refracted_rejection.Length2())) * normal;
    return refracted_projection + refracted_rejection;
}

using TexCoord = Vec2;
using Point2 = Vec2;

#endif