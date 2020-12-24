#include "PPM.h"
#include "Sphere.h"
#include "Common.h"
#include "HittableList.h"
#include "Camera.h"

RGB RayGradient(const Ray &r);

int main(void)
{
    const float aspect_ratio = 16.0 / 9.0;
    const int image_width = 500;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    float strata_length = image_width / 10.0f;
    float num_strata = 10 * image_height / strata_length;
    const int samples_per_strata = 100;
    const int samples_per_pixel = 25;

    Camera camera;

    Image test_img(image_width, image_height);
    const char *filename = "./testing123.ppm";
    
    HittableList world;
    world.Add(std::make_shared<Sphere>(Point3f(0,0,-1), 0.5f));
    world.Add(std::make_shared<Sphere>(Point3f(0,-100.5,-1), 100));

    for(auto i = image_height - 1; i >= 0; i--)
    {
        for(auto j = 0; j <  image_width; j++)
        {
            RGB pixel_color(0);
            for(int s = 0; s < samples_per_pixel; s++)
            {
                float u = (j + Random())/(image_width - 1);
                float v = (i + Random())/(image_height - 1);
                Ray ray = camera.GetRay(u, v);
                if(world.Hit(ray, 0, infinity))
                {
                    HitRecord hit = world.GetHit();
                    RGB normal_color = 0.5f * (hit.normal + 1.0f);
                    pixel_color += normal_color;
                }
                else
                {
                    pixel_color += RayGradient(ray);
                }
            }
            pixel_color /= samples_per_pixel;
            test_img << static_cast<int>(255.99f * pixel_color.r);
            test_img << static_cast<int>(255.99f * pixel_color.g);
            test_img << static_cast<int>(255.99f * pixel_color.b);
        }
    }

    test_img.SaveImage(filename);
    test_img.~Image();
    return 0;
}

RGB RayGradient(const Ray &ray)
{
    float t = 0.5f * (Normalized(ray.GetDirection()).y + 1.0f);
    return Lerp(RGB(1.0f, 1.0f, 1.0f), RGB(0.5f, 0.7f, 1.0f), t);
}

void TestImage()
{
    Image test_img(500,200);
    const char *filename = "./testing123.ppm";

    for (int j = test_img.height-1; j >= 0; j--) {
        for (int i = 0; i < test_img.width; i++) {
            auto r = double(i) / (test_img.width-1);
            auto g = double(j) / (test_img.height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);
            test_img << ir;
            test_img << ig;
            test_img << ib;
        }
    }
    test_img.Print();
    test_img.SaveImage(filename);
    test_img.~Image();
}