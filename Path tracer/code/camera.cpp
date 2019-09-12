#include "camera.h"

camera::camera() {
	focus = vec4(0, 0, 0, 1);
	pos = vec4(0, 0, 1, 1);
}

camera::camera(float n, float f, float fov, float aspect) {
	focus = vec4(0, 0, 0, 1);
	pos = vec4(0, 0, 1, 1);

	this->n = n;
	this->f = f;
	this->fov = fov*DEG;
	this->aspect = aspect;
	this->test = vec4(1, 1, 1, 1);
}


camera::~camera() {

}

void camera::lookAt(vec4 target) {
	focus = target;
	vec4 direction = (getPos()-target).norm();
	//direction.print();
	vec4 up(0,1,0,1);
	vec4 right = (up%direction).norm();
	vec4 camUp = right%direction;

	rotMat = mat4(
		right[0], right[1], right[2], 0,
		camUp[0], camUp[1], camUp[2], 0,
		direction[0], direction[1], direction[2], 0,
		0, 0, 0, 1);
}

void camera::lookAt(float x, float y, float z) {
	vec4 target(x, y, z, 1);
	lookAt(target);
}


void camera::setPos(vec4 newPos) {
	pos = newPos;
	posMat = mat4::transform(newPos);
}
void camera::setPos(float x, float y, float z) {
	pos = vec4(x,y,z);
	posMat = mat4::transform(-x, -y, -z);
}


void camera::setRot(vec4 newRot) {
	rotMat = mat4::rotd3(newRot);
}
void camera::setRot(float x, float y, float z) {
	rotMat = mat4::rotd3(x, y, z);
}


void camera::move(vec4 dir) {
	posMat = mat4::transform((getPos() + dir)*-1);
	dir[3] = 0;
	pos += dir;
	focus += dir;
	//cout << "Focus: " << endl;
	//focus.print();
}

void camera::move(float x, float y, float z) {
	vec4 dir(x, y, z);
	move(dir);
}


void camera::rotAround(vec4 dir) {
	float d = (focus - getPos()).abs();
	setPos(focus + dir*d);
	lookAt(focus);
}

void camera::rotAround(float h, float v) {
	float d = (focus - pos).abs();
	vec4 dir = vec4(sin(h),sin(v),cos(h),0).norm();
	dir[3] = 0;
	setPos(focus - (dir * d));
	d = (focus - pos).abs();/*
	cout << "Focus: ";
	focus.print();
	cout << "Predict: ";
	(focus + (dir * d)).print();
	cout << "Actual: ";
	getPos().print();
	cout << "Pet" << dir.abs() << endl;
	cout << "Dist: " << d << endl;*/
	
	lookAt(focus);
}

void camera::setAmbient(float r, float g, float b) {
	ambientLight[0] = r;
	ambientLight[1] = g;
	ambientLight[2] = b;
}

mat4 camera::view() {
	return rotMat * posMat;
}

mat4 camera::perspective() {
	return mat4(
		1 / (aspect*tan(fov*0.5)), 0, 0, 0,
		0, 1 / (tan(fov*0.5)), 0, 0,
		0, 0, ((n + f) / (n - f)), -1,
		0, 0, ((2 * f*n) / (n - f)), 0);
}

vec4 camera::getPos() {
	return vec4(-posMat[0][3], -posMat[1][3], -posMat[2][3]);
}