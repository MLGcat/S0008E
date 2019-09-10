#pragma once

#include"Math4D.h"

vector4D::vector4D() {
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 0;
	vec[3] = 1;
}
vector4D::vector4D(float a, float b, float c, float d) {
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
	vec[3] = d;
};
vector4D::vector4D(float a, float b, float c) {
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
	vec[3] = 1;
};
vector4D::vector4D(const vector4D& src) {
	vec[0] = src.vec[0];
	vec[1] = src.vec[1];
	vec[2] = src.vec[2];
	vec[3] = src.vec[3];
};
vector4D::~vector4D() {};

///Returnerar true om vektorerna har identiska värden
bool vector4D::operator==(const vector4D& rhs) {
	return (
		vec[0] == rhs.vec[0] &&
		vec[1] == rhs.vec[1] &&
		vec[2] == rhs.vec[2] &&
		vec[3] == rhs.vec[3]);
};

///Returnerar true om vektorerna har olika värden
bool vector4D::operator!=(const vector4D& rhs) {
	return !(
		vec[0] == rhs.vec[0] &&
		vec[1] == rhs.vec[1] &&
		vec[2] == rhs.vec[2] &&
		vec[3] == rhs.vec[3]);
};

///Addition med vektor
void vector4D::operator+=(const vector4D& rhs) {
	vec[0] += rhs.vec[0];
	vec[1] += rhs.vec[1];
	vec[2] += rhs.vec[2];
	vec[3] += rhs.vec[3];
};

///Subtraktion med vektor
void vector4D::operator-=(const vector4D& rhs) {
	vec[0] -= rhs.vec[0];
	vec[1] -= rhs.vec[1];
	vec[2] -= rhs.vec[2];
	vec[3] -= rhs.vec[3];
};

///Addition med vektor
vector4D vector4D::operator+(const vector4D& rhs) {
	return vector4D(
		vec[0] + rhs.vec[0],
		vec[1] + rhs.vec[1],
		vec[2] + rhs.vec[2],
		vec[3] + rhs.vec[3]);
};

///Subtraktion med vektor
vector4D vector4D::operator-(const vector4D& rhs) {
	return vector4D(vec[0] - rhs.vec[0],
		vec[1] - rhs.vec[1],
		vec[2] - rhs.vec[2],
		vec[3] - rhs.vec[3]);
};

///Multiplikation med vektor
float vector4D::operator*(const vector4D& rhs) {
	return(vec[0] * rhs.vec[0] +
		vec[1] * rhs.vec[1] +
		vec[2] * rhs.vec[2] +
		vec[3] * rhs.vec[3]);
};

///Kryssprodukt
vector4D vector4D::operator%(const vector4D& rhs) {
	vector4D ret(
		vec[1] * rhs.vec[2] - vec[2] * rhs.vec[1],
		vec[2] * rhs.vec[0] - vec[0] * rhs.vec[2],
		vec[0] * rhs.vec[1] - vec[1] * rhs.vec[0],
		1
	);
	return ret;
};

///Multiplikation med skalär
vector4D vector4D::operator*(float s) {
	return(vector4D(
		vec[0] * s,
		vec[1] * s,
		vec[2] * s,
		vec[3] * s));
};

///Multiplikation med skalär
void vector4D::operator*=(float s) {
	vec[0] *= s;
	vec[1] *= s;
	vec[2] *= s;
	vec[3] *= s;
};

///Kopierar värden från vektor
void vector4D::operator=(const vector4D& rhs) {
	vec[0] = rhs.vec[0];
	vec[1] = rhs.vec[1];
	vec[2] = rhs.vec[2];
	vec[3] = rhs.vec[3];
};

///Returnerar vektorns absolutbelopp
float vector4D::abs() {
	return(sqrt(
		pow(vec[0], 2) +
		pow(vec[1], 2) +
		pow(vec[2], 2)));
};

float& vector4D::operator[](const int i) {
	return vec[i];
};

float vector4D::operator[](const int i) const {
	return vec[i];
};

///Returnerar vektorn som ett float array
float & vector4D::get() {
	return vec[0];
}
float & vector4D::get3() {
	return vec[0];
}
void vector4D::set(float x, float y, float z) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}
void vector4D::set(float x, float y, float z, float a) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = a;
}

///Returnerar vektorn i normalform
vector4D vector4D::norm() {
	float a = 1 / this->abs();
	return vector4D(vec[0] * a, vec[1] * a, vec[2] * a);
};

