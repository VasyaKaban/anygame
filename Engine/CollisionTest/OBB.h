#pragma once
#include <array>
#include <vector>
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"

class OBB
{
public:
	OBB();
	~OBB();
	void Compute(Vector3 min, Vector3 max);
	void Recompute(Matrix4x4 Model);
	void FindMinMax(Vector3 axis, float &min, float &max);

	std::array<Vector3, 3> Normals;
	std::array<Vector3, 8> Vertexes;

	std::array<Vector3, 3> RecNormals;
	std::array<Vector3, 8> RecVertexes;
private:
	
	

};

void GlobalLength(float min1, float max1, float min2, float max2, float &l1, float &l2, float &l);

bool SATtest(OBB b1, OBB b2);

std::vector<Vector3> GetCross(Vector3 v11, Vector3 v12, Vector3 v13, Vector3 v21, Vector3 v22, Vector3 v23);

