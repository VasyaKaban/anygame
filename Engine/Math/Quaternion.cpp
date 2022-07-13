#include "Quaternion.h"
#include "EMath.h"
#include "Matrix4x4.h"

Quaternion::Quaternion()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 1;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::~Quaternion()
{
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	this->x = q.x;
	this->y = q.y;
	this->z = q.z;
	this->w = q.w;
	return *this;
}

Quaternion Quaternion::operator*(const Quaternion& q)
{
	return Quaternion(this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
		this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x,
		this->w * q.z + this->x * q.y + this->y * q.x + this->z * q.w,
		this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z);
}

void Quaternion::conjugate()
{
	this->x = -x;
	this->y = -y;
	this->z = -z;
}

float Quaternion::GetMagnitude()
{
	return sqrt(w*w + x*x + y*y + z*z);
}

void Quaternion::Normalize()
{
	float InvMag = 1.0 / GetMagnitude();
	this->x *= InvMag;
	this->y *= InvMag;
	this->z *= InvMag;
	this->w *= InvMag;
}

Quaternion RotateFromAxisAngle(Vector3 axis, float Angle)
{
	axis.Normalize();
	return Quaternion(axis.x * sin(DEGtoRAD(Angle) / 2.0),
		axis.y * sin(DEGtoRAD(Angle) / 2.0),
		axis.z * sin(DEGtoRAD(Angle) / 2.0),
		cos(DEGtoRAD(Angle) / 2));

}

Quaternion RotateYawPitchRoll(Vector3 Angles)
{
	float yaw = Angles.x;
	float pitch = Angles.y;
	float roll = Angles.z;
	Quaternion Qyaw, Qpitch, Qroll, Qret;
	Qyaw.x = sin(DEGtoRAD(yaw) / 2.0);
	Qyaw.w = cos(DEGtoRAD(yaw) / 2.0);
	
	Qpitch.y = sin(DEGtoRAD(pitch) / 2.0);
	Qpitch.w = cos(DEGtoRAD(pitch) / 2.0);
	
	Qroll.z = sin(DEGtoRAD(roll) / 2.0);
	Qroll.w = cos(DEGtoRAD(roll) / 2.0);

	Qret = Qyaw * Qpitch;
	Qret = Qret * Qroll;
	
	return Qret;
}

Quaternion Quaternion::operator*(const Vector3& v)
{
	return (*this * Quaternion(v.x, v.y, v.z, 0.0f));
}