void vector4D::print() {
	cout << "|";
	for (int i = 0; i < 4; i++) {
		cout << vec[i] << "|";
	}
	cout << endl;
}

//Creates identity matrix by default
matrix4D::matrix4D() {
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

matrix4D::matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) {
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

matrix4D::~matrix4D() {};

float* matrix4D::operator[](int i) {
	return &mat[i][0];
};


matrix4D matrix4D::rotX(float v) {
	float c = cos(v);
	float s = sin(v);
	return matrix4D(
		1, 0, 0, 0,
		0, c, s, 0,
		0,-s, c, 0,
		0, 0, 0, 1);
};

matrix4D matrix4D::rotY(float v) {
	float c = cos(v);
	float s = sin(v);
	return matrix4D(
		c, 0,-s, 0,
		0, 1, 0, 0,
		s, 0, c, 0,
		0, 0, 0, 1);
};

matrix4D matrix4D::rotZ(float v) {
	float c = cos(v);
	float s = sin(v);
	return matrix4D(
		c, s, 0, 0,
	   -s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
};

matrix4D matrix4D::transform(float x, float y, float z) {
	return matrix4D(
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1);
};
matrix4D matrix4D::transform(vector4D pos) {
	return matrix4D(
		1, 0, 0, pos[0], 
		0, 1, 0, pos[1], 
		0, 0, 1, pos[2], 
		0, 0, 0, 1);
};
matrix4D matrix4D::rot(float v, vector4D axis) {
	float c = cos(v);
	float s = sin(v);
	float x = axis[0];
	float y = axis[1];
	float z = axis[2];
	return matrix4D(
		c+x*x*(1-c), x*y*(1-c)-z*s, x*z*(1-c)+y*s, 0,
		y*x*(1-c)+z*s, c+y*y*(1-c), y*z*(1-c)-x*s, 0,
		z*x*(1-c)-y*s, z*y*(1-c)+x*s, c+z*z*(1-c), 0,
		0, 0, 0, 1);
};
matrix4D matrix4D::rot3(float x, float y, float z) {
	return rotX(x)*rotY(y)*rotZ(z);
}

matrix4D matrix4D::rotdX(float v) {
	return rotX(v*DEG);
}
matrix4D matrix4D::rotdY(float v) {
	return rotY(v*DEG);
}
matrix4D matrix4D::rotdZ(float v) {
	return rotZ(v*DEG);
}
matrix4D matrix4D::rotd(float v, vector4D axis) {
	return rot(v*DEG, axis);
}
matrix4D matrix4D::rotd3(float x, float y, float z) {
	return rotX(x*DEG)*rotY(y*DEG)*rotZ(z*DEG);
}
matrix4D matrix4D::rotd3(vector4D rot) {
	return rotX(rot[0]*DEG)*rotY(rot[1] *DEG)*rotZ(rot[2] *DEG);
}


matrix4D matrix4D::scale(float x, float y, float z) {
	return matrix4D(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}

void matrix4D::operator=(const matrix4D& rhs) {
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

matrix4D matrix4D::operator*(const matrix4D& b) {
	matrix4D ret;
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

vector4D matrix4D::operator*(const vector4D &rhs) {
	return vector4D(
		mat[0][0] * rhs[0] + mat[0][1] * rhs[1] + mat[0][2] * rhs[2] + mat[0][3] * rhs[3],
		mat[1][0] * rhs[0] + mat[1][1] * rhs[1] + mat[1][2] * rhs[2] + mat[1][3] * rhs[3],
		mat[2][0] * rhs[0] + mat[2][1] * rhs[1] + mat[2][2] * rhs[2] + mat[2][3] * rhs[3],
		mat[3][0] * rhs[0] + mat[3][1] * rhs[1] + mat[3][2] * rhs[2] + mat[3][3] * rhs[3]
	);
};
matrix4D matrix4D::operator*(float s) {
	matrix4D ret(
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

matrix4D matrix4D::transpose() {
	matrix4D ret(
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

matrix4D matrix4D::inv() {

	matrix4D ret(
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
		matrix4D a;
		return a;
	}
	det = 1/det;
	return (ret*det);
}

float* matrix4D::get() {
	return &mat[0][0];
}

void matrix4D::print() {
	for (int i = 0; i < 4; i++) {
		cout << "|";
		for (int j = 0; j < 4; j++) {
			cout << mat[i][j] << "|";
		}
		cout << endl;
	}
	cout << endl;
}