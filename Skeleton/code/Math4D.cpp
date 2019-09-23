#pragma once

#include"Math4D.h"

vec4::vec4() {
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 0;
	vec[3] = 1;
}
vec4::vec4(float a, float b, float c, float d) {
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
	vec[3] = d;
};
vec4::vec4(float a, float b, float c) {
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
	vec[3] = 1;
};
vec4::vec4(const vec4& src) {
	vec[0] = src.vec[0];
	vec[1] = src.vec[1];
	vec[2] = src.vec[2];
	vec[3] = src.vec[3];
};
vec4::~vec4() {};

///Returnerar true om vektorerna har identiska v�rden
bool vec4::operator==(const vec4& rhs) {
	return (
		vec[0] == rhs.vec[0] &&
		vec[1] == rhs.vec[1] &&
		vec[2] == rhs.vec[2] &&
		vec[3] == rhs.vec[3]);
};

///Returnerar true om vektorerna har olika v�rden
bool vec4::operator!=(const vec4& rhs) {
	return !(
		vec[0] == rhs.vec[0] &&
		vec[1] == rhs.vec[1] &&
		vec[2] == rhs.vec[2] &&
		vec[3] == rhs.vec[3]);
};

///Addition med vektor
void vec4::operator+=(const vec4& rhs) {
	vec[0] += rhs.vec[0];
	vec[1] += rhs.vec[1];
	vec[2] += rhs.vec[2];
	vec[3] += rhs.vec[3];
};

///Subtraktion med vektor
void vec4::operator-=(const vec4& rhs) {
	vec[0] -= rhs.vec[0];
	vec[1] -= rhs.vec[1];
	vec[2] -= rhs.vec[2];
	vec[3] -= rhs.vec[3];
};

///Addition med vektor
vec4 vec4::operator+(const vec4& rhs) const {
	return vec4(
		vec[0] + rhs.vec[0],
		vec[1] + rhs.vec[1],
		vec[2] + rhs.vec[2]);
};

///Subtraktion med vektor
vec4 vec4::operator-(const vec4& rhs) const {
	return vec4(vec[0] - rhs.vec[0],
		vec[1] - rhs.vec[1],
		vec[2] - rhs.vec[2],
		vec[3] - rhs.vec[3]);
};

///Multiplikation med vektor
float vec4::operator*(const vec4& rhs) const{
	return(vec[0] * rhs.vec[0] +
		vec[1] * rhs.vec[1] +
		vec[2] * rhs.vec[2]);
};

vec4 vec4::transMultiply(const vec4& rhs) const
{
	return vec4(
		vec[0]*rhs[0], 
		vec[1]*rhs[1],
		vec[2]*rhs[2]);
};

///Kryssprodukt
vec4 vec4::operator%(const vec4& rhs) {
	vec4 ret(
		vec[1] * rhs.vec[2] - vec[2] * rhs.vec[1],
		vec[2] * rhs.vec[0] - vec[0] * rhs.vec[2],
		vec[0] * rhs.vec[1] - vec[1] * rhs.vec[0],
		1
	);
	return ret;
};

///Multiplikation med skal�r
vec4 vec4::operator*(float s) const{
	return(vec4(
		vec[0] * s,
		vec[1] * s,
		vec[2] * s));
};

///Multiplikation med skal�r
void vec4::operator*=(float s) {
	vec[0] *= s;
	vec[1] *= s;
	vec[2] *= s;
};

///Division med skal�r
vec4 vec4::operator/(float s) {
	return(vec4(
		vec[0] / s,
		vec[1] / s,
		vec[2] / s));
};

///Division med skal�r
void vec4::operator/=(float s) {
	vec[0] /= s;
	vec[1] /= s;
	vec[2] /= s;
};

///Kopierar v�rden fr�n vektor
void vec4::operator=(const vec4& rhs) {
	vec[0] = rhs.vec[0];
	vec[1] = rhs.vec[1];
	vec[2] = rhs.vec[2];
};

///Returnerar vektorns absolutbelopp
const float vec4::abs() const{
	return(sqrt(
		pow(vec[0], 2) +
		pow(vec[1], 2) +
		pow(vec[2], 2)));
};

float& vec4::operator[](const int i) {
	return vec[i];
};

float vec4::operator[](const int i) const {
	return vec[i];
};

///Returnerar vektorn som ett float array
float & vec4::get() {
	return vec[0];
}
float & vec4::get3() {
	return vec[0];
}
void vec4::set(float x, float y, float z) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}
void vec4::set(float x, float y, float z, float a) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}

