#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <fstream>


using namespace std;

class ppm {
    public:
        ppm() : width(500), height(500), max_intensity(255), image_buffer(new int[500*500*3]) {}
        ppm(int width, int height) : 
            width(width), height(height), max_intensity(255), image_buffer(new int[width*height*3]) {}
        ppm(int width, int height, float max_intensity) :
            width(width), 
            height(height), 
            max_intensity(max_intensity), 
            image_buffer(new int[width*height*3]) {}

        void PrintParams()
        {
            printf("W: %d, H: %d, I: %3.2f\n", width, height, max_intensity);
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

        bool operator<<(const int intensity)
        {
            if(filled > width * height * 3 - 1) return false;
            cout << intensity << endl;
            image_buffer[filled++] = intensity;
            return true;
        }

        bool SaveImage(const char *filename)
        {
            ofstream image;
            image.open(filename);
            if((image.rdstate() && ofstream::failbit) != 0)
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

        ~ppm(){
            image_buffer = NULL;
            delete image_buffer;
        }

    public:
        int width, height, filled = 0;
        float max_intensity;
        int *image_buffer;
};

using Image = ppm;



#endif