#ifndef RAY_H
#define RAY_H

#include "Vec3f.h"

class Ray {
    public:
        Ray(const Point3f& origin, const Vec3f& direction)
            : origin(origin), direction(direction)
        {}

        inline Point3f At(float t) const { return origin + t*direction; }
        inline Point3f GetOrigin() const { return origin; }
        inline Vec3f GetDirection() const { return direction; }

    public:
        Point3f origin;
        Vec3f direction;
};

#endif