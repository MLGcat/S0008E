#pragma once
#include "core/app.h"
#include <stdio.h>
#include <stdlib.h>
#include <stb_image.h>

class textureResource
{
public:
	textureResource(char* typeName);
	textureResource() : textureResource("Diffuse"){};
	textureResource(unsigned char * img, int width, int height, char* typeName);
	textureResource(unsigned char * img, int width, int height) : textureResource(img, width, height, "Diffuse"){};
	~textureResource();
	void loadTexture(char* path);
	void use(GLuint & program);
	int width, height;
	GLuint tex;
	char* name;
	unsigned char* img;
};

