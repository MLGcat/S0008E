#pragma once
#include "Math4D.h"
#include <vector>

class Ray
{
public:
    Ray();
    Ray(const vec4& origin, const vec4& direction) {Origin = origin; Direction = direction;};
    vec4 GetPoint(float t) {return Origin + Direction * t; };
    vec4 Origin;
    vec4 Direction;
};
class Material;
struct Hitdata
{
    float t;
    vec4 point;
    vec4 normal;
    Material* material;
};

class Hitable
{
public:
    virtual bool Hit(Ray& ray, float t_min, float t_max, Hitdata& hits) = 0;
};

class Material
{
public:
    virtual bool Scatter(const Ray& ray_in, const Hitdata& hit, vec4& somethings, Ray& scattered) = 0;
    vec4 randPointInSphere()
    {
        return vec4(2*drand48()-1,2*drand48()-1,2*drand48()).norm();
    }

    vec4 reflect(const vec4 & in, const vec4 & normal) const
    {
        return in - (normal*(in*normal));
    }
};

class Diffuse : public Material
{
public:
    bool Scatter(const Ray& ray_in, const Hitdata& hit , vec4& somethings, Ray& scattered) override
    {
        vec4 target = hit.point + hit.normal + randPointInSphere();
        scattered = Ray(hit.point, target-hit.point);
        somethings = albedo;
        return true;
    }

    vec4 albedo;
};

class Metal : public Material
{
public:
    bool Scatter(const Ray& ray_in, const Hitdata& hit , vec4& somethings, Ray& scattered) override
    {
        vec4 reflect = reflect(ray_in.Direction.norm(), &hit.normal);
        scattered = Ray(hit.point, target-hit.point);
        somethings = albedo;
        return true;
    }

    vec4 albedo;
};

class HitableList : public Hitable
{
public:
    void Register(Hitable* object){objects.push_back(object);};
    bool Hit(Ray& ray, float t_min, float t_max, Hitdata& hits) override
    {
        bool hasHit = false;
        Hitdata closestHit;
        closestHit.t = t_max;
        for(int i = 0; i < objects.size(); i++)
        {
            Hitdata hit;
            if(objects[i]->Hit(ray, t_min, closestHit.t, hit))
            {
                closestHit = hit;
                hasHit = true;
            }
        }
        hits = closestHit;
        return hasHit;
    }
private:
    std::vector<Hitable*> objects;
};

class Sphere : public Hitable
{
public:
    Sphere(vec4 pos, float radius){this->pos = pos; this->radius = radius;};
    Sphere(float x, float y, float z, float radius){this->pos = vec4(x,y,z); this->radius = radius;};
    bool Hit(Ray& ray, float t_min, float t_max, Hitdata& hit) override
    {
        vec4 oc = ray.Origin - pos;
        float a = ray.Direction*ray.Direction;
        float b = (oc * ray.Direction) * 2;
        float c = (oc*oc) - (radius * radius);
        float disc = b*b-4*a*c;
        if(disc > 0)
        {
            //Negative sqrt
            float t = (-b -sqrt(disc))/(a*2);
            if(t > t_min && t < t_max)
            {
                hit.t = t;
                hit.point = ray.GetPoint(t);
                hit.normal = (hit.point - pos) / radius;
                return true;
            }

            //Postitive sqrt
            t = (-b +sqrt(disc))/(a*2);
            if(t > t_min && t < t_max)
            {
                hit.t = t;
                hit.point = ray.GetPoint(t);
                hit.normal = (hit.point - pos) / radius;
                return true;
            }

        }
        return false;
        
    }
private:
    vec4 pos;
    float radius;
};

class Camera
{
public :
    Camera()
    {
        origin = vec4(0,0,0);
        bottomLeft = vec4(-1,-1,-1);
        horizontal = vec4(2,0,0);
        vertical = vec4(0,2,0);
    }

    Ray GetRay(float u, float v)
    {
        vec4 direction(bottomLeft + (horizontal * u) + (vertical * v));
        direction[3] = 0;
        return Ray(origin, direction);
    }
    vec4 origin;
    vec4 bottomLeft;
    vec4 horizontal;
    vec4 vertical;
};

class PathTracer
{
public:
    PathTracer(int width,int height);
    unsigned char * Render(unsigned int samples,int & widthOut, int & heightOut);
private:
    Camera* camera;
    int width;
    int height;
};