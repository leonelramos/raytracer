#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "Ray.h"

class Camera
{
public:
        Camera(
            const Point3 &position,
            const Point3 &look_at,
            const Vec3 &world_up,
            const double v_fov, 
            const double aspect_ratio,
            const double aperture,
            const double depth_of_field
            )
        {
            auto radians = DegreesToRadians(v_fov);
            auto viewport_height = 2 * tan(radians/2);
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            look_direction = Normalized(position - look_at);
            horizontal_axis = Cross(world_up, look_direction);
            up_axis = Cross(look_direction, horizontal_axis);

            origin = position;
            horizontal = depth_of_field * viewport_width * horizontal_axis;
            vertical = depth_of_field * viewport_height * up_axis;
            Point3 focus_offset = look_direction * depth_of_field * focal_length;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_offset;

            lens_radius = aperture / 2.0;
        }

        Ray GetRay(double u, double v) const {
            Point3 rand_in_radius = lens_radius * RandomInUnitDisk();
            Vec3 offset = rand_in_radius.x * horizontal_axis + rand_in_radius.y * up_axis;
            Point3 center_of_attention = lower_left_corner + u*horizontal + v*vertical;
            return Ray(
                origin + offset, 
                center_of_attention - origin - offset
                );
        }

    private:
        Point3 origin;
        Point3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 look_direction;
        Vec3 horizontal_axis;
        Vec3 up_axis;
        double lens_radius;
};

#endif