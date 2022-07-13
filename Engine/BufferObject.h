#pragma once

#include "glew.h"

class BufferObject
{
public:
	BufferObject();
	BufferObject(GLenum target);
	~BufferObject();
	void Bind();
	void UnBind();
	void SetType(GLenum target);
private:
	GLuint dataBuffer;
	GLenum target;
};