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

        vector<mat4*> transformsTemp;
        vector<mat4*> bindposeTemp;
        do
        {
            i++;
            joints.push_back(Joint::FromXML(*joint, this));
            transformsTemp.push_back(&joints.at(i)->model);
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
        Root->RefreshTransform(mat4());

       
        string indexStr = src.FirstChildElement("Nebula3")->FirstChildElement("Model")->FirstChildElement("Skins")->FirstChildElement("Skin")->FirstChildElement("Fragment")->FirstChildElement("Joints")->GetText();
        
        weightIndices = new GLuint[joints.size()];
        weightIndices[0] = std::atoi(strtok((char*)indexStr.c_str(),",")); //Hatar denna omvandling

        for(int i = 1; i < joints.size(); i++)
        {
            weightIndices[i] = std::atoi(strtok(NULL,","));
        }


        for(GLuint i = 0; i < joints.size(); i++)
        {
            transforms.push_back(transformsTemp.at(weightIndices[i]));
            bindPose.push_back(transforms.at(i)->inv());
        }


        
        std::cout << "XML loaded!" << std::endl;
    }
    else
    {
        std::cout << "XML load failed!" << std::endl;
    }
    
}

void Skeleton::ApplyKey(const unsigned int clipIndex, const float keyIndex)
{
    if(clipIndex >= animation->ClipCount) return;
    if(animation != nullptr)
    {
        for(int i = 0; i < joints.size(); i++)
        {
            joints[i]->pos = animation->Clips[clipIndex].getKey(i*4, keyIndex);
            joints[i]->rot = animation->Clips[clipIndex].getKey(i*4+1, keyIndex);
            joints[i]->scale = animation->Clips[clipIndex].getKey(i*4+2, keyIndex);
        }
    }
}

void Skeleton::draw(camera & c, light* lights, unsigned int size)
{
    Root->RefreshTransform(mat4());
    if(showSkeleton)Root->draw(c, lights, size);
    
    shader->use();
	texture->use(shader->program);

	glUniformMatrix4fv(glGetUniformLocation(shader->program, "m"), 1, GL_TRUE, model.get());
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "v"), 1, GL_TRUE, c.view().get());
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "p"), 1, GL_TRUE, c.perspective().get());

	//Lights
	glUniform1ui(glGetUniformLocation(shader->program, "lightArraySize"), size);
	for (int i = 0; i < size; i++) {
		string name = "lightArray[" + std::to_string(i) + "]";
		glUniform1fv(glGetUniformLocation(shader->program, (name + ".pos").c_str()), 4, lights[i].pos);
		glUniform1uiv(glGetUniformLocation(shader->program, (name + ".col").c_str()), 3, lights[i].color);
		glUniform1f(glGetUniformLocation(shader->program, (name + ".intensity").c_str()), lights[i].intensity);
	}

    //Lights
	glUniform1ui(glGetUniformLocation(shader->program, "boneCount"), transforms.size());
	for (int i = 0; i < transforms.size(); i++) {
		glUniformMatrix4fv(glGetUniformLocation(shader->program, ("bones[" + std::to_string(i) + "]").c_str()), 1,GL_TRUE, (*transforms.at(i)*bindPose.at(i)).get());
	}

	//Camera
	float* test = &c.pos.get3();
	GLfloat test2[3];
	test2[0] = test[0];
	test2[1] = test[1];
	test2[2] = test[2];
	glUniform1fv(glGetUniformLocation(shader->program, "camPos"), 3, test2);
	glUniform1fv(glGetUniformLocation(shader->program, "ambientLight"), 3, c.ambientLight);
    
    

	//Specular data
	glUniform1fv(glGetUniformLocation(shader->program, "specData"), 5, specData);

	glBindVertexArray(mesh->vao);
	glDrawElements(GL_TRIANGLES, mesh->fCount*3, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

