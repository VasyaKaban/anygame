#include "OBB.h"

OBB::OBB(){}

OBB::~OBB(){}

void OBB::Compute(Vector3 min, Vector3 max)
{

	Vertexes[0] = min;
	Vertexes[1] = Vector3(max.x, min.y, min.z);
	Vertexes[2] = Vector3(max.x, max.y, min.z);
	Vertexes[3] = Vector3(min.x, max.y, min.z);
	Vertexes[4] = max;
	Vertexes[5] = Vector3(min.x, max.y, max.z);
	Vertexes[6] = Vector3(min.x, min.y, max.z);
	Vertexes[7] = Vector3(max.x, min.y, max.z);

	Normals[0] = CrossProd(Vertexes[4] - Vertexes[7], Vertexes[4] - Vertexes[2]);//x->
	Normals[0].Normalize();
	Normals[1] = CrossProd(Vertexes[4] - Vertexes[2], Vertexes[4] - Vertexes[5]);//y->
	Normals[1].Normalize();
	Normals[2] = CrossProd(Vertexes[4] - Vertexes[5], Vertexes[4] - Vertexes[7]);//z->
	Normals[2].Normalize();
}

void OBB::Recompute(Matrix4x4 Model)
{
	Model.Invert();
	for (int i = 0; i < 8; i++)
	{
		RecVertexes[i] = Mat_mul_Vec(Model, Vertexes[i]);

	}

	RecNormals[0] = CrossProd(RecVertexes[4] - RecVertexes[7], RecVertexes[4] - RecVertexes[2]);//x->
	RecNormals[0].Normalize();
	RecNormals[1] = CrossProd(RecVertexes[4] - RecVertexes[2], RecVertexes[4] - RecVertexes[5]);//y->
	RecNormals[1].Normalize();
	RecNormals[2] = CrossProd(RecVertexes[4] - RecVertexes[5], RecVertexes[4] - RecVertexes[7]);//z->
	RecNormals[2].Normalize();
}

void OBB::FindMinMax(Vector3 axis, float &min, float &max)
{
	min = max = DotProd(RecVertexes[0], axis);
	float dm;

	for (size_t i = 0; i < 8; i++)
	{
		dm = DotProd(RecVertexes[i], axis);
		if (min > dm) min = dm;
		if (max < dm) max = dm;
	}
}

void GlobalLength(float min1, float max1, float min2, float max2, float &l1, float &l2, float &l)
{
	l1 = max1 - min1;
	l2 = max2 - min2;
	float glmin = min1;
	float glmax = max1;
	if (glmin > min2) glmin = min2;
	if (glmax < max2) glmax = max2;
	l = glmax - glmin;
}

bool SATtest(OBB b1, OBB b2)
{
	std::vector<Vector3> NewAxises;
	NewAxises.clear();
	/*NewAxises = GetCross(
		b1.Vertexes[4] - b1.Vertexes[5], b1.Vertexes[4] - b1.Vertexes[6], b1.Vertexes[4] - b1.Vertexes[7],
		b2.Vertexes[4] - b2.Vertexes[5], b2.Vertexes[4] - b2.Vertexes[6], b2.Vertexes[4] - b2.Vertexes[7]);*/

	NewAxises = GetCross(
		b1.RecNormals[0], b1.RecNormals[1], b1.RecNormals[2],
		b2.RecNormals[0], b2.RecNormals[1], b2.RecNormals[2]);
	float minB1, minB2, maxB1, maxB2, l1, l2, l;
	for (size_t i = 0; i < 3; i++)
	{
		b1.FindMinMax(b1.RecNormals[i], minB1, maxB1);
		b2.FindMinMax(b1.RecNormals[i], minB2, maxB2);
		GlobalLength(minB1, maxB1, minB2, maxB2, l1, l2, l);
		if ((l1 + l2) < l) return false;
	}
	for (size_t i = 0; i < 3; i++)
	{
		b1.FindMinMax(b2.RecNormals[i], minB1, maxB1);
		b2.FindMinMax(b2.RecNormals[i], minB2, maxB2);
		GlobalLength(minB1, maxB1, minB2, maxB2, l1, l2, l);
		if ((l1 + l2) < l) return false;
	}
	for (size_t i = 0; i < NewAxises.size(); i++)
	{
		b1.FindMinMax(NewAxises[i], minB1, maxB1);
		b2.FindMinMax(NewAxises[i], minB2, maxB2);
		GlobalLength(minB1, maxB1, minB2, maxB2, l1, l2, l);
		if ((l1 + l2) < l) return false;
	}
	return true;
}

std::vector<Vector3> GetCross(Vector3 v11, Vector3 v12, Vector3 v13, Vector3 v21, Vector3 v22, Vector3 v23)
{
	std::vector<Vector3> v;
	Vector3 axis;

	axis = CrossProd(v11, v21);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v11, v22);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v11, v23);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v12, v21);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v12, v22);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v12, v23);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v13, v21);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v13, v22);
	axis.Normalize();
	v.push_back(axis);

	axis = CrossProd(v13, v23);
	axis.Normalize();
	v.push_back(axis);
	return v;
}
