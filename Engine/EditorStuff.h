#pragma once
#include "glew.h"
#include "Math/Matrix4x4.h"
#include <vector>

struct MeshCoord
{
	MeshCoord(float x, float y, float z);
	MeshCoord();
	float x, y, z;
};

void CreateCS();

void DrawCS();

static GLuint CSvbo, CSvao;

extern Matrix4x4 CSModel;


static bool CSis_tech = 1;

static std::vector<MeshCoord> CSa;

