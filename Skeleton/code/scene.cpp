#include "scene.h"
scene::scene()
{

};
void scene::addObject(graphicsNode * obj)
{
    objects.push_back(obj);
};
void scene::removeObject()
{

};

void scene::addLight(light newLight)
{
    lights.push_back(newLight);
};

void scene::draw(camera & cam)
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->draw(cam, &lights[0], lights.size());
    }

};