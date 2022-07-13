#pragma once

#include "Matrix4x4.h"

class Vector3
{
public:
	Vector3(float x, float y, float z);
	Vector3();
	Vector3& operator=(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	Vector3 operator+(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	bool operator==(const Vector3& other);
	bool operator!=(const Vector3& other);

	Vector3 operator/(float value);
	Vector3 operator*(float value);
	Vector3 operator+(float value);

	float GetLength();
	void Normalize();
	~Vector3();

	float x, y, z;
private:
	

};

Vector3 CrossProd(Vector3 f, Vector3 s);

float DotProd(Vector3 f, Vector3 s);

float AngleBetween(Vector3 f, Vector3 s);

Vector3 Mat_mul_Vec(Matrix4x4 m, Vector3 v);
