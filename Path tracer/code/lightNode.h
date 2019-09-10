#pragma once
#include "Math4D.h"
class light {
public:
	light();
	light(vector4D pos, vector4D color, float intensity);
	light(float x, float y, float z, unsigned int r, unsigned int g, unsigned int b, float intensity);
	~light();


	void setPos(float x, float y, float z);
	void setPos(vector4D pos);

	void setColor(unsigned int r, unsigned int g, unsigned int b);
	void setColor(vector4D col);

	void setIntensity(float intensity);

	float pos[4];
	unsigned int color[3];
	float intensity;
};

