#pragma once

class VAO
{
public:
	VAO();
	~VAO();
	void Bind();
	void UnBind();

private:
	unsigned int dataVAO;
};