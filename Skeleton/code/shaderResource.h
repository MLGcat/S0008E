#pragma once
#include "core/app.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;
class shaderResource
{
public:
	shaderResource();
	~shaderResource();

	GLuint compile();

	void loadV(char* src);
	void loadF(char* src);

	GLuint use();
	GLuint program;
private:
	GLchar vsString[2048] = "\0";
	GLchar fsString[2048] = "\0";
	GLuint vertexShader;
	GLuint fragmentShader;
	GLchar* loadFile(char* src);
};

