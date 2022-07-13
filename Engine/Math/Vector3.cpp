#include "Vector3.h"
#include "EMath.h"
#include "Quaternion.h"
#include <iostream>
#include "Matrix4x4.h"

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::~Vector3()
{
}

Vector3& Vector3::operator=(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
	return *this;
}

Vector3 Vector3::operator/(float value)
{
	return Vector3(this->x / value, this->y / value, this->z / value);
}

Vector3 Vector3::operator*(float value)
{
	return Vector3(this->x * value, this->y * value, this->z * value);;
}

Vector3 Vector3::operator+(float value)
{
	return Vector3(this->x + value, this->y + value, this->z + value);;
}

bool Vector3::operator==(const Vector3& other)
{
	return (x == other.x && y == other.y && z == other.z);
}

bool Vector3::operator!=(const Vector3& other)
{
	return (x != other.x && y != other.y && z != other.z);
}

float Vector3::GetLength()
{
	return sqrt(x*x + y*y + z*z);
}

void Vector3::Normalize()
{
	float InversedLength = 1.0 / GetLength();
	this->x *= InversedLength;
	this->y *= InversedLength;
	this->z *= InversedLength;
}

Vector3 CrossProd(Vector3 f, Vector3 s)
{
	return Vector3(f.y * s.z - f.z * s.y, f.z * s.x - f.x * s.z, f.x * s.y - f.y * s.x);
}

float DotProd(Vector3 f, Vector3 s)
{
	return f.x * s.x + f.y * s.y + f.z * s.z;
}

float AngleBetween(Vector3 f, Vector3 s)
{
	return RADtoDEG(acos(DotProd(f, s) / (f.GetLength() * s.GetLength())));
}

Vector3 Mat_mul_Vec(Matrix4x4 m, Vector3 v)
{
	return Vector3(m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3),
		m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3),
		m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3));
}

//http://programmerart.weebly.com/separating-axis-theorem.html
//https://habr.com/ru/post/509568/
