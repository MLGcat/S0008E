#include "pathtracer.h"
PathTracer::PathTracer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->camera = new Camera(36,((float)height)/width,.1,10, vec4(13,2,3), vec4(0,0,0));
    this->image = new unsigned char[width * height * 3];
}

vec4 GetColor(Ray ray, Hitable* object, int recursionDepth)
{
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

HitableList *randomScene()
{
    int n = 10;
    HitableList* ret = new HitableList();
    ret->Register(new Sphere(0,-1000,0, 1000, new Diffuse(0.5,0.5,0.5)));
    int i = 1;
    for(int a = -11; a < 11; a++)
    {
        for(int b = -11; b < 11; b++)
        {
            float mat = drand48();
            vec4 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if((center-vec4(4,0.2,0)).abs() > 0.9)
            {
                if(mat < 0.8)
                {
                    ret->Register(new Sphere(center, 0.2, new Diffuse(drand48()*drand48(), drand48()*drand48(),drand48()*drand48())));
                }
                else if(mat < 0.95)
                {
                    ret->Register(new Sphere(center, 0.2, new Metal(0.5*(1+drand48()), 0.5*(1+drand48()),0.5*(1+drand48()), drand48())));
                }
                else
                {
                    ret->Register(new Sphere(center, 0.2, new Dielectric(1.5)));
                }
                
            }
        }
    }
    ret->Register(new Sphere(vec4(0,1,0),1, new Dielectric(1.5)));
    ret->Register(new Sphere(vec4(-4,1,0),1, new Diffuse(0.4,0.2,0.1)));
    ret->Register(new Sphere(vec4(4,1,0),1, new Metal(0.7,0.6,0.5,0)));
    return ret;
}

void PathTracer::Render(unsigned int samples,int & widthOut, int & heightOut)
{
    srand48(time(0));
    HitableList* world = randomScene();

    for(int s = 1; s <= samples; s++)
    {
        std::cout << "SAMPLE: " << s << std::endl;
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                vec4 pixelColor(0,0,0,0);
                float u = (x + drand48()) / (float)width;
                float v = (y + drand48()) / (float)height;
                pixelColor += GetColor(camera->GetRay(u,v), world, 50);
                
                pixelColor = vec4(sqrt(pixelColor[0]), sqrt(pixelColor[1]),sqrt(pixelColor[2]));
                image[(y * width + x) * 3] = (image[(y * width + x) * 3]*(s-1) + pixelColor[0]*255) / s;
                image[(y * width + x) * 3+1] = (image[(y * width + x) * 3+1]*(s-1) + pixelColor[1]*255) / s;
                image[(y * width + x) * 3+2] = (image[(y * width + x) * 3+2]*(s-1) + pixelColor[2]*255) / s;
            }
        }
    }
    widthOut = this->width;
    heightOut = this->height;
}
