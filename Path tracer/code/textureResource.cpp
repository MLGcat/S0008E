#include "textureResource.h"



textureResource::textureResource()
{
	glGenTextures(1, &tex);
}

textureResource::textureResource(unsigned char * img, int width, int height)
{
	this->img = img;
	this->width = width;
	this->height = height;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
}


textureResource::~textureResource()
{
}

void textureResource::loadTexture(char* path) {
	//TEXTUR
	int chan;
	img = stbi_load(path, &width, &height, &chan, STBI_rgb);
}

void textureResource::use(GLuint & program) {
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLint texID = glGetUniformLocation(program, "Texture");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texID, 0);
}
