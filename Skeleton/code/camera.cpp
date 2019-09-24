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
	vec4 forward = (getPos() - target).norm();
	vec4 worldUp = vec4(0,1,0,0);
	vec4 right = (worldUp%forward).norm();
	vec4 camUp = forward%right;

	viewMat = mat4(
		right[0],right[1],right[2],-(right*pos),
		camUp[0],camUp[1],camUp[2],-(camUp*pos),
		forward[0],forward[1],forward[2],-(forward*pos),
		0,0,0,1
	);
}

vec4 camera::forward()
{
	return (getPos()-focus).norm();
}

vec4 camera::right()
{
	return (vec4(0,1,0,1)%this->forward());
}

vec4 camera::up()
{
	return (this->right()%this->forward());	
}

void camera::lookAt(float x, float y, float z) {
	vec4 target(x, y, z, 0);
	lookAt(target);
}


void camera::setPos(vec4 newPos) {
	pos = newPos;
	posMat = mat4(
		1,0,0,-pos[0],
		0,1,0,-pos[1],
		0,0,1,-pos[2],
		0,0,0,1
	);
}
void camera::setPos(float x, float y, float z) {
	pos = vec4(x,y,z);
	setPos(pos);
}

void camera::setRot(vec4 newRot) {
}
void camera::setRot(float x, float y, float z) {
}


void camera::move(vec4 dir) {
	dir[3] = 0;
	pos += dir;
	focus += dir;
	lookAt(focus);
}

void camera::move(float x, float y, float z) {
	vec4 dir(x, y, z);
	move(dir);
}


void camera::zoom(float ammount) {
	pos += forward() * ammount;
	lookAt(focus);
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
	d = (focus - pos).abs();
	
	lookAt(focus);
}

void camera::setAmbient(float r, float g, float b) {
	ambientLight[0] = r;
	ambientLight[1] = g;
	ambientLight[2] = b;
}

mat4 camera::view() {
	return viewMat;
}

mat4 camera::perspective() {


	return mat4(
		1/tan(fov*0.5), 0, 0, 0,
		0, 1/tan(fov*0.5), 0, 0,
		0, 0, -((f+n)/(f-n)), -(2*f*n)/(f-n),
		0, 0, -1, 0
	);
}

vec4 camera::getPos() {
	return pos;
}