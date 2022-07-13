#pragma once

#include "Vector3.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	Quaternion& operator=(const Quaternion& q);
	Quaternion operator*(const Quaternion& q);
	Quaternion operator*(const Vector3& v);
	
	void conjugate();
	float GetMagnitude();
	void Normalize();

	float x, y, z, w;
private:

};

Quaternion RotateFromAxisAngle(Vector3 axis, float Angle);

Quaternion RotateYawPitchRoll(Vector3 Angles);