#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
    public:
        Ray(const Point3& origin, const Vec3& direction)
            : origin(origin), direction(direction) {}

        inline Point3 At(double t) const { return origin + t*direction; }
        inline Point3 GetOrigin() const { return origin; }
        inline Vec3 GetDirection() const { return direction; }

    private:
        Point3 origin;
        Vec3 direction;
};

#endif