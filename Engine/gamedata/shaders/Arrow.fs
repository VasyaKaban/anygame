#version 330 core

out vec4 color;
in vec3 OColor;

void main()
{
	color = vec4(OColor, 1.0 );
};