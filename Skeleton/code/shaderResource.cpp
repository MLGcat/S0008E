#include "shaderResource.h"



shaderResource::shaderResource()
{
}


shaderResource::~shaderResource()
{
}

void shaderResource::loadV(char* src) {
	ifstream file;
	file.open(src);
	int i = 0;
	while (file.get(vsString[i])) {
		i++;
	}
}

void shaderResource::loadF(char* src) {
	ifstream file;
	file.open(src);
	int i = 0;
	while (file.get(fsString[i])) {
		i++;
	}
}

GLuint shaderResource::use() {
	glUseProgram(program);
	return program;
}


GLuint shaderResource::compile() {
	//Defines shader from 
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vBuf = vsString; //Maybe fix this
	GLint length = strlen(vBuf);
	glShaderSource(vertexShader, 1, &vBuf, &length);

	glCompileShader(vertexShader);

	GLint logSize;
	glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &logSize);
	if (logSize > 1)
	{
		GLchar* buf = new GLchar[logSize];
		glGetShaderInfoLog(this->vertexShader, logSize, NULL, buf);
		printf("[VSHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}


	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fBuf = fsString; //Maybe fix this
	GLint lengthb = strlen(fBuf);
	glShaderSource(fragmentShader, 1, &fBuf, &lengthb);

	glCompileShader(fragmentShader);

	glGetShaderiv(this->fragmentShader, GL_INFO_LOG_LENGTH, &logSize);
		if (logSize > 1)
		{
			GLchar* buf = new GLchar[logSize];
			glGetShaderInfoLog(this->fragmentShader, logSize, NULL, buf);
			printf("[FSHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}
	this->program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	std::cout << "Shader loaded!" << std::endl;
	return program;

}
