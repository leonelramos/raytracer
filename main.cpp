#include "PPM.h"
#include "Sphere.h"
#include "Common.h"
#include "HittableList.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

RGB RayGradient(const Ray &r);
RGB HitColor(const Ray &ray, Hittable &world, const double max_depth);

int main(void)
{
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 650;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 200;
    const int samples_per_strata = samples_per_pixel / 4;
    double max_depth = 50;
    
    const Point3 camera_position(-1,1.5,0);
    const Point3 center_of_attention(0,0,-1);
    const Vec3 world_up(0,1,0);
    const double vertical_fov = 90.0;
    const double aperture = 0.25;
    const double depth_of_field = (center_of_attention - camera_position).Length();
    Camera camera(
        camera_position, 
        center_of_attention, 
        world_up, vertical_fov, 
        aspect_ratio,
        aperture,
        depth_of_field
        );
    Image test_img(image_width, image_height, 255);
    const char *filename = "out.ppm";
    
    HittableList world;
    auto texture_ground = std::make_shared<Texture>();
    RGB ground_color(0.8, 0.1, 0.4);
    auto material_ground = std::make_shared<Lambertian>(ground_color, texture_ground, ground_color, ground_color / 2.0);
    auto material_diffuse = std::make_shared<Lambertian>(RGB(52, 201, 235)/255.0);
    auto material_center = std::make_shared<Dielectric>(1.5);
    //auto material_left   = std::make_shared<Dielectric>(1.5);
    auto material_right  = std::make_shared<Metal>(RGB(0.8, 0.6, 0.2), 0.1);

    // auto material_ground = std::make_shared<Lambertian>(RGB(0.8, 0.8, 0.0));
    // auto material_center = std::make_shared<Lambertian>(RGB(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(RGB(0.8, 0.8, 0.8), 0);
    // auto material_right  = std::make_shared<Metal>(RGB(0.8, 0.6, 0.2), 0);

    world.Add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.Add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.5),   0.5, material_center));
    world.Add(std::make_shared<Sphere>(Point3( 0.0,    0.0, 0),   0.5, material_diffuse));
    //world.Add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.Add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  -0.4, material_center));
    world.Add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  0.5, material_center));
    world.Add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.6, material_right));

    bool with_strata = true;
    for(auto i = image_height - 1; i >= 0; i--)
    {
        std::cout << "row: " << image_height - i << " of " << image_height << std::endl;
        for(auto j = 0; j <  image_width; j++)
        {
            RGB pixel_color(0);
            for(int s = 0; s < samples_per_pixel; s++)
            {
                const double curr_strata = s / samples_per_strata; 
                double random_u_offset;
                double random_v_offset;
                if( curr_strata < 1)
                {
                    random_u_offset = RandomRange(-1, 0);
                    random_v_offset = RandomRange(0, 1);
                }
                else if(curr_strata < 2)
                {
                    random_u_offset = RandomRange(0, 1);
                    random_v_offset = RandomRange(0, 1);
                }
                else if(curr_strata < 3)
                {
                    random_u_offset = RandomRange(0, 1);
                    random_v_offset = RandomRange(-1, 0);
                }
                else
                {
                    random_u_offset = RandomRange(-1, 0);
                    random_v_offset = RandomRange(-1, 0);
                }
                double u = (j + (with_strata ? random_u_offset : RandomRange(-1, 1)))/(image_width - 1);
                double v = (i + (with_strata ? random_v_offset : RandomRange(-1, 1)))/(image_height - 1);
                u = Clamp(u, 0, 1);
                v = Clamp(v, 0, 1);
                const Ray ray = camera.GetRay(u, v);
                pixel_color += HitColor(ray, world, max_depth);
            }
            pixel_color /= samples_per_pixel;
            test_img << static_cast<int>(256 * Clamp(std::sqrt(pixel_color.r), 0.0, 0.999));
            test_img << static_cast<int>(256 * Clamp(std::sqrt(pixel_color.g), 0.0, 0.999));
            test_img << static_cast<int>(256 * Clamp(std::sqrt(pixel_color.b), 0.0, 0.999));
        }
    }
    test_img.SaveImage(filename);
    test_img.~Image();
    return 0;
}

RGB HitColor(const Ray &ray, Hittable &world, const double max_depth)
{
    if(max_depth == 0) return Vec3(0);
    if(world.Hit(ray, 0.001, infinity))
    {
        HitRecord hit = world.GetHit();
        std::shared_ptr<Material> mat = hit.material;
        if(mat->Scatter(ray, hit))
        {
            double texture_intensity = 1.0;
            if(mat->UsingTexture()) 
                texture_intensity = mat->GetTextureIntensity(hit.tex_coords.u, hit.tex_coords.v);
            if(texture_intensity <= 0) std::cout << texture_intensity << std::endl;
            
            return mat->GetAttenuation() * texture_intensity * HitColor(mat->GetScatteredRay(), world, max_depth - 1);
        } 
        return RGB(0);
    }
    return RayGradient(ray);
}

RGB RayGradient(const Ray &ray)
{
    double t = 0.5 * (Normalized(ray.GetDirection()).y + 1.0);
    return Lerp(RGB(1.0, 1.0, 1.0), RGB(0.5, 0.7, 1.0), t);
}

void TestImage()
{
    Image test_img(500,500,255);
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