#pragma once
#include "core/app.h"
#include <stdio.h>
#include <stdlib.h>
#include <stb_image.h>

enum TextureType
{
	TexDiffuse,
	TexNormal,
	TexSpecular
};

class textureResource
{

public:
	textureResource(unsigned int type);
	textureResource() : textureResource(0){};
	textureResource(unsigned char * img, int width, int height, unsigned int type);
	textureResource(unsigned char * img, int width, int height) : textureResource(img, width, height, 0){};
	~textureResource();
	void loadTexture(char* path);
	void use(GLuint & program);
	int width, height;
	GLuint tex;
	GLuint type = 0;
	char* name;
	unsigned char* img;
protected:
	char* getName();
};

