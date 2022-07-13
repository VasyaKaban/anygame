#include "Matrix_Transformations.h"
#include "EMath.h"

/*Our/C style
m00, m01, m02, m03
m10, m11, m12, m13
m20, m21, m22, m23
m30, m31, m32, m33*/

/*OGL style
m00, m10, m20, m30
m01, m11, m21, m31
m02, m12, m22, m32
m03, m13, m23, m33*/


Matrix4x4 Perspective(float fov, float aspect, float near, float far)
{
	Matrix4x4 PerspMat;

	float top = near * tan(DEGtoRAD(fov / 2.0f));
	float bottom = -top;
	float right = top * aspect;
	float left = -right;

	PerspMat.m[0][0] = 2 * near / (right - left);
	PerspMat.m[1][1] = 2 * near / (top - bottom);

	//PerspMat.m[2][0] = (right + left) / (right - left);
	//PerspMat.m[2][1] = (top + bottom) / (top - bottom);
	PerspMat.m[2][2] = -(far + near) / (far - near);
	PerspMat.m[2][3] = -1;

	PerspMat.m[3][2] = -2 * far * near / (far - near);
	PerspMat.m[3][3] = 0;


	//PerspMat.m[0][0] = 2 * near / (right - left);
	//PerspMat.m[1][1] = 2 * near / (top - bottom);

	////PerspMat.m[2][0] = (right + left) / (right - left);
	////PerspMat.m[2][1] = (top + bottom) / (top - bottom);
	//PerspMat.m[2][2] = -(far + near) / (near - far);
	//PerspMat.m[2][3] = 1;

	//PerspMat.m[3][2] = 2 * far * near / (near - far);


	return PerspMat;
}

Matrix4x4 FromQuatToMat(Quaternion q)
{
	Matrix4x4 QM;
	QM.Identity();

	QM.m[0][0] = 1 - 2 * (q.y * q.y + q.z * q.z);
	QM.m[1][0] = 2 * (q.x * q.y - q.z * q.w);
	QM.m[2][0] = 2 * (q.x * q.z + q.y * q.w);

	QM.m[0][1] = 2 * (q.x * q.y + q.z * q.w);
	QM.m[1][1] = 1 - 2 * (q.x * q.x + q.z * q.z);
	QM.m[2][1] = 2 * (q.y * q.z - q.x * q.w);

	QM.m[0][2] = 2 * (q.x * q.z - q.y * q.w);
	QM.m[1][2] = 2 * (q.y * q.z + q.x * q.w);
	QM.m[2][2] = 1 - 2 * (q.x * q.x + q.y * q.y);

	return QM;
}

Matrix4x4 QuatLook(Quaternion q, Vector3 Position, Vector3 &Orientation, Vector3 &SideOrientation)
{
	Matrix4x4 TranslateView, RotateView, Result;
	TranslateView.m[3][0] = -Position.x;
	TranslateView.m[3][1] = -Position.y;
	TranslateView.m[3][2] = -Position.z;

	RotateView = FromQuatToMat(q);

	Result = TranslateView * RotateView;

	Orientation = Vector3(-Result.m[0][2], -Result.m[1][2], -Result.m[2][2]);
	SideOrientation = Vector3(-Result.m[0][0], -Result.m[1][0], -Result.m[2][0]);

	return Result;
}