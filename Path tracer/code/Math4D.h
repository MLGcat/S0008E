#pragma once
#include<iostream>
#include <math.h>
#define DEG 0.01745329252

using namespace std;

class vec4 {
public:
	vec4();
	vec4(float a, float b, float c, float d);
	vec4(float a, float b, float c);
	vec4(const vec4& src);
	~vec4();

	bool operator==(const vec4& rhs);
	bool operator!=(const vec4& rhs);

	//Addition, subtraktion
	void operator+=(const vec4& rhs);
	void operator-=(const vec4& rhs);
	vec4 operator+(const vec4& rhs) const;
	vec4 operator-(const vec4& rhs) const;

	//Multiplikation
	float operator*(const vec4& rhs) const;
	vec4 operator*(float s) const;
	void operator*=(float s);


	//Division
	float operator/(const vec4& rhs) const;
	vec4 operator/(float s);
	void operator/=(float s);

	//Kryssprodukt
	vec4 operator%(const vec4& rhs);

	//Tilldelning
	void operator=(const vec4& rhs);

	//Normalvektor
	vec4 norm();

	//Vektorl�ngd
	float abs();

	//Get
	float& operator[](const int i);
	float operator[](const int i) const;
	float & get();
	float & get3();
	void set(float x, float y, float z);
	void set(float x, float y, float z, float a);

	void print();

private:
	float vec[4];
};


class mat4
{
public:
	//Konstruktorer
	mat4();
	mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
	~mat4();

	//Get
	float* operator[](int i);

	//Rotation
	static mat4 rotX(float v);
	static mat4 rotY(float v);
	static mat4 rotZ(float v);
	static mat4 rot(float v, vec4 axis);
	static mat4 rot3(float x, float y, float z);
	
	//Rotation med grader
	static mat4 rotdX(float v);
	static mat4 rotdY(float v);
	static mat4 rotdZ(float v);
	static mat4 rotd(float v, vec4 axis);
	static mat4 rotd3(float x, float y, float z); 
	static mat4 rotd3(vec4 rot);


	//Translate
	static mat4 transform(float x, float y, float z);
	static mat4 transform(vec4 pos);

	static mat4 scale(float x, float y, float z);

	//Multiplikation
	void operator=(const mat4& rhs);
	mat4 operator*(float s);
	mat4 operator*(const mat4& rhs);
	vec4 operator*(const vec4 &rhs);

	//Transponat
	mat4 transpose();

	//Invers
	mat4 inv();

	//Print (f�r det mesta debug)
	void print();

	float* get();

private:
	float mat[4][4];
};

