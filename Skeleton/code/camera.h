#pragma once
#include "Math4D.h"

class camera {
public:
	camera();
	camera(float n, float f, float fov, float aspect);
	~camera();
	void setPos(vec4 newPos);
	void setPos(float x, float y, float z);

	void setRot(vec4 newRot);
	void setRot(float x, float y, float z);

	void lookAt(vec4 target); 
	void lookAt(float x, float y, float z);

	void move(vec4 dir);
	void move(float x, float y, float z);

	void zoom(float ammount);

	void rotAround(vec4 dir);
	void rotAround(float h, float v);

	void setAmbient(float r, float g, float b);

	vec4 getPos();

	mat4 view();
	mat4 perspective();

	vec4 focus, pos;
	vec4 test;
	vec4 forward();
	vec4 right();
	vec4 up();

	float ambientLight[3]{ 0,0,0 };

private:
	float n, f, aspect, fov;
	mat4 viewMat, posMat;
};