///Returnerar vektorn i normalform
const vec4 vec4::norm() const{
	float a = 1 / this->abs();
	return vec4(vec[0] * a, vec[1] * a, vec[2] * a, 1);
};

void vec4::print() {
	cout << "|";
	for (int i = 0; i < 4; i++) {
		cout << vec[i] << "|";
	}
	cout << endl;
}

//Creates identity matrix by default
mat4::mat4() {
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
};

mat4::mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) {
	mat[0][0] = a;
	mat[0][1] = b;
	mat[0][2] = c;
	mat[0][3] = d;
	mat[1][0] = e;
	mat[1][1] = f;
	mat[1][2] = g;
	mat[1][3] = h;
	mat[2][0] = i;
	mat[2][1] = j;
	mat[2][2] = k;
	mat[2][3] = l;
	mat[3][0] = m;
	mat[3][1] = n;
	mat[3][2] = o;
	mat[3][3] = p;
};

mat4::~mat4() {};

float* mat4::operator[](int i) {
	return &mat[i][0];
};


mat4 mat4::rotX(float v) {
	float c = cos(v);
	float s = sin(v);
	return mat4(
		1, 0, 0, 0,
		0, c, s, 0,
		0,-s, c, 0,
		0, 0, 0, 1);
};

mat4 mat4::rotY(float v) {
	float c = cos(v);
	float s = sin(v);
	return mat4(
		c, 0,-s, 0,
		0, 1, 0, 0,
		s, 0, c, 0,
		0, 0, 0, 1);
};

