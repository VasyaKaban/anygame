#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#include "Quaternion.h"

Matrix4x4 Perspective(float fov, float aspect, float near, float far);

Matrix4x4 FromQuatToMat(Quaternion q);

Matrix4x4 QuatLook(Quaternion q, Vector3 Position, Vector3 &Orientation, Vector3 &SideOrientation);