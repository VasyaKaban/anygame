#version 330 core

layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 inTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(Position, 0.0, 1.0);
	TexCoord = inTexCoord;
}