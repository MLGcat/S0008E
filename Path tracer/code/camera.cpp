#include "camera.h"

camera::camera() {
	focus = vector4D(0, 0, 0, 1);
	pos = vector4D(0, 0, 1, 1);
}

camera::camera(float n, float f, float fov, float aspect) {
	focus = vector4D(0, 0, 0, 1);
	pos = vector4D(0, 0, 1, 1);

	this->n = n;
	this->f = f;
	this->fov = fov*DEG;
	this->aspect = aspect;
	this->test = vector4D(1, 1, 1, 1);
}


camera::~camera() {

}

void camera::lookAt(vector4D target) {
	focus = target;
	vector4D direction = (getPos()-target).norm();
	//direction.print();
	vector4D up(0,1,0,1);
	vector4D right = (up%direction).norm();
	vector4D camUp = right%direction;

	rotMat = matrix4D(
		right[0], right[1], right[2], 0,
		camUp[0], camUp[1], camUp[2], 0,
		direction[0], direction[1], direction[2], 0,
		0, 0, 0, 1);
}

void camera::lookAt(float x, float y, float z) {
	vector4D target(x, y, z, 1);
	lookAt(target);
}


void camera::setPos(vector4D newPos) {
	pos = newPos;
	posMat = matrix4D::transform(newPos);
}
void camera::setPos(float x, float y, float z) {
	pos = vector4D(x,y,z);
	posMat = matrix4D::transform(-x, -y, -z);
}


void camera::setRot(vector4D newRot) {
	rotMat = matrix4D::rotd3(newRot);
}
void camera::setRot(float x, float y, float z) {
	rotMat = matrix4D::rotd3(x, y, z);
}


void camera::move(vector4D dir) {
	posMat = matrix4D::transform((getPos() + dir)*-1);
	dir[3] = 0;
	pos += dir;
	focus += dir;
	//cout << "Focus: " << endl;
	//focus.print();
}

void camera::move(float x, float y, float z) {
	vector4D dir(x, y, z);
	move(dir);
}


void camera::rotAround(vector4D dir) {
	float d = (focus - getPos()).abs();
	setPos(focus + dir*d);
	lookAt(focus);
}

void camera::rotAround(float h, float v) {
	float d = (focus - pos).abs();
	vector4D dir = vector4D(sin(h),sin(v),cos(h),0).norm();
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

matrix4D camera::view() {
	return rotMat * posMat;
}

matrix4D camera::perspective() {
	return matrix4D(
		1 / (aspect*tan(fov*0.5)), 0, 0, 0,
		0, 1 / (tan(fov*0.5)), 0, 0,
		0, 0, ((n + f) / (n - f)), -1,
		0, 0, ((2 * f*n) / (n - f)), 0);
}

vector4D camera::getPos() {
	return vector4D(-posMat[0][3], -posMat[1][3], -posMat[2][3]);
}