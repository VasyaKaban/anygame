#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "glew.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"
#include "VAO.h"
#include "BufferObject.h"
#include "Texture.h"
#include "CollisionTest/AABB.h"
#include "CollisionTest/OBB.h"

class Object
{
public:
	Object(std::string path, std::string Tpath);

	~Object();

	void Draw();

	void ReadObject();

	void CreateBuffers();

	void CreateTexture();

	Matrix4x4 Model;

	Matrix4x4 Trans, Rotate;

	void ModelCreate();

	struct Vec2
	{
		float u, v;
	};

	std::vector<Vector3> Vertexes;

	std::vector<Vec2> Textures;

	std::vector<Vector3> Normals;

	VAO vao;

	Vector3 RGBid;

	std::string GetName();

	bool isPicked;

	AABB objAABB;

	OBB objOBB;

private:

	std::string path;

	std::string Tpath;

	BufferObject vbo;

	BufferObject tbo;

	BufferObject nbo;

	static unsigned int PickID;

	Texture ObjectTexture;
};