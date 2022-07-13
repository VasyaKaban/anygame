#pragma once

#include "glew.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();
	void Read();
	void Draw();
	void Bind();
	void UnBind();
	const char* GetStatus();


private:
	unsigned int dataFBO;

};