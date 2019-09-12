#pragma once
#include "Math4D.h"
#include "mesh.h"
#include "camera.h"
#include "textureResource.h"
#include "shaderResource.h"
#include "graphicsNode.h"
#include "lightNode.h"

class scene
{
public:
    scene();
    void addObject(graphicsNode obj);
    void removeObject();
    void addLight(light newLight);
    void draw(camera & cam);

private:
    std::vector<graphicsNode> objects;
    std::vector<light> lights;
    camera* activeCamera;
};