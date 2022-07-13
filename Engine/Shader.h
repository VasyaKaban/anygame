#pragma once

#include "glew.h"
#include <string>
#include "Math/Vector3.h"

class Shader
{
public:
	Shader(std::string VertexShaderPath, std::string FragmentShaderPath);

	~Shader();

	void UseShader();

	void SetMat4(std::string name, const float *value);

	void SetFloat(std::string name, float value);

	void SetBool(std::string name, bool value);

	void SetVec3(std::string name, Vector3 data);

	void CreateVertexShader();

	void CreateFragmentShader();

	void CreateShaderProgram();

private:

	std::string VertexShaderPath;

	std::string FragmentShaderPath;

	

	GLuint ShaderProgram;

	GLuint VertexShader;

	GLuint FragmentShader;

	

	


};