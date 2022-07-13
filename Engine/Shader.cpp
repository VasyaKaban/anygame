#include "Shader.h"
#include "glew.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Camera.h"

Shader::Shader(std::string VertexShaderPath, std::string FragmentShaderPath)
{
	this->VertexShaderPath = VertexShaderPath;

	this->FragmentShaderPath = FragmentShaderPath;

	//CreateVertexShader();
	//CreateFragmentShader();
	//CreateShaderProgram();
};

Shader::~Shader()
{
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
	glDeleteProgram(ShaderProgram);
}

void Shader::CreateVertexShader()
{

	std::ifstream Vert(VertexShaderPath);
	char vb;
	std::string VertexSource;
	std::string vbs;
	if (!Vert.is_open())
	{
		std::cout <<"VertexShader has not exist!" << std::endl;
	}
	else
	{
		while (!Vert.eof())
		{
			vbs = "";
			std::getline(Vert,vbs);
			for (int i = 0; i < vbs.size(); i++)
			{
				vb = vbs[i];
				VertexSource.push_back(vb);
			}
			VertexSource.push_back('\n');
			
		}
		Vert.close();

		const char* VS = VertexSource.c_str();
		VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShader, 1, &VS, NULL);
		glCompileShader(VertexShader);

		GLint success;

		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar InfoLog[512];
			//std::string InfoLog;
			std::cout << "VERTEX SHADER COMPILATION FAILED!" << std::endl;
			glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
			for (int i = 0; i < 512; i++)
			{
				std::cout << InfoLog[i];
				if (InfoLog[i] == NULL){break;}
				
			}
		}
	}

}

void Shader::CreateFragmentShader()
{

	std::ifstream Frag(FragmentShaderPath);
	char fb;
	std::string FragmentSource;
	std::string fbs;
	if (!Frag.is_open())
	{
		std::cout << "FragmentShader has not exist!" << std::endl;
	}
	else
	{
		while (!Frag.eof())
		{
			fbs = "";
			std::getline(Frag, fbs);
			for (int i = 0; i < fbs.size(); i++)
			{
				fb = fbs[i];
				FragmentSource.push_back(fb);
			}
			FragmentSource.push_back('\n');
			
		}
		Frag.close();

		const char* FS = FragmentSource.c_str();
		FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShader, 1, &FS, NULL);
		glCompileShader(FragmentShader);

		GLint success;

		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar InfoLog[512];
			std::cout << "FRAGMENT SHADER COMPILATION FAILED!" << std::endl;
			glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
			for (int i = 0; i < 512; i++)
			{
				std::cout << InfoLog[i];
				if (InfoLog[i] == NULL){ break;}
			}
		}
	}
}

void Shader::CreateShaderProgram()
{
	ShaderProgram = glCreateProgram();

	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	GLint success;

	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar InfoLog[512];
		std::cout << "SHADER LINKING FAILED!" << std::endl;
		glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
		for (int i = 0; i < 512; i++)
		{
			std::cout <<InfoLog[i];
			if (InfoLog[i] == NULL){ break; } 
		}
	}
	
}

void Shader::SetMat4(std::string name, const float *value)
{
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, GL_FALSE, value);
}

void Shader::SetFloat(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value);
}

void Shader::SetBool(std::string name, bool value)
{
	glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value);
}

void Shader::SetVec3(std::string name, Vector3 data)
{
	glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), data.x, data.y, data.z);
}

void Shader::UseShader()
{
	glUseProgram(ShaderProgram);
}