mat4 mat4::rotZ(float v) {
	float c = cos(v);
	float s = sin(v);
	return mat4(
		c, s, 0, 0,
	   -s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
};

mat4 mat4::transform(float x, float y, float z) {
	return mat4(
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1);
};
mat4 mat4::transform(vec4 pos) {
	return mat4(
		1, 0, 0, pos[0], 
		0, 1, 0, pos[1], 
		0, 0, 1, pos[2], 
		0, 0, 0, 1);
};
mat4 mat4::rot(float v, vec4 axis) {
	float c = cos(v);
	float s = sin(v);
	float x = axis[0];
	float y = axis[1];
	float z = axis[2];
	return mat4(
		c+x*x*(1-c), x*y*(1-c)-z*s, x*z*(1-c)+y*s, 0,
		y*x*(1-c)+z*s, c+y*y*(1-c), y*z*(1-c)-x*s, 0,
		z*x*(1-c)-y*s, z*y*(1-c)+x*s, c+z*z*(1-c), 0,
		0, 0, 0, 1);
};
mat4 mat4::rot3(float x, float y, float z) {
	return rotX(x)*rotY(y)*rotZ(z);
}
mat4 mat4::quaternion(vec4 quaternion) {
	float qx = quaternion[0];
	float qy = quaternion[1];
	float qz = quaternion[2];
	float qw = quaternion[3];
	float n = 1.0/sqrt(qx*qx+qy*qy+qz*qz+qw*qw);
	qx *= n;
	qy *= n;
	qz *= n;
	qw *= n;
	return mat4(
    1.0f - 2.0f*qy*qy - 2.0f*qz*qz, 2.0f*qx*qy - 2.0f*qz*qw, 2.0f*qx*qz + 2.0f*qy*qw, 0.0f,
    2.0f*qx*qy + 2.0f*qz*qw, 1.0f - 2.0f*qx*qx - 2.0f*qz*qz, 2.0f*qy*qz - 2.0f*qx*qw, 0.0f,
    2.0f*qx*qz - 2.0f*qy*qw, 2.0f*qy*qz + 2.0f*qx*qw, 1.0f - 2.0f*qx*qx - 2.0f*qy*qy, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f);
}

mat4 mat4::rotdX(float v) {
	return rotX(v*DEG);
}
mat4 mat4::rotdY(float v) {
	return rotY(v*DEG);
}
mat4 mat4::rotdZ(float v) {
	return rotZ(v*DEG);
}
mat4 mat4::rotd(float v, vec4 axis) {
	return rot(v*DEG, axis);
}
mat4 mat4::rotd3(float x, float y, float z) {
	return rotX(x*DEG)*rotY(y*DEG)*rotZ(z*DEG);
}
mat4 mat4::rotd3(vec4 rot) {
	return rotX(rot[0]*DEG)*rotY(rot[1] *DEG)*rotZ(rot[2] *DEG);
}


mat4 mat4::scale(float x, float y, float z) {
	return mat4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

mat4 mat4::scale(vec4 scale) {
	return mat4(
		scale[0], 0, 0, 0,
		0, scale[1], 0, 0,
		0, 0, scale[2], 0,
		0, 0, 0, 1);
}

void mat4::operator=(const mat4& rhs) {
	mat[0][0] = rhs.mat[0][0];
	mat[0][1] = rhs.mat[0][1];
	mat[0][2] = rhs.mat[0][2];
	mat[0][3] = rhs.mat[0][3];
	mat[1][0] = rhs.mat[1][0];
	mat[1][1] = rhs.mat[1][1];
	mat[1][2] = rhs.mat[1][2];
	mat[1][3] = rhs.mat[1][3];
	mat[2][0] = rhs.mat[2][0];
	mat[2][1] = rhs.mat[2][1];
	mat[2][2] = rhs.mat[2][2];
	mat[2][3] = rhs.mat[2][3];
	mat[3][0] = rhs.mat[3][0];
	mat[3][1] = rhs.mat[3][1];
	mat[3][2] = rhs.mat[3][2];
	mat[3][3] = rhs.mat[3][3];
};

mat4 mat4::operator*(const mat4& b) {
	mat4 ret;
	ret.mat[0][0] = mat[0][0] * b.mat[0][0] + mat[0][1] * b.mat[1][0] + mat[0][2] * b.mat[2][0] + mat[0][3] * b.mat[3][0];
	ret.mat[0][1] = mat[0][0] * b.mat[0][1] + mat[0][1] * b.mat[1][1] + mat[0][2] * b.mat[2][1] + mat[0][3] * b.mat[3][1];
	ret.mat[0][2] = mat[0][0] * b.mat[0][2] + mat[0][1] * b.mat[1][2] + mat[0][2] * b.mat[2][2] + mat[0][3] * b.mat[3][2];
	ret.mat[0][3] = mat[0][0] * b.mat[0][3] + mat[0][1] * b.mat[1][3] + mat[0][2] * b.mat[2][3] + mat[0][3] * b.mat[3][3];
	ret.mat[1][0] = mat[1][0] * b.mat[0][0] + mat[1][1] * b.mat[1][0] + mat[1][2] * b.mat[2][0] + mat[1][3] * b.mat[3][0];
	ret.mat[1][1] = mat[1][0] * b.mat[0][1] + mat[1][1] * b.mat[1][1] + mat[1][2] * b.mat[2][1] + mat[1][3] * b.mat[3][1];
	ret.mat[1][2] = mat[1][0] * b.mat[0][2] + mat[1][1] * b.mat[1][2] + mat[1][2] * b.mat[2][2] + mat[1][3] * b.mat[3][2];
	ret.mat[1][3] = mat[1][0] * b.mat[0][3] + mat[1][1] * b.mat[1][3] + mat[1][2] * b.mat[2][3] + mat[1][3] * b.mat[3][3];
	ret.mat[2][0] = mat[2][0] * b.mat[0][0] + mat[2][1] * b.mat[1][0] + mat[2][2] * b.mat[2][0] + mat[2][3] * b.mat[3][0];
	ret.mat[2][1] = mat[2][0] * b.mat[0][1] + mat[2][1] * b.mat[1][1] + mat[2][2] * b.mat[2][1] + mat[2][3] * b.mat[3][1];
	ret.mat[2][2] = mat[2][0] * b.mat[0][2] + mat[2][1] * b.mat[1][2] + mat[2][2] * b.mat[2][2] + mat[2][3] * b.mat[3][2];
	ret.mat[2][3] = mat[2][0] * b.mat[0][3] + mat[2][1] * b.mat[1][3] + mat[2][2] * b.mat[2][3] + mat[2][3] * b.mat[3][3];
	ret.mat[3][0] = mat[3][0] * b.mat[0][0] + mat[3][1] * b.mat[1][0] + mat[3][2] * b.mat[2][0] + mat[3][3] * b.mat[3][0];
	ret.mat[3][1] = mat[3][0] * b.mat[0][1] + mat[3][1] * b.mat[1][1] + mat[3][2] * b.mat[2][1] + mat[3][3] * b.mat[3][1];
	ret.mat[3][2] = mat[3][0] * b.mat[0][2] + mat[3][1] * b.mat[1][2] + mat[3][2] * b.mat[2][2] + mat[3][3] * b.mat[3][2];
	ret.mat[3][3] = mat[3][0] * b.mat[0][3] + mat[3][1] * b.mat[1][3] + mat[3][2] * b.mat[2][3] + mat[3][3] * b.mat[3][3];
	return ret;
};

vec4 mat4::operator*(const vec4 &rhs) {
	return vec4(
		mat[0][0] * rhs[0] + mat[0][1] * rhs[1] + mat[0][2] * rhs[2] + mat[0][3] * rhs[3],
		mat[1][0] * rhs[0] + mat[1][1] * rhs[1] + mat[1][2] * rhs[2] + mat[1][3] * rhs[3],
		mat[2][0] * rhs[0] + mat[2][1] * rhs[1] + mat[2][2] * rhs[2] + mat[2][3] * rhs[3],
		mat[3][0] * rhs[0] + mat[3][1] * rhs[1] + mat[3][2] * rhs[2] + mat[3][3] * rhs[3]
	);
};
mat4 mat4::operator*(float s) {
	mat4 ret(
		mat[0][0] * s,
		mat[0][1] * s,
		mat[0][2] * s,
		mat[0][3] * s,
		mat[1][0] * s,
		mat[1][1] * s,
		mat[1][2] * s,
		mat[1][3] * s,
		mat[2][0] * s,
		mat[2][1] * s,
		mat[2][2] * s,
		mat[2][3] * s,
		mat[3][0] * s,
		mat[3][1] * s,
		mat[3][2] * s,
		mat[3][3] * s);
	return ret;
};

mat4 mat4::transpose() {
	mat4 ret(
		mat[0][0],
		mat[1][0], 
		mat[2][0], 
		mat[3][0],
		mat[0][1],
		mat[1][1],
		mat[2][1],
		mat[3][1],
		mat[0][2],
		mat[1][2],
		mat[2][2],
		mat[3][2],
		mat[0][3],
		mat[1][3],
		mat[2][3],
		mat[3][3]);
	return ret;
};

mat4 mat4::inv() {

	mat4 ret(
		mat[1][1] * mat[2][2] * mat[3][3] - //0
		mat[1][1] * mat[2][3] * mat[3][2] -
		mat[2][1] * mat[1][2] * mat[3][3] +
		mat[2][1] * mat[1][3] * mat[3][2] +
		mat[3][1] * mat[1][2] * mat[2][3] -
		mat[3][1] * mat[1][3] * mat[2][2],

		-mat[0][1] * mat[2][2] * mat[3][3] + //1
		mat[0][1] * mat[2][3] * mat[3][2] +
		mat[2][1] * mat[0][2] * mat[3][3] -
		mat[2][1] * mat[0][3] * mat[3][2] -
		mat[3][1] * mat[0][2] * mat[2][3] +
		mat[3][1] * mat[0][3] * mat[2][2],

		mat[0][1] * mat[1][2] * mat[3][3] - //2
		mat[0][1] * mat[1][3] * mat[3][2] -
		mat[1][1] * mat[0][2] * mat[3][3] +
		mat[1][1] * mat[0][3] * mat[3][2] +
		mat[3][1] * mat[0][2] * mat[1][3] -
		mat[3][1] * mat[0][3] * mat[1][2],

		-mat[0][1] * mat[1][2] * mat[2][3] + //3
		mat[0][1] * mat[1][3] * mat[2][2] +
		mat[1][1] * mat[0][2] * mat[2][3] -
		mat[1][1] * mat[0][3] * mat[2][2] -
		mat[2][1] * mat[0][2] * mat[1][3] +
		mat[2][1] * mat[0][3] * mat[1][2],

		-mat[1][0] * mat[2][2] * mat[3][3] + //4
		mat[1][0] * mat[2][3] * mat[3][2] +
		mat[2][0] * mat[1][2] * mat[3][3] -
		mat[2][0] * mat[1][3] * mat[3][2] -
		mat[3][0] * mat[1][2] * mat[2][3] +
		mat[3][0] * mat[1][3] * mat[2][2],

		mat[0][0] * mat[2][2] * mat[3][3] - //5 
		mat[0][0] * mat[2][3] * mat[3][2] -
		mat[2][0] * mat[0][2] * mat[3][3] +
		mat[2][0] * mat[0][3] * mat[3][2] +
		mat[3][0] * mat[0][2] * mat[2][3] -
		mat[3][0] * mat[0][3] * mat[2][2],

		-mat[0][0] * mat[1][2] * mat[3][3] + //6
		mat[0][0] * mat[1][3] * mat[3][2] +
		mat[1][0] * mat[0][2] * mat[3][3] -
		mat[1][0] * mat[0][3] * mat[3][2] -
		mat[3][0] * mat[0][2] * mat[1][3] +
		mat[3][0] * mat[0][3] * mat[1][2],

		mat[0][0] * mat[1][2] * mat[2][3] - //7
		mat[0][0] * mat[1][3] * mat[2][2] -
		mat[1][0] * mat[0][2] * mat[2][3] +
		mat[1][0] * mat[0][3] * mat[2][2] +
		mat[2][0] * mat[0][2] * mat[1][3] -
		mat[2][0] * mat[0][3] * mat[1][2],

		mat[1][0] * mat[2][1] * mat[3][3] - //8
		mat[1][0] * mat[2][3] * mat[3][1] -
		mat[2][0] * mat[1][1] * mat[3][3] +
		mat[2][0] * mat[1][3] * mat[3][1] +
		mat[3][0] * mat[1][1] * mat[2][3] -
		mat[3][0] * mat[1][3] * mat[2][1],

		-mat[0][0] * mat[2][1] * mat[3][3] + //9
		mat[0][0] * mat[2][3] * mat[3][1] +
		mat[2][0] * mat[0][1] * mat[3][3] -
		mat[2][0] * mat[0][3] * mat[3][1] -
		mat[3][0] * mat[0][1] * mat[2][3] +
		mat[3][0] * mat[0][3] * mat[2][1],

		mat[0][0] * mat[1][1] * mat[3][3] - //10
		mat[0][0] * mat[1][3] * mat[3][1] -
		mat[1][0] * mat[0][1] * mat[3][3] +
		mat[1][0] * mat[0][3] * mat[3][1] +
		mat[3][0] * mat[0][1] * mat[1][3] -
		mat[3][0] * mat[0][3] * mat[1][1],

		-mat[0][0] * mat[1][1] * mat[2][3] + //11
		mat[0][0] * mat[1][3] * mat[2][1] +
		mat[1][0] * mat[0][1] * mat[2][3] -
		mat[1][0] * mat[0][3] * mat[2][1] -
		mat[2][0] * mat[0][1] * mat[1][3] +
		mat[2][0] * mat[0][3] * mat[1][1],

		-mat[1][0] * mat[2][1] * mat[3][2] + //12
		mat[1][0] * mat[2][2] * mat[3][1] +
		mat[2][0] * mat[1][1] * mat[3][2] -
		mat[2][0] * mat[1][2] * mat[3][1] -
		mat[3][0] * mat[1][1] * mat[2][2] +
		mat[3][0] * mat[1][2] * mat[2][1],

		mat[0][0] * mat[2][1] * mat[3][2] - //13
		mat[0][0] * mat[2][2] * mat[3][1] -
		mat[2][0] * mat[0][1] * mat[3][2] +
		mat[2][0] * mat[0][2] * mat[3][1] +
		mat[3][0] * mat[0][1] * mat[2][2] -
		mat[3][0] * mat[0][2] * mat[2][1],

		-mat[0][0] * mat[1][1] * mat[3][2] + //14
		mat[0][0] * mat[1][2] * mat[3][1] +
		mat[1][0] * mat[0][1] * mat[3][2] -
		mat[1][0] * mat[0][2] * mat[3][1] -
		mat[3][0] * mat[0][1] * mat[1][2] +
		mat[3][0] * mat[0][2] * mat[1][1],

		mat[0][0] * mat[1][1] * mat[2][2] - //15
		mat[0][0] * mat[1][2] * mat[2][1] -
		mat[1][0] * mat[0][1] * mat[2][2] +
		mat[1][0] * mat[0][2] * mat[2][1] +
		mat[2][0] * mat[0][1] * mat[1][2] -
		mat[2][0] * mat[0][2] * mat[1][1]);

	float det = mat[0][0] * ret[0][0] + mat[0][1] * ret[1][0] + mat[0][2] * ret[2][0] + mat[0][3] * ret[3][0];


	//If no inverse exists, returns identity matrix
	if (det == 0) {
		mat4 a;
		return a;
	}
	det = 1/det;
	return (ret*det);
}

float* mat4::get() {
	return &mat[0][0];
}

void mat4::print() {
	for (int i = 0; i < 4; i++) {
		cout << "|";
		for (int j = 0; j < 4; j++) {
			cout << mat[i][j] << "|";
		}
		cout << endl;
	}
	cout << endl;
}