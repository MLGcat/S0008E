#include "pathtracer.h"
PathTracer::PathTracer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->camera = new Camera();
}

vec4 GetColor(Ray ray, Hitable* object)
{
    Hitdata hit;
    if(object->Hit(ray, 0, 100, hit))
    {
        return (hit.normal + vec4(1,1,1,0))*0.5;
    }
    return vec4(0,0,0,0);
};

unsigned char * PathTracer::Render(unsigned int samples,int & widthOut, int & heightOut)
{

    HitableList hitList;
    unsigned char * ret = new unsigned char[width * height * 3];
	Sphere sphere(0,-1,-2,0.8);
	Sphere sphere2(0,1,-2,0.8);
    hitList.Register(&sphere);
    hitList.Register(&sphere2);
    
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            vec4 pixelColor(0,0,0,0);
            for(int s = 0; s < samples; s++)
            {
                float u = (x + drand48()) / (float)width;
                float v = (y + drand48()) / (float)height;
                pixelColor += GetColor(camera->GetRay(u,v), &hitList);
            }
            pixelColor /= samples;
            
            ret[(y + x * height) * 3] = pixelColor[0]*255;
            ret[(y + x * height) * 3 + 1] = pixelColor[1]*255;
            ret[(y + x * height) * 3 + 2] = pixelColor[2]*255;
        }
    }
    widthOut = this->width;
    heightOut = this->height;
    return ret;
}