#pragma once
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include <vector>

class AABB
{
public:
	AABB();
	AABB(Vector3 min, Vector3 max);
	~AABB();
	void Pass(Vector3 min, Vector3 max);
	void Recompute(Matrix4x4 Model, std::vector<Vector3> vert);
	
	Vector3 min, max;
private:
	
};

