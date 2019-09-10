#pragma once
#include "Math4D.h"

class camera {
public:
	camera();
	camera(float n, float f, float fov, float aspect);
	~camera();
	void setPos(vector4D newPos);
	void setPos(float x, float y, float z);

	void setRot(vector4D newRot);
	void setRot(float x, float y, float z);

	void lookAt(vector4D target); 
	void lookAt(float x, float y, float z);

	void move(vector4D dir);
	void move(float x, float y, float z);

	void rotAround(vector4D dir);
	void rotAround(float h, float v);

	void setAmbient(float r, float g, float b);

	vector4D getPos();

	matrix4D view();
	matrix4D perspective();

	vector4D focus, pos;
	vector4D test;

	float ambientLight[3]{ 0,0,0 };

private:
	float n, f, aspect, fov;
	matrix4D posMat, rotMat;
};