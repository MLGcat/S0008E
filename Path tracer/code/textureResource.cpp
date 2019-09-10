#include "textureResource.h"



textureResource::textureResource()
{
}


textureResource::~textureResource()
{
}

void textureResource::loadTexture(char* path) {
	//TEXTUR
	int chan;
	img = stbi_load(path, &width, &height, &chan, STBI_rgb);
	
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
}

void textureResource::use(GLuint & program) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLint texID = glGetUniformLocation(program, "Texture");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texID, 0);
}
