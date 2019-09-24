#pragma once
#include <vector>
#include "graphicsNode.h"
#include "Math4D.h"
#include "tinyxml.h"

class Joint;

class Skeleton : public graphicsNode
{
public:
    Joint* Root;
    meshResource* boneMesh;
    shaderResource* boneShader;
    textureResource* boneTexture;
    std::vector<Joint*> joints;

    void Load(string path);

	void draw(camera & c, light* lights, unsigned int size) override;
   
};

class Joint : public graphicsNode
{   
public:
    std::vector<Joint*> Children;
    int ID;
    vec4 pos, rot, scale;

    static Joint* FromXML(const TiXmlElement & element, Skeleton* skeleton) 
    {
        Joint* ret = new Joint();
        ret->setMesh(*skeleton->boneMesh);
        ret->setShader(*skeleton->boneShader);
        ret->setTexture(*skeleton->boneTexture);
        ret->ID = std::atoi(element.Attribute("index"));
        ret->pos = arrToVec((char*)element.Attribute("position"))*3;
        ret->rot = arrToVec((char*)element.Attribute("rotation"));
        ret->scale = arrToVec((char*)element.Attribute("scale"));
        ret->RefreshTransform(mat4());
        return ret;
    };

    void RefreshTransform(mat4 parent)
    {
        model = parent * mat4::transform(pos) * mat4::quaternion(rot) * mat4::scale(scale);
        for(int i = 0; i < Children.size(); i++)
        {
            Children[i]->RefreshTransform(model);
        }
    };

    void draw(camera & c, light* lights, unsigned int size) override
    {
        graphicsNode::draw(c,lights,size);
        vec4 A = vec4(0,0,0,0);
        for(int i = 0; i < Children.size(); i++)
        {
            vec4 B = Children[i]->pos;
            glBegin(GL_LINES);
            glVertex3f(A[0], A[1], A[2]);
            glVertex3f(B[0], B[1], B[2]);
            glEnd();
        }
        for(int i = 0; i < Children.size(); i++)
        {
            Children[i]->draw(c,lights,size);
        }
    }



private:
    static vec4 arrToVec(char* str)
    {
        float x = std::atof(strtok(str,","));
        float y = std::atof(strtok(NULL,","));
        float z = std::atof(strtok(NULL,","));
        float w = std::atof(strtok(NULL,","));
        return vec4(x,y,z,w);
    }
};


