#pragma once

#include <iostream>

class Matrix4x4
{
public:
	Matrix4x4(); 
	Matrix4x4(float data[4][4]);
	Matrix4x4(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);
	~Matrix4x4();
	Matrix4x4 operator+(const Matrix4x4& other);
	Matrix4x4 operator-(const Matrix4x4& other);
	Matrix4x4 operator*(const Matrix4x4& other);
	Matrix4x4& operator=(const Matrix4x4& other);

	float& operator()(int ind1, int ind2);

	Matrix4x4 operator+(const float value);
	Matrix4x4 operator-(const float value);
	Matrix4x4 operator*(const float value);

	void Invert();

	void Identity();

	void PrintMat();

	float m[4][4];
private:
	
};