#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 inTexCoord;
layout (location = 2) in vec3 inNormal;

out vec2 TexCoord;
out vec3 Normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(Position.x, Position.y, Position.z, 1.0);
	TexCoord = inTexCoord;
	Normal = inNormal;
	Normal = normalize((model * vec4(Normal.x, Normal.y, Normal.z, 1.0)).xyz);
};