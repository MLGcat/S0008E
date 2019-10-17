#include "textureResource.h"



textureResource::textureResource(unsigned int type)
{
	this->type = type;
	this->name = getName();
	glGenTextures(1, &tex);
}

textureResource::textureResource(unsigned char * img, int width, int height, unsigned int type)
{
	this->img = img;
	this->width = width;
	this->height = height;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
}

char* textureResource::getName()
{
	switch (type)
	{
		case 0: return "Diffuse";
		case 1: return "Normal";
		case 2: return "Specular";
		default: return "";
	}
}

textureResource::~textureResource()
{
}

void textureResource::loadTexture(char* path) {
	//TEXTUR
	int chan;
	img = stbi_load(path, &width, &height, &chan, STBI_rgb_alpha);
}

void textureResource::use(GLuint & program) {
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	GLint texID = glGetUniformLocation(program, name);
	glActiveTexture(GL_TEXTURE1 + type);
	glUniform1i(texID, type);
}
