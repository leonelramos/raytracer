#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <fstream>

class PPM
{
public:
    PPM() 
        : width(500), height(500), max_intensity(255), 
        image_buffer(new int[500*500*3]) {}

    PPM(int width, int height, int max_intensity) 
        : width(width), height(height), 
        max_intensity(max_intensity), 
        image_buffer(new int[width*height*3]) {}
        
    PPM(int width, double aspect_ratio, int max_intensity) 
        : width(width), height(static_cast<int>(width/aspect_ratio)), 
        max_intensity(max_intensity), 
        image_buffer(new int[width*height*3]) {}

    bool operator<<(const int intensity)
    {
        if(filled > width * height * 3 - 1) return false;
        image_buffer[filled] = intensity;
        filled++;
        return true;
    }

    void Print()
    {
        printf("W: %d, H: %d, I: %d\n", width, height, max_intensity);
        printf("pixel count: %d\n", filled/3);
        printf("image data:\n");
        for(auto i = 0; i+2 < filled; i+=3)
        {
            int r = image_buffer[i];
            int g = image_buffer[i+1];
            int b = image_buffer[i+2];
            
            printf("r: %d, g: %d, b: %d\n", r, g, b);
        }
    }

    bool SaveImage(const char *filename)
    {
        std::ofstream image;
        image.open(filename);
        if((image.rdstate() && std::ofstream::failbit) != 0)
        {
            printf("Error opening %s\n", filename);
            return false;
        }
        image << "P3\n" << width << " " << height << "\n255\n";
        for(auto i = 0; i+2 < filled; i+=3)
        {
            int r = image_buffer[i];
            int g = image_buffer[i+1];
            int b = image_buffer[i+2];
            image << r << ' ' << g << ' ' << b << '\n';
        }
        image.close();
        return true;
    }

    ~PPM()
    {
        image_buffer = nullptr;
        delete image_buffer;
    }

public:
    int width, height, max_intensity, filled = 0;
    int *image_buffer;
};

using Image = PPM;

#endif