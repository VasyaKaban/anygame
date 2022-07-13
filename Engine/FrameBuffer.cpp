#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &dataFBO);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &dataFBO);
}

void FrameBuffer::Read()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, dataFBO);
}

void FrameBuffer::Draw()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dataFBO);
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, dataFBO);
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const char* FrameBuffer::GetStatus()
{
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		return "framebuffer building completed!";
	}
	else
	{
		return "framebuffer building uncompleted!";
	}
};