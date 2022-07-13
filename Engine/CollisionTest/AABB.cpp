#include "AABB.h"

AABB::AABB(){}

AABB::AABB(Vector3 min, Vector3 max)
{
	this->min = min;
	this->max = max;
}

AABB::~AABB(){}

void AABB::Pass(Vector3 min, Vector3 max)
{
	this->min = min;
	this->max = max;
}
void AABB::Recompute(Matrix4x4 Model, std::vector<Vector3> vert)
{
	Model.Invert();
	Vector3 v = Mat_mul_Vec(Model, vert[0]);
	min = max = v;
	for (int i = 0; i < vert.size(); i++)
	{
		v = Mat_mul_Vec(Model, vert[i]);

		if (min.x > v.x) min.x = v.x;
		if (min.y > v.y) min.y = v.y;
		if (min.z > v.z) min.z = v.z;

		if (max.x < v.x) max.x = v.x;
		if (max.y < v.y) max.y = v.y;
		if (max.z < v.z) max.z = v.z;
	}
}