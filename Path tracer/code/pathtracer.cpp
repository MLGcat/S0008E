#include "pathtracer.h"
PathTracer::PathTracer(int width, int height)
{
    this->width = width;
    this->height = height;
    this->camera = new Camera(90,1,1,1, vec4(0,0,0), vec4(0,0,-1));
}

vec4 GetColor(Ray ray, Hitable* object, int recursionDepth)
{
    recursionDepth--;
    Hitdata hit;
    if(recursionDepth > 0 && object->Hit(ray, 0, MAXFLOAT, hit))
    {
        Ray scattered;
        vec4 attenuation;
        if (hit.material->Scatter(ray, hit, attenuation, scattered))
        {
            return attenuation.transMultiply(GetColor(scattered, object, recursionDepth));
        }
        else
        {
            return vec4();
        }
    }
    float t = 0.5 * (ray.Direction.norm()[1] + 1);
    return vec4(1,1,1) * t + vec4(0.1, 0.3, 0.5) * (1-t);
    
};

unsigned char * PathTracer::Render(unsigned int samples,int & widthOut, int & heightOut)
{

    HitableList hitList;
    unsigned char * ret = new unsigned char[width * height * 3];

	Sphere sphere(1,0,-2,0.5, new Metal(.8, .6, .2, 0));
	Sphere sphere2(-1,0,-2,0.5, new Dielectric(1.5));
	Sphere sphere3(0,0,-2,0.5, new Diffuse(.1, .2, .5));

    Material* materials[3];
    materials[0] = new Metal(.8, .6, .2, 0);
    materials[1] = new Dielectric(1.5);
    materials[2] = new Diffuse(.1, .2, .5);

    for(int i = 0; i < 10; i++)
    {
        float x = drand48()*2-1;
        float radius = 0.1+drand48()*0.3;
        float z = -1-drand48()*4;
        hitList.Register(new Sphere(x, 0.5-radius, z, radius, materials[(int)(drand48()*3)]));
    }

	Sphere groundSphere(0,100.5,-2,100, new Diffuse(.8,.8,0));
    hitList.Register(&sphere);
    hitList.Register(&sphere2);
    hitList.Register(&sphere3);
    hitList.Register(&groundSphere);
    
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            vec4 pixelColor(0,0,0,0);
            for(int s = 0; s < samples; s++)
            {
                float u = (x + drand48()) / (float)width;
                float v = (y + drand48()) / (float)height;
                pixelColor += GetColor(camera->GetRay(u,v), &hitList, 5);
            }
            pixelColor /= samples;
            pixelColor = vec4(sqrt(pixelColor[0]), sqrt(pixelColor[1]),sqrt(pixelColor[2]));
            ret[(y * width + x) * 3] = pixelColor[0]*255;
            ret[(y * width + x) * 3 + 1] = pixelColor[1]*255;
            ret[(y * width + x) * 3 + 2] = pixelColor[2]*255;
        }
    }
    widthOut = this->width;
    heightOut = this->height;
    return ret;
}