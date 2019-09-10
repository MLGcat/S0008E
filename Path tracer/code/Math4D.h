#pragma once
#include<iostream>
#include <math.h>
#define DEG 0.01745329252

using namespace std;

class vector4D {
public:
	vector4D();
	vector4D(float a, float b, float c, float d);
	vector4D(float a, float b, float c);
	vector4D(const vector4D& src);
	~vector4D();

	bool operator==(const vector4D& rhs);
	bool operator!=(const vector4D& rhs);

	//Addition, subtraktion
	void operator+=(const vector4D& rhs);
	void operator-=(const vector4D& rhs);
	vector4D operator+(const vector4D& rhs);
	vector4D operator-(const vector4D& rhs);

	//Multiplikation
	float operator*(const vector4D& rhs);
	vector4D operator*(float s);
	void operator*=(float s);

	//Kryssprodukt
	vector4D operator%(const vector4D& rhs);

	//Tilldelning
	void operator=(const vector4D& rhs);

	//Normalvektor
	vector4D norm();

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


class matrix4D
{
public:
	//Konstruktorer
	matrix4D();
	matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
	~matrix4D();

	//Get
	float* operator[](int i);

	//Rotation
	static matrix4D rotX(float v);
	static matrix4D rotY(float v);
	static matrix4D rotZ(float v);
	static matrix4D rot(float v, vector4D axis);
	static matrix4D rot3(float x, float y, float z);
	
	//Rotation med grader
	static matrix4D rotdX(float v);
	static matrix4D rotdY(float v);
	static matrix4D rotdZ(float v);
	static matrix4D rotd(float v, vector4D axis);
	static matrix4D rotd3(float x, float y, float z); 
	static matrix4D rotd3(vector4D rot);


	//Translate
	static matrix4D transform(float x, float y, float z);
	static matrix4D transform(vector4D pos);

	static matrix4D scale(float x, float y, float z);

	//Multiplikation
	void operator=(const matrix4D& rhs);
	matrix4D operator*(float s);
	matrix4D operator*(const matrix4D& rhs);
	vector4D operator*(const vector4D &rhs);

	//Transponat
	matrix4D transpose();

	//Invers
	matrix4D inv();

	//Print (f�r det mesta debug)
	void print();

	float* get();

private:
	float mat[4][4];
};

