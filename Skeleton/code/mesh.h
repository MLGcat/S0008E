#pragma once
#include "Math4D.h"
#include "config.h"
#include "render/window.h"
#include "core/app.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <memory>

#include "Nvx2structs.h"
#include <fstream>

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
	static meshResource fromNVX2(const char path[]);

	int vCount, fCount; //Vertex and face count
	GLfloat* verts;
	GLuint* index;


	GLuint vbo;
	GLuint ibo;
	GLuint vao;

};

