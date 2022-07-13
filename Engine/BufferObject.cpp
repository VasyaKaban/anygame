#include "BufferObject.h"
#include <iostream>

BufferObject::BufferObject()
{
	glGenBuffers(1, &dataBuffer);
}

BufferObject::BufferObject(GLenum target)
{
	this->target = target;
	glGenBuffers(1, &dataBuffer);
}

BufferObject::~BufferObject()
{
	glDeleteBuffers(1, &dataBuffer);
}

void BufferObject::Bind()
{
	glBindBuffer(target, dataBuffer);
}

void BufferObject::UnBind()
{
	glBindBuffer(target, 0);
}

void BufferObject::SetType(GLenum target)
{
	this->target = target;
}