#pragma once
#include "core/app.h"
#include <stdio.h>
#include <stdlib.h>
#include <stb_image.h>

class textureResource
{
public:
	textureResource();
	~textureResource();
	void loadTexture(char* path);
	void use(GLuint & program);

private:
	int width, height;
	GLuint tex;
	unsigned char* img;
};

