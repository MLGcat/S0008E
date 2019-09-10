#pragma once
#include "Math4D.h"
#include "config.h"
#include "render/window.h"
#include "core/app.h"
#include <iostream>
#include <vector>
#include <string.h>

struct vert {
	int coord;
	int uv = 1;
	int normal;
};

struct face {
	vert verts[3];
};


class meshResource
{
public:
	meshResource();
	meshResource(GLfloat* verts, int length, GLuint* index, int faces);
	~meshResource();

	void bake();
	void load(char* src);

	int vCount, fCount; //Vertex and face count
	GLfloat* verts;
	GLuint* index;


	GLuint vbo;
	GLuint ibo;
	GLuint vao;
	GLuint tex;

	GLuint vertexShader;
	GLuint pixelShader;

};

