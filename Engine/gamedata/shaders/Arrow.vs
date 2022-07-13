#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 2) in vec3 VColor;

out vec3 OColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(Position.x, Position.y, Position.z, 1.0);
	OColor = VColor;
};