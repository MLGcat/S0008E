#pragma once
#include "Math4D.h"
class light {
public:
	light();
	light(vec4 pos, vec4 color, float intensity);
	light(float x, float y, float z, unsigned int r, unsigned int g, unsigned int b, float intensity);
	~light();


	void setPos(float x, float y, float z);
	void setPos(vec4 pos);

	void setColor(unsigned int r, unsigned int g, unsigned int b);
	void setColor(vec4 col);

	void setIntensity(float intensity);

	float pos[4];
	unsigned int color[3];
	float intensity;
};

