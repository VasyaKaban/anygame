#include "VAO.h"
#include "glew.h"
#include <iostream>

VAO::VAO()
{
	glGenVertexArrays(1, &dataVAO);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &dataVAO);
}

void VAO::Bind()
{
	glBindVertexArray(dataVAO);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}