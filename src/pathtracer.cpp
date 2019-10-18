#include "pathtracer.h"
PathTracer::PathTracer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->camera = new Camera(36,((float)height)/width,.1,10, vec4(13,2,3), vec4(0,0,0));
    this->image = new unsigned char[width * height * 3];
}
unsigned int seed = 133742069;
float xorshift()
{
    unsigned int ret = seed;
    ret ^= ret << 13;
    ret ^= ret >> 17;
    ret ^= ret << 5;
    seed = ret;
    return (float)ret/4294967296;
}

vec4 PathTracer::GetColor(Ray ray, Hitable* object, int recursionDepth)
{
    rayCount++;
    recursionDepth--;
    Hitdata hit;
    if(object->Hit(ray, 0.001, MAXFLOAT, hit))
    {
        Ray scattered;
        vec4 attenuation;
        if (recursionDepth > 0 && hit.material->Scatter(ray, hit, attenuation, scattered))
        {
            return attenuation.transMultiply(GetColor(scattered, object, recursionDepth));
        }
        else
        {
            return vec4(0,0,0,0);
        }
    }
    float t = 0.5 * (ray.Direction.norm()[1] + 1);
    return vec4(1,1,1) * t + vec4(0.1, 0.3, 0.5) * (1-t);
    
};

HitableList *randomScene(const unsigned int objects, const bool bigSpheres)
{
    int n = 10;
    HitableList* ret = new HitableList();
    ret->Register(new Sphere(0,-1000,0, 1000, new Diffuse(0.5,0.5,0.5)));
    int i = 1;
    for(int n = 0; n < objects; n++)
    {
        float mat = xorshift();
        vec4 center(20*xorshift()-10,0.2,20*xorshift()-10);
        if((center-vec4(4,0.2,0)).abs() > 0.9)
        {
            if(mat < 0.8)
            {
                ret->Register(new Sphere(center, 0.2, new Diffuse(xorshift()*xorshift(), xorshift()*xorshift(),xorshift()*xorshift())));
            }
            else if(mat < 0.95)
            {
                ret->Register(new Sphere(center, 0.2, new Metal(0.5*(1+xorshift()), 0.5*(1+xorshift()),0.5*(1+xorshift()), xorshift())));
            }
            else
            {
                ret->Register(new Sphere(center, 0.2, new Dielectric(1.5)));
            }
            
        }
    }
    if(bigSpheres)
    {
        ret->Register(new Sphere(vec4(0,1,0),1, new Dielectric(1.5)));
        ret->Register(new Sphere(vec4(-4,1,0),1, new Diffuse(0.4,0.2,0.1)));
        ret->Register(new Sphere(vec4(4,1,0),1, new Metal(0.7,0.6,0.5,0)));
    }
    return ret;
}

void PathTracer::Render(unsigned int samples, unsigned int count)
{
    std::ofstream output ("/home/ludfra-7/Pictures/REEEE.p3", std::ofstream::binary);
    output << "P3\n256 256\n256\n";
    std::cout << "Render started!" << std::endl;
    running = true;
    HitableList* world = randomScene(count, false);

    for(int s = 1; s <= samples; s++)
    {
        std::cout << "SAMPLE: " << s << std::endl;
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                vec4 pixelColor(0,0,0,0);
                float u = (x + xorshift()) / (float)width;
                float v = (y + xorshift()) / (float)height;
                pixelColor += GetColor(camera->GetRay(u,1-v), world, 50);
                
                pixelColor = vec4(sqrt(pixelColor[0]), sqrt(pixelColor[1]),sqrt(pixelColor[2]));
                image[(y * width + x) * 3] = (image[(y * width + x) * 3]*(s-1) + pixelColor[0]*255) / s;
                image[(y * width + x) * 3+1] = (image[(y * width + x) * 3+1]*(s-1) + pixelColor[1]*255) / s;
                image[(y * width + x) * 3+2] = (image[(y * width + x) * 3+2]*(s-1) + pixelColor[2]*255) / s;
            }
        }
    }
    for(unsigned int y = 0; y < height; y++)
    {
        for(unsigned int x = 0; x < width; x++)
        {
            output << (int)image[(y * width + x) * 3] << " " << (int)image[(y * width + x) * 3 + 1] << " " << (int)image[(y * width + x) * 3 + 2] << " ";
        }
        output << "\n";
    }
    std::cout << "Render complete! Time: " << std::endl;
    running = false;
}
