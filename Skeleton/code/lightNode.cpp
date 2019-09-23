#include "lightNode.h"

light::light() {

}

light::~light() {

}

light::light(vec4 pos, vec4 color, float intensity) {
	pos[0] = pos[0];
	pos[1] = pos[1];
	pos[2] = -pos[2];
	pos[3] = pos[3];

	color[0] = color[0];
	color[1] = color[1];
	color[2] = color[2];

	intensity = intensity;
}

light::light(float x, float y, float z, unsigned int r, unsigned int g, unsigned int b, float intensity) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = 0;

	color[0] = r;
	color[1] = g;
	color[2] = b;

	this->intensity = intensity;
}

void light::setPos(float x, float y, float z) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	pos[3] = 0;
}

void light::setPos(vec4 pos) {
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->pos[2] = pos[2];
	this->pos[3] = pos[3];
}

void light::setColor(unsigned int r, unsigned int g, unsigned int b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void light::setColor(vec4 color) {
	color[0] = abs(color[0]);
	color[1] = abs(color[1]);
	color[2] = abs(color[2]);
}

void light::setIntensity(float intensity) {
	intensity = intensity;
}