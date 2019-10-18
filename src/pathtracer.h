#pragma once
#include "Math4D.h"
#include <vector>
#include <fstream>

class Ray
{
public:
    Ray(){};
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

    vec4 Reflect(const vec4 & in, const vec4 & normal) const
    {
        float proj = normal*in;
        return in - (normal*(in*normal*2));
    }

    bool refract(const vec4 & in, const vec4 & normal, float IORs, vec4& refracted)
    {
        vec4 in_normalized = in.norm();
        float dt = in_normalized * normal;
        float discriminant = 1 - IORs*IORs*(1-dt*dt);
        if(discriminant > 0)
        {
            refracted = (in_normalized - normal*dt)*IORs - normal*sqrt(discriminant);
            return true;
        }
        return false;
        
    }

    float schlick(float cosine, float IOR)
    {
        float r0 = (1-IOR)/(1+IOR);
        r0 = r0 * r0;
        return r0 + (1-r0)*pow((1 -cosine),5);
    }
};

class Diffuse : public Material
{
public:
    Diffuse(float r, float g, float b){albedo = vec4(r,g,b,1);};
    bool Scatter(const Ray& ray_in, const Hitdata& hit , vec4& attenuation, Ray& scattered) override
    {
        vec4 target = hit.point + hit.normal + randPointInSphere();
        scattered = Ray(hit.point, target-hit.point);
        attenuation = albedo;
        return true;
    }

    vec4 albedo;
};

class Metal : public Material
{
public:
    Metal(float r, float g, float b, float roughness){albedo = vec4(r,g,b,1); this->roughness = roughness;};
    bool Scatter(const Ray& ray_in, const Hitdata& hit , vec4& attenuation, Ray& scattered) override
    {
        vec4 reflect = Reflect(ray_in.Direction.norm(), hit.normal.norm());
        scattered = Ray(hit.point, reflect + randPointInSphere() * roughness);
        attenuation = albedo;
        return (scattered.Direction * hit.normal.norm()) > 0;
    }

    vec4 albedo;
    float roughness;
};

class Dielectric : public Material
{
public:
    Dielectric(float IOR){this->IOR = IOR;};
    bool Scatter(const Ray& ray_in, const Hitdata& hit , vec4& attenuation, Ray& scattered) override
    {
        vec4 normal = hit.normal;
        vec4 reflected = Reflect(ray_in.Direction.norm(), hit.normal);
        vec4 refracted;

        float IORresult;
        float cosine;
        float reflectionChance;

        attenuation = vec4(1,1,1,0);

        if(ray_in.Direction * normal > 0)
        {
            normal = hit.normal*-1;
            IORresult = IOR;
            cosine = IOR * (ray_in.Direction * hit.normal) / ray_in.Direction.abs();
        }
        else
        {
            IORresult = 1/IOR;
            cosine = -(ray_in.Direction * hit.normal) / ray_in.Direction.abs();
        }

        if(refract(ray_in.Direction, normal, IORresult, refracted))
        {
            reflectionChance = schlick(cosine, IOR);
        }
        else
        {
            scattered = Ray(hit.point, reflected);
            return true;
        }

        if(drand48() < reflectionChance)
        {
            scattered = Ray(hit.point, reflected);
        }
        else
        {
            scattered = Ray(hit.point, refracted);
        }
        return true;
    }

    float IOR;
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
    Sphere(vec4 pos, float radius, Material* material){this->pos = pos; this->radius = radius; this->material = material;};
    Sphere(float x, float y, float z, float radius, Material* material ){this->pos = vec4(x,y,z); this->radius = radius; this->material = material;};
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
                hit.material = material;
                return true;
            }

            //Postitive sqrt
            t = (-b +sqrt(disc))/(a*2);
            if(t > t_min && t < t_max)
            {
                hit.t = t;
                hit.point = ray.GetPoint(t);
                hit.normal = (hit.point - pos) / radius;
                hit.material = material;
                return true;
            }

        }
        return false;
        
    }

    Material* material;

private:
    vec4 pos;
    float radius;
};

class Camera
{
public :
    Camera()
    {
        origin = vec4(0,0,0,0);
        bottomLeft = vec4(-1,-1,-1,0);
        horizontal = vec4(2,0,0,0);
        vertical = vec4(0,2,0,0);
    }

    Camera(float fov, float aspect, float aperture, float focusDist, vec4 position, vec4 lookatPoint)
    {
        lensRadius = aperture / 2;

        float halfWidth = tan(fov*M_PI/360);
        float halfHeight = aspect * halfWidth;

        forward = (lookatPoint - position).norm();
        right = (forward%vec4(0,1,0,0)).norm();
        camUp = right%forward;

        origin = position;
        bottomLeft = origin - right * halfWidth * focusDist - camUp * halfHeight * focusDist + forward * focusDist;
        horizontal = right*2*halfWidth*focusDist;
        vertical = camUp*2*halfHeight*focusDist;
    }
    

    Ray GetRay(float u, float v)
    {
        vec4 random = randomInDisc() * lensRadius;
        vec4 sharpnessOffset = right * random[0] + camUp * random[1];
        vec4 direction = bottomLeft + horizontal * u + vertical * v - origin;
        return Ray(origin + sharpnessOffset, direction - sharpnessOffset);
    }
    vec4 origin;
    vec4 bottomLeft;
    vec4 horizontal;
    vec4 vertical;
    vec4 forward, right, camUp;

    float lensRadius;
    private:
        vec4 randomInDisc()
        {
            return vec4((2*drand48())-1, (2*drand48())-1,0,0).norm();
        }
};

class PathTracer
{
public:
    PathTracer(int width,int height);
    void Render(unsigned int samples, unsigned int count);
    unsigned char* image;
    bool running = false;
private:
    vec4 GetColor(Ray ray, Hitable* object, int recursionDepth);
    Camera* camera;
    int width;
    int height;
    unsigned int rayCount;
};