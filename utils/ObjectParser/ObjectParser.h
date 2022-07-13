#pragma once

#include <string>
#include <vector>
#include <fstream>

	void Draw();

	void ObjectParserCenter(std::string path);

	static std::string Type;

	static std::ifstream fs;

	static std::string path;

	void ObjectVertexParser();

	void ObjectVertexTextureParser();

	void ObjectVertexNormalsParser();

	void ObjectSurfacesParser();

	struct VertexAndNormalsCoord
	{
		float x;
		float y;
		float z;
	};

	struct TextureCoord
	{
		float x;
		float y;
	};

	struct CompletedCoord
	{
		float vx, vy, vz, tx, ty, nx, ny, nz;
	};

	static std::vector<VertexAndNormalsCoord> vc;

	static std::vector<TextureCoord> vt;

	static std::vector<VertexAndNormalsCoord> vn;

	static std::vector<int> VertexIndexes;

	static std::vector<int> TextureIndexes;

	static std::vector<int> NormalsIndexes;

	static std::vector<VertexAndNormalsCoord> VertexCompleted;

	static std::vector<TextureCoord> TextureCompleted;

	static std::vector<VertexAndNormalsCoord> NormalsCompleted;

	static std::vector<CompletedCoord> Completed;

	static std::ofstream of;

	void CreateTXT();

	static std::string txtpath;

	static std::string CompletedPath;