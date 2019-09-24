#include "skeleton.h"

void Skeleton::Load(string path)
{
    TiXmlDocument src(path.c_str());

    if(src.LoadFile())
    {
        joints.clear();
        TiXmlElement* firstBone = src.FirstChildElement("Nebula3")->FirstChildElement("Model")->FirstChildElement("CharacterNodes")->FirstChildElement("CharacterNode")->FirstChildElement("Joint");
        TiXmlElement* joint = firstBone;
        int i = -1;
        do
        {
            i++;
            joints.push_back(Joint::FromXML(*joint, this));
            int parent = std::atoi(joint->Attribute("parent"));
            if(parent != -1)
            {
                if(parent < joints.size())
                {
                    joints[parent]->Children.push_back(joints[joints.size()-1]);
                }
                else
                {
                    std::cout << "WARNING! PARENT HAS NOT BEEN ADDED YET!" << std::endl; 
                }
                
            }
            joint = joint->NextSiblingElement("Joint");
        } while (joint);
        Root = joints[0];
        std::cout << "XML loaded!" << std::endl;
    }
    else
    {
        std::cout << "XML load failed!" << std::endl;
    }
    
}

void Skeleton::draw(camera & c, light* lights, unsigned int size)
{
    Root->RefreshTransform(mat4());
    Root->draw(c, lights, size);
}

