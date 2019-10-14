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

	vec4 transMultiply(const vec4& rhs) const;
	//Kryssprodukt
	vec4 operator%(const vec4& rhs);

	//Tilldelning
	void operator=(const vec4& rhs);

	//Normalvektor
	const vec4 norm() const;

	//Vektorl�ngd
	const float abs() const;

	//Get
	float& operator[](const int i);
	float operator[](const int i) const;
	float & get();
	float & get3();
	void set(float x, float y, float z);
	void set(float x, float y, float z, float a);

	static vec4 lerp(const vec4 & A, const vec4 & B, float t)
	{
		float u = 1-t;
		return vec4(
			A[0]*u + B[0]*t,
			A[1]*u + B[1]*t,
			A[2]*u + B[2]*t,
			A[3]*u + B[3]*t
		);
	};

	static vec4 qslerp(vec4 A, vec4 B, float t)
	{
		A = A.norm();
		B = B.norm();

		float dot = A*B;

		if(dot < 0)
		{
			dot = -dot;
			A[0] = -A[0];
			A[1] = -A[1];
			A[2] = -A[2];
			A[3] = -A[3];
		}
		
		float theta_0 = acos(dot);        
		float theta = theta_0*t;          
		float sin_theta = sin(theta);     
		float sin_theta_0 = sin(theta_0); 

		float As = cos(theta) - dot * sin_theta / sin_theta_0;
		float Bs = sin_theta / sin_theta_0;

		return (A*As) + (B*Bs);
	};

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
	static mat4 quaternion(const vec4 &quaternion);
	
	//Rotation med grader
	static mat4 rotdX(float v);
	static mat4 rotdY(float v);
	static mat4 rotdZ(float v);
	static mat4 rotd(float v, vec4 axis);
	static mat4 rotd3(float x, float y, float z); 
	static mat4 rotd3(vec4 euler);


	//Translate
	static mat4 transform(float x, float y, float z);
	static mat4 transform(vec4 pos);

	static mat4 scale(float x, float y, float z);
	static mat4 scale(vec4 pos);

	//Multiplikation
	void operator=(const mat4& rhs);
	mat4 operator*(float s);
	mat4 operator*(const mat4& rhs);
	vec4 operator*(const vec4 &rhs);

	//Division
	mat4 operator/(const mat4& rhs);